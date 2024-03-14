#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "include/graphics/SpriteSheet.h"
#include "include/entities/Entity.h"
#include "include/core/Observer.h"
#include "include/core/AudioManager.h"
#include "include/core/Game.h"

void adaptiveLoop(Game& game, float& lastTime, float updateTarget = 0)
{
    float startTime = game.getElapsed().asSeconds();
    float elapsedTime = startTime - lastTime;
    game.handleInput();
    game.update(elapsedTime);
    game.render(elapsedTime);
    float beforeSleep = game.getElapsed().asSeconds();
    sf::Time timeSpent = sf::seconds(startTime + updateTarget - beforeSleep);
    sf::sleep(timeSpent);
    float afterTime = game.getElapsed().asSeconds();
    elapsedTime = afterTime - startTime;
    int fps = static_cast<int>(1 / elapsedTime);
    game.setFPS(fps);
    lastTime = startTime;
}

int main(int argc, char** argv[])
{
    std::ifstream levelRead{ "levels/lvl0.txt" };

    if (!levelRead)
    {
        throw std::exception("File not found\n");
    }

    std::vector<std::string> lines;

    while (levelRead)
    {
        std::string strInput;
        std::getline(levelRead, strInput);
        lines.emplace_back(strInput);
    }

    Game game;
    game.init(lines);
    float updateTarget = 0.016f;
    float lastTime = game.getElapsed().asSeconds();

    while (!game.getWindow()->isWindowDone())
    {
        adaptiveLoop(game, lastTime, updateTarget);
    }

    return 0;
}