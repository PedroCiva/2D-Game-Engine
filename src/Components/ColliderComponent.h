#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "../SDL2/include/SDL.h"
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "../TextureManager.h"

class ColliderComponent : public Component {
private :
	bool collider_H_WasInitialized;
	bool collider_W_WasInitialized;

	//This makes sure we only call OnCollisionEnter once, once the collision was received
	bool collisionReceived;
	SDL_Rect collider;
public : 
	//Setter for the collider dimentions, for use when we specify collider values on another class Initialize()
	void colliderH(int H_value) { collider.h = H_value; collider_H_WasInitialized = true; }
	void colliderW(int W_value) { collider.w = W_value; collider_W_WasInitialized = true; }

	//Getter for the collider dimentions and positions
	float colliderH() const{ return collider.h; };
	float colliderW() const{ return collider.w; };
	float colliderX() const{ return collider.x; };
	float colliderY() const{ return collider.y; };
	

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
		collider_H_WasInitialized = true;
		collider_W_WasInitialized = true;
	}

	void Start() override {
		//If one of the collider dimentions was not specified, set it to the transform dimentions
		if (!collider_H_WasInitialized)
		{
			collider.h = transform->height * transform->scale;
		}
		if (!collider_W_WasInitialized)
		{
			collider.w = transform->width * transform->scale;
		}
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
			//Update collider position to match transform	
			collider.x = static_cast<int>(transform->position.x);
			collider.y = static_cast<int>(transform->position.y);
			destinationRectangle.x = collider.x - Game::camera.x;
			destinationRectangle.y = collider.y - Game::camera.y;
		
		//If there is a collision involving this gameObject and none of the objects involved have a collider with isTrigger
		if (EntityManager::CheckEntityCollisions(this->gameObject) && !this->isTrigger && !otherColliderComponent.isTrigger)
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
		}
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