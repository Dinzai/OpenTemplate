#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>

//Fill in your asset types here
enum Asset
{
    PLAYER,
    UI,
    WHATEVER,
    
};
//this is for the Scene, drawable system
enum Layers
{
    BACKGROUND,
    ENTITY,
    UI,
};

class IPreloadable
{
public:
    virtual void Preload() = 0;
};

class IDrawable
{
public:
    virtual void Render(sf::RenderTarget &target) = 0;
};

class IListen
{
public:
    virtual void OnInput(std::unordered_set<sf::Keyboard::Key> keys) = 0;

    virtual void OnClick(std::unordered_set<sf::Mouse::Button> buttons) = 0;

    virtual void OnCheck(std::map<Layers, std::vector<IDrawable*>>& renderMap) = 0;

};

