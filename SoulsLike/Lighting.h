#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Manager/Interface.h"

struct CLight 
{

    CLight()
    {
        clearColour = sf::Color::Transparent;
        radius = 30;
        intensity = 1.0f;
        lightTexture.create(radius * 2, radius * 2);
        lightShape.setFillColor(sf::Color(0, 255, 0));
        lightShape.setOrigin(radius, radius);
        lightShape.setPosition(radius, radius);
        lightShape.setRadius(radius);      
    }

    void Draw()
    {
        lightTexture.clear(clearColour);      
        lightTexture.draw(lightShape, sf::BlendAdd);
        lightTexture.display();
    }

    float radius;
    float intensity;
    sf::Color clearColour;
    sf::RenderTexture lightTexture;
    sf::CircleShape lightShape;
};

struct AllLights : public IDrawable
{

    AllLights()
    {
        lights.push_back(new CLight());
    }


    virtual void Render(sf::RenderTarget &target) override
    {
        for (auto light : lights)
        {
            light->Draw();
            sf::Sprite sprite(light->lightTexture.getTexture());
            sprite.setPosition(0, 0);
            target.draw(sprite, sf::BlendAdd);
        }
    }

    std::vector<CLight*> lights;
};