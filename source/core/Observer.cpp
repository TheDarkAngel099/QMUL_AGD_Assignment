#include <iostream>
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/core/Subject.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/entities/Fire.h"
#include "../../include/entities/StaticEntities.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/entities/Player.h"
#include "../../include/systems/Systems.h"
#pragma once

void AchievementManager::init(Game& game)
{
	game.getPlayer()->getSubjectPotion().addObserver(this);
	game.getPlayer()->getSubjectShout().addObserver(this);
};

bool AchievementManager::onNotify(Events event) 
{
	switch(event) 
	{
		case(Events::PotionEvent): 
		{
			++potionInGame;
			if (potionInGame == 6)
				unlockAchievement(Achievements::COLLECTOR);
			return true;
			break;
		}

		case(Events::ShoutEvent): 
		{
			++shoutedInGame;
			if (shoutedInGame == 5)
				unlockAchievement(Achievements::SCREAMER);
			return true;
			break;
		}
	}
	return false;
}

void AchievementManager::unlockAchievement(Achievements abc)
{
	switch(abc)
	{
		case (Achievements::COLLECTOR):
		{
			std::cout << "Achievement Unlocked: Collector" << std::endl;
			break;
		}

		case (Achievements::SCREAMER):
		{
			std::cout << "Achievement Unlocked: Screamer" << std::endl;
			break;
		}
	}
}