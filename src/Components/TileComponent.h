#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include <../../SDL2/include/SDL.h>
#include "../EntityManager.h"
#include "../AssetManager.h"
#include <../libs/glm/glm.hpp>

class TileComponent : public Component {
public : 
	SDL_Texture* texture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	glm::vec2 position;

	TileComponent(int sourceRectX, int sourceRectY, int posX, int posY, int tileSize, int tileScale, std::string assetTextureID) {
		texture = Game::assetManager->GetTexture(assetTextureID);
		sourceRectangle.x = sourceRectX;
		sourceRectangle.y = sourceRectY;
		//Source rectangle width and height are equal to our tile size (32x32?)
		sourceRectangle.w = tileSize; 
		sourceRectangle.h = tileSize;

		//Where we are gonna draw it on the screen
		destinationRectangle.x = posX;
		destinationRectangle.y = posY;
		//Final width and scale are equal to our original tile size * any scale
		destinationRectangle.w = tileSize * tileScale;
		destinationRectangle.h = tileSize * tileScale;

		position.x = posX;
		position.y = posY;
	};

	~TileComponent() {
		SDL_DestroyTexture(texture);
	};

	void Update(float deltaTime) override {
		//Here is where we take care of the tile positions based on the camera control that will keep moving around
		destinationRectangle.x = position.x - Game::camera.x;
		destinationRectangle.y = position.y - Game::camera.y;
	}
	void Render() override {
		TextureManager::Draw(texture, sourceRectangle, destinationRectangle, SDL_FLIP_NONE);
	}
};

#endif // !TILECOMPONENT_H
