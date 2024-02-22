#pragma once
class Game;
class Entity;

enum class Events 
{
    PotionEvent,
    ShoutEvent
};

enum class Achievements 
{
    SCREAMER,
    COLLECTOR
};

class Observer
{
public:
    virtual ~Observer() {};
	virtual bool onNotify(Events event) = 0;
};

class AchievementManager : public Observer
{
public:
    virtual void init(Game& game);
    virtual bool onNotify(Events event);

private:
    int potionInGame = 0;
    int shoutedInGame = 0;
    void unlockAchievement(Achievements abc);
};