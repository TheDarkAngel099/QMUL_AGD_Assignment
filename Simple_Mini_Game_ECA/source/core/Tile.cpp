#include "../../include/core/Tile.h"

void Tile::loadTile(int x, int y, float sc, const std::string& textureFilename)
{
	if (textureFilename.size() > 0)
	{
		tileTexture = std::make_shared<TileTexture>(textureFilename);
	}
	else
	{
		tileTexture = std::make_shared<TileTexture>();
		loadDefaultTexture();
	}

	place(x, y, sc);
}

void Tile::place(int x, int y, float sc)
{
	position.x = x;
	position.y = y;
	sprite.setScale(sc, sc);
	sf::Vector2u textSize = tileTexture->texture.getSize();
	float pixels_x = static_cast<float>(x * (textSize.x * sc));
	float pixels_y = static_cast<float>(y * (textSize.y * sc));
	sprite.setPosition(pixels_x, pixels_y);
}

void Tile::loadDefaultTexture()
{
	switch (type)
	{
	case TileType::CORRIDOR:
		if (!(tileTexture->texture.loadFromFile("img/floor.png")))
			throw std::exception("floor.png image not found");
		break;

	case TileType::WALL:
		if (!(tileTexture->texture.loadFromFile("img/wall.png")))
			throw std::exception("wall.png image not found");
		break;

	default:
		if (!(tileTexture->texture.loadFromFile("img/mushroom50-50.png")))
			throw std::exception("mushroom50-50.png image not found");
		break;
	}

	sprite.setTexture(tileTexture->texture);
}

void Tile::draw(Window* window)
{
	window->draw(sprite);
}
