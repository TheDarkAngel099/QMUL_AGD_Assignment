#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"

InputHandler::InputHandler() : pauseCommand(std::make_shared<PauseCommand>()) {};

std::shared_ptr<Command> InputHandler::handleInput() 
{

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) 
    {
        return pauseCommand;
    }
    return nullptr;
}

PlayerInputHandler::PlayerInputHandler()
   :commands{}, moveRightCommand{ std::make_shared<MoveRightCommand>() },
    moveLeftCommand{ std::make_shared<MoveLeftCommand>() },
    moveUpCommand{ std::make_shared<MoveUpCommand>() },
    moveDownCommand{ std::make_shared<MoveDownCommand>() },
    shoutCommand{ std::make_shared<ShoutCommand>() },
    attackCommand{ std::make_shared<AttackCommand>() },
    switchCommand{ std::make_shared<SwitchCommand>() }
{
    inputMode = InputMode::ASDW_KEYS;
}

void PlayerInputHandler::switchInput() 
{
    if (inputMode == InputMode::ASDW_KEYS)
        inputMode = InputMode::CURSOR_KEYS;
    else
        inputMode = InputMode::ASDW_KEYS;
}

std::vector<std::shared_ptr<Command>>& PlayerInputHandler::handleInput()
{
    commands.clear();

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        commands.push_back(switchCommand);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        commands.push_back(attackCommand);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        commands.push_back(shoutCommand);
    }

    if (inputMode == InputMode::ASDW_KEYS)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            commands.push_back(moveRightCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            commands.push_back(moveLeftCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            commands.push_back(moveUpCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            commands.push_back(moveDownCommand);
        }
    }

    else if (inputMode == InputMode::CURSOR_KEYS) 
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            commands.push_back(moveRightCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            commands.push_back(moveLeftCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            commands.push_back(moveUpCommand);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            commands.push_back(moveDownCommand);
        }
    }

    return commands;
}




