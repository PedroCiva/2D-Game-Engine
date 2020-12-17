#ifndef GAME_H
#define GAME_H

#include <../../SDL2/include/SDL.h>
#include <../../SDL2/include/SDL_image.h>
#include <../../SDL2/include/SDL_ttf.h>
#include "Entity.h"
#include "Component.h"
#include "EntityManager.h"

// Doing this to avoid the circular inclusion problem, in this case AssetManager.h includes TextureManager.h
//  which includes Game.h which then includes all of the above classes again
class AssetManager;

//This Game.h file contains all the basic methods for our game loop
class Game
{
	private:
		bool isRunning;
		SDL_Window* window;
		
	public:
		Game();
		~Game();
		int ticksLastFrame=0;
		bool IsRunning() const;
		static SDL_Renderer* renderer;
		static AssetManager* assetManager;
		static SDL_Event event;
		static SDL_Rect camera;
		void LoadLevel(int levelNumber);
		void Initialize(int width, int height);
		void ProcessInput();
		void Update();
		void Render();
		void Destroy();
		void HandleCameraMovement();
		void CheckCollisions();
};

#endif
