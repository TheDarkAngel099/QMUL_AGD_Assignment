#include "SFML/Graphics.hpp"
#include "../utils/Vector2.h"
#include "Components.h"
#pragma once

class PositionComponent : public Component
{
public:
	const Vector2f& getPosition()
	{ 
	    return position;
	}
	void setPosition(float x, float y) 
	{ 
		position.x = x; 
		position.y = y; 
	}
	ComponentID getID() const override { return ComponentID::POSITION; }

private:
	Vector2f position; 
};
