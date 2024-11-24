#pragma once

#include <iostream>
#include <SFML/graphics.hpp>

#include "component.h"
#include "gameObject.h"


class SpriteWrapper : public Component
{
private:
	sf::Sprite sprite;
	sf::Texture texture;

public:
	SpriteWrapper(GameObject* owner) : Component(owner, ComponentType::T_Sprite) { };
	SpriteWrapper(GameObject* owner, std::string filePath);

	void setSprite(sf::Sprite sprite) { this->sprite = sprite; }
	void render(sf::RenderWindow* window) override;
	void lateUpdate() override;
};