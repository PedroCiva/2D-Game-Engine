#ifndef COMPONENT_H
#define COMPONENT_H

class Entity;

//Base class from which our components will inherit from
class Component 
{
	
public:
	 Entity* gameObject;

	//Virtual methods because they will be overrided by each individual component
	virtual ~Component(){}

	/// <summary>
	/// Initialize method is called once as soon as the component is added to an Entity
	/// </summary>
	virtual void Initialize(){}

	/// <summary>
	/// Start method is called once before the Update method and after Initialize
	/// </summary>
	virtual void Start(){}

	virtual void Update(float deltaTime) {}
	virtual void Render(){}
};
#endif	
