#include <iostream>
#include "EntityManager.h"
#include "Collision.h"
#include "Components/ColliderComponent.h"

void EntityManager::ClearData() {
	for (auto& entity : entities)
		entity->Destroy();
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity : entities)
		entity->Update(deltaTime);
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

std::string EntityManager::CheckEntityCollisions(Entity& myEntity) const {
	ColliderComponent *myColliderPtr = myEntity.GetComponent<ColliderComponent>();
	ColliderComponent myCollider = *myColliderPtr;
	for (auto& entity : entities) {
		if (entity->name.compare(myEntity.name) != 0 && entity->name.compare("Tile") != 0) {
			if (entity->HasComponent<ColliderComponent>())
			{
				ColliderComponent *otherColliderPtr = entity->GetComponent<ColliderComponent>();
				ColliderComponent otherCollider = *otherColliderPtr;
				if (Collision::CheckRectangleCollision(myCollider, otherCollider))
				{
					return otherCollider.colliderTag;
				}							
			}
		}
	}
	return std::string();
}


