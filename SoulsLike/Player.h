#pragma once
#include "Basic.h"

struct Player : public Base, CController, IWatchable
{

    Player(Assets& asset);

    virtual void SetCamera(sf::RenderWindow& window) override;

    virtual sf::Vector2f GetValues() override;

    void SetPosition(float x, float y);

    void Update(sf::Time deltaTime) override;

    void OnCheck(std::map<Layers, std::vector<IDrawable*>>& renderMap)override;

    void OnDamage(IStatus* damager, IStatus* damagee) override;
    
    sf::Vector2f offset = {0, 0};

    float coolDownTimer = 0.5f;

    float rollDuration = 0.25f;

    float attackDuration = 0.25f;

    bool coolDownIsReady = true;

    bool canDamage = false;

    float health = 100;
    float stamina = 75;


    int startFrame = 0;
    int limitFrame = 4;

};