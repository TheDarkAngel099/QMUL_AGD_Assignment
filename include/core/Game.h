#include "../core/Board.h"
#include <functional>
#pragma once

class InputHandler;
class Entity;
class Player;
class System;
class Observer;
class AudioManager;

enum class ECS
{
	BIGARRAY,
	ARCHETYPE
};

class Game
{
public:

	const int spriteWH = 50;
	const float tileScale = 2.0f;
	const float itemScale = 1.0f;

	Game();
	~Game();

	void init(std::vector<std::string> lines);
	void addEntity(std::shared_ptr<Entity> newEntity);
	void buildBoard(size_t width, size_t height);
	void initWindow(size_t width, size_t height);

	void handleInput();
	void update(float elapsed);
	void render(float elapsed);
	Window* getWindow() { return &window; }

	sf::Time getElapsed() const;
	void setFPS(int FPS);
	void togglePause() { paused = !paused; }
	bool isPaused() const { return paused; }

	std::shared_ptr<Player> getPlayer();

	EntityID getIDCounter();
	std::shared_ptr<Entity> getEntity(unsigned int idx);

	template <typename T>
	std::shared_ptr<T> buildEntityAt(const std::string& filename, int col, int row);

	AudioManager& getSound() { return sound; }

	void bigArray(float elaspedTime, std::vector<std::shared_ptr<System>> systems);
	void archetypeBigArray(float elaspedTime, std::vector<std::shared_ptr<System>> systems);

	const std::vector<std::shared_ptr<Entity>>& getPlayerArchetype() const { return playerArchetype; }
	const std::vector<std::shared_ptr<Entity>>& getFireArchetype() const { return fireArchetype; }
	const std::vector<std::shared_ptr<Entity>>& getStaticArchetype() const { return staticArchetype; }

private:

	Window window;
	bool paused;
	sf::Clock gameClock;
	sf::Time elapsed;

	std::unique_ptr<Board> board;
	std::vector<std::shared_ptr<Entity>> entities;
	EntityID entityCounter;

	std::shared_ptr<Player> player;
	std::shared_ptr<InputHandler> inputHandler;
	std::vector <std::shared_ptr<System>> logicSystems;
	std::vector <std::shared_ptr<System>> graphicsSystems;

	AudioManager sound;

	AchievementManager achievementManager;

	std::vector <std::shared_ptr<Entity>> playerArchetype;
	std::vector<std::shared_ptr<Entity>> fireArchetype;
	std::vector<std::shared_ptr<Entity>> staticArchetype;
	ECS ecs;

	//std::unordered_map<EntityType, std::function<void(Entity&, Game&)>> collisionCallbacks;

	std::map<EntityType, std::function<void(std::shared_ptr<Entity>, Game&)>> collisionCallbacks;

};

