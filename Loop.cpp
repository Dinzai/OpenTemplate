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
    scene = Scene();
    manager = InputManager();
    collisionManager = CollisionManager();

    player = new Player(*asset);
    player->SetPosition(200, 200);

    otherTest = new Player(*asset);
    otherTest->SetPosition(500, 500);

    manager.AddToListeners(player);
    collisionManager.AddToCollisionManager(player->collision);
    scene.AddToScene(Layers::ENTITY, player->currentView);    
    scene.AddToCamera(player);

    collisionManager.AddToCollisionManager(otherTest->collision);
    scene.AddToScene(Layers::UI, otherTest->currentView); 

}

void Loop::FixedUpdate()
{
    
    manager.NotifyEvent();
    
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if(event.type == sf::Event::MouseButtonPressed)
        {
            manager.MouseDown(event.mouseButton.button);
        }

         if(event.type == sf::Event::MouseButtonReleased)
        {
            manager.MouseUp(event.mouseButton.button);
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if(event.key.code == sf::Keyboard::Escape)
            {
                window.close();
            }
            manager.KeyDown(event.key.code);
        }

        if (event.type == sf::Event::KeyReleased)
        {
            manager.KeyUp(event.key.code);
        }
    }
}

void Loop::Update()
{
    deltaTime = mainClock.getElapsedTime();
    manager.GetDeltaTime(deltaTime);
    manager.NotifyScene(scene.renderMap);
    collisionManager.UpdateNormals();
    collisionManager.CheckCollisions();
    mainClock.restart();
}

void Loop::Render()
{
    window.clear();
    scene.CameraFollow(window);
    scene.RenderAll(window);
    window.display();
}
