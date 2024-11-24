#pragma once

#include <vector>

#include "component.h"
#include "gameObject.h"
#include "enum.h"

class Collider;

class Manifold
{
public:
	bool colliding;
	Collider* other;
};

class Collider : public Component
{
private:
	CollisionLayer layer;
	std::vector<CollisionLayer> collideLayers;
	sf::FloatRect rect;
	Manifold manifold;

public:
	bool isTrigger;

public:
	Collider(GameObject* owner);

	void setLayer(CollisionLayer newLayer) { this->layer = newLayer; }
	void setRect(sf::FloatRect newRect) { this->rect = newRect;  }
	void setTrigger(bool isTrigger) { this->isTrigger = isTrigger; }
	void addCollisionLayer(CollisionLayer layer);
	std::vector<CollisionLayer> getCollideLayers() { return this->collideLayers; }

	sf::FloatRect getRect() { return this->rect; }
	CollisionLayer getLayer() { return this->layer; }
	bool isTriggered() { return this->manifold.colliding; }

	void update() override;
	void setPosition();

	Manifold intersects(Collider* other);
	void resolveOverlap(Manifold other);
	void setManifold(bool colliding, Collider* other);
	void resetManifold();
};

