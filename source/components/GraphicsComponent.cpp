#include "../../include/components/GraphicsComponent.h"
#include "../../include/entities/Entity.h"
#include "../../include/components/ColliderComponent.h"

void SpriteSheetGraphics::init(const std::string& textureFile, float scale)
{
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
}

void SpriteSheetGraphics::positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity)
{
    sf::Vector2f scaleV2f = getSpriteScale();
    sf::Vector2i textureSize = getTextureSize();

    float x = col * spriteWH * tileScale;
    float y = (row)*spriteWH * tileScale;
    float spriteSizeY = scaleV2f.y * textureSize.y;
    float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);
    float cntrFactorX = cntrFactorY * 0.5f;						

    entity->setPosition(x + cntrFactorX, y + cntrFactorY);
}

void SpriteSheetGraphics::initSpriteSheet(const std::string& spriteSheetFile)
{
    spriteSheet.loadSheet(spriteSheetFile);
    isSpriteSheet = true;
    spriteSheet.setAnimation("Idle", true, true);
}

void SpriteSheetGraphics::draw(Window* window)
{
     sf::Sprite* sp = &spriteSheet.getSprite();
     const sf::Vector2f pos = sp->getPosition();
     window->draw(spriteSheet.getSprite());
}

const sf::Vector2f& SpriteSheetGraphics::getSpriteScale() const
{
    return spriteSheet.getSpriteScale();
}

sf::Vector2i SpriteSheetGraphics::getTextureSize() const
{
    return spriteSheet.getSpriteSize();
}

void SpriteSheetGraphics::update(float elapsed, Entity& entity)
{
    spriteSheet.getSprite().setPosition(entity.getPosition().x, entity.getPosition().y);
    spriteSheet.update(elapsed);
}

void SpriteSheetGraphics::setPosition(float x, float y)
{
    spriteSheet.getSprite().setPosition(x, y);
}

void SpriteGraphics::positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity)
{
    sf::Vector2f scaleV2f = getSpriteScale();
    sf::Vector2i textureSize = getTextureSize();

    float x = col * spriteWH * tileScale;
    float y = (row)*spriteWH * tileScale;
    float spriteSizeY = scaleV2f.y * textureSize.y;
    float cntrFactorY = ((spriteWH * tileScale) - spriteSizeY);	
    float cntrFactorX = cntrFactorY * 0.5f;						

    entity->setPosition(x + cntrFactorX, y + cntrFactorY);
}

void SpriteGraphics::draw(Window* window)
{
    window->draw(sprite);
}

const sf::Vector2f& SpriteGraphics::getSpriteScale() const
{
    return sprite.getScale();
}

sf::Vector2i SpriteGraphics::getTextureSize() const
{
    return { static_cast<int>(texture.getSize().x), static_cast<int>(texture.getSize().y) };
}

void SpriteGraphics::initSpriteSheet(const std::string& spriteSheetFile)
{
    throw std::exception("Trying to call initSpriteSheet of sub class SpriteGraphics, which doesn't do anything");
}

void SpriteGraphics::init(const std::string& textureFile, float scale)
{
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);
    sprite.setScale(scale, scale);
}

void SpriteGraphics::update(float elapsed, Entity& entity) 
{
    sprite.setPosition(entity.getPosition().x, entity.getPosition().y);
}

void SpriteGraphics::setPosition(float x, float y) 
{
    sprite.setPosition(x, y);
}