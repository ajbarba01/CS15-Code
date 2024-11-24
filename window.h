#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


class Window
{
private:
	sf::VideoMode videoMode;

	sf::View view;

	const float ASPECT_RATIO = 1.764705882f;
	const float VIEW_DIMENSIONS[2] = {960.0f, 540.0f};

private:
	void resize(int width, int height);

public:
	sf::RenderWindow* window;

	bool windowClosed;

public:
	Window();
	~Window();

	void update(sf::Event ev);
	void prepare();
	void render();

	sf::Vector2f getMousePos();
};