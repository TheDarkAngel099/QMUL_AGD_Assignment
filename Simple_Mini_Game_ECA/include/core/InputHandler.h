enum class InputMode
{
    ASDW_KEYS,
    CURSOR_KEYS
};

class InputHandler 
{
public:
    InputHandler();
    std::shared_ptr<Command> handleInput();

private:
    std::shared_ptr<Command> pauseCommand;
};

class PlayerInputHandler
{
public:
	PlayerInputHandler();
    std::vector<std::shared_ptr<Command>>& handleInput();

    InputMode inputMode;
    void switchInput();

private:
    std::vector<std::shared_ptr<Command>> commands;
    std::shared_ptr<Command> moveRightCommand;
    std::shared_ptr<Command> moveLeftCommand;
    std::shared_ptr<Command> moveUpCommand;
    std::shared_ptr<Command> moveDownCommand;
    std::shared_ptr<Command> attackCommand;
    std::shared_ptr<Command> shoutCommand;
    std::shared_ptr<Command> switchCommand;

};

