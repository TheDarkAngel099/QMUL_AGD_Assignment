#include "Components.h"
#include <memory>

class Game;
class PlayerInputHandler;

class InputComponent : public Component
{
public:
    virtual ~InputComponent() {}
    ComponentID getID() const override{ return ComponentID::INPUT; }

    virtual std::shared_ptr<PlayerInputHandler> getInputHandler() = 0;
};

class PlayerInputComponent : public InputComponent 
{
public:
    PlayerInputComponent();
    std::shared_ptr<PlayerInputHandler> getInputHandler() override { return inputHandler; }

private:
   std::shared_ptr<PlayerInputHandler> inputHandler;
};