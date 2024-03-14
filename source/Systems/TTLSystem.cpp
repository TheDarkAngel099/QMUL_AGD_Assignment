#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/components/TTLComponent.h"
#include <iostream>

TTLSystem::TTLSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::TTL));
}

TTLSystem :: ~TTLSystem() {}

void TTLSystem::update(Game* game, Entity* entity, float gELapsedTime)
{
	auto ttlComp = entity->getTTLComponent();
	if (ttlComp == nullptr)
	{
		throw std::exception("TTL null ptr");
	}
	else
	{
		ttlComp->decreaseTTL();
		if (ttlComp->getTTL() <= 0)
		{
			entity->deleteEntity();
			std::cout << "Fire deleted" << std::endl;
		}
	}
}

std::vector<EntityType> TTLSystem::getArchetypes() const 
{
	return { EntityType::FIRE };
}