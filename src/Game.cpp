#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include <../src/Components/TransformComponent.h>
#include <../src/Components/SpriteComponent.h>
#include <../src/Components/ColliderComponent.h>
#include <../src/Components/KeyboardControlComponent.h> 
#include <../libs/glm/glm.hpp>

EntityManager manager;
//Passing entity manager "manager" here because our AssetManager constructor requires it.. making it on the heap so its alive throughout the program
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Map* map;


Game::Game()
{
	this->isRunning = false;
}

Game::~Game()
{
	//TO-DO
}

bool Game::IsRunning() const
{
	return this->isRunning;
}

//Creating the window and renderer with SDL and loading the level
void Game::Initialize(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
		return;
	}

	window = SDL_CreateWindow("My 2d Game Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
	if (!window)
	{
		std::cerr << "Error creating SDL window." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, 0);
	if (!renderer)
	{
		std::cerr << "Error creating SDL renderer." << std::endl;
		return;
	}

	LoadLevel(0);

	//If everything was created successfully, isRunning is true.
	isRunning = true;
	return;
}

Entity& player(manager.AddEntity("chopper", PLAYER_LAYER));
void Game::LoadLevel(int levelNumber){
	//Start including new assets to the AssetManager list
	assetManager->AddTexture("tank-image", "./assets/images/tank-big-right.png"); //Adding texture to texture manager
	assetManager->AddTexture("chopper-image", "./assets/images/chopper-spritesheet.png"); //Adding texture to texture manager
	assetManager->AddTexture("jungle-tiletexture", "./assets/tilemaps/jungle.png");

	map = new Map("jungle-tiletexture", 2, 32); //Scale size 1 and tile size 32 by 32
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20); // map size is 25 tiles by 20 tiles

	//Start including entities and also components to them

	player.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
	player.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
	player.AddComponent<ColliderComponent>();
	player.AddComponent <KeyboardControlComponent>("up", "right", "down", "left", "space");


	Entity& tank(manager.AddEntity("tank",ENEMY_LAYER));
	tank.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
	tank.AddComponent<SpriteComponent>("tank-image");
	tank.AddComponent<ColliderComponent>("enemy", 64, 64);

	manager.PrintEntitiesList();
}

void Game::ProcessInput()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{	
		case SDL_QUIT://Clicking the X button
			isRunning = false;
			break;
		case SDL_KEYDOWN://Press escape to exit as well
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
		default : 
			break;
	}
}

void Game::Update()
{
	//Wait until 16.6ms (target frame rate) has ellapsed since the last frame, so it looks the same on every computer
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks()-ticksLastFrame) ;

	if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME)
		SDL_Delay(timeToWait);


	//Delta time is the difference in ticks from last frame converted to seconds
	float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

	//Clamp deltaTime to a maximum value, in case we debug with breakpoints it won't cause weird issues in our game due to excessive deltaTime 
	deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

	//Sets the new ticks time for the current frame to be used in the next pass
	ticksLastFrame = SDL_GetTicks(); 

	//Here we call the manager.update to update all entities as a function of deltaTime
	manager.Update(deltaTime);
	HandleCameraMovement();
	CheckCollisions();
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255); //Setting background colors
	SDL_RenderClear(renderer); //Clearing SDL backbuffer

	//Here we call the manager.render to render all entities
	if (manager.HasNoEntities())
		return;

	manager.Render();

	//Swap backbuffer with the frontbuffer
	SDL_RenderPresent(renderer);
}

void Game::HandleCameraMovement() {
	camera.x = player.GetComponent<TransformComponent>()->position.x - (WINDOW_WIDTH / 2); //Move only when player reaches half of the window
	camera.y = player.GetComponent<TransformComponent>()->position.y - (WINDOW_WIDTH / 2); //Move only when player reaches half of the window

	//Clamping camera
	camera.x = camera.x < 0 ? 0 : camera.x;
	camera.y = camera.y < 0 ? 0 : camera.y;
	camera.x = camera.x > camera.w ? camera.w : camera.x;
	camera.y = camera.y > camera.h ? camera.h : camera.y;
}

void Game::CheckCollisions() {
	std::string collisionTagType = manager.CheckEntityCollisions(player);
	if (collisionTagType.compare("enemy") == 0) {
		//TODO: do something when collision with a enemy is identified
	    isRunning = false;
	}
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

