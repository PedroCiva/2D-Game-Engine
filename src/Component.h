#ifndef COMPONENT_H
#define COMPONENT_H


class Entity;

//Base class from which our components will inherit from
class Component 
{
	
public:
	 Entity* owner;

	//Virtual methods because they will be overrided by each individual component
	virtual ~Component(){}
	virtual void Initialize(){}
	virtual void Update(float deltaTime) {}
	virtual void Render(){}
};
#endif	
