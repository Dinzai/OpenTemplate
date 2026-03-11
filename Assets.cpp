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

void Assets::Preload()
{
    Add(Asset::PLAYERF, "Asset/playerFront.png");
    Add(Asset::PLAYERB, "Asset/playerBack.png");
    Add(Asset::PLAYERL, "Asset/playerLeft.png");
    Add(Asset::PLAYERR, "Asset/playerRight.png");

    Add(Asset::PLAYERROLLFB, "Asset/roll.png");
    Add(Asset::PLAYERROLLLR, "Asset/rollOther.png");

    Add(Asset::PLAYERATTACKF, "Asset/attackFront.png");
    Add(Asset::PLAYERATTACKB, "Asset/attackBack.png");
    Add(Asset::PLAYERATTACKL, "Asset/attackLeft.png");
    Add(Asset::PLAYERATTACKR, "Asset/attackRight.png");

}

sf::Texture *Assets::PassTexture(Asset type)
{
    for (auto t : allTextures.at(type))
    {
        return t;
    }
    return nullptr;
}
