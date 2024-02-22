#pragma once
enum class ComponentID
{
	UNDEFINED = -1,
	INPUT = 0,
	POSITION = 1,
	VELOCITY = 2,
	HEALTH = 3,
	GRAPHICS = 4,
	COLLIDER = 5,
	PLAYERSTATE = 6,
	TTL = 7
};

class Component
{
public:
	virtual ComponentID getID() const = 0;

};
