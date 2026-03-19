#include "World.h"

Tile::Tile(Assets &asset, Asset type, int xFrame)
{
    SetTexture(asset, type, 26, 16, 0.1f, xFrame, xFrame);
}

TileData::TileData()
{
    stringUtil.Do("test/bigTest.csv", ',');
}

void TileData::SetPosition(sf::Vector2f position)
{
    for(Tile* t : tiles)
    {
        sf::Vector2f currentPosition = t->GetPosition();
        t->currentView->texture2D->anim->SetPosition(currentPosition.x + position.x, currentPosition.y + position.y);
    }
}

void TileData::MakeTileWorld(Assets &asset)
{
    static int posX = 0;
    static int posY = 0;
    static int counter = 0;
    for (size_t i = 0; i < stringUtil.numList.size(); i++)
    {
        Tile *temp = new Tile(asset, TEST, stringUtil.numList.at(i));
        if(stringUtil.numList.at(i) >= 100)
        {
            temp->isCollideable = true;
            temp->collision->isStatic = true;
        }
        temp->GetActiveSprite()->setPosition(posX, posY);
        tiles.push_back(temp);
        posX += temp->currentView->texture2D->anim->GetSpriteSheetSize().width;
        counter++;
        if (counter == stringUtil.numCharactersX)
        {
            posX = 0;
            posY += temp->currentView->texture2D->anim->GetSpriteSheetSize().height;
            counter = 0;
        }
    }
}
