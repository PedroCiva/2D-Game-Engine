#ifndef  KEYBOARDCONTROLCOMPONENT_H
#define  KEYBOARDCONTROLCOMPONENT_H

#include "../Game.h"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include <iostream>

class KeyboardControlComponent : public Component {
public:
	std::string upKey;
	std::string downKey;
	std::string leftKey;
	std::string rightKey;
	std::string shootKey;
	//These are components that will likely be affected by the keyboard input
	TransformComponent* transform;
	SpriteComponent* sprite;

	KeyboardControlComponent() {}

	KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string shootKey) {
		//Translates string to sdl key code
		this->upKey = GetSDLKeyStringCode(upKey);
		this->rightKey = GetSDLKeyStringCode(rightKey);
		this->downKey = GetSDLKeyStringCode(downKey);
		this->leftKey = GetSDLKeyStringCode(leftKey);
		this->shootKey = GetSDLKeyStringCode(shootKey);

		printf("Controls are:\n");
		std::cout << "Up: " << upKey.c_str()<< std::endl;
		std::cout << "Down: " << downKey.c_str()<< std::endl;
		std::cout << "Left: " << leftKey.c_str()<< std::endl;
		std::cout << "Right: " << rightKey.c_str()<< std::endl;
		std::cout << "Shoot: " << shootKey.c_str()<< std::endl;
		std::cout << "Turn on show collider boxes: TO-DO " << "F1"<< std::endl;
	}

	std::string GetSDLKeyStringCode(std::string key) {
		//SDL code for arrow keys are as follow
		if (key.compare("up") == 0) return "1073741906";
		if (key.compare("down") == 0) return "1073741905";
		if (key.compare("left") == 0) return "1073741904";
		if (key.compare("right") == 0) return "1073741903";
		//SDL code for all the other keys follow the ASCII table
		if (key.compare("space") == 0) return "32";

		return std::to_string(static_cast<int>(key[0])); //Gets ASCII equivalent
	}

	void Initialize() override {
		transform = owner->GetComponent<TransformComponent>();
		sprite = owner->GetComponent<SpriteComponent>();
	}
	void Update(float deltaTime) override {
		//If key pressed get the key and handle
		if (Game::event.type == SDL_KEYDOWN) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);

			//Handling what each key should do
			if (keyCode.compare(upKey) == 0) {
				transform->velocity.y = -80; //Sets velocity, everything else updates on the transform component update
				transform->velocity.x = 0;
				sprite->Play("UpAnimation"); //Play respective animation
			}
			if (keyCode.compare(rightKey) == 0) {
				transform->velocity.y = 0;
				transform->velocity.x = 80;
				sprite->Play("RightAnimation");
			}
			if (keyCode.compare(downKey) == 0) {
				transform->velocity.y = 80;
				transform->velocity.x = 0;
				sprite->Play("DownAnimation");
			}
			if (keyCode.compare(leftKey) == 0) {
				transform->velocity.y = 0;
				transform->velocity.x = -80;
				sprite->Play("LeftAnimation");
			}		
			if (keyCode.compare(shootKey) == 0) {
				//TODO:
				//Shoot projectiles when "shootKey" is pressed
			}
		}
		//If key released get the key and handle
		if (Game::event.type == SDL_KEYUP) {
			std::string keyCode = std::to_string(Game::event.key.keysym.sym);

			//Handling what each key should do
			if (keyCode.compare(upKey) == 0) {
				transform->velocity.y = 0;
			}
			if (keyCode.compare(rightKey) == 0) {
				transform->velocity.x = 0;
			}
			if (keyCode.compare(downKey) == 0) {
				transform->velocity.y = 0;
			}
			if (keyCode.compare(leftKey) == 0) {
				transform->velocity.x = 0;
			}			
		}
	}
};

#endif // !KEYBOARDCONTROLCOMPONENT_H