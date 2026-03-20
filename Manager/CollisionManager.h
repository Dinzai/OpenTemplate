#pragma once
#include "Interface.h"

class CollisionManager
{
public:
    CollisionManager();

    void AddToCollisionManager(IKnock* knocker);

    void RemoveFromCollisionManager(IKnock* knocker);

    void VerifyKnockables();

    void UpdateNormals();

    void CheckCollisions();

    std::vector<IKnock*> knockables;
};
