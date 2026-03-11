#include "Basic.h"

CTexture::CTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame)
{
    anim = new DINZAI::SpriteSheet(asset.PassTexture(type), xFrame, yFrame, animTime, startFrame, endFrame);
}

CView::CView(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame)
{
    texture2D = new CTexture(asset, type, xFrame, yFrame, animTime, startFrame, endFrame);
}

void CView::Render(sf::RenderTarget &target)
{
    target.draw(*texture2D->anim->GetSprite());
}

void CView::SetZoom(float zoomValue)
{
    currentZoom = zoomValue;
    cameraView.setSize(WINDOW_WIDTH * currentZoom, WINDOW_HEIGHT * currentZoom);
}

void CView::SetView(sf::RenderWindow &window, const sf::Sprite &spr, sf::Vector2f shakeOffset)
{
    float windowAspect = static_cast<float>(window.getSize().x) / window.getSize().y;
    float viewAspect = WINDOW_WIDTH / WINDOW_HEIGHT;

    if (windowAspect > viewAspect)
    {
        float newWidth = WINDOW_HEIGHT * windowAspect * currentZoom;
        cameraView.setSize(newWidth, WINDOW_HEIGHT * currentZoom);
    }
    else
    {
        float newHeight = WINDOW_WIDTH / windowAspect * currentZoom;
        cameraView.setSize(WINDOW_WIDTH * currentZoom, newHeight);
    }

    cameraView.setCenter(spr.getPosition() + shakeOffset);

    // window.setView(uiView);
    window.setView(cameraView);
}

CController::CController()
{
}

void CController::OnClick(std::unordered_set<sf::Mouse::Button> buttons)
{
    isStateAttackDown = false;
    isStateAttackUp = false;
    isStateAttackLeft = false;
    isStateAttackRight = false;
    if (buttons.find(sf::Mouse::Button::Left) != buttons.end())
    {
        if (lastDirection.y == 1)
        {
            isStateAttackDown = true;
        }
        if (lastDirection.y == -1)
        {
            isStateAttackUp = true;
        }
        if (lastDirection.x == 1)
        {
            isStateAttackRight = true;
        }
        if (lastDirection.x == -1)
        {
            isStateAttackLeft = true;
        }
    }
}

void CController::OnCheck(std::map<Layers, std::vector<IDrawable *>> &renderMap)
{
}

void CController::OnInput(std::unordered_set<sf::Keyboard::Key> keys)
{
    direction = {0, 0};
    initalStateRoll = false;

    if (keys.find(sf::Keyboard::W) != keys.end())
    {
        direction.y = -1;
        lastDirection = direction;
    }
    if (keys.find(sf::Keyboard::S) != keys.end())
    {
        direction.y = 1;
        lastDirection = direction;
    }
    if (keys.find(sf::Keyboard::A) != keys.end())
    {
        direction.x = -1;
        lastDirection = direction;
    }
    if (keys.find(sf::Keyboard::D) != keys.end())
    {
        direction.x = 1;
        lastDirection = direction;
    }
    if (keys.find(sf::Keyboard::Space) != keys.end())
    {
        initalStateRoll = true;
    }

    isMovingDown = direction.y == 1;
    isMovingUp = direction.y == -1;

    isMovingLeft = direction.x == -1;
    isMovingRight = direction.x == 1;
}

void CController::Update(sf::Time deltaTime)
{
}

Base::Base()
{
    collision = new CCollideable();
}

void Base::SetTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame)
{
    CView *viewable = new CView(asset, type, xFrame, yFrame, animTime, startFrame, endFrame);

    viewables.push_back(viewable);
    currentView = viewables.at(0);

    collision->AddTo(viewable->texture2D->anim->GetSprite());
}

sf::Vector2f Base::Normalize(sf::Vector2f &value)
{
    float distanceSQR = (value.x * value.x + value.y * value.y);
    float mag = std::sqrt(distanceSQR);
    float newX = value.x / mag;
    float newY = value.y / mag;
    return sf::Vector2f(newX, newY);
}

sf::Sprite *Base::GetActiveSprite()
{
    return currentView->texture2D->anim->GetSprite();
}

std::vector<CView *> Base::GetAllSprites()
{
    return viewables;
}

void Base::OnUpdateNormals()
{
    collision->OnUpdateNormals();
}

void Base::OnCollision(IKnock *other)
{
    collision->OnCollision(other);
}

sf::Vector2f Base::GetPosition()
{
    return currentView->texture2D->anim->GetSprite()->getPosition();
}

void Base::SetChannel(int channel)
{
    this->channel = channel;
}

sf::Vector2f Base::GetValues()
{
    return sf::Vector2f(0, 0);
}