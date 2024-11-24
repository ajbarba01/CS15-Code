#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "window.h"
#include "objectCollection.h"
#include "input.h"
#include "gameObject.h"
#include "collision.h"


class Game
{
private:
	sf::Event ev;
	bool shouldClose;

	sf::Clock clock;
	float deltaTime;
	float lastTime;
	
	Window window;
	sf::RenderWindow* renderWindow;
	ObjectCollection objCollection;
	Collision collisionSystem;
	Input input;

	GameObject* player;


public:
	~Game();

	void pollEvents();
	void startFrame();

	void awake();
	void earlyUpdate();
	void update();
	void lateUpdate();
	void render();
	void calculateDt();

	float getElapsedTime();
	bool isRunning();


};