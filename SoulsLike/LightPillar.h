#pragma once 
#include "Lighting.h"
#include "Basic.h"


struct LightingPillar : public Base
{
    LightingPillar(Assets& asset);
    void SetPosition(int index, sf::Vector2f position);
    
    AllLights* lightComponent;
};
