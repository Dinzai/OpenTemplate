#pragma once
#include "Interface.h"
#include "AssetLib.h"

class Assets : public IPreloadable
{

public:
    Assets();

    virtual void Preload() override;

    void Add(Asset type, std::string name);

    void Add(Asset type);

    sf::Texture *PassTexture(Asset type);

    std::map<Asset, std::vector<sf::Texture *>> allTextures;

    AssetManager loader;
};