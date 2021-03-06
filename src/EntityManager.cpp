#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "LayerMatrix.h"
#include "Components/ColliderComponent.h"

//Defining Collider component static member
ColliderComponent ColliderComponent::otherColliderComponent;

void EntityManager::ClearData() {
	entities.clear();
}

void EntityManager::Start() {
	for (auto& entity : entities)
		entity->Start();
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity : entities) 
	{
		if (entity->IsActive())
		{
			entity->Update(deltaTime);
		}
	}
}

void EntityManager::DestroyEntity(Entity* entity) {
	
	auto entityToDestroy = std::find_if(entities.begin(), entities.end(), [=](Entity* p) { return p->GetEntity() == entity->GetEntity(); });
	int index = std::distance(entities.begin(), entityToDestroy);
	if (entityToDestroy != entities.end()) 
	{
		std::cout << "Destroying entity" << entities[index]->name << std::endl;
		entities.erase(entities.begin() + index);
	}
		
}

void EntityManager::Render() {
	for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber)))
			entity->Render();
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName,LayerType layer) {

	//Creating new entity on the heap. Our entity is somewhere in the heap memory
	Entity* entity = new Entity(*this, entityName, layer);

	//Adding our new entity to the list of entities
	entities.emplace_back(entity);
	
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}

Entity* EntityManager::GetEntityByName(std::string entityName) const {
	for (auto* entity : entities) {
		if (entity->name.compare(entityName) == 0) {
			return entity;
		}
	}
	return NULL;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities) {
		if (entity->layer == layer)
			selectedEntities.emplace_back(entity);
	}
	return selectedEntities;
}

unsigned int EntityManager::GetEntityCount() {
	return entities.size();
}

//Prints all entities and its components to the console
void EntityManager::PrintEntitiesList() const{
	unsigned int i = 0;
	for (Entity* entity : entities)
	{
		if (entity->layer != TILEMAP_LAYER) {
			std::cout << "Entity " << i << " name: " << entity->name.c_str() << std::endl;
			std::cout << "Components: " << entity->GetComponentsName() << std::endl;
			i++;
		}		
	}
}

/// <summary>
/// Checks for any collisions with a certain entity and assigns the ColliderComponent of the object we collided with
/// </summary>
/// <param name="entity"> The entity to check the collisions for </param>
/// <returns> Returns true or false depending wether a collisions happened or not </returns>
bool EntityManager::CheckEntityCollisions(Entity* entity){	
	auto& thisEntity = entity;
	//Safe check for component
	if (thisEntity->HasComponent<ColliderComponent>())
	{
		//Grabing entity collider component
		ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();

		//Looping through all entities to check for collision with thisCollider (comes from thisEntity)
		for (int j = 0; j < entities.size(); j++)
		{
			if (thisEntity->name.compare(entities[j]->name) != 0 && entities[j]->HasComponent<ColliderComponent>() && entities[j]->layer != TILEMAP_LAYER)
			{
				auto& thatEntity = entities[j];

				//If the colliders have different names and thatEntity has a collider component


				ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();

				if (Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider))
				{
					//Set the otherColliderComponent to thatCollider (for use on OnCollisionEnter in ColliderComponent.h)
					ColliderComponent::otherColliderComponent = *thatCollider;

					//If there is a collision, check if the 2 objects even should collide based on the Collision Layer Matrix
					return (LayerMatrix::ShouldCollide(thisCollider->gameObject->layer, thatCollider->gameObject->layer));
				}
			}
		}
		//If no collisions at all
		return false;
	}
}



