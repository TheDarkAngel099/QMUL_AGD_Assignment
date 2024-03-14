#pragma once
#include "../utils/Rectangle.h"
#include "../graphics/Window.h"
#include "Components.h"

class Entity;

class ColliderComponent : public Component
{
public:
     ColliderComponent(){}
     ~ColliderComponent(){}

     void init(const Entity& entity, Vector2f size);

     bool intersects(std::shared_ptr <ColliderComponent> otherCollider)
     {
        return boundingBox.intersects(otherCollider->boundingBox);
     }

     Rectangle& getBoundingBox() { return boundingBox; }

     Vector2f& getBboxSize() { return bboxSize; }

     void setBoundingBox(const Vector2f& pos);

     ComponentID getID() const override{ return ComponentID::COLLIDER; }

private:
     Rectangle boundingBox;
     Vector2f bboxSize;
};