#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H
#include "../EntityManager.h"
#include "../Game.h"
#include <../libs/glm/glm.hpp>
#include <../../SDL2/include/SDL.h>
#include "../Constants.h"
#include <iostream>
class TransformComponent : public Component {
public:
	glm::vec2 position;
	glm::vec2 velocity;
	int width;
	int height;
	int scale;

	TransformComponent() {
		//If no parameters were specified then initialize these default values
		position = glm::vec2(0, 0);
		velocity = glm::vec2(0, 0);
		width = 32;
		height = 32;
		scale = 1;
	}
	TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(velX, velY);
		width = w;
		height = h;
		scale = s;
	}
	TransformComponent(int posX, int posY){
		position = glm::vec2(posX, posY);
		velocity = glm::vec2(0, 0);
		width = 32;
		height = 32;
		scale = 1;
	}

	void Initialize() override {
	}

	void Update(float deltaTime) override {

		position.x += velocity.x * deltaTime;
		position.y += velocity.y * deltaTime;	
	}

	void Render() override {
	}

private:

};
#endif 

