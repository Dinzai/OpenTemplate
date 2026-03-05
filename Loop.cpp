#include "Loop.h"
#include <iostream>


//inheriting from Base class with a custom entity will give it the things
//it needs to be drawable, i suggets making the player ineheirt both Base, and CController
//Found in Basic.h/Basic.cpp

//i intentionally removed my player class from this

Loop::Loop() : window(sf::VideoMode(1200, 800), "True Rouge")
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
    
//this is where you add what is event driven
    //manager.AddToListeners();

//this is where you add what is drawn 
    //scene.AddToScene();

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
//only the manager should update and handle events, no other entitys 
//should handle that individually, add them to the listeners
void Loop::Update()
{
    deltaTime = mainClock.getElapsedTime();
    manager.NotifyScene(scene.renderMap);
    manager.GetDeltaTime(deltaTime);
    mainClock.restart();
}
//only the scene should render, not individual entitys,
//leave it to the scene to add them to the renderMap
void Loop::Render()
{
    window.clear();
    scene.RenderAll(window);
    window.display();
}
