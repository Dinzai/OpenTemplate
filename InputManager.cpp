#include "InputManager.h"

void InputManager::AddToListeners(IListen *ctrlComponent)
{
    listeners.push_back(ctrlComponent);
}

void InputManager::MouseDown(sf::Mouse::Button button)
{
    buttons.insert(button);
}

void InputManager::MouseUp(sf::Mouse::Button button)
{
    buttons.erase(button);
}

void InputManager::KeyDown(sf::Keyboard::Key key)
{

    keys.insert(key);
}

void InputManager::KeyUp(sf::Keyboard::Key key)
{
    keys.erase(key);
}

void InputManager::GetDeltaTime(sf::Time deltaTime)
{
    for (auto l : listeners)
    {
        l->Update(deltaTime);
    }
}

void InputManager::NotifyScene(std::map<Layers, std::vector<IDrawable*>>& renderMap)
{
    for (auto l : listeners)
    {
        l->OnCheck(renderMap);
    }
}

void InputManager::SendToMailers(IStatus* sender)
{
    sender->values.x = 20;
}

void InputManager::NotifyEvent()
{
    for (auto l : listeners)
    {
        l->OnInput(keys);
        l->OnClick(buttons);
    }

}