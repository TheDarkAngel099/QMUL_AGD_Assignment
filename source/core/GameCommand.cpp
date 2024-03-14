#pragma once
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"

void PauseCommand::execute(Game& game) 
{
    game.togglePause();
}