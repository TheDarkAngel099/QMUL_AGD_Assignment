#include "Components.h"

class HealthComponent : public Component
{
protected:
    int currentHealth;
    int maximumPossibleHealth;

public:
    HealthComponent(int startingHealth, int maximumHealth) : currentHealth{ startingHealth }, maximumPossibleHealth{ maximumHealth } {}

    int getHealth() const
    {
        return currentHealth;
    }

    void changeHealth(int healthRestored)
    {
        currentHealth += healthRestored;
        if (currentHealth > maximumPossibleHealth) 
        {
            currentHealth = maximumPossibleHealth;
        }
        else if (currentHealth < 0) 
        {
            currentHealth = 0;
        }
    }

    ComponentID getID() const override{ return ComponentID::HEALTH; }
};