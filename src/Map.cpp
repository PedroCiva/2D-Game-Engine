#include <fstream>
#include "Game.h"
#include "Map.h"
#include "EntityManager.h"
#include "Components/TileComponent.h"

extern EntityManager manager; //Extern because the EntityManager was already defined on Game.cpp
Map::Map(std::string textureID, int scale, int tileSize) {
	this->textureID = textureID;
	this->scale = scale;
	this->tileSize = tileSize;
}

//Loads up the raw map file, the one that defines all the tiles we can use.
void Map::LoadMap(std::string filePath, int mapSizeX, int mapSizeY) {
	std::fstream mapFile;
	mapFile.open(filePath); //defining mapFile
	//Iterating through the map Y and X,  Y meaning rows and X meaning columns, watch section 7 video 31 at 23:00 if lost
	for (int y = 0; y < mapSizeY; y++) {
		for (int x = 0; x < mapSizeX; x++) {
			char ch; //Using char to get only the first number
			mapFile.get(ch);
			int sourceRectY = atoi(&ch) * tileSize; //ascii to integer
			mapFile.get(ch);
			int sourceRectX= atoi(&ch) * tileSize;
											//X and Y here are indicator of which tile we are in in our loop
			AddTile(sourceRectX, sourceRectY, x * (scale * tileSize), y * (scale * tileSize));
			mapFile.ignore();
		}
	}
	mapFile.close();
}

void Map::AddTile(int sourceRectX, int sourceRectY, int posX, int posY) {
	Entity& newTile(manager.AddEntity("tile",TILEMAP_LAYER));
	newTile.AddComponent<TileComponent>(sourceRectX, sourceRectY, posX, posY, tileSize,scale, textureID);
}