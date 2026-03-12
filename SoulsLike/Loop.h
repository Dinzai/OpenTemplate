#pragma once
#include <SFML/Graphics.hpp>
#include "Assets.h"
#include "Manager.h"
#include "LightPillar.h"
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
    THEUI* ui;
    LightingPillar* light;

    ManagerLib managerLib;
    
    Assets* asset;

    sf::Time deltaTime;
    sf::Clock mainClock;

    sf::Event event;
    sf::RenderWindow window;
    sf::ContextSettings settings;
};