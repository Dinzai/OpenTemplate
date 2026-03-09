#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

void CollisionManager::AddToCollisionManager(IKnock* knocker)
{
    knockables.push_back(knocker);
}

void CollisionManager::UpdateNormals()
{
    for(IKnock* temp : knockables)
    {
        temp->OnUpdateNormals();
    }
}

void CollisionManager::CheckCollisions()
{
    for(size_t i = 0; i < knockables.size(); i++)
    {
        IKnock* tempA = knockables.at(i);
        for (size_t j = i + 1; j < knockables.size(); j++)
        {
            IKnock* tempB = knockables.at(j);
            if(tempA != tempB)
            {
                tempA->OnCollision(tempB);
                tempB->OnCollision(tempA);
            }
        }
        
    }    
}
