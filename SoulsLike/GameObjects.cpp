#include "GameObjects.h"    


GameObject::GameObject()
{
    player = nullptr;
    playerUI = nullptr;
    allEnemies = nullptr;
    light = nullptr;
}

void GameObject::Init(Assets& asset)
{
    player = new Player(asset);
    player->SetPosition(200, 200);

    playerUI = new THEUI(player->health, player->stamina);
    playerUI->SetRecieverChannel(1); 

    allEnemies = new AllEnemies(asset);

    light = new LightingPillar(asset);
    light->SetPosition(0, sf::Vector2f(200, 200));
}

Player* GameObject::GetPlayer()
{
    return player;
}

THEUI* GameObject::GetPlayerUI()
{
    return playerUI;
}   

AllEnemies* GameObject::GetEnemies()
{
    return allEnemies;
}

LightingPillar* GameObject::GetLight()
{
    return light;
}

