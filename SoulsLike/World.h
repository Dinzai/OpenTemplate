#pragma once
#include "CSV_TileMapReader.h"
#include "Basic.h"

class Tile : public Base
{
public:
    Tile(Assets &asset, Asset type, int xFrame);

    bool isCollideable = false;
};

class TileData
{
public:
    TileData();

    void MakeTileWorld(Assets &asset);

    void SetPosition(sf::Vector2f position);

    Dinzai::SimpleStringSplit stringUtil;
    std::vector<Tile *> tiles;
};