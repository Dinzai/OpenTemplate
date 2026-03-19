#pragma once
#include "LightPillar.h"
#include "Player.h"
#include "Enemy.h"
#include "World.h"

class GameObject
{
public:
    GameObject();

    void Init(Assets& asset);

    Player* GetPlayer();
    THEUI* GetPlayerUI();
    AllEnemies* GetEnemies();
    std::vector<LightingPillar*>  GetLights();
    BackGround* GetBackground();

    TileData* GetData();


private:
    BackGround *backGround;
    Player *player;
    THEUI *playerUI;
    AllEnemies *allEnemies;
    std::vector<LightingPillar*> allLights;

    TileData* data;
    

};