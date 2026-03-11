#include "Loop.h"
#include <iostream>

Loop::Loop() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Souls_Like")
{
    asset = new Assets();
}

void Loop::Play()
{
    Init();
    while (window.isOpen())
    {
        FixedUpdate();
        Update();
        Render();
    }
}

void Loop::Init()
{

    managerLib = ManagerLib();

    player = new Player(*asset);
    player->SetPosition(200, 200);

    ui = new THEUI(player->health, player->stamina);
    managerLib.GetScene().AddToScene(Layers::UI, ui);

    managerLib.GetSignalManager().AddToMailer(player);
    managerLib.GetSignalManager().AddToSubscibed(ui);

    otherTest = new Player(*asset);
    otherTest->SetPosition(500, 500);

    managerLib.GetInputManager().AddToListeners(player);
    managerLib.GetCollisionManager().AddToCollisionManager(player->collision);
    managerLib.GetScene().AddToScene(Layers::ENTITY, player->currentView);
    managerLib.GetScene().AddToCamera(player);

    managerLib.GetCollisionManager().AddToCollisionManager(otherTest->collision);
    managerLib.GetScene().AddToScene(Layers::BACKGROUND, otherTest->currentView);
}

void Loop::FixedUpdate()
{

    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            managerLib.GetInputManager().MouseDown(event.mouseButton.button);
        }

        if (event.type == sf::Event::MouseButtonReleased)
        {
            managerLib.GetInputManager().MouseUp(event.mouseButton.button);
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::H)
            {
                managerLib.GetInputManager().SendToMailers(managerLib.GetSignalManager().senders.at(0));
            }

            managerLib.GetInputManager().KeyDown(event.key.code);
        }

        if (event.type == sf::Event::KeyReleased)
        {
            managerLib.GetInputManager().KeyUp(event.key.code);
        }
    }
    managerLib.GetInputManager().NotifyEvent();
}

void Loop::Update()
{
    deltaTime = mainClock.getElapsedTime();
    managerLib.GetInputManager().GetDeltaTime(deltaTime);
    managerLib.GetInputManager().NotifyScene(managerLib.GetScene().renderMap);
    managerLib.GetCollisionManager().UpdateNormals();
    managerLib.GetCollisionManager().CheckCollisions();
    managerLib.GetSignalManager().Update();
    mainClock.restart();
}

void Loop::Render()
{
    window.clear();
    managerLib.GetScene().CameraFollow(window);
    managerLib.GetScene().RenderAll(window);
    window.display();
}
