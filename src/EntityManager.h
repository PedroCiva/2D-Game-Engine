#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include<vector>

class EntityManager {
private:
	//List of all entities
	inline static std::vector <Entity*> entities;
public:
	void ClearData(); //Destroys everything
	void Update(float deltaTime);
	void Render();
	bool HasNoEntities();
	Entity& AddEntity(std::string entityName,LayerType layer);
	std::vector<Entity*> GetEntities() const;//Returns all entities
	std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;//Returns all entities
	unsigned int GetEntityCount();
	void PrintEntitiesList() const;
	static bool CheckEntityCollisions(Entity* entity);
};


#endif
