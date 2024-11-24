#include "spriteWrapper.h"


SpriteWrapper::SpriteWrapper(GameObject* owner, std::string filePath) : Component(owner, ComponentType::T_Sprite)
{
	if (!this->texture.loadFromFile(filePath))
	{
		std::cout << "COULDNT LOAD TEXTURE\n";
		return;
	}
	this->sprite.setTexture(this->texture);
}

void SpriteWrapper::render(sf::RenderWindow* target)
{
	target->draw(this->sprite);
}

void SpriteWrapper::lateUpdate()
{
	this->sprite.setPosition(this->owner->transform->getPosition());
}
