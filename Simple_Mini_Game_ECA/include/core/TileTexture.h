#pragma once
#include "../graphics/Window.h"

class TileTexture
{
public:
    sf::Texture texture;

    TileTexture() {};

    TileTexture(const std::string& filename)
    {
        if (!texture.loadFromFile(filename))
        {
            throw std::runtime_error("Texture file not found: " + filename);
        }
    }
};