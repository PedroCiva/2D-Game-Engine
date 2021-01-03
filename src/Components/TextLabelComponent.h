#ifndef TEXTLABELCOMPONENT_H
#define TEXTLABELCOMPONENT_H

#include <../../SDL2/include/SDL.h>
#include <../../SDL2/include/SDL_ttf.h>
#include "../FontManager.h"
#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"

class TextLabelComponent : public Component {
private :
	SDL_Rect position;
	std::string textContent;
	std::string fontFamily; 
	SDL_Color color;

	//Texture where we are gonna render our label
	SDL_Texture* texture;

public:
	TextLabelComponent(int x, int y, std::string text, std::string fontFamily, const SDL_Color& color) {
		this->position.x = x;
		this->position.y = y;
		this->textContent = text;
		this->fontFamily = fontFamily;
		this->color = color;
		SetLabelText(text, fontFamily);
	}

	/// <summary>
	/// Creates a texture from our font
	/// </summary>
	/// <param name="text"> The text content </param>
	/// <param name="fontFamily"> The font family </param>
	void SetLabelText(std::string text, std::string fontFamily) {
		SDL_Surface* surface = TTF_RenderText_Blended(Game::assetManager->GetFont(fontFamily), text.c_str(), color);
		texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(texture, NULL, NULL, &position.w, &position.h);
	}

	void Render() override {
		FontManager::Draw(texture, position);
	}
};

#endif // !TEXTLABELCOMPONENT_H

