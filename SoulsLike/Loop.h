#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Manager.h"
#include "GameObjects.h"


class Loop
{
public:
    Loop();

    void Play();

protected:
    void Init();

    void FixedUpdate();

    void Update();

    void Render();

    void AddToScene();

    void AddToInputManager();

    void AddToSignalManager();

    void AddToCollisionManager();

    GameObject gameObjects;

    ManagerLib managerLib;
    
    Assets* asset;

    sf::Time deltaTime;
    sf::Clock mainClock;

    sf::Event event;
    sf::RenderWindow window;
    sf::ContextSettings settings;
};