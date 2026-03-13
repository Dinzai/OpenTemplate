#pragma once
#include "LightPillar.h"
#include "Player.h"
#include "Enemy.h"

class GameObject
{
public:
    GameObject();

    void Init(Assets& asset);

    Player* GetPlayer();
    THEUI* GetPlayerUI();
    Enemy* GetEnemy();
    THEUI* GetEnemyUI();
    LightingPillar* GetLight();


private:
    Player *player;
    THEUI *playerUI;

    Enemy *enemy;
    THEUI *enemyUI;

    LightingPillar *light;
};