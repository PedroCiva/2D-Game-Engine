#include "Collision.h"

//Checks for collision between 2 colliders (more specifically its collider component (SDL_Rect))
bool Collision::CheckRectangleCollision(const ColliderComponent colliderA, const ColliderComponent colliderB) {
    if (colliderA.colliderX() + colliderA.colliderW() >= colliderB.colliderX() &&
        colliderB.colliderX() + colliderB.colliderW()>= colliderA.colliderX() &&
        colliderA.colliderY() + colliderA.colliderH()>= colliderB.colliderY() &&
        colliderB.colliderY() + colliderB.colliderH()>= colliderA.colliderY())
    {

        return true;
    }
    return false;        
}