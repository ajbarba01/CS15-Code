#include "component.h"

#include <iostream>


Component::Component(GameObject* owner, ComponentType componentType)
{
	this->owner = owner;
	this->componentType = componentType;
}