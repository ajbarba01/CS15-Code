#include "gameObject.h"
#include "spriteWrapper.h"


int GameObject::nextID = 1;

GameObject::GameObject()
{
	this->gameID = nextID++;
	this->isQueuedForRemoval = false;
	this->transform = new Transform(this);

	// this->transform gets deleted via this->components in the dtor
	this->addComponent(this->transform);
}

GameObject::~GameObject()
{
	std::cout << "DELETING: " << this->getID() << "\n";
	for (const auto& pair : this->components)
	{
		std::cout << "DELEETING COMPONENT: " << pair.second->componentType << "\n";
		delete pair.second;
	}
}

void GameObject::awake()
{
	for (const auto& pair : this->components)
	{
		pair.second->awake();
	}
}

void GameObject::start()
{
	for (const auto& pair : this->components)
	{
		pair.second->start();
	}
}

void GameObject::earlyUpdate()
{
	for (const auto& pair : this->components)
	{
		pair.second->earlyUpdate();
	}
}

void GameObject::update()
{
	for (const auto& pair : this->components)
	{
		pair.second->update();
	}
}

void GameObject::lateUpdate()
{
	for (const auto& pair : this->components)
	{
		pair.second->lateUpdate();
	}
}

void GameObject::render(sf::RenderWindow* window)
{
	if (this->hasComponent(ComponentType::T_Sprite))
	{
		this->getComponent(ComponentType::T_Sprite)->render(window);
	}
}

void GameObject::addComponent(Component* component)
{
	this->components[component->componentType] = component;
}

void GameObject::removeComponent(ComponentType componentType)
{
	this->components.erase(componentType);
}

Component* GameObject::getComponent(ComponentType componentType)
{
	return this->components[componentType];
}

bool GameObject::hasComponent(ComponentType componentType)
{
	return this->components.count(componentType) != 0;
}

void GameObject::queueForRemoval()
{
	this->isQueuedForRemoval = true;
}

