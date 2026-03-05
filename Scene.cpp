#include "Scene.h"


void Scene::AddToScene(Layers layer, IDrawable* viewComponent)
{
    renderMap[layer].push_back(viewComponent);
}

void Scene::RemoveFromScene(Layers layer, int index)
{
    renderMap[layer].erase(renderMap[layer].begin() + index);
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