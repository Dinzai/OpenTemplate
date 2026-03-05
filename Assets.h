#pragma once
#include "Interface.h"

class Assets : public IPreloadable
{

public:
    Assets();

    virtual void Preload() override;

    void Add(Asset type, std::string name);

    sf::Texture* PassTexture(Asset type);

    std::map<Asset, std::vector<sf::Texture *>> allTextures;
};