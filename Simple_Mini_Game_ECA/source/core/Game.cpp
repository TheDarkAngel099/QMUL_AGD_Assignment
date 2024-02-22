#include <iostream>
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/systems/Systems.h"
#include <functional>
#pragma once

Game::Game() : paused(false), entityCounter{ 0 }, ecs{ ECS::BIGARRAY }
{
	inputHandler = std::make_shared<InputHandler>();

	std::shared_ptr <System> inputSystem = std::make_shared<InputSystem>();
	logicSystems.push_back(inputSystem);

	std::shared_ptr <System> movementSystem = std::make_shared<MovementSystem>();
	logicSystems.push_back(movementSystem);

	std::shared_ptr <System> graphicsSystem = std::make_shared<GraphicsSystem>();
	graphicsSystems.push_back(graphicsSystem);

	std::shared_ptr <System> printDebugSystem = std::make_shared<PrintDebugSystem>();
	graphicsSystems.push_back(printDebugSystem);

	std::shared_ptr <System> gameplaySystem = std::make_shared<GameplaySystem>();
	logicSystems.push_back(gameplaySystem);

	std::shared_ptr <System> colliderSystem = std::make_shared<ColliderSystem>();
	logicSystems.push_back(colliderSystem);

	std::shared_ptr <System> ttlSystem = std::make_shared<TTLSystem>();
	logicSystems.push_back(ttlSystem);
}

Game::~Game()
{
}

template <typename T>
std::shared_ptr<T> Game::buildEntityAt(const std::string& filename, int col, int row)
{
	auto ent = std::make_shared<T>();
	ent->init(filename, itemScale);
	float x = col * spriteWH * tileScale;
	float y = row * spriteWH * tileScale;
	float cntrFactor = (tileScale - itemScale) * spriteWH * 0.5f;
	ent->setPosition(x + cntrFactor, y + cntrFactor);
	return ent;
}

void Game::buildBoard(size_t width, size_t height)
{
	board = std::make_unique<Board>(width, height);
}

void Game::initWindow(size_t width, size_t height)
{
	int wdt = static_cast<int>(width * spriteWH * tileScale);
	int hgt = static_cast<int>(height * spriteWH * tileScale);
	window.setSize(sf::Vector2u(wdt, hgt));
	window.redraw();
}

void Game::init(std::vector<std::string> lines)
{

	size_t h = lines.size() - 1;
	if (h < 0)
		throw std::exception("No data in level file");
	size_t w = -1;

	window.loadFont("font/Amatic-Bold.ttf");
	window.setTitle("Mini-Game");
	
	auto it = lines.cbegin();
	int row = 0;
	while (it != lines.cend())
	{
		int col = 0;
		if(w == -1)
		{
			w = it->size();
			buildBoard(w, h);
			initWindow(w, h);		
		}
		
		std::string::const_iterator is = it->cbegin();
		while (is != it->cend())
		{
			switch (*is)
			{
			case '.':
			{
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'w':
			{
				board->addTile(col, row, tileScale, TileType::WALL);
				break;
			}
			case 'x':
			{
				auto log = buildEntityAt<Log>("img/log.png", col, row);
				addEntity(log);	
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case 'p':
			{
				auto potion = buildEntityAt<Potion>("img/potion.png", col, row);
				addEntity(potion);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			case '*':
			{
				player = std::make_shared<Player>();
				player->initSpriteSheet("img/DwarfSpriteSheet_data.txt");
				player->positionSprite(row, col, spriteWH, tileScale);
				addEntity(player);
				board->addTile(col, row, tileScale, TileType::CORRIDOR);
				break;
			}
			}
		col++; is++;
		}
	row++; it++;
	}

	achievementManager.init(*this);
	sound = Locator::getAudioManager();
	collisionCallbacks[EntityType::LOG] = std::bind(&Player::handleLogCollision, player.get(), std::placeholders::_1, std::placeholders::_2);
	collisionCallbacks[EntityType::POTION] = std::bind(&Player::handlePotionCollision, player.get(), std::placeholders::_1, std::placeholders::_2);
}

void Game::addEntity(std::shared_ptr<Entity> newEntity)
{
	++entityCounter;
	newEntity->setID(getIDCounter());
	entities.push_back(newEntity);

	switch (newEntity->getEntityType())
	{
	case EntityType ::PLAYER:
		playerArchetype.push_back(std::dynamic_pointer_cast <Entity>(newEntity));
		break;

	case EntityType :: FIRE:
		fireArchetype.push_back(std::dynamic_pointer_cast<Entity>(newEntity));
		break;

	case EntityType::LOG:
		staticArchetype.push_back(std::dynamic_pointer_cast<Entity>(newEntity));
		break;

	case EntityType::POTION:
		staticArchetype.push_back(std::dynamic_pointer_cast<Entity>(newEntity));
		break;
	}
}

void Game::handleInput()
{
	auto command = inputHandler->handleInput();
	if (command)
	{
		command->execute(*this);
	}
}

void Game::update(float elapsed)
{
	if (!paused) 
	{
		switch(ecs)
		{
		case ECS::BIGARRAY:
			bigArray(elapsed, logicSystems);
			break;
		case ECS::ARCHETYPE:
			archetypeBigArray(elapsed, logicSystems);
			break;
		}
		
		auto iterator = entities.begin();
		while (iterator != entities.end()) 
		{
			if(player->collidesWith(*iterator->get()))
			{
				switch ((*iterator)->getEntityType())
				{
					case EntityType::FIRE:
					{
						std::cout << "Collide with fire" << std::endl;
						break;
					}

					case EntityType::POTION:
					{
						collisionCallbacks[EntityType::POTION](*iterator, *this);
						break;	
					}

					case EntityType::LOG:
					{
						collisionCallbacks[EntityType::LOG](*iterator, *this);
						break;
					}
				}
			}
			++iterator;
		}
	
		iterator = entities.begin();
		while (iterator != entities.end())
		{
			if ((*iterator)->isDeleted())
				iterator = entities.erase(iterator);
			else
				++iterator; 
		}
	}

	window.update();
}

void Game::render(float elapsed)
{
	window.beginDraw();
	board->draw(&window);
	switch (ecs)
	{
	case ECS::BIGARRAY:
		bigArray(elapsed, graphicsSystems);
		break;
	case ECS::ARCHETYPE:
		archetypeBigArray(elapsed, graphicsSystems);
		break;
	}
	
	for (const auto& entity : entities) {
		entity->draw(&window);
	}

	window.drawGUI(*this);
	window.endDraw();
}

sf::Time Game::getElapsed() const { return gameClock.getElapsedTime(); }

void Game::setFPS(int FPS)
{
	std::string text("FPS: " + std::to_string(FPS));
	window.getFPSText().setString(text);
}

std::shared_ptr<Player> Game::getPlayer()
{
	return player;
}

EntityID Game::getIDCounter()
{
	return entityCounter;
}

std::shared_ptr<Entity> Game::getEntity(unsigned int idx)
{
	if (idx >= entities.size())
	{
		throw std::exception("idx not valid/out of bounds");
		return nullptr;
	}
	return entities.at(idx);
}

void Game::bigArray(float elapsedTime, std::vector<std::shared_ptr<System>> systems)
{
	auto systemIt = systems.begin();
	while (systemIt != systems.end())
	{
		auto entityIt = entities.begin();
		while (entityIt != entities.end())
		{
			if (!(entityIt->get()->isDeleted()) && (systemIt->get()->validate(entityIt->get())))
			{
				systemIt->get()->update(this, entityIt->get(), elapsedTime);
			}
			entityIt++;
		}
		systemIt++;
	}
}

void Game::archetypeBigArray(float elapsedTime, std::vector<std::shared_ptr<System>> systems)
{
	for (const auto& system : systems) 
	{
		const std::vector<EntityType>& archetypes = system->getArchetypes();
		for (const auto& entity : entities) 
		{
			if (!entity->isDeleted() && std::find(archetypes.begin(), archetypes.end(), entity->getEntityType()) != archetypes.end() && system->validate(entity.get())) 
			{
				system->update(this, entity.get(), elapsedTime);
			}
		}
	}
}