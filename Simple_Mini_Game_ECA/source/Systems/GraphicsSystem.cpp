#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"

GraphicsSystem::GraphicsSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::POSITION));
	componentMask.turnOnBit(static_cast<int> (ComponentID::GRAPHICS));
}

GraphicsSystem :: ~GraphicsSystem() {}

void GraphicsSystem::update(Game* game, Entity* entity, float gElapsedTime)
{
	if (!(entity->getGraphicsComponent() == nullptr))
	{
		entity->getGraphicsComponent()->update(gElapsedTime, *entity);
	}
}

std::vector<EntityType> GraphicsSystem::getArchetypes() const
{
	return { EntityType::PLAYER , EntityType::FIRE, EntityType::LOG , EntityType::POTION };
}