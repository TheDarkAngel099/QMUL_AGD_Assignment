#pragma once
#include "TileTexture.h"

enum class TileType 
{
	CORRIDOR,
	WALL
};

class Tile
{
private:
	TileType type;
	sf::Vector2i position;
	sf::Sprite sprite;
	std::shared_ptr<TileTexture> tileTexture;

	void loadDefaultTexture();
	void place(int x, int y, float sc);

public:
	Tile(TileType tt) : position(0, 0), type(tt) {}
	void loadTile(int x, int yy, float sc, const std::string& textureFilename = "");
	inline int x() const { return position.x; }
	inline int y() const { return position.y; }
	inline const sf::Vector2f& getScale() const { return sprite.getScale(); }
	inline TileType getType() const { return type; }
	inline float getSpriteXpos() const { return sprite.getPosition().x; }
	inline float getSpriteYpos() const { return sprite.getPosition().y; }
	void draw(Window* window);

};
