#include <iostream>
#include "Entity.h"
#include "./Components/TransformComponent.h"

//Creates entity and sets isActive to true
Entity::Entity(EntityManager& manager) : manager(manager) {
	this->isActive = true;
	this->AddComponent<TransformComponent>();
}
Entity::Entity(EntityManager& manager,std::string name, LayerType layer) : manager(manager), name(name), layer(layer) {
	this->isActive = true;
	this->AddComponent<TransformComponent>();
}

void Entity::Start() {
	for (auto& component : components)
		component->Start();
}
void Entity::Update(float deltaTime) {
	//Foreach component <T> in components
	for(auto& component : components)	
		component->Update(deltaTime);	
}

void Entity::Render() {

	for (auto& component : components)
		component->Render();
}
void Entity::Destroy() {
	this->isActive = false;
}

bool Entity::IsActive() const {
	return this->isActive;
}

//Returns the name of the component
std::string Entity::GetComponentsName() const {
	std::string componentInfo;
	for (auto mapElement : componentTypeMap) {
		componentInfo.append("<");
		componentInfo.append(mapElement.first->name());
		componentInfo.append(">   ");
	}
	return componentInfo;
}


