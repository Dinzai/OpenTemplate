#include "Player.h"

Player::Player(Assets &asset)
{
    SetTexture(asset, PLAYERF, 4, 2, 0.15f, 0, 4); // 0
    SetTexture(asset, PLAYERF, 4, 2, 0.15f, 4, 8);

    SetTexture(asset, PLAYERB, 4, 2, 0.15f, 0, 4); // 2
    SetTexture(asset, PLAYERB, 4, 2, 0.15f, 4, 8);

    SetTexture(asset, PLAYERR, 4, 2, 0.25f, 0, 4); // 4
    SetTexture(asset, PLAYERR, 4, 2, 0.25f, 4, 8);

    SetTexture(asset, PLAYERL, 4, 2, 0.25f, 0, 4); // 6
    SetTexture(asset, PLAYERL, 4, 2, 0.25f, 4, 8);

    // roll
    SetTexture(asset, PLAYERROLLFB, 4, 1, 0.15f, 0, 4); // 8

    SetTexture(asset, PLAYERROLLLR, 4, 2, 0.15f, 0, 4); // L
    SetTexture(asset, PLAYERROLLLR, 4, 2, 0.15f, 4, 8); // R 10
}

void Player::SetCamera(sf::RenderWindow &window)
{
    if (!hasCameraAccess)
    {
        currentView->SetZoom(0.5);
        hasCameraAccess = true;
    }
    currentView->SetView(window, *currentView->texture2D->anim->GetSprite(), offset);
}

void Player::SetPosition(float x, float y)
{
    for (size_t i = 0; i < viewables.size(); i++)
    {
        viewables.at(i)->texture2D->anim->SetPosition(x, y);
        viewables.at(i)->texture2D->anim->SetScale(1, 1);
    }
}

void Player::OnCheck(std::map<Layers, std::vector<IDrawable *>> &renderMap)
{
    if (coolDownTimer > 0 && direction.y == 1 && isStateRoll)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(8));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    else if (direction.y == 1 || (isMovingDown && !isStateWalk))
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(1));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    if (isStateWalk && !isMovingDown && lastDirection.y == 1)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(0));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = false;
    }

    //------------------------------------------------------------------------

    if (coolDownTimer > 0 && direction.y == -1 && isStateRoll)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(8));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    else if (direction.y == -1 || (isMovingUp && !isStateWalk))
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(3));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    if (isStateWalk && !isMovingUp && lastDirection.y == -1)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(2));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = false;
    }
    //-------------------------------------------------
    if (direction.x == 1 && isStateRoll)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(10));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    else if (direction.x == 1 || (isMovingRight && !isStateWalk))
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(5));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    if (isStateWalk && !isMovingRight && lastDirection.x == 1)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(4));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = false;
    }

    //-------------------------------------------------
    if (direction.x == -1 && isStateRoll)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(9));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    else if (direction.x == -1 || (isMovingLeft && !isStateWalk))
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(7));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = true;
    }

    if (isStateWalk && !isMovingLeft && lastDirection.x == -1)
    {
        renderMap[Layers::ENTITY].push_back(viewables.at(6));
        renderMap[Layers::ENTITY].erase(renderMap[Layers::ENTITY].begin() + 0);
        currentView = viewables.at(0);
        isStateWalk = false;
    }
}

void Player::Update(sf::Time deltaTime)
{

    if (initalStateRoll && coolDownIsReady)
    {
        isStateRoll = true;
        rollDuration -= deltaTime.asSeconds();
        speed = 500;
        if (rollDuration <= 0)
        {

            coolDownTimer = 0;
            coolDownIsReady = false;
            initalStateRoll = false;
        }
    }
    else
    {
        isStateRoll = false;
        speed = 200;
        coolDownTimer += deltaTime.asSeconds();
        if (coolDownTimer >= 0.5)
        {
            rollDuration = 0.25;
            coolDownIsReady = true;
            coolDownTimer = 0.5;
        }
    }

    if (direction.x != 0 && direction.y != 0)
    {
        direction = Normalize(direction);
    }

    sf::Vector2f movement(speed * direction.x * deltaTime.asSeconds(),
                          speed * direction.y * deltaTime.asSeconds());

    for (auto view : viewables)
    {
        view->texture2D->anim->Animate();
        view->texture2D->anim->GetSprite()->move(movement);
    }
}
