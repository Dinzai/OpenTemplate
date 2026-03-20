#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}

void CollisionManager::AddToCollisionManager(IKnock *knocker)
{
    knockables.push_back(knocker);
}

void CollisionManager::VerifyKnockables()
{
    for(size_t i = 0; i < knockables.size(); i++)
    {
        if(knockables.at(i)->isMarkedForDeath)
        {
            RemoveFromCollisionManager(knockables.at(i));
        }
    }
}

void CollisionManager::RemoveFromCollisionManager(IKnock *knocker)
{
    auto it = std::find(knockables.begin(), knockables.end(), knocker);
    if (it != knockables.end())
    {
        knockables.erase(it);
    }
}

void CollisionManager::UpdateNormals()
{
    for (IKnock *temp : knockables)
    {
        temp->OnUpdateNormals();
    }
}

void CollisionManager::CheckCollisions()
{
    for (size_t i = 0; i < knockables.size(); i++)
    {
        IKnock *tempA = knockables.at(i);

        for (size_t j = i + 1; j < knockables.size(); j++)
        {
            IKnock *tempB = knockables.at(j);

            if (tempA != tempB)
            {
                tempA->OnCollision(tempB);
            }
        }
    }
}
