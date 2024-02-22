#include"../entities/Entity.h"
class Game;

class System
{
public:
	virtual void update(Game* game, Entity* entity, float gElapsedTime) = 0;
	bool validate(Entity* entity) { return(entity->hasComponent(componentMask)); }
	virtual std::vector<EntityType> getArchetypes() const = 0; 

protected:
	Bitmask componentMask;
};

class TTLSystem : public System
{
public:
	TTLSystem();
	~TTLSystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};

class InputSystem : public System 
{
public:
	InputSystem();
	~InputSystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};

class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};

class GraphicsSystem : public System
{
public:
	GraphicsSystem();
	~GraphicsSystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};

class ColliderSystem : public System
{
public:
	ColliderSystem();
	~ColliderSystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};

class GameplaySystem : public System
{
public:
	GameplaySystem();
	~GameplaySystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};

class PrintDebugSystem : public System
{
public:
	PrintDebugSystem();
	~PrintDebugSystem();
	virtual void update(Game* game, Entity* entity, float gElapsedTime) override;
	virtual std::vector<EntityType> getArchetypes() const override;
};