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

CController::CController()
{
}

void CController::OnClick(std::unordered_set<sf::Mouse::Button> buttons)
{
}

void CController::OnCheck(std::map<Layers, std::vector<IDrawable*>>& renderMap)
{

}


void CController::OnInput(std::unordered_set<sf::Keyboard::Key> keys)
{
    direction = {0, 0};
    if (keys.find(sf::Keyboard::W) != keys.end())
    {
        direction.y = -1;
    }
    if (keys.find(sf::Keyboard::S) != keys.end())
    {
        direction.y = 1;
    }
    if (keys.find(sf::Keyboard::A) != keys.end())
    {
        direction.x = -1;
    }
    if (keys.find(sf::Keyboard::D) != keys.end())
    {
        direction.x = 1;
    }

    isMoving = (direction.x != 0) || (direction.y != 0);

}

void CController::Update(sf::Time deltaTime)
{
}

Base::Base()
{
}

void Base::SetTexture(Assets &asset, Asset type, int xFrame, int yFrame, float animTime, int startFrame, int endFrame)
{
    CView* viewable = new CView(asset, type, xFrame, yFrame, animTime, startFrame, endFrame);

    viewables.push_back(viewable);
}