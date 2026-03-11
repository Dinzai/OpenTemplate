#pragma once

#include "Interface.h"
#include <vector>
#include <map>


class Scene
{
public:
    

    void AddToScene(Layers layer, IDrawable* viewComponent);
    void AddToCamera(IWatchable* watchable);
    void RemoveFromScene(Layers layer, int index);
    void CameraFollow(sf::RenderWindow& window);
    void RenderAll(sf::RenderTarget& target);


    std::map<Layers, std::vector<IDrawable*>> renderMap;
    std::vector<IWatchable*> watchables;
};