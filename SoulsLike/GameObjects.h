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
    AllEnemies* GetEnemies();
    LightingPillar* GetLight();


private:
    Player *player;
    THEUI *playerUI;
    AllEnemies *allEnemies;
    LightingPillar *light;
};