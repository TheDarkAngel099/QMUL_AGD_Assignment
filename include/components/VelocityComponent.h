#pragma once
#include "../utils/Vector2.h"
#include "Components.h"

class Entity;

class VelocityComponent : public Component
{
public:
	VelocityComponent(float s = 1.0f) : speed(s){}
	void setVelocity(float x, float y) { direction.x = x; direction.y = y; }

	const Vector2f& getVelocity() const
	{
		return direction;
	}

	const float& getSpeed() const
	{
		return speed;
	}

	ComponentID getID() const override { return ComponentID::VELOCITY; }

private:
	Vector2f direction;
	float speed;
	
};


