#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "../Manager/Interface.h"

struct CLight : public IApply
{

    CLight(float r, float g, float b, float radius)
    {
        clearColour = sf::Color::Transparent;
        this->radius = radius;
        intensity = 1.0f;
        lightTexture.create(radius * 2, radius * 2);
        colour = sf::Color(r, g, b);
        lightShape.setFillColor(sf::Color(colour));
        lightShape.setOrigin(radius, radius);
        lightShape.setPosition(radius, radius);
        lightShape.setRadius(radius);
        sprite.setTexture(lightTexture.getTexture());
        SetChannel(0);
    }

    void SetPosition(sf::Vector2f position) override
    {
        sprite.setPosition(sf::Vector2f(position.x - radius, position.y - radius));
    }

    void SetValues(sf::Vector2f values) override
    {
    }

    void SetChannel(int channel) override
    {
        this->channel = channel;
    }

    void Draw(sf::RenderTarget &target)
    {
        lightTexture.clear(colour);
        lightTexture.draw(lightShape, sf::BlendAdd);
        lightTexture.display();
        target.draw(sprite, sf::BlendMultiply);
    }
    sf::Color colour;
    float radius;
    float intensity;
    sf::Color clearColour;
    sf::RenderTexture lightTexture;
    sf::CircleShape lightShape;
    sf::Sprite sprite;
};

struct AllLights : public IDrawable
{

    AllLights()
    {
    }

    void SetPosition(int index, sf::Vector2f position)
    {
        lights.at(index)->SetPosition(sf::Vector2f(position.x - lights.at(index)->radius, position.y - lights.at(index)->radius));
    }

    void AddToLights(CLight *temp)
    {
        lights.push_back(temp);
    }

    virtual void Render(sf::RenderTarget &target) override
    {
        for (auto light : lights)
        {
            light->Draw(target);
        }
    }

    std::vector<CLight *> lights;
};