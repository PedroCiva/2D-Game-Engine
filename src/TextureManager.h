#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H


//This class loads and draws the sprite textures on the game.

#include "Game.h"
#include "Constants.h"

class TextureManager {
public:
	static SDL_Texture* LoadTexture(const char* fileName);
	static void Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip);
	static void DrawOutline(SDL_Rect rectangle, ColorValues color); 

};
#endif