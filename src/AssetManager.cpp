#include "AssetManager.h"

AssetManager::AssetManager(EntityManager* manager) : manager(manager) {

}

/// <summary>
/// Clears all data from our dictionaries
/// </summary>
void AssetManager::ClearData() {
	textures.clear();
	fonts.clear();
}

/// <summary>
/// Adds a texture to our textures dictionary
/// </summary>
/// <param name="textureId"> The texture ID to pass as key </param>
/// <param name="filePath"> File path to load the texture from the texture manager and pass the return SDL_Texture as the value </param>
void AssetManager::AddTexture(std::string textureId, const char* filePath) {
	textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

/// <summary>
/// Adds a font to our fonts dictionary
/// </summary>
/// <param name="fontId"> The font ID to pass as key </param>
/// <param name="filePath"> First parameter to load the font from our font manager and pass the return SDL_Font as the value </param>
/// <param name="fontSize"> Second parameter required for loading the texture from our font manager </param>
void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
	fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

/// <summary>
/// Gets and returns a SDL_Texture from our textures dictionary
/// </summary>
/// <param name="textureId">The texture ID identifier</param>
/// <returns> returns a SDL_Texture </returns>
SDL_Texture* AssetManager::GetTexture(std::string textureId) {
	return textures[textureId];
}

/// <summary>
/// Gets and returns a TTF_Font from our fonts dictionary
/// </summary>
/// <param name="fontId"> The font ID identifier </param>
/// <returns> returns a TTF_Font </returns>
TTF_Font* AssetManager::GetFont(std::string fontId) {
	return fonts[fontId];
}