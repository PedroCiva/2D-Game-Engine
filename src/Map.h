#ifndef MAP_H
#define MAP_H

#include <string>

class Map {
private:
	std::string textureID; // points to our png tile map
	int scale;
	int tileSize;

public:
	Map(std::string textureID, int scale, int tileSize);
	~Map();
	void LoadMap(std::string filePath, int mapSizeX, int mapSizeY); //Loads up the raw map file, the one that defines all the tiles we can use.
	void AddTile(int sourceRectX, int sourceRectY, int posX, int posY);

};


#endif
