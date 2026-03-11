#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <unordered_set>
#include <iostream>

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

enum Asset
{
    PLAYERF,
    PLAYERB,
    PLAYERL,
    PLAYERR,
    PLAYERROLLFB,
    PLAYERROLLLR,
    PLAYERATTACKF,
    PLAYERATTACKB,
    PLAYERATTACKL,
    PLAYERATTACKR,
};

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

class IWatchable
{
public:
    virtual void SetCamera(sf::RenderWindow &window) = 0;
};

class IKnock
{
public:
    virtual void OnUpdateNormals() = 0;
    virtual void OnCollision(IKnock *other) = 0;
};

class IListen
{
public:
    virtual void OnInput(std::unordered_set<sf::Keyboard::Key> keys) = 0;

    virtual void OnClick(std::unordered_set<sf::Mouse::Button> buttons) = 0;

    virtual void OnCheck(std::map<Layers, std::vector<IDrawable *>> &renderMap) = 0;

    virtual void Update(sf::Time deltaTime) = 0;
};

class IStatus
{
public:
    virtual sf::Vector2f GetPosition() = 0;
    virtual sf::Vector2f GetValues() = 0;
    virtual void SetChannel(int channel) = 0;


    sf::Vector2f values;
    int channel = 0;
};

class IApply
{
public:
    virtual void SetPosition(sf::Vector2f position) = 0;
    virtual void SetValues(sf::Vector2f values) = 0;
    virtual void SetChannel(int channel) = 0;

    int channel = 0;
};