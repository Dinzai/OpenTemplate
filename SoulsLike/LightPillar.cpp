#include "LightPillar.h"

LightingPillar::LightingPillar(Assets& asset, int channel)
{
    SetTexture(asset, LIGHTPILLARS, 1, 1, 0.15f, 0, 1); // 0
    lightComponent = new AllLights();
    CLight* temp = new CLight(230, 126, 30, 100, channel);
    lightComponent->AddToLights(temp);

    collision->isStatic = true;
    SetSenderChannel(channel);
}

void LightingPillar::SetPosition(int index, sf::Vector2f position)
{
    GetActiveSprite()->setPosition(position);
    lightComponent->SetPosition(index, position);

}

