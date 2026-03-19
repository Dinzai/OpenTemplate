#pragma once
#include "Anim.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
/*

MIT Licence
Author -> Brett Rogers
Reference/Inspiration -> https://www.youtube.com/watch?v=jwNRV9Al83Y&t=225s


String Splitting Utility Extension
This is meant to be part an extension of the anim.h 

Using the program Tiled, make a Map
The tileset you use will be the SpriteSheet in the anim.h class

Export the tiled map as a .csv file

this will give numbers

add a comma at the end of each row

example->

1,2,3,1,0,1,3,2,
0,1,2,3,2,1,3,0,
3,0,1,1,0,0,1,0,
1,3,3,1,0,3,1,1,
3,2,3,0,3,2,0,2,
1,0,0,1,0,1,1,1,
0,1,2,0,0,0,3,2,
0,2,1,1,1,1,2,0,


each number, represents that xFrame in the anim.h class

example->
anim = new DINZAI::SpriteSheet(asset.PassTexture(type), xFrame, yFrame, animTime, startFrame, endFrame);

this could be abstracted with a utility function like SetTexture bellow
You would have to make that

Tile::Tile(Assets &asset, Asset type, int xFrame)
{
    SetTexture(asset, type, 4, 1, 0.1f, xFrame, xFrame);
}

TileData::TileData()
{
    stringUtil.Do("test/testOther.csv", ',');  <----- Use DO!
}

void TileData::MakeTileWorld(Assets &asset)
{
    static int posX = 0;
    static int posY = 0;
    static int counter = 0;
    for (size_t i = 0; i < stringUtil.numList.size(); i++) <---- now with numlist, make your map
    {
        Tile *temp = new Tile(asset, TEST, stringUtil.numList.at(i));
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

How to Use?

Run Do(file.txt, ',');     <------ run this function, split by the ignore character

and use numList

*/

namespace Dinzai
{

    struct SimpleStringSplit
    {

        SimpleStringSplit()
        {
        }

        ~SimpleStringSplit()
        {
        }

    private:
        std::vector<std::string> AddData(std::string fileLocation)
        {
            std::vector<std::string> data;

            std::ifstream in(fileLocation);
            std::string w;

            if (in.is_open())
            {

                while (std::getline(in, w))
                {
                    data.push_back(w);
                }
                in.close();
            }
            else
            {
                std::cout << "failed";
            }
            return data;
        }

        std::vector<std::string> Split(std::string input, char splitChar)
        {

            std::vector<std::string> output;

            std::string tempString;

            for (size_t i = 0; i < input.size(); i++)
            {
                if (input.at(i) != splitChar)
                {
                    tempString += input.at(i);
                }
                else
                {
                    output.push_back(tempString);
                    tempString = "";
                }
            }

            return output;
        }

    public:
        std::vector<int> ConverToInt(std::vector<std::string> stringArray)
        {
            std::vector<int> trueData;

            for (size_t i = 0; i < stringArray.size(); i++)
            {
                int tempNum = std::stoi(stringArray[i]);
                trueData.push_back(tempNum);
            }
            return trueData;
        }

        void Do(std::string fileLocation, char splitChar)
        {

            std::vector<std::string> in = AddData(fileLocation);
            std::vector<std::string> out;
            numCharactersY = in.size();
            for (size_t i = 0; i < in.size(); i++)
            {
                std::string chunk = in.at(i);
                out = Split(chunk, splitChar);

                for (size_t j = 0; j < out.size(); j++)
                {
                    goal.push_back(out.at(j));
                }
            }
            numCharactersX = goal.size() / numCharactersY;
            Convert();
        }

    private:
        void Convert()
        {
            numList = ConverToInt(goal);
        }

        std::vector<std::string> goal;

    public:
        int numCharactersX = 0;
        int numCharactersY = 0;
        std::vector<int> numList;
    };
}
