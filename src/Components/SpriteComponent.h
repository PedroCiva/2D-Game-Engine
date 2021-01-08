#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "../SDL2/include/SDL.h"
#include "../AssetManager.h"
#include "../TextureManager.h"
#include "../Animation.h"


class SpriteComponent :public Component {
private: 
	TransformComponent* transform;
	SDL_Texture* texture;
	SDL_Rect sourceRect;
	SDL_Rect destinationRect;
	bool isAnimated;
	bool isFixed; //Does this sprite move, or is it supposed to always stay on the same position on the screen, such as UI
	int numFrames; // Number of frames in the animation spritesheet
	int animationSpeed;
	std::map<std::string, Animation> animations; //Map of different animations in this sprite
	std::string currentAnimationName;
	unsigned int animationIndex = 0;

public:
	SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
	//Constructor for non-animated sprite
	SpriteComponent(const char* textureID) {
		isAnimated = false;
		isFixed = false;
		SetTexture(textureID);
	}
															//hasDirection=does the sprite have more than 1 direction? It turns?
	SpriteComponent(std::string textureID, unsigned int numFrames,unsigned int animationSpeed,bool hasDirections, bool isFixed) {
		this->isAnimated = true;
		this->numFrames = numFrames;
		this->animationSpeed = animationSpeed;
		this->isFixed = isFixed;
		
		//Each direction is a diferent animation, each index corresponds to the spritesheet (look at spritesheet if needed)
		if (hasDirections) {
			Animation downAnimation = Animation(0, numFrames, animationSpeed);
			Animation rightAnimation = Animation(1, numFrames, animationSpeed);
			Animation leftAnimation = Animation(2, numFrames, animationSpeed);
			Animation upAnimation = Animation(3, numFrames, animationSpeed);

			animations.emplace("DownAnimation", downAnimation);
			animations.emplace("RightAnimation", rightAnimation);
			animations.emplace("LeftAnimation", leftAnimation);
			animations.emplace("UpAnimation", upAnimation);

			//Giving a starting animation
			this->animationIndex = 0;
			this->currentAnimationName = "DownAnimation";
		}
		else {
			//Animation *singleAnimation = new Animation(0, numFrames, animationSpeed);
			//Animation singleAnimation(0, numFrames, animationSpeed);
			Animation singleAnimation = Animation(0, numFrames, animationSpeed);
			animations.emplace("SingleAnimations", singleAnimation); //Adding animation to our map
			this->animationIndex = 0;
			this->currentAnimationName = "SingleAnimation";
		}
		Play(this->currentAnimationName);
		SetTexture(textureID);
	}

	//This method sets all the member variables related to animations
	void Play(std::string animationName) {
		numFrames = animations[animationName].numFrames;
		animationIndex = animations[animationName].animationIndex;
		animationSpeed = animations[animationName].animationSpeed;
		currentAnimationName = animationName;
	}

	void SetTexture(std::string assetTextureId) {
		texture = Game::assetManager->GetTexture(assetTextureId);
	}

	void Initialize() override {
		//If this gameObject already has a transform component then initialize its dimentions to match the transform
		if (gameObject->HasComponent<TransformComponent>())
		{
			transform = gameObject->GetComponent<TransformComponent>();
			sourceRect.x = 0;
			sourceRect.y = 0;
			sourceRect.w = transform->width;//Dimentions of the sprite are gonna be equal to the transform widht and height
			sourceRect.h = transform->height;
		}
		else
		{
			std::cerr << "Error initializing Sprite Component, this object does not have a Transform, this object will be initialized without a sprite..." << "\n" << "Object: " << gameObject->name << std::endl;
		}
	}

	//Width changes animations same direction, height changes animation direction
	void Update(float deltaTime) override {
		if (gameObject->HasComponent<TransformComponent>()) {
			if (isAnimated) {
				//This pretty much goes back and forth between animations squares on the spritesheet, using mod so we dont go over
				sourceRect.x = sourceRect.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames); //Shifts 32 32 32 32 on x on the spritesheet, goes back and forth due to the mod
			}
			//animationIndex meaning which row of the spritesheet it is times the animations height (size of each animation square on the spritesheet)
			sourceRect.y = animationIndex * transform->height;
			destinationRect.x = static_cast<int>(transform->position.x) - (isFixed ? 0 : Game::camera.x);//Only subtract if sprite is not fixed
			destinationRect.y = static_cast<int>(transform->position.y) - (isFixed ? 0 : Game::camera.y);
			destinationRect.w = transform->width * transform->scale;
			destinationRect.h = transform->height * transform->scale;
		}
	}

	void Render() override {
		if (gameObject->HasComponent<TransformComponent>())
		{
			TextureManager::Draw(texture, sourceRect, destinationRect, spriteFlip);
		}
	}
};

#endif 

