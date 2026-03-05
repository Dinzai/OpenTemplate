#pragma once

#include "Interface.h"
#include <vector>
#include <map>


class Scene
{
public:
    

    void AddToScene(Layers layer, IDrawable* viewComponent);
    void RemoveFromScene(Layers layer, int index);
    void RenderAll(sf::RenderTarget& target);


    std::map<Layers, std::vector<IDrawable*>> renderMap;

};