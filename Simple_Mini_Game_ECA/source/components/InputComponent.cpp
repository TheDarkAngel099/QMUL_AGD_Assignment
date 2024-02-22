#include "../../include/components/InputComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"

PlayerInputComponent::PlayerInputComponent() : inputHandler(std::make_shared<PlayerInputHandler>()) {}