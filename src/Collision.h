#ifndef COLLISION_H
#define COLLISION_H

#include "../SDL2/include/SDL.h"
#include "../src/Components/ColliderComponent.h"

class Collision {
public:
	//Checks for collision between 2 colliders (more specifically its collider component (SDL_Rect))
	static bool CheckRectangleCollision(const ColliderComponent colliderA, const ColliderComponent colliderB);
	Entity* gameObject;
	static Collision* collision;
	TransformComponent* transform;
};



#endif

