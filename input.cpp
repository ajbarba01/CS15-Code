
#include "input.h"

Input::Input()
{
    for (int key = sf::Keyboard::A; key < sf::Keyboard::KeyCount; ++key) {
        this->keysPressed[static_cast<sf::Keyboard::Key>(key)] = false;
        this->keysJustPressed[static_cast<sf::Keyboard::Key>(key)] = false;
    }

    for (int button = sf::Mouse::Left; button < sf::Mouse::Middle; ++button) {
        this->buttonsPressed[static_cast<sf::Mouse::Button>(button)] = false;
        this->buttonsJustPressed[static_cast<sf::Mouse::Button>(button)] = false;
    }
}


void Input::update()
{
    for (const auto& pair : this->keysPressed) 
    {
        sf::Keyboard::Key key = pair.first;
        bool state = pair.second;
        bool pressed = sf::Keyboard::isKeyPressed(key);

        this->keysJustPressed[key] = !state && pressed;
        this->keysPressed[key] = pressed;
    }

    for (const auto& pair : this->buttonsPressed)
    {
        sf::Mouse::Button button = pair.first;
        bool state = pair.second;
        bool pressed = sf::Mouse::isButtonPressed(button);

        this->buttonsJustPressed[button] = !state && pressed;
        this->buttonsPressed[button] = pressed;
    }
}

bool Input::isKeyPressed(sf::Keyboard::Key key)
{
    return this->keysPressed[key];
}

bool Input::isKeyJustPressed(sf::Keyboard::Key key)
{
    return this->keysJustPressed[key];
}

bool Input::isButtonPressed(sf::Mouse::Button button)
{
    return this->buttonsPressed[button];
}

bool Input::isButtonJustPressed(sf::Mouse::Button button)
{
    return this->buttonsJustPressed[button];
}

