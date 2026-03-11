#include "Assets.h"

Assets::Assets()
{
    Preload();
}

void Assets::Add(Asset type, std::string name)
{
    sf::Texture *tempPtr = new sf::Texture();
    tempPtr->loadFromFile(name);
    allTextures[type].push_back(tempPtr);
}

void Assets::Add(Asset type)
{
    sf::Texture *tempPtr = new sf::Texture();
    tempPtr = loader.PassLoadedTexture(type);
    allTextures[type].push_back(tempPtr);
}



void Assets::Preload()
{
    Add(Asset::PLAYERF);
    Add(Asset::PLAYERB);
    Add(Asset::PLAYERL);
    Add(Asset::PLAYERR);

    Add(Asset::PLAYERROLLFB);
    Add(Asset::PLAYERROLLLR);

    Add(Asset::PLAYERATTACKF); 
    Add(Asset::PLAYERATTACKB);
    Add(Asset::PLAYERATTACKL);
    Add(Asset::PLAYERATTACKR);

}

sf::Texture *Assets::PassTexture(Asset type)
{
    for (auto t : allTextures.at(type))
    {
        return t;
    }
    return nullptr;
}
