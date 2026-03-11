#pragma once
#include "Basic.h"

struct THEUI : public IDrawable, IApply
{
    THEUI(float maxHealth, float maxStamina);

    virtual void SetPosition(sf::Vector2f position) override;

    virtual void SetValues(sf::Vector2f values) override;

    virtual void SetChannel(int channel) override;
    
    virtual void Render(sf::RenderTarget& target) override;
    
    float sWidth;
    float sHeight;

    float maxStamina;
    float currentStamina;

    float hWidth;
    float hHeight;

    float maxHealth;
    float currentHealth;

    sf::View uiView;

    sf::Vector2f healthPos;
    sf::Vector2f staminaPos;

    sf::RectangleShape healthShape;
    sf::RectangleShape staminaShape;


};

struct Player : public Base, CController, IWatchable
{

    Player(Assets& asset);

    virtual void SetCamera(sf::RenderWindow& window) override;

    virtual sf::Vector2f GetValues() override;

    void SetPosition(float x, float y);

    void Update(sf::Time deltaTime) override;

    void OnCheck(std::map<Layers, std::vector<IDrawable*>>& renderMap)override;
    
    sf::Vector2f offset = {0, 0};

    float coolDownTimer = 0.5f;

    float rollDuration = 0.25f;

    bool coolDownIsReady = true;

    float health = 100;
    float stamina = 75;

};