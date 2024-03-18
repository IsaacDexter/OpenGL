#ifndef COMPONENT_H
#define COMPONENT_H


class Component
{
public:
	Component() {};
	virtual void OnUpdate(const float deltaTime) {};
	virtual void OnRender() {};
};


#endif // !COMPONENT_H