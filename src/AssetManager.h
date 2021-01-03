#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <../../SDL2/include/SDL_ttf.h>
#include "TextureManager.h"
#include "FontManager.h"
#include "EntityManager.h"

//This class holds textures that we can use in our game, has methods to ADD them and GET them.
class AssetManager {
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures; //Textures dictionary
	std::map<std::string, TTF_Font*> fonts; //Fonts dictionary
public:
	AssetManager(EntityManager* manager);
	~AssetManager();

	void ClearData(); //Clears all data from dictionary

	void AddTexture(std::string textureId, const char* filePath); //Adds texture to the dictionary
	void AddFont(std::string fontID, const char* filePath, int fontSize);

	SDL_Texture* GetTexture(std::string textureId); 
	TTF_Font* GetFont(std::string fontID);
};
#endif