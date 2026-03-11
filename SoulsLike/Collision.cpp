#include "Collision.h"

CCollideable::CCollideable()
{
}

void CCollideable::AddTo(sf::Sprite *sprite)
{
    ptrToSprites.push_back(sprite);
}

sf::Vector2f CCollideable::Normalize(sf::Vector2f &vector)
{
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);

    if (magnitude == 0)
    {
        return vector;
    }

    return vector / magnitude;
}

std::vector<sf::Vector2f> CCollideable::GetSpriteVerticies()
{
    std::vector<sf::Vector2f> vertices;

    sf::FloatRect bounds = ptrToSprites.at(0)->getGlobalBounds();
    sf::Transform transform = ptrToSprites.at(0)->getTransform();

    vertices.push_back(transform.transformPoint(0.f, 0.f));
    vertices.push_back(transform.transformPoint(bounds.width, 0.f));
    vertices.push_back(transform.transformPoint(bounds.width, bounds.height));
    vertices.push_back(transform.transformPoint(0.f, bounds.height));

    return vertices;
}

void CCollideable::CalculateEdgeNormals()
{
    normals.clear();

    auto verticies = GetSpriteVerticies();

    for (size_t i = 0; i < verticies.size(); i++)
    {
        sf::Vector2f point = verticies[i];
        sf::Vector2f nextPoint = verticies[(i + 1) % verticies.size()];

        sf::Vector2f edge = sf::Vector2f(nextPoint.x - point.x, nextPoint.y - point.y);

        sf::Vector2f aNormal = sf::Vector2f(-edge.y, edge.x);

        sf::Vector2f normal = Normalize(aNormal);

        normals.push_back(normal);
    }
}

CollisionHelper CCollideable::DotPointsToAxis(sf::Vector2f &axis)
{
    CollisionHelper contain = CollisionHelper();
    auto verticies = GetSpriteVerticies();

    for (sf::Vector2f point : verticies)
    {
        float dot = point.x * axis.x + point.y * axis.y;
        contain.AddTo(dot);
    }

    contain.CalculateMinMax();

    return contain;
}

bool CCollideable::CollisionDetection(IKnock *kOther)
{
    CCollideable *other = dynamic_cast<CCollideable *>(kOther);

    if (!other)
    {
        std::cout << "no" << '\n';
        return false;
    }

    std::vector<sf::Vector2f> axies;
    for (sf::Vector2f normal : normals)
    {
        axies.push_back(normal);
    }

    for (sf::Vector2f normal : other->normals)
    {
        axies.push_back(normal);
    }

    for (sf::Vector2f axis : axies)
    {
        CollisionHelper one = DotPointsToAxis(axis);
        CollisionHelper two = other->DotPointsToAxis(axis);

        if (one.GetMax() < two.GetMin())
        {
            this->isColliding = false;
            other->isColliding = false;
            return false;
        }

        if (two.GetMax() < one.GetMin())
        {
            this->isColliding = false;
            other->isColliding = false;
            return false;
        }
    }

    this->isColliding = true;
    other->isColliding = true;
    return true;
}

CollisionResult CCollideable::CollisionDetectionWithResolution(CCollideable *other)
{
    CollisionResult result;

    float smallestOverlap = INFINITY;
    sf::Vector2f smallestAxis;

    std::vector<sf::Vector2f> axes;

    for (auto normal : normals)
        axes.push_back(normal);

    for (auto normal : other->normals)
        axes.push_back(normal);

    for (auto axis : axes)
    {
        CollisionHelper a = DotPointsToAxis(axis);
        CollisionHelper b = other->DotPointsToAxis(axis);

        float overlap = std::min(a.GetMax(), b.GetMax()) -
                        std::max(a.GetMin(), b.GetMin());

        if (overlap < 0)
        {
            result.collided = false;
            return result;
        }

        if (overlap < smallestOverlap)
        {
            smallestOverlap = overlap;

            sf::Vector2f d = ptrToSprites.at(0)->getPosition() -
                             other->ptrToSprites.at(0)->getPosition();

            if ((d.x * axis.x + d.y * axis.y) < 0)
                smallestAxis = -axis;
            else
                smallestAxis = axis;
        }
    }

    result.collided = true;

    result.mtv = smallestAxis * smallestOverlap;

    return result;
}

void CCollideable::ResolveCollision(CCollideable *other)
{
    auto result = CollisionDetectionWithResolution(other);

    if (!result.collided)
        return;
/*
    for (sf::Sprite *spr : ptrToSprites)
    {
        spr->move(result.mtv * 0.5f);
    }
    */

    for (sf::Sprite *spr : other->ptrToSprites)
    {
        spr->move(-result.mtv * 0.5f);
    }
    
}

void CCollideable::OnUpdateNormals()
{
    CalculateEdgeNormals();
}

void CCollideable::OnCollision(IKnock *other)
{
    CCollideable *collider = dynamic_cast<CCollideable *>(other);

    if (!collider)
        return;

    ResolveCollision(collider);
}
/*
void CCollideable::OnCollision(IKnock *other)
{
    if (CollisionDetection(other))
    {
        std::cout << "yo" << '\n';
        ptrToSprite->move(200, 50);
    }
}
*/
