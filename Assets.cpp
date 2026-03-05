#include "Assets.h"

Assets::Assets()
{
    Preload();
}

void Assets::Add(Asset type, std::string name)
{
    sf::Texture* tempPtr = new sf::Texture();
    tempPtr->loadFromFile(name);
    allTextures[type].push_back(tempPtr);
}

void Assets::Preload()
{   
    Add(Asset::PLAYER, "PATH To YOUR PLAYER");

}

sf::Texture* Assets::PassTexture(Asset type)
{
    for(auto t : allTextures.at(type))
    {
        return t;
    } 
    return nullptr;
}

