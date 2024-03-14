#include "../../include/systems/Systems.h"
#include "../../include/components/Components.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"

InputSystem :: InputSystem()
{
	componentMask.turnOnBit(static_cast<int> (ComponentID::INPUT));
    componentMask.turnOnBit(static_cast<int> (ComponentID::VELOCITY));
}

InputSystem :: ~InputSystem() {}

void InputSystem::update(Game* game, Entity* entity, float gElapsedTime)
{
    entity->getVelocityComponent()->setVelocity(0.0f, 0.0f);
    auto& commands = entity->getInputComponent()->getInputHandler()->handleInput();
    auto iterator = commands.begin();
    while (iterator != commands.end())
    {
        (*iterator)->execute(*game);
        ++iterator;
    }
}

std::vector<EntityType> InputSystem::getArchetypes() const
{
    return { EntityType::PLAYER };
}