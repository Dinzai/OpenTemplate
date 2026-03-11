#include <SFML/Graphics.hpp>
#include <vector>

#include "CollisionManager.h"
#include "InputManager.h"
#include "Scene.h"
#include "SignalManager.h"


struct ManagerLib
{

    Scene& GetScene()
    {
        return scene;
    }

    CollisionManager& GetCollisionManager()
    {
        return collisionManager;
    }

    InputManager& GetInputManager()
    {
        return inputManager;
    }

    SignalManager& GetSignalManager()
    {
        return signalManager;
    }


    ManagerLib()
    {
        scene = Scene();
        collisionManager = CollisionManager();
        inputManager = InputManager();
        signalManager = SignalManager();
    }

    Scene scene;
    CollisionManager collisionManager;
    InputManager inputManager;
    SignalManager signalManager;

};