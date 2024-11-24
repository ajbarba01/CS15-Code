#pragma once

#include <iostream>
#include <map>
#include <unordered_map>

#include <SFML/Graphics.hpp>


class Input
{
private:
	std::unordered_map<sf::Keyboard::Key, bool> keysPressed;
	std::unordered_map<sf::Keyboard::Key, bool> keysJustPressed;

	std::unordered_map<sf::Mouse::Button, bool> buttonsPressed;
	std::unordered_map<sf::Mouse::Button, bool> buttonsJustPressed;

public:
	Input();

public:
	void update();
	bool isKeyPressed(sf::Keyboard::Key key);
	bool isKeyJustPressed(sf::Keyboard::Key key);

	bool isButtonPressed(sf::Mouse::Button button);
	bool isButtonJustPressed(sf::Mouse::Button button);


};