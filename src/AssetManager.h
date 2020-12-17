#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include "TextureManager.h"
#include "EntityManager.h"

//This class holds textures that we can use in our game, has methods to ADD them and GET them.
class AssetManager {
private:
	EntityManager* manager;
	std::map<std::string, SDL_Texture*> textures; //Textures dictionary
public:
	AssetManager(EntityManager* manager);
	~AssetManager();
	void AddTexture(std::string textureId, const char* filePath); //Adds texture to the dictionary
	void ClearData(); //Clears all data from dictionary
	SDL_Texture* GetTexture(std::string textureId); 
};
#endif