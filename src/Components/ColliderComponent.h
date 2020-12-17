#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <../../SDL2/include/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
private :
	bool colliderWasInitialized;
public : 
	std::string colliderTag;
	SDL_Rect collider;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	TransformComponent* transform;
	bool isTrigger;
	bool drawColliderBoundries;

	//Default constructor
	ColliderComponent(bool isTrigger) { 
		this->isTrigger = isTrigger;
	}

	//Constructor that allows to specify the collider proportions
	ColliderComponent(std::string colliderTag, int width, int height) { 
		this->colliderTag = colliderTag;
		this->collider.w = width;
		this->collider.h = height;
		colliderWasInitialized = true;
	}

	void Initialize() override {

		if (owner->HasComponent<TransformComponent>())
		{
			transform = owner->GetComponent<TransformComponent>();
			sourceRectangle = { 0,0, transform->width,transform->height }; //Shouldn't this be initialized to the transform X and Y as well?
			//Always remember the destination rectangle is where and how we wanna draw the final rectangle on the screen, in this case how we want our collider to be
			destinationRectangle = { collider.x,collider.y,collider.w,collider.h };
		}
	}

	void Update(float deltaTime) override {
		 //If collider was initialized with specific proportions then update only the position
		if (colliderWasInitialized == true)
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			destinationRectangle.x = collider.x - Game::camera.x;
			destinationRectangle.y = collider.y - Game::camera.y;
		}
		else
		{
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			collider.w = transform->width * transform->scale;
			collider.h = transform->height * transform->scale;
			destinationRectangle.x = collider.x - Game::camera.x;
			destinationRectangle.y = collider.y - Game::camera.y;
		}
	}

	void Render() override {
		//TODO: add choose color option, add on button press activate
		//if(drawColliderBoundries)
			TextureManager::DrawOutline(collider,Color::Green);
	}
};
#endif