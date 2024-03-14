#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/entities/Entity.h" 
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/core/InputHandler.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include <iostream>

void MoveRightCommand::execute(Game& game)
{
	auto v = game.getPlayer()->getVelocityComponent();
	v -> setVelocity(1.0f, v->getVelocity().y);
}

void MoveLeftCommand::execute(Game& game)
{
	auto v = game.getPlayer()->getVelocityComponent();
	v->setVelocity(-1.0f, v->getVelocity().y);
}

void MoveUpCommand::execute(Game& game)
{
	auto v = game.getPlayer()->getVelocityComponent();
	v->setVelocity(v->getVelocity().x, -1.0f);
}

void MoveDownCommand::execute(Game& game)
{
	auto v = game.getPlayer()->getVelocityComponent();
	v->setVelocity(v->getVelocity().x, 1.0f);
}

void AttackCommand::execute(Game& game)
{
	if (!game.getPlayer()->getPlayerStateComponent()->isAttacking())
	{
		game.getPlayer()->getPlayerStateComponent()->setAttacking(true);

		if (game.getPlayer()->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isInAction())
		{
			game.getSound().AxeSound();
		}
	}
}

void ShoutCommand::execute(Game& game)
{
	if (!game.getPlayer()->getPlayerStateComponent()->isShouting())
	{
		game.getPlayer()->getPlayerStateComponent()->setShouting(true);
		game.getPlayer()->getSubjectShout().notify(Events::ShoutEvent);
	}
}

void SwitchCommand::execute(Game& game)
{
	game.getPlayer()->getInputComponent()->getInputHandler()->switchInput();
}