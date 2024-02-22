#pragma once
#include "../../include/graphics/Window.h"
#include "../../include/utils/Rectangle.h"
#include "../../include/components/PositionComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/components/GraphicsComponent.h"
#include "../../include/components/ColliderComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/Components.h"

Entity::Entity() :
	isSpriteSheet(false),
	id(0),
	type(EntityType::UNDEFINED), deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
}

Entity::Entity(EntityType et) : 
	isSpriteSheet(false),
	id(0),
	type (et), deleted(false)
{
	position = std::make_shared<PositionComponent>();
	addComponent(position);
}

Entity::~Entity()
{
}

void Entity::init(const std::string& textureFile, float scale)
{
	gc = std::make_shared<SpriteGraphics>(textureFile);
	addComponent(gc);
	gc->init(textureFile, scale);
}

void Entity::draw(Window* window)
{
	gc->draw(window);
}

void Entity::initSpriteSheet(const std::string& spriteSheetFile)
{
	gc = std::make_shared<SpriteSheetGraphics>(spriteSheetFile);
	addComponent(gc);
	gc->initSpriteSheet(spriteSheetFile);
}

void Entity::setPosition(float x, float y)
{
	position->setPosition(x, y);
	gc->setPosition(x, y);
}	

const Vector2f&  Entity :: getPosition() const
{
	return position->getPosition();
}

void Entity::addComponent(std::shared_ptr<Component> comp)
{
	ComponentID id = comp->getID();
	componentSet.turnOnBit(static_cast <unsigned int> (id));
}

bool Entity::hasComponent(Bitmask mask) const 
{
	return (componentSet.contains(mask));
}


