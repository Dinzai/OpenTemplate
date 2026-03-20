#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "../Manager/Interface.h"

struct CLight : public IApply
{
    CLight(float r, float g, float b, float radius, int channel)
    {
        this->radius = radius;
        colour = sf::Color(r, g, b);

        int segments = 32;

        lightMesh.setPrimitiveType(sf::TriangleFan);
        lightMesh.resize(segments + 2);

        // center vertex
        lightMesh[0].position = sf::Vector2f(0, 0);
        lightMesh[0].color = sf::Color(colour.r, colour.g, colour.b, 240);

        for (int i = 0; i <= segments; i++)
        {
            float angle = i * 2 * 3.1415926f / segments;

            float x = std::cos(angle) * radius;
            float y = std::sin(angle) * radius;

            lightMesh[i + 1].position = sf::Vector2f(x, y);

            lightMesh[i + 1].color = sf::Color(colour.r, colour.g, colour.b, 0);
        }

        SetRecieverChannel(channel);
    }

    void SetPosition(sf::Vector2f position) override
    {
        this->position = position;
    }

    void SetValues(sf::Vector2f values) override {}

    void SetRecieverChannel(int channel) override
    {
        recieverChannel = channel;
    }

    void Draw(sf::RenderTarget& target)
    {
        sf::RenderStates states;
        states.blendMode = sf::BlendAdd;
        states.transform.translate(position);

        target.draw(lightMesh, states);
    }

    sf::VertexArray lightMesh;
    sf::Vector2f position;
    float radius;
    float intensity = 1.0f;
    sf::Color colour;
};

struct BackGround : public IDrawable
{
    BackGround()
    {
        darkShape.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        darkShape.setScale(5 ,5);
        darkShape.setFillColor(sf::Color(30,30,30));
    }

    virtual void Render(sf::RenderTarget& target) override
    {
        target.draw(darkShape, sf::BlendMultiply);
    }


    sf::RectangleShape darkShape;
};


struct AllLights : public IDrawable
{
    AllLights()
    {
    }

    void SetPosition(int index, sf::Vector2f position)
    {
        lights.at(index)->SetPosition(position);
    }

    void AddToLights(CLight* light)
    {
        lights.push_back(light);
    }

    virtual void Render(sf::RenderTarget& target) override
    {

        for (auto light : lights)
        {
            light->Draw(target);
        }
    }

    std::vector<CLight*> lights;
};