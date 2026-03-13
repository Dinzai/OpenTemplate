#include "GameObjects.h"    


GameObject::GameObject()
{
    player = nullptr;
    playerUI = nullptr;
    enemy = nullptr;
    enemyUI = nullptr;
    light = nullptr;
}

void GameObject::Init(Assets& asset)
{
    player = new Player(asset);
    player->SetPosition(200, 200);

    enemy = new Enemy(asset);
    enemy->SetPosition(400, 400);

    playerUI = new THEUI(player->health, player->stamina);
    playerUI->SetRecieverChannel(1); 

    enemyUI = new THEUI(enemy->health, enemy->stamina);
    enemyUI->SetRecieverChannel(2); 

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

Enemy* GameObject::GetEnemy()
{
    return enemy;
}
THEUI* GameObject::GetEnemyUI()
{
    return enemyUI;
}

LightingPillar* GameObject::GetLight()
{
    return light;
}

