#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include <iostream>

Fire::Fire() : Entity(EntityType::FIRE)
{
	ttl = std::make_shared<TTLComponent>(startTimeToLive);
	addComponent(ttl);
	velocity = std::make_shared<VelocityComponent>();
	addComponent(velocity);
	AudioManager& sound = Locator::getAudioManager();
	sound.FireSound();
}

Fire::~Fire()
{}
