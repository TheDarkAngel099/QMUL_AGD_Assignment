#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"

GameplaySystem::GameplaySystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::PLAYERSTATE));
}

GameplaySystem::~GameplaySystem() {}

void GameplaySystem::update(Game* game, Entity* entity, float gElapsedTime) 
{
	auto state = entity->getPlayerStateComponent();
	if (state == nullptr)
		throw std::exception("No player state component is found!");
	else
		state->update(entity, game, gElapsedTime);
}

std::vector<EntityType> GameplaySystem::getArchetypes() const
{
	return { EntityType::PLAYER , EntityType::FIRE, EntityType::LOG , EntityType::POTION };
}