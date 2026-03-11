#pragma once
#include "../Manager/Interface.h"
#include "Assets.h"
#include "Anim.h"
#include "Collision.h"

struct CTexture
{
    CTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame);

    DINZAI::SpriteSheet *anim;
};

struct CView : public IDrawable
{
    CView();

    CView(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame);

    virtual void Render(sf::RenderTarget &target) override;

    void SetZoom(float zoomValue);

    void SetView(sf::RenderWindow &window, const sf::Sprite &spr, sf::Vector2f shakeOffset = {0, 0});

    // view has a CTextureComponent
    CTexture *texture2D;

    sf::View cameraView;
    sf::View uiView;
    float currentZoom = 1.0f;
};

struct CController : public IListen
{
    CController();

    virtual void OnInput(std::unordered_set<sf::Keyboard::Key> keys) override;

    virtual void OnClick(std::unordered_set<sf::Mouse::Button> buttons) override;

    virtual void OnCheck(std::map<Layers, std::vector<IDrawable *>> &renderMap) override;

    virtual void Update(sf::Time deltaTime);

    sf::Vector2f direction = {0, 0};

    bool isMovingUp = false;
    bool isMovingDown = false;
    bool isMovingLeft = false;
    bool isMovingRight = false;
    
    sf::Vector2f lastDirection = {0, 1};

    bool initalStateRoll = false;
    bool isStateWalk = false;
    bool isStateRoll = false;
    bool isStateAttackDown = false;
    bool isStateAttackUp = false;
    bool isStateAttackLeft = false;
    bool isStateAttackRight = false;
};

// base is the base class for all Entity's in this game
struct Base : public IKnock, IStatus
{

    Base();

    sf::Sprite *GetActiveSprite();

    std::vector<CView *> GetAllSprites();

    void SetTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame);

    sf::Vector2f Normalize(sf::Vector2f& value);

    virtual void OnUpdateNormals() override;
    virtual void OnCollision(IKnock *other) override;

    virtual sf::Vector2f GetPosition() override;
    virtual sf::Vector2f GetValues() override;
    virtual void SetChannel(int channel) override;

    std::vector<CView *> viewables;
    CView *currentView;
    CCollideable *collision;

    float speed = 200;
    bool hasCameraAccess = false;
};
