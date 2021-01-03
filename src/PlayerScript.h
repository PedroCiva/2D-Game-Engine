#ifndef PLAYER_H
#define PLAYER_H
/*
#include <iostream>
#include "Entity.h"
#include "Components/ColliderComponent.h"

class PlayerScript : public Component {

public:
	LayerType layer = PLAYER_LAYER;
	ColliderComponent* colliderComponent;
	//TransformComponent* transformComponent;

	//Check out why is Start not being called, the code works if this method is replace by Initialize(), has something to do with the order that the methods are called
	void Initialize() override {

		//Defining our layer 
		this->gameObject->name = "ThaPlayer";
		this->gameObject->layer = PLAYER_LAYER;
		this->gameObject->AddComponent<ColliderComponent>();
		this->gameObject->GetComponent<TransformComponent>()->position.x = 100;
		this->gameObject->GetComponent<TransformComponent>()->position.y = 100;
		gameObject->GetComponent<ColliderComponent>()->colliderH(32);
		gameObject->GetComponent<ColliderComponent>()->colliderW(32);
		std::cout << "Player name is : " <<  this->gameObject->name << std::endl;
	}

	//Behaves like the Update() method in Unity
	void Update(float deltaTime) override {

	}

};
*/

#endif
