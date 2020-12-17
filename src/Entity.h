#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <map>
#include "Constants.h"
#include "EntityManager.h"
#include "Component.h"
#include <typeinfo>

class EntityManager;
class Component;

class Entity {
private:
	EntityManager& manager;
	bool isActive;
	std::vector<Component*> components; //List of components in this entity
	std::map <const std::type_info*, Component*> componentTypeMap;// Contais information about the components in this entity

public:
	std::string name;
	LayerType layer;
	Entity(EntityManager& manager); //Create a new entity with or without specifying a name
	Entity(EntityManager& manager, std::string name,LayerType layer);
	void Update(float deltaTime);
	void Render();
	void Destroy();
	std::string GetComponentsName() const;
	bool IsActive() const; //Getter for isActive, allows for if(Entity.IsActive()==true) etc...

	template <typename T, typename... TArgs> //Add component method template.
	T& AddComponent(TArgs&&... args) { //TArgs have a double ampersand because the values passed are rvalues,roughly meaning we just wanna use them once 
		T* newComponent(new T(std::forward<TArgs>(args)...)); //Creating new component of type T and managing the args to handle our rvalues parameters with std::forward
		newComponent->owner = this;//component owner = this
		components.emplace_back(newComponent); //Adding the component to this list of components
		newComponent->Initialize(); // Initializing component
		componentTypeMap[&typeid(*newComponent)] = newComponent; //Adding key and value pair (component info and component) to our dictionary
		return *newComponent; 
	}

	template <typename T>
	T* GetComponent() {
		return static_cast<T*>(componentTypeMap[&typeid(T)]); //Returns component from typeID dictionary key
	}

	template <typename T>
	bool HasComponent() const {
		return componentTypeMap.count(&typeid(T));
	}
};
#endif 

