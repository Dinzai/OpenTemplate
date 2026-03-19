#include "Loop.h"

Loop::Loop() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Souls_Like")
{
    // allocate Assets
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
// collision
void Loop::AddToCollisionManager()
{
    for (size_t i = 0; i < gameObjects.GetLights().size(); i++)
    {
        managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetLights().at(i)->collision);
    }

    managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetPlayer()->collision);

    for (size_t i = 0; i < gameObjects.GetEnemies()->allSquidEnemies.size(); i++)
    {
        managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetEnemies()->allSquidEnemies.at(i)->collision);
    }

    for (size_t i = 0; i < gameObjects.GetData()->tiles.size(); i++)
    {
        if (gameObjects.GetData()->tiles.at(i)->isCollideable)
        {
            managerLib.GetCollisionManager().AddToCollisionManager(gameObjects.GetData()->tiles.at(i)->collision);
        }
    }
}
// input
void Loop::AddToInputManager()
{
    managerLib.GetInputManager().AddToListeners(gameObjects.GetPlayer());
}
// scene
void Loop::AddToScene()
{
     managerLib.GetScene().AddToScene(Layers::LIGHTS, gameObjects.GetBackground());
    for (size_t i = 0; i < gameObjects.GetLights().size(); i++)
    {
        managerLib.GetScene().AddToScene(Layers::ENTITY, gameObjects.GetLights().at(i)->currentView);
        managerLib.GetScene().AddToScene(Layers::LIGHTS, gameObjects.GetLights().at(i)->lightComponent);
    }

    managerLib.GetScene().AddToCamera(gameObjects.GetPlayer());
    managerLib.GetScene().AddToScene(Layers::PLAYER, gameObjects.GetPlayer()->currentView);
    managerLib.GetScene().AddToScene(Layers::UI, gameObjects.GetPlayerUI());

    for (size_t i = 0; i < gameObjects.GetEnemies()->allSquidEnemies.size(); i++)
    {
        managerLib.GetScene().AddToScene(Layers::ENTITY, gameObjects.GetEnemies()->allSquidEnemies.at(i)->currentView);
    }

    for (size_t i = 0; i < gameObjects.GetEnemies()->allSquidEnemyUI.size(); i++)
    {
        managerLib.GetScene().AddToScene(Layers::UI, gameObjects.GetEnemies()->allSquidEnemyUI.at(i));
    }

    for (size_t i = 0; i < gameObjects.GetData()->tiles.size(); i++)
    {
        managerLib.GetScene().AddToScene(Layers::BACKGROUND, gameObjects.GetData()->tiles.at(i)->currentView);
    }
}
// signal
void Loop::AddToSignalManager()
{

    for (size_t i = 0; i < gameObjects.GetLights().size(); i++)
    {
        managerLib.GetSignalManager().AddToMailer(gameObjects.GetLights().at(i));
        managerLib.GetSignalManager().AddToSubscibed(gameObjects.GetLights().at(i)->lightComponent->lights.at(0));
    }

    managerLib.GetSignalManager().AddToMailer(gameObjects.GetPlayer());
    managerLib.GetSignalManager().AddToSubscibed(gameObjects.GetPlayerUI());

    for (size_t i = 0; i < gameObjects.GetEnemies()->allSquidEnemies.size(); i++)
    {
        managerLib.GetSignalManager().AddToMailer(gameObjects.GetEnemies()->allSquidEnemies.at(i));
    }

    for (size_t i = 0; i < gameObjects.GetEnemies()->allSquidEnemyUI.size(); i++)
    {
        managerLib.GetSignalManager().AddToSubscibed(gameObjects.GetEnemies()->allSquidEnemyUI.at(i));
    }
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
    for (size_t i = 2; i < managerLib.GetSignalManager().senders.size(); i++)
    {
        managerLib.GetInputManager().SendToMailers(managerLib.GetSignalManager().senders.at(1), managerLib.GetSignalManager().senders.at(i));
    }

    for (size_t i = 0; i < gameObjects.GetEnemies()->allSquidEnemies.size(); i++)
    {
        Enemy *tempE = gameObjects.GetEnemies()->allSquidEnemies.at(i);
        if (tempE->markedForDeath)
        {
            managerLib.GetScene().RemoveFromScene(Layers::ENTITY, i);
            gameObjects.GetEnemies()->allSquidEnemies.erase(gameObjects.GetEnemies()->allSquidEnemies.begin() + i);
        }
    }

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
