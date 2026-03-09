#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Scene.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "Player.h"

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

    Player* player;
    Player* otherTest;
    
    Assets* asset;
    Scene scene;
    InputManager manager; 
    CollisionManager collisionManager;

    sf::Time deltaTime;
    sf::Clock mainClock;

    sf::Event event;
    sf::RenderWindow window;
    sf::ContextSettings settings;
};