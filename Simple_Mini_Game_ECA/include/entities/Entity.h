#pragma once
#include "../graphics/Window.h"
#include "../utils/Rectangle.h"
#include "../../include/core/Bitmask.h"
#include "../../include/graphics/SpriteSheet.h"

class Game;
class GraphicsComponent;
class ColliderComponent;
class PositionComponent;
class SpriteSheet;
class Component;
class TTLComponent;
class PlayerStateLogic;
class VelocityComponent;
class InputComponent;

using EntityID = unsigned int;
enum class EntityType
{
	UNDEFINED = -1,
	PLAYER = 0,
	POTION = 1,
	LOG = 2,
	FIRE = 3
};

class Entity
{
public:

	Entity();
	Entity(EntityType et);
	~Entity();

	virtual void init(const std::string& textureFile, float scale);
	virtual void initSpriteSheet(const std::string& spriteSheetFile);
	virtual void draw(Window* window);

	void setID(EntityID entId) { id = entId; }
	EntityID getID() const { return id; }
	void setPosition(float x, float y);
	EntityType getEntityType() const { return type; }
	const Vector2f& getPosition() const;
	const SpriteSheet* getSpriteSheet() const { return &spriteSheet; }
	bool isSpriteSheetEntity() const { return isSpriteSheet; }

	virtual bool collidesWith(Entity& other) { return false; };

	bool isDeleted() const { return deleted; }
	auto deleteEntity() { deleted = true; }
	Bitmask getComponentSet() { return componentSet; }
	void addComponent(std::shared_ptr<Component> comp);
	bool hasComponent(Bitmask mask) const;

	virtual std::shared_ptr<GraphicsComponent>& getGraphicsComponent() { return gc; }
	virtual std::shared_ptr<PositionComponent> getPositionComponent() { return position; }
	virtual std::shared_ptr<TTLComponent> getTTLComponent() { return nullptr; }
	virtual std::shared_ptr<ColliderComponent> getColliderComponent() { return nullptr; }
	virtual std::shared_ptr<VelocityComponent> getVelocityComponent() { return nullptr; }
	virtual std::shared_ptr<InputComponent> getInputComponent() { return nullptr; }
	virtual std::shared_ptr<PlayerStateLogic> getPlayerStateComponent() { return nullptr; }

protected:

	EntityType type;
	EntityID id;

	bool isSpriteSheet;
	SpriteSheet spriteSheet;
	sf::Texture texture;
	sf::Sprite sprite;

	bool deleted;

	std::shared_ptr <PositionComponent> position;
	std::shared_ptr <GraphicsComponent> gc;
	Bitmask componentSet;

};