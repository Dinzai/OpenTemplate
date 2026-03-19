#include "GameObjects.h"    


GameObject::GameObject()
{
    player = nullptr;
    playerUI = nullptr;
    allEnemies = nullptr;
    data = nullptr;
}

void GameObject::Init(Assets& asset)
{
    backGround = new BackGround();

    player = new Player(asset);
    player->SetPosition(200, 200);

    playerUI = new THEUI(player->health, player->stamina);
    playerUI->SetRecieverChannel(1); 

    allEnemies = new AllEnemies(asset);
    
    LightingPillar* temp = new LightingPillar(asset, 30);
    temp->SetPosition(0, sf::Vector2f(250, 175));

    LightingPillar* tempTwo = new LightingPillar(asset, 31);
    tempTwo->SetPosition(0, sf::Vector2f(500, 240));

    LightingPillar* tempThree = new LightingPillar(asset, 32);
    tempThree->SetPosition(0, sf::Vector2f(800, 240));

    allLights.push_back(temp);
    allLights.push_back(tempTwo);
    allLights.push_back(tempThree);

    data = new TileData();
    data->MakeTileWorld(asset); 
    data->SetPosition(sf::Vector2f(150, 180));
}

TileData* GameObject::GetData()
{
    return data;
}

Player* GameObject::GetPlayer()
{
    return player;
}

THEUI* GameObject::GetPlayerUI()
{
    return playerUI;
}  

BackGround* GameObject::GetBackground()
{
    return backGround;
}

AllEnemies* GameObject::GetEnemies()
{
    return allEnemies;
}

std::vector<LightingPillar*> GameObject::GetLights()
{
    return allLights;
}

