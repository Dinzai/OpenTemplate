#include "LightPillar.h"

LightingPillar::LightingPillar(Assets& asset)
{
    SetTexture(asset, LIGHTPILLARS, 1, 1, 0.15f, 0, 1); // 0
    lightComponent = new AllLights();
    CLight* temp = new CLight(250, 169, 30, 30);
    lightComponent->AddToLights(temp);
    SetSenderChannel(0);
}

void LightingPillar::SetPosition(int index, sf::Vector2f position)
{
    GetActiveSprite()->setPosition(position);
    lightComponent->SetPosition(index, position);
}

