#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <limits.h>
#include "../Manager/Interface.h"

struct CollisionResult
{
    bool collided = false;
    sf::Vector2f mtv; // minimum translation vector
};

struct CollisionHelper
{
public:
    CollisionHelper()
    {
        min = std::numeric_limits<float>::max();
        max = std::numeric_limits<float>::lowest();
    }

    void AddTo(float value)
    {
        values.push_back(value);
    }

    void CalculateMinMax()
    {
        if (values.empty())
            return;

        min = std::numeric_limits<float>::max();
        max = std::numeric_limits<float>::lowest();

        for (float value : values)
        {
            if (value < min)
                min = value;

            if (value > max)
                max = value;
        }

        values.clear();
    }

    float GetMax()
    {
        return max;
    }

    float GetMin()
    {
        return min;
    }

private:
    std::vector<float> values;
    float min;
    float max;
};

struct CCollideable : public IKnock
{
public:
    CCollideable();

private:
    float ProjectPointOntoAxis(sf::Vector2f point, sf::Vector2f axis)
    {
        return point.x * axis.x + point.y * axis.y;
    }

    sf::Vector2f Normalize(sf::Vector2f &vector);

    std::vector<sf::Vector2f> GetSpriteVerticies();

    CollisionHelper DotPointsToAxis(sf::Vector2f &axis);

    CollisionResult CollisionDetectionWithResolution(CCollideable *other);

    void ResolveCollision(CCollideable *other);

public:
    void CalculateEdgeNormals();

    void AddTo(sf::Sprite *sprite);

    bool CollisionDetection(IKnock *other);

    virtual void OnCollision(IKnock *other) override;

    virtual void OnUpdateNormals() override;

    bool isColliding;

private:
    std::vector<sf::Vector2f> normals;

    std::vector<sf::Sprite *> ptrToSprites;
};
