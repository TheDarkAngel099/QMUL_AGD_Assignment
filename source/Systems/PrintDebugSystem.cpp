#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"

PrintDebugSystem::PrintDebugSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::COLLIDER));
}
PrintDebugSystem::~PrintDebugSystem()
{}

void PrintDebugSystem::update(Game* game, Entity* entity, float gElapsedTime)
{
	auto collider = entity->getColliderComponent();
	if (collider == nullptr)
		throw std::exception("No collider component is found!");
	else
	{
		game->getWindow()->draw(collider->getBoundingBox().getDrawableRect());
	}
}

std::vector<EntityType> PrintDebugSystem::getArchetypes() const
{
	return { EntityType::PLAYER , EntityType::FIRE, EntityType::LOG , EntityType::POTION };
}