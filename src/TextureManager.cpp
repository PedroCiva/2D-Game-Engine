#include  "TextureManager.h"
#include<iostream>


SDL_Texture* TextureManager::LoadTexture(const char* filePath) {
	SDL_Surface* surface = IMG_Load(filePath); //SDL surface contains raw information about the sprites data such as size and pixel format
	if (surface == NULL)
		printf("IMG_Load: %s\n", IMG_GetError());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);// Creates a texture using the renderer and the information from the surface 
	SDL_FreeSurface(surface);//Surface has been used and can now be freed

	return texture;
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect sourceRect, SDL_Rect destinationRect, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, texture, &sourceRect, &destinationRect, 0.0, NULL, flip); //Draws the texture on the screen using our renderer and texture plus some position information from the SDL_Rect's
}

void TextureManager::DrawOutline(SDL_Rect rectangle,glm::vec4 color) {
	SDL_SetRenderDrawColor(Game::renderer, color.x, color.y, color.z, color.w);
	SDL_RenderDrawRect(Game::renderer, &rectangle);
}