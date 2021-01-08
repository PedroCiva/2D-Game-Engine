#ifndef COLOR_H
#define COLOR_H

#include "../libs/glm/glm.hpp"
#include "../SDL2/include/SDL.h"
#include <iostream>



/// <summary>
/// My own struct for colors
/// </summary>
typedef struct ColorValues
{
public:
	 Uint8 r;
	 Uint8 g;
	 Uint8 b;
	 Uint8 a;

	/// <summary>
	/// Converts our color struct to the SDL version
	/// </summary>
	/// <returns> Returns the converted version </returns>
	 SDL_Color toSDLColor() const
	 {
		SDL_Color sdlColor = { r, g, b, a };	
		return sdlColor;
	 }

}ColorValues;

/// <summary>
/// Struct of ColorValues with predefined rgba values that compose colors
/// </summary>
struct Color
{
public:
	const inline static ColorValues Red    = { 255, 0, 0, 255 };
	const inline static ColorValues Blue   = { 0, 0, 255, 255 };
	const inline static ColorValues Green  = { 0, 255, 0, 255 };
	const inline static ColorValues Black  = { 0, 0, 0, 255 };
	const inline static ColorValues Yellow = { 255, 255, 0 ,255 };
	const inline static ColorValues White  = { 255, 255, 255, 255 };
	const inline static ColorValues Grey   = { 160, 160, 160, 255 };
};
#endif