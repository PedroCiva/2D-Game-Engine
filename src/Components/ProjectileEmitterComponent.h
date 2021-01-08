#ifndef PROJECTILEEMITTERCOMPONENT_H
#define PROJECTILEEMITTERCOMPONENT_H

#include "../../libs/glm/glm.hpp"
#include "../EntityManager.h"
#include "TransformComponent.h"

class ProjectileEmitterComponent : public Component {
private:
	TransformComponent* transform;
	glm::vec2 origin;
	int speed;
	int range;
	float angleRad; // in radians
	bool shouldLoop;
public:
	ProjectileEmitterComponent(int speed, int range, float angleDeg, bool shouldLoop) {
		this->speed = speed;
		this->range = range;
		this->shouldLoop = shouldLoop;
		this->angleRad = glm::radians(static_cast<float>(angleDeg));
	}

	void Initialize() override {
		transform = this->gameObject->GetComponent<TransformComponent>();
		origin = glm::vec2(transform->position.x, transform->position.y);
		//transform->velocity = 
	}
};
#endif
