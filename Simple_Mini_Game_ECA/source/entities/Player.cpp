#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h" 
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include"../../include/entities/StaticEntities.h"
#include "../../include/core/AudioManager.h"
#pragma once

Player::Player() : Entity(EntityType::PLAYER)
{
	inputComponent = std::make_shared<PlayerInputComponent>();
	addComponent(inputComponent);
	healthComponent = std::make_shared<HealthComponent>(startingHealth, maxHealth);
	addComponent(healthComponent);
	velocityComponent = std::make_shared<VelocityComponent>(playerSpeed);
	addComponent(velocityComponent);
	colliderComponent = std::make_shared<ColliderComponent>();
	addComponent(colliderComponent);
	stateComponent = std::make_shared<PlayerStateLogic>();
	addComponent(stateComponent);
}

Player::~Player() {}

void Player::initSpriteSheet(const std::string& spriteSheetFile)
{
	Entity::initSpriteSheet(spriteSheetFile);
	auto size{ Vector2f(gc->getSpriteSheet()->getSpriteSize().x * gc->getSpriteSheet()->getSpriteScale().x,
		gc->getSpriteSheet()->getSpriteSize().y * gc->getSpriteSheet()->getSpriteScale().y) };
	colliderComponent->init(*this, size);
}

void Player::draw(Window* window) 
{
	Entity::draw(window);
}

std::shared_ptr<Fire> Player::createFire(Player& entity) const
{
	auto fire = stateComponent->createFire(entity);
	return fire;
}

void Player::positionSprite(int row, int col, int spriteWH, float tileScale)
{
	gc->positionSprite(row, col, spriteWH, tileScale, this);
}

bool Player::collidesWith(Entity& other) 
{
	std::shared_ptr <ColliderComponent> collider = getColliderComponent();
	if (collider != nullptr)
	{
		std::shared_ptr <ColliderComponent> otherCollider = other.getColliderComponent();
		if (otherCollider != nullptr)
			return collider->intersects(otherCollider);
	}
	return false;
}

void Player:: handlePotionCollision(std::shared_ptr<Entity> other, Game &game)
{
	auto potion = dynamic_cast<Potion*>(other.get());
	if (potion)
	{
		int healthRestore = potion->getHealth();
		potion->deleteEntity();
		game.getSound().PotionSound();
		game.getPlayer()->getHealthComponent()->changeHealth(healthRestore);
		std::cout << "Collide with potion! Restored health: " << healthRestore << " Total Health: " << game.getPlayer()->getHealthComponent()->getHealth() << std::endl;
		game.getPlayer()->getSubjectPotion().notify(Events::PotionEvent);
	}
}

void Player::handleLogCollision(std::shared_ptr<Entity> other, Game& game)
{
	if (game.getPlayer()->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction() && game.getPlayer()->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->getName() == "Attack")
	{
		Log* log = dynamic_cast<Log*>(other.get());
		if (log)
		{
			getPlayerStateComponent()->addWood(log->getWood());
			std::cout << "Wood collected: " << log->getWood() << " Total Wood: " << getPlayerStateComponent()->getWood() << std::endl;
			log->deleteEntity();
		}

	}
	std::cout << "Collide with wood!" << std::endl;
}