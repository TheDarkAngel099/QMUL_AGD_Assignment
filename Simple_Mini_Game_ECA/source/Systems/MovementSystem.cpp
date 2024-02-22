#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"

MovementSystem::MovementSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int> (ComponentID::VELOCITY));
}

MovementSystem :: ~MovementSystem() {}

void MovementSystem::update(Game* game, Entity* entity, float gElapsedTime) 
{
	auto velocity = entity->getVelocityComponent();
	entity->getPositionComponent()->setPosition((entity->getPositionComponent()->getPosition().x + (velocity->getVelocity().x * velocity->getSpeed() * gElapsedTime)), (entity->getPositionComponent()->getPosition().y + (velocity->getVelocity().y * velocity->getSpeed() * gElapsedTime)));
}

std::vector<EntityType> MovementSystem::getArchetypes() const 
{
	return { EntityType::PLAYER , EntityType::FIRE };
}