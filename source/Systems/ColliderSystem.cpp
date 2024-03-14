#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"

ColliderSystem::ColliderSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int> (ComponentID::COLLIDER));
}

ColliderSystem :: ~ColliderSystem() {}

void ColliderSystem::update(Game* game, Entity* entity, float gElapsedTime)
{
	auto collider = entity->getColliderComponent();
	if (collider == nullptr)
		throw std::exception("No collider component is found!");
	else
	{
		collider->setBoundingBox(entity->getPositionComponent()->getPosition());
	}
}

std::vector<EntityType> ColliderSystem::getArchetypes() const 
{
	return { EntityType::PLAYER , EntityType::FIRE, EntityType::LOG , EntityType::POTION };
}