#include "Enemy.h"

Enemy::Enemy(Assets &asset)
{
    SetTexture(asset, SQUIDENEMY, 4, 1, 0.15f, 0, 2);
    //SetSenderChannel(2);

    values = sf::Vector2f(health, stamina);
}

void Enemy::SetPosition(float x, float y)
{
    for (size_t i = 0; i < viewables.size(); i++)
    {
        viewables.at(i)->texture2D->anim->SetPosition(x, y);
        viewables.at(i)->texture2D->anim->SetScale(1, 1);
    }
}

sf::Vector2f Enemy::GetPosition()
{
    return GetActiveSprite()->getPosition();
}

sf::Vector2f Enemy::GetValues()
{
    return values;
}

AllEnemies::AllEnemies(Assets& asset)
{
    AddToEnemies(asset, 10);
}

void AllEnemies::AddToEnemies(Assets& asset, int amount)
{
    static int posX = 20;
    static int posY = 20;
    static int channel = 2;

    for (int i = 0; i < amount; i++)
    {
        Enemy *e = new Enemy(asset);
        e->SetPosition(posX, posY);

        THEUI* uiTemp = new THEUI(e->health, e->stamina);
        e->SetSenderChannel(channel);
        uiTemp->SetRecieverChannel(channel);
        allSquidEnemyUI.push_back(uiTemp);
        allSquidEnemies.push_back(e);
        
        posX += 30;
        posY += 50;
        channel++;

    }
}
