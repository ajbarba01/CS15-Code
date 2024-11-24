#include "collider.h"


Collider::Collider(GameObject* owner) : Component(owner, ComponentType::T_Collider)
{
	this->isTrigger = false;
	this->layer = CollisionLayer::Default;
	this->manifold = Manifold();
}

void Collider::addCollisionLayer(CollisionLayer layer)
{
	this->collideLayers.push_back(layer);
}

void Collider::update()
{
	this->setPosition();
}

void Collider::setPosition()
{
	sf::Vector2f ownerPosition = this->owner->transform->getPosition();
	this->rect = sf::FloatRect(ownerPosition.x, ownerPosition.y, this->getRect().width, this->getRect().height);
}

Manifold Collider::intersects(Collider* other)
{
	sf::FloatRect rectSelf = this->getRect();
	sf::FloatRect rectOther = other->getRect();

	if (rectSelf.intersects(rectOther))
	{
		this->setManifold(true, other);
	}

	return this->manifold;
}

void Collider::resolveOverlap(Manifold manifold)
{
	Transform* transform = this->owner->transform;
	if (transform->getStatic())
	{
		return;
	}

	sf::FloatRect rectSelf = this->getRect();
	sf::FloatRect rectOther = manifold.other->getRect();

    std::vector<std::pair<float, std::pair<int, int>>> overlaps = {
        {rectOther.left + rectOther.width - rectSelf.left, {1, 0}},
        {rectSelf.left + rectSelf.width - rectOther.left, {-1, 0}},
        {rectOther.top + rectOther.height - rectSelf.top, {0, 1}},
        {rectSelf.top + rectSelf.height - rectOther.top, {0, -1}}
    };

    float smallestOverlap = std::numeric_limits<float>::infinity();
    std::pair<int, int> smallestOverlapDirection = {0, 0};

	for (const auto& overlap : overlaps) {
		if (overlap.first > 0 && overlap.first < smallestOverlap) {
			smallestOverlap = overlap.first;
			smallestOverlapDirection = overlap.second;
		}
	}

	if (smallestOverlap != std::numeric_limits<float>::infinity())
	{
		if (smallestOverlapDirection == std::pair<int, int>(0, 0))
		{
			// HANDLE GRAVITY RESET HERE
		}

		transform->move(sf::Vector2f(smallestOverlap * smallestOverlapDirection.first, smallestOverlap * smallestOverlapDirection.second));
	}
	
}

void Collider::setManifold(bool colliding, Collider* other)
{
	this->manifold.colliding = colliding;
	this->manifold.other = other;
}

void Collider::resetManifold()
{
	this->manifold.colliding = false;
	this->manifold.other = nullptr;
}