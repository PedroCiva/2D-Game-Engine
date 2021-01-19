#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "../SDL2/include/SDL.h"
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
public : 
	SDL_Rect collider;
	TransformComponent* transform;
	static ColliderComponent otherColliderComponent;
	bool isTrigger;
	bool drawColliderBoundries;


	//Default constructor
	ColliderComponent() { 
		this->isTrigger = false;
	}

	void Start() override {

	}
	void Initialize() override {
			
		if (gameObject->HasComponent<TransformComponent>())
		{
			transform = gameObject->GetComponent<TransformComponent>();
		}
	}

	void Update(float deltaTime) override {
		//Update collider position to match transform	
		collider.x = static_cast<int>(transform->position.x) - Game::camera.x;
		collider.y = static_cast<int>(transform->position.y) -Game::camera.y;
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	
		//If there is a collision involving this gameObject and none of the objects involved have a collider with isTrigger
		/*if (EntityManager::CheckEntityCollisions(this->gameObject) && !this->isTrigger && !otherColliderComponent.isTrigger)
		{
			//Only call this method once, once the collision was received
			if (!collisionReceived) 
			{
				//Call OnCollisionEnter passing as parameter the other ColliderComponent
				//OnCollisionEnter(otherColliderComponent);
			}			
		}

		//If there is a collision involving this gameObject and at least one of the objects involved have a collider with isTrigger
		if (EntityManager::CheckEntityCollisions(this->gameObject) && (this->isTrigger || otherColliderComponent.isTrigger))
		{
			//Call OnTriggerEnter passing as parameter the other ColliderComponent
		//	OnTriggerEnter(otherColliderComponent);
		}*/
	}

	void Render() override {
		//TODO: add choose color option, add on button press activate
		//if(drawColliderBoundries)
			TextureManager::DrawOutline(collider,Color::Green);
	}
	
	/*virtual void OnCollisionEnter(ColliderComponent other)
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
	
	}*/
};
#endif