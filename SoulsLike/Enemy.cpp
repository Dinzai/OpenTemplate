#include "Enemy.h"

Enemy::Enemy(Assets &asset)
{
    SetTexture(asset, SQUIDENEMY, 4, 1, 0.15f, 0, 2);
    SetSenderChannel(2);

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

