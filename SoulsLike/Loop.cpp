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

void Loop::AddToCollisionManager()
{
    managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetLight()->collision);
    managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetEnemy()->collision);
    managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetPlayer()->collision);
}

void Loop::AddToInputManager()
{
    managerLib.GetInputManager().AddToListeners(gameObjects.GetPlayer());
}

void Loop::AddToScene()
{
    managerLib.GetScene().AddToScene(Layers::ENTITY, gameObjects.GetLight()->currentView);
    managerLib.GetScene().AddToScene(Layers::LIGHTS, gameObjects.GetLight()->lightComponent);
    managerLib.GetScene().AddToScene(Layers::ENTITY, gameObjects.GetEnemy()->currentView);
    managerLib.GetScene().AddToScene(Layers::UI, gameObjects.GetPlayerUI());
    managerLib.GetScene().AddToScene(Layers::UI, gameObjects.GetEnemyUI());
    managerLib.GetScene().AddToScene(Layers::PLAYER, gameObjects.GetPlayer()->currentView);
    managerLib.GetScene().AddToCamera(gameObjects.GetPlayer());
}

void Loop::AddToSignalManager()
{
    managerLib.GetSignalManager().AddToMailer(gameObjects.GetLight());
    managerLib.GetSignalManager().AddToSubscibed(gameObjects.GetLight()->lightComponent->lights.at(0));

    managerLib.GetSignalManager().AddToMailer(gameObjects.GetPlayer());
    managerLib.GetSignalManager().AddToSubscibed(gameObjects.GetPlayerUI());

    managerLib.GetSignalManager().AddToMailer(gameObjects.GetEnemy());
    managerLib.GetSignalManager().AddToSubscibed(gameObjects.GetEnemyUI());
}

void Loop::Init()
{
    managerLib = ManagerLib();
    gameObjects = GameObject();
    gameObjects.Init(*asset);

    AddToInputManager();
    AddToCollisionManager();
    AddToSignalManager();
    AddToScene();
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
    // SendToMailers needs to loop through all senders, and recivers, to check for damage messeges
    managerLib.GetInputManager().SendToMailers(managerLib.GetSignalManager().senders.at(1), managerLib.GetSignalManager().senders.at(2));
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
