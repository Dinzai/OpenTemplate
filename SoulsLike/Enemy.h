#pragma once
#include "Basic.h"


struct Enemy : public Base
{
    Enemy(Assets& asset);

    virtual sf::Vector2f GetValues() override;

    void SetPosition(float x, float y);

    virtual sf::Vector2f GetPosition() override;

    float health = 100;
    float stamina = 75;

};

struct AllEnemies 
{
    AllEnemies(Assets& asset);

    void AddToEnemies(Assets& asset, int amount);

    std::vector<Enemy*> allSquidEnemies;
    std::vector<THEUI*> allSquidEnemyUI;
};