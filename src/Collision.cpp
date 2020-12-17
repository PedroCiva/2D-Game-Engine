#include "Collision.h"

//Checks for collision between 2 colliders (more specifically its collider component (SDL_Rect))
bool Collision::CheckRectangleCollision(const ColliderComponent colliderA, const ColliderComponent colliderB) {
    return (
       colliderA.collider.x +colliderA.collider.w >= colliderB.collider.x &&
        colliderB.collider.x + colliderB.collider.w >= colliderA.collider.x &&
        colliderA.collider.y + colliderA.collider.h >= colliderB.collider.y &&
        colliderB.collider.y + colliderB.collider.h >= colliderA.collider.y
        );
}