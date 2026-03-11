#pragma once
#include "Interface.h"

class CollisionManager
{
public:
    CollisionManager();

    void AddToCollisionManager(IKnock* knocker);

    void UpdateNormals();

    void CheckCollisions();

    std::vector<IKnock*> knockables;
};
