#pragma once
#include "Interface.h"
#include "Assets.h"
#include "Anim.h"


struct CTexture//Component Texture, uses the animation that holds a sprite
{//that sprite is preallocated in Assets, passed into anim
    CTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame);

    DINZAI::SpriteSheet *anim;
};

struct CView : public IDrawable
{//CView is a component that holds a component texture, and is responsilble
//for being attached to the renderMap
    CView();

    CView(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame);

    virtual void Render(sf::RenderTarget &target) override;

    // view has a CTextureComponent
    CTexture *texture2D;
};

struct CController : public IListen
{//this system can be attached to the inputmanager
    CController();

    virtual void OnInput(std::unordered_set<sf::Keyboard::Key> keys) override;

    virtual void OnClick(std::unordered_set<sf::Mouse::Button> buttons) override;

    virtual void OnCheck(std::map<Layers, std::vector<IDrawable*>>& renderMap) override;

    virtual void Update(sf::Time deltaTime);

    sf::Vector2f direction = {0, 0};
    bool isMoving = false;
    bool isStateWalk = false;
};

//base is the base class for all Entity's in this game
struct Base
{

    Base();

    void SetTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame);

    std::vector<CView*> viewables;

    float speed = 200;

};

