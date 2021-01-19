#include <iostream>
#include "Constants.h"
#include "Game.h"
#include "AssetManager.h"
#include "Map.h"
#include "LayerMatrix.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/TextLabelComponent.h"
#include "Components/ProjectileEmitterComponent.h"
#include "../libs/glm/glm.hpp"

EntityManager manager;
//Passing entity manager "manager" here because our AssetManager constructor requires it.. making it on the heap so its alive throughout the program
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
Entity* mainPlayer = NULL;
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

	if (TTF_Init() != 0)
	{
		std::cerr << "Error initializing SDL_TTF" << std::endl;
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

	LoadLevel(1);

	//If everything was created successfully, isRunning is true.
	isRunning = true;
	return;
}


void Game::LoadLevel(int levelNumber){

	//LayerMatrix layerMatrix;


	sol::state lua;
	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

	std::string levelName = "Level" + std::to_string(levelNumber);
	lua.script_file("./assets/scripts/" + levelName +".lua");

	sol::table levelData = lua[levelName];

	/*********************************************/
	/* LOADS ASSETS FROM LUA CONFIG FILE         */
	/*********************************************/
	sol::table levelAssets = levelData["assets"];

	unsigned int assetIndex = 0;
	while (true) {
		sol::optional<sol::table> existsAssetIndexNode = levelAssets[assetIndex];
		if (existsAssetIndexNode == sol::nullopt) {
			break;
		}
		else {
			sol::table asset = levelAssets[assetIndex];
			std::string assetType = asset["type"];
			if (assetType.compare("texture") == 0) {
				std::string assetId = asset["id"];
				std::string assetFile = asset["file"];
				assetManager->AddTexture(assetId, assetFile.c_str());
			}
			else if (assetType.compare("font") == 0) {
				std::string fontId = asset["id"];
				std::string fontFile = asset["file"];
				int fontSize = asset["fontSize"];
				assetManager->AddFont(fontId, fontFile.c_str(), fontSize);
			}
		}
		assetIndex++;
	}

	/*********************************************/
	/* LOADS ENTITIES FROM LUA CONFIG FILE       */
	/*********************************************/
	sol::table levelEntities = levelData["entities"];
	unsigned int entityIndex = 0;
	while (true) {
		sol::optional<sol::table> existsEntitieIndexNode = levelEntities[entityIndex];
		if (existsEntitieIndexNode == sol::nullopt) {
			break;
		}
		else {
			sol::table entity = levelEntities[entityIndex];
			std::string entityName = entity["name"];
			LayerType entityLayer = entity["layer"];
			//Adding entity
			auto& newEntity(manager.AddEntity(entityName, entityLayer));

			//Adding Transform component
			sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
			if (existsTransformComponent != sol::nullopt) {
				int posX = entity["components"]["transform"]["position"]["x"];
				int posY = entity["components"]["transform"]["position"]["y"];
				int velX = entity["components"]["transform"]["velocity"]["x"];
				int velY = entity["components"]["transform"]["velocity"]["y"];
				int width = entity["components"]["transform"]["width"];
				int height = entity["components"]["transform"]["height"];
				int scale = entity["components"]["transform"]["scale"];
				int rotation = entity["components"]["transform"]["rotation"];
				if (entityName == "player") {
					newEntity.AddComponent<TransformComponent>(32, 32);
				}
				else {
					newEntity.AddComponent<TransformComponent>(posX, posY, velX, velY, width, height, scale); 	//// Missing rotation on transform contructor ////
				}
				
			}
			//Adding Sprite component
			sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
			if (existsSpriteComponent != sol::nullopt) {
				bool isAnimated = entity["components"]["sprite"]["animated"];
				if (isAnimated) {
					std::string textureAssetId = entity["components"]["sprite"]["textureAssetId"];
					int frameCount = entity["components"]["sprite"]["frameCount"];
					int animationSpeed = entity["components"]["sprite"]["animationSpeed"];
					bool hasDirections = entity["components"]["sprite"]["hasDirections"];
					bool fixed = entity["components"]["sprite"]["fixed"];
					newEntity.AddComponent<SpriteComponent>(textureAssetId.c_str(), frameCount, animationSpeed, hasDirections, fixed); //// Using my own parameters on sprite contructor ////
				}
				else {
					std::string textureAssetId = entity["components"]["sprite"]["textureAssetId"];
					newEntity.AddComponent<SpriteComponent>(textureAssetId.c_str());
				}									
			}
			//Adding Collider component
			sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
			if (existsColliderComponent != sol::nullopt) {
				newEntity.AddComponent<ColliderComponent>();								//// Ignoring collider tag inside Lua ///
			}
			//Adding Projectile Emitter component
			sol::optional<sol::table> existsProjectileEmmiterComponent = entity["components"]["projectileEmitter"];
			if (existsProjectileEmmiterComponent != sol::nullopt) {
				int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
				int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
				int parentEntityWidth = entity["components"]["transform"]["width"];
				int parentEntityHeight = entity["components"]["transform"]["height"];
				int projectileWidth = entity["components"]["projectileEmitter"]["width"];
				int projectileHeight = entity["components"]["projectileEmitter"]["height"];
				int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
				int projectileRange = entity["components"]["projectileEmitter"]["range"];
				int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
				bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
				std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
				Entity& projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
				projectile.AddComponent<TransformComponent>(parentEntityXPos + (parentEntityWidth / 2), parentEntityYPos + (parentEntityHeight / 2), 0, 0, projectileWidth, projectileHeight, 1);
				projectile.AddComponent<SpriteComponent>(textureAssetId.c_str());
				projectile.AddComponent<ProjectileEmitterComponent>(projectileSpeed,projectileAngle,projectileRange,projectileShouldLoop);
				projectile.AddComponent<ColliderComponent>();
			}
			//Adding Keyboard Control component
			sol::optional<sol::table> existsKeyboardControlComponent = entity["components"]["input"];
			if (existsKeyboardControlComponent != sol::nullopt) {
				std::string up = entity["components"]["input"]["keyboard"]["up"];
				std::string left = entity["components"]["input"]["keyboard"]["left"];
				std::string down = entity["components"]["input"]["keyboard"]["down"];
				std::string right = entity["components"]["input"]["keyboard"]["right"];
				std::string shoot = entity["components"]["input"]["keyboard"]["shoot"];
				newEntity.AddComponent<KeyboardControlComponent>(up,right,down,left,shoot);
			}		
			//Adding TextLabelComponent
			sol::optional<sol::table> existsLabelComponent = entity["components"]["label"];
			if (existsLabelComponent != sol::nullopt) {
				int posX = entity["components"]["label"]["x"];
				int posY = entity["components"]["label"]["y"];
				std::string text = entity["components"]["label"]["text"];
				std::string fontFamily = entity["components"]["label"]["fontFamily"];			   			
				//SDL_Color color = static_cast<SDL_Color>(entity["components"]["label"]["color"]);			//// Gotta change color method here ////
				newEntity.AddComponent<TextLabelComponent>(posX, posY, text, fontFamily, Color::Red.toSDLColor());
			}
		}
		entityIndex++;
	}
	



	/*********************************************/
	/* LOADS MAP FROM LUA CONFIG FILE            */
	/*********************************************/
	sol::table levelMap = levelData["map"];
	std::string mapTextureId = levelMap["textureAssetId"];
	std::string mapFile = levelMap["file"];

	map = new Map(mapTextureId, static_cast<int>(levelMap["scale"]), static_cast<int>(levelMap["tileSize"]));	
	map->LoadMap(mapFile, static_cast<int>(levelMap["mapSizeX"]), static_cast<int>(levelMap["mapSizeY"]));

	mainPlayer = manager.GetEntityByName("player");

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
	int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

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
	if (mainPlayer) {
		TransformComponent* mainPlayerTransform = mainPlayer->GetComponent<TransformComponent>();
		camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
		camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

		camera.x = camera.x < 0 ? 0 : camera.x;
		camera.y = camera.y < 0 ? 0 : camera.y;
		camera.x = camera.x > camera.w ? camera.w : camera.x;
		camera.y = camera.y > camera.h ? camera.h : camera.y;
	}
}

void Game::CheckCollisions() {
	/*if (manager.CheckEntityCollisions(&player))
	{
		tank.Destroy();
	}*/
}

void Game::Destroy()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

