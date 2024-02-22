#include "../../include/components/ColliderComponent.h"
#include "../../include/graphics/SpriteSheet.h"
#include "../../include/entities/Entity.h"

void ColliderComponent::init(const Entity& entity, Vector2f size) 
{
    bboxSize = size;
    boundingBox.setTopLeft(entity.getPosition());
    boundingBox.setBottomRight(bboxSize + entity.getPosition());
}

void ColliderComponent::setBoundingBox(const Vector2f& pos)
{
    boundingBox.setTopLeft(pos);
    boundingBox.setBottomRight(bboxSize + pos);
}