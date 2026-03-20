#include "Scene.h"


void Scene::VerifyDrawables()
{
    for(auto& [layer, objects] : renderMap)
    {
        for(size_t i = 0; i < objects.size(); i++)
        {
            if(objects.at(i)->isMarkedForDeath)
            {
                RemoveFromScene(layer, i);
            }
        }
    }
}

void Scene::AddToScene(Layers layer, IDrawable* viewComponent)
{
    renderMap[layer].push_back(viewComponent);
}

void Scene::AddToCamera(IWatchable* watchable)
{
    watchables.push_back(watchable);
}

void Scene::RemoveFromScene(Layers layer, int index)
{
    renderMap[layer].erase(renderMap[layer].begin() + index);
}

void Scene::CameraFollow(sf::RenderWindow& window)
{
    for(IWatchable* w : watchables)
    {
        w->SetCamera(window);
    }
}

void Scene::RenderAll(sf::RenderTarget& target)
{
    for(auto [layer, objects] : renderMap)
    {
        for(auto obj : objects)
        {
            obj->Render(target);
        }
    }
}