#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h" 
#include "../../include/core/Observer.h"
#include "../../include/core/AudioManager.h"
#include "../../include/core/Game.h"
#include "../../include/core/Command.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/InputComponent.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/components/HealthComponent.h"
#include "../../include/components/VelocityComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/PlayerStateComponent.h"
#include "../../include/components/TTLComponent.h"
#include "../../include/core/Subject.h"
#include "../../include/entities/Player.h"
#include "../../include/graphics/AnimBase.h"
#include "../../include/entities/Fire.h"
#include "../../include/components/PlayerStateComponent.h"

void PlayerStateLogic::update(Entity* entity, Game* game, float elapsed)
{
	auto player = dynamic_cast<Player*>(entity);

	if (shouting)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Shout", true);
	}
	else if (attacking)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Attack", true);
	}
	else if (player->getVelocityComponent()->getVelocity().x > 0)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setSpriteDirection(Direction::Right);
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Walk", true, true);
	}
	else if (player->getVelocityComponent()->getVelocity().x < 0)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setSpriteDirection(Direction::Left);
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Walk", true, true);
	}
	else if (player->getVelocityComponent()->getVelocity().y != 0)
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Walk", true, true);
	}
	else
	{
		player->getGraphicsComponent()->getSpriteSheet()->setAnimation("Idle", true, true);
	}

	if (shootCooldown > 0)
	{
		shootCooldown -= elapsed;
	}

	if (isShouting() && wood >= shootingCost && player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isPlaying() && shootCooldown <= 0)
	{
		auto fire = createFire(*player);
		game->addEntity(fire);
		wood -= shootingCost;
		shootCooldown = shootCooldownTime;
	}

	if (attacking && !player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isPlaying())
	{
		attacking = false;
	}

	if (shouting && !player->getGraphicsComponent()->getSpriteSheet()->getCurrentAnim()->isPlaying())
	{
		shouting = false;
	}
}

void PlayerStateLogic::addWood(int w)
{
	wood += w;
	if (wood > maxWood) wood = maxWood;
	if (wood < 0) wood = 0;
}

std::shared_ptr<Fire> PlayerStateLogic::createFire(Player& entity) const
{
	auto fireEntity = std::make_shared<Fire>();
	Vector2f pos{entity.getPosition().x + entity.getGraphicsComponent()->getTextureSize().x * 0.5f, entity.getPosition().y + entity.getGraphicsComponent()->getTextureSize().y * 0.5f};
	fireEntity->init("img/fire.png", 1.0f);
	fireEntity->setPosition(pos.x, pos.y);
	Vector2f vel(fireSpeed, 0.0f);
	if (entity.getGraphicsComponent()->getSpriteSheet()->getSpriteDirection() == Direction::Left)
		vel.x = vel.x * -1.0f;
	auto fireVelComp = fireEntity->getVelocityComponent();
	fireVelComp->setVelocity(vel.x, vel.y);
	return fireEntity;
}
