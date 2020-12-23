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

	//This makes sure we only call OnCollisionEnter once, once the collision was received
	bool collisionReceived;
public : 
	SDL_Rect collider;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
	TransformComponent* transform;
	static ColliderComponent otherColliderComponent;
	bool isTrigger;
	bool drawColliderBoundries;

	//Default constructor
	ColliderComponent() { 
		this->isTrigger = false;
	}

	//Constructor that allows to specify the collider proportions
	ColliderComponent(int width, int height) { 
		this->collider.w = width;
		this->collider.h = height;
		colliderWasInitialized = true;
	}

	void Initialize() override {

		if (gameObject->HasComponent<TransformComponent>())
		{
			transform = gameObject->GetComponent<TransformComponent>();
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

		//If there is a collision involving this gameObject and none of the objects involved have a collider with isTrigger
		if (EntityManager::CheckEntityCollisions(this->gameObject) && !this->isTrigger && !otherColliderComponent.isTrigger)
		{
			//Only call this method once, once the collision was received
			if (!collisionReceived) 
			{
				//Call OnCollisionEnter passing as parameter the other ColliderComponent
				OnCollisionEnter(otherColliderComponent);
			}			
		}

		//If there is a collision involving this gameObject and at least one of the objects involved have a collider with isTrigger
		if (EntityManager::CheckEntityCollisions(this->gameObject) && (this->isTrigger || otherColliderComponent.isTrigger))
		{
			//Call OnTriggerEnter passing as parameter the other ColliderComponent
			OnTriggerEnter(otherColliderComponent);
		}
	}

	void Render() override {
		//TODO: add choose color option, add on button press activate
		//if(drawColliderBoundries)
			TextureManager::DrawOutline(collider,Color::Green);
	}
	
	virtual void OnCollisionEnter(ColliderComponent other)
	{
		 //Default behavior is to set the collisionReceived to true so we ensure this only runs once
		collisionReceived = true;
	}

	virtual void OnCollisionExit(ColliderComponent other)
	{
		//Default behavior is to reset the collisionReceived back to false to ensure we are ready to execute OnCollisionEnter again
		collisionReceived = false;
	}

	virtual void OnTriggerEnter(ColliderComponent other)
	{

	}

	virtual void OnTriggerExit(ColliderComponent other)
	{

	}
};
#endif