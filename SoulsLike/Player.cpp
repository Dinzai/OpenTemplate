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

    SetTexture(asset, PLAYERATTACKF, 4, 1, 0.15f, 0, 4); // 11
    SetTexture(asset, PLAYERATTACKB, 4, 1, 0.15f, 0, 4); // 12
    SetTexture(asset, PLAYERATTACKR, 4, 1, 0.15f, 0, 4); // 13
    SetTexture(asset, PLAYERATTACKL, 4, 1, 0.15f, 0, 4); // 14

    SetSenderChannel(1);

    values = sf::Vector2f(health, stamina);
    sentDamage = 0.1f;
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

void Player::OnDamage(IStatus *damager, IStatus *damagee)
{
    Base *temp = dynamic_cast<Base *>(damagee);
    if (!temp)
    {
        return;
    }

    if (canDamage && collision->CollisionDetection(temp->collision))
    {

        if (damagee->senderChannel >= 2)
        {

            damagee->values.x -= sentDamage;
            canDamage = false;
        }
    }
}

void Player::OnCheck(std::map<Layers, std::vector<IDrawable *>> &renderMap)
{

    if (coolDownTimer == 0.5 && direction.y == 1 && isStateRoll)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(8));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }

    else if (direction.y == 1 || (isMovingDown && !isStateWalk))
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(1));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }
    if (coolDownTimer == 0.5 && isStateAttackDown)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(11));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = true;
        isStateWalk = true;
    }
    else if (!isStateAttackDown && isStateWalk && !isMovingDown && lastDirection.y == 1)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(0));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = false;
    }

    //------------------------------------------------------------------------

    if (coolDownTimer == 0.5 && direction.y == -1 && isStateRoll)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(8));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }

    else if (direction.y == -1 || (isMovingUp && !isStateWalk))
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(3));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }
    if (coolDownTimer == 0.5 && isStateAttackUp)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(12));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = true;
        isStateWalk = true;
    }
    else if (isStateWalk && !isMovingUp && lastDirection.y == -1)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(2));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = false;
    }
    //-------------------------------------------------
    if (coolDownTimer == 0.5 && direction.x == 1 && isStateRoll)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(10));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }

    else if (direction.x == 1 || (isMovingRight && !isStateWalk))
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(5));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }

    if (coolDownTimer == 0.5 && isStateAttackRight)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(13));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = true;
        isStateWalk = true;
    }

    else if (isStateWalk && !isMovingRight && lastDirection.x == 1)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(4));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = false;
    }

    //-------------------------------------------------
    if (coolDownTimer == 0.5 && direction.x == -1 && isStateRoll)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(9));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }

    else if (direction.x == -1 || (isMovingLeft && !isStateWalk))
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(7));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = true;
    }

    if (coolDownTimer == 0.5 && isStateAttackLeft)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(14));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = true;
        isStateWalk = true;
    }

    else if (isStateWalk && !isMovingLeft && lastDirection.x == -1)
    {
        renderMap[Layers::PLAYER].push_back(viewables.at(6));
        renderMap[Layers::PLAYER].erase(renderMap[Layers::PLAYER].begin() + 0);
        currentView = viewables.at(0);
        canDamage = false;
        isStateWalk = false;
    }
}

void Player::Update(sf::Time deltaTime)
{

    if (initalStateRoll && coolDownIsReady)
    {
        isStateRoll = true;
        rollDuration -= deltaTime.asSeconds();
        if (values.y > 0)
        {
            values.y -= 0.1f;
        }
        speed = 500;
        if (rollDuration <= 0)
        {
            values.y = 0;
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
        if (values.y < 75)
        {
            values.y += 0.1f;
        }
        if (coolDownTimer >= 0.5)
        {
            rollDuration = 0.25;
            values.y = 75;
            coolDownIsReady = true;
            coolDownTimer = 0.5;
        }
    }
    //-----------

    if (canDamage)
    {
        values.y = 0.0f;
    }

    if (initialStateAttack && coolDownIsReady)
    {
        attackDuration -= deltaTime.asSeconds();

        if (lastDirection.y == 1)
        {
            isStateAttackDown = true;
        }
        else if (lastDirection.y == -1)
        {
            isStateAttackUp = true;
        }
        else if (lastDirection.x == 1)
        {
            isStateAttackRight = true;
        }
        else if (lastDirection.x == -1)
        {
            isStateAttackLeft = true;
        }

        if (attackDuration <= 0)
        {
            coolDownTimer = 0;
            coolDownIsReady = false;
            initialStateAttack = false;
        }
    }
    else
    {
        initialStateAttack = false;
        coolDownTimer += deltaTime.asSeconds();
        if (coolDownTimer >= 0.5)
        {
            attackDuration = 0.25;
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

sf::Vector2f Player::GetValues()
{
    return values;
}
