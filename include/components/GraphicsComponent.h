#pragma once
#include <SFML/Graphics.hpp>
#include "../../include/graphics/SpriteSheet.h"
#include "../graphics/Window.h"
#include "../utils/Rectangle.h"
#include "../../include/graphics/AnimDirectional.h"
#include "Components.h"

class Entity;

class GraphicsComponent : public Component
{
public:
    virtual ~GraphicsComponent() {}
    virtual void init(const std::string& textureFile, float scale) = 0;
    virtual void positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity) = 0;
    virtual void initSpriteSheet(const std::string& spriteSheetFile) = 0;
    virtual void draw(Window* window) = 0;
    virtual const sf::Vector2f& getSpriteScale() const = 0;
    virtual sf::Vector2i getTextureSize() const = 0;
    virtual bool isSpriteSheetEntity() const = 0;
    virtual void update(float elapsed, Entity& entity) = 0;
    virtual void setPosition(float x, float y) = 0;
    SpriteSheet* getSpriteSheet() { return &spriteSheet; }
    sf::Sprite* getSprite() { return &sprite; }
    ComponentID getID() const override { return ComponentID::GRAPHICS; }

protected:
    bool isSpriteSheet;
    SpriteSheet spriteSheet;
    sf::Texture texture;
    sf::Sprite sprite;
};

class SpriteSheetGraphics : public GraphicsComponent 
{
public:
    SpriteSheetGraphics(const std::string& spriteSheet) {}
    void init(const std::string& textureFile, float scale) override;
    void positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity) override;
    void initSpriteSheet(const std::string& spriteSheetFile) override;
    void draw(Window* window) override;
    const sf::Vector2f& getSpriteScale() const override;
    sf::Vector2i getTextureSize() const override;
    const SpriteSheet* getSpriteSheet() const { return &spriteSheet; }
    bool isSpriteSheetEntity() const override { return isSpriteSheet; }
    void update(float elapsed, Entity& entity) override;
    void setPosition(float x, float y) override;  

};

class SpriteGraphics : public GraphicsComponent 
{
public:
    SpriteGraphics(const std::string& simpleSprite) {}
    void init(const std::string& textureFile, float scale) override;
    void positionSprite(int row, int col, int spriteWH, float tileScale, Entity* entity) override;
    void initSpriteSheet(const std::string& spriteSheetFile) override;
    void draw(Window* window) override;
    const sf::Vector2f& getSpriteScale() const override;
    sf::Vector2i getTextureSize() const override;
    bool isSpriteSheetEntity() const override { return isSpriteSheet; }
    const sf::Sprite* getSprite() const { return &sprite; }
    void update(float elapsed, Entity& entity) override;
    void setPosition(float x, float y) override;

};
