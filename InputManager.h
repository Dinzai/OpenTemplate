#pragma once
#include "Basic.h"

#include <unordered_set>
#include <vector>


class InputManager
{
public:

    void AddToListeners(IListen* ctrlComponent);

    void MouseDown(sf::Mouse::Button button);

    void MouseUp(sf::Mouse::Button button);

    void KeyDown(sf::Keyboard::Key key);

    void KeyUp(sf::Keyboard::Key key);

    void GetDeltaTime(sf::Time deltaTime);

    void NotifyScene(std::map<Layers, std::vector<IDrawable*>>& renderMap);

    void SendToMailers(IStatus* sender);

    void NotifyEvent();

    std::vector<IListen*> listeners;
    std::unordered_set<sf::Keyboard::Key> keys;
    std::unordered_set<sf::Mouse::Button> buttons;

};