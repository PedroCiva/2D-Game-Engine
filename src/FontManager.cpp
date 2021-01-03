#include "FontManager.h"

/// <summary>
/// Loads font using the file name and the font size
/// </summary>
/// <param name="fileName"></param>
/// <param name="fontSize"></param>
/// <returns></returns>
TTF_Font* FontManager::LoadFont(const char* fileName, int fontSize) {
	return TTF_OpenFont(fileName, fontSize);
}

/// <summary>
/// Draws the font on the screen
/// </summary>
/// <param name="texture"> The texture to use </param>
/// <param name="position"> Where to draw on the screen </param>
void FontManager::Draw(SDL_Texture* texture, SDL_Rect position) {
									//If source rect is null, then we use the whole texture as source rect
	SDL_RenderCopy(Game::renderer, texture, NULL, &position);
}