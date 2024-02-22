#pragma once
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"
#include "Components.h"

class Fire;
class GraphicsComponent;
class Player;

class PlayerStateComponent : public Component
{
public:
	virtual void update(Entity* entity, Game* game, float elapsed) = 0;
};

class PlayerStateLogic : public PlayerStateComponent
{
public:
	PlayerStateLogic() : attacking(false), shouting(false), shootCooldown(0), wood(0) {}
	virtual void update(Entity* entity, Game* game, float elapsed) override;
	bool isAttacking() const { return attacking; }
	bool isShouting() const { return shouting; }
	float getShootCooldown() const { return shootCooldown; }
	int getWood() const { return wood; }
	constexpr int getShootingCost() { return shootingCost; }
	constexpr float getFireSpeed() { return fireSpeed; }
	constexpr float getShootCooldownTime() { return shootCooldownTime; }
	void setAttacking(bool at) { attacking = at; }
	void setShouting(bool sh) { shouting = sh; }
	void setCooldown(float cd) { shootCooldown = cd; }
	void addWood(int w);
	std::shared_ptr<Fire> createFire(Player& entity) const;
	ComponentID getID() const override{ return ComponentID::PLAYERSTATE; }

protected:
	const int maxWood = 100;
	const int shootingCost = 20;
	const float fireSpeed = 200.0f;
	const float shootCooldownTime = 3.0f;

	int wood;
	bool attacking;
	bool shouting;
	float shootCooldown;
};