#include "window.h"

#include <iostream>


Window::Window()
{
	this->windowClosed = false;
	this->videoMode.width = 1500;
	this->videoMode.height = 800;
	this->window = new sf::RenderWindow(this->videoMode, "2D Game Engine", sf::Style::Close | sf::Style::Titlebar | sf::Style::Resize);
	this->view = sf::View::View(sf::FloatRect(0.0f, 0.0f, this->VIEW_DIMENSIONS[0], this->VIEW_DIMENSIONS[1]));

	this->resize(this->videoMode.width, this->videoMode.height);
}

Window::~Window()
{
	std::cout << "DELETING WINDOW\n";
	this->window->close();
	delete this->window;
}

void Window::resize(int width, int height)
{
	float viewWidth;
	float viewHeight;

	float floatWidth = static_cast<float>(width);
	float floatHeight = static_cast<float>(height);

	// Limited by width
	if (height * this->ASPECT_RATIO > width)
	{
		viewWidth = floatWidth;
		viewHeight = floatHeight / this->ASPECT_RATIO;
	}

	// Limited by height
	else
	{
		viewWidth = floatHeight * this->ASPECT_RATIO;
		viewHeight = floatHeight;
	}

	this->view.setViewport(sf::FloatRect((width - viewWidth) / (2 * width), (height - viewHeight) / (2 * height), viewWidth / width, viewHeight / height));

}

void Window::update(sf::Event ev)
{
	while (window->pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->windowClosed = true;

		case sf::Event::Resized:
			this->resize(ev.size.width, ev.size.height);
		}
	}
}

void Window::prepare()
{
	this->window->clear(sf::Color::Black);
	this->window->setView(this->view);

	sf::RectangleShape bg(this->view.getSize());
	bg.setFillColor(sf::Color(50, 50, 50, 255));
	bg.setPosition(0, 0);

	this->window->draw(bg);
}

void Window::render()
{
	this->window->display();
}

sf::Vector2f Window::getMousePos()
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	return this->window->mapPixelToCoords(mousePos);
}
