#include <SFML/Graphics.hpp>
#include <vector>

#include "playerFront.h"
#include "playerBack.h"
#include "playerLeft.h"
#include "playerRight.h"
#include "roll.h"
#include "rollOther.h"
#include "attackFront.h"
#include "attackBack.h"
#include "attackLeft.h"
#include "attackRight.h"


#include "lightPillar.h"


struct AssetManager
{

    sf::Texture* PassLoadedTexture(int data)
    {
        sf::Texture* temp = new sf::Texture();

        if (data == PlayerFront)
        {
            temp->create(Player_Front.width, Player_Front.height);
            temp->update(Player_Front.pixel_data);
        }

        if(data == PlayerBack)
        {
            temp->create(Player_Back.width, Player_Back.height);
            temp->update(Player_Back.pixel_data);
        }

        if(data == PlayerLeft)
        {
            temp->create(Player_Left.width, Player_Left.height);
            temp->update(Player_Left.pixel_data);
        }

        if(data == PlayerRight)
        {
            temp->create(Player_Right.width, Player_Right.height);
            temp->update(Player_Right.pixel_data);
        }   

        if(data == Roll)
        {
            temp->create(Player_Roll.width, Player_Roll.height);
            temp->update(Player_Roll.pixel_data);
        }   

        if(data == OtherRoll)
        {
            temp->create(Player_RollOther.width, Player_RollOther.height);
            temp->update(Player_RollOther.pixel_data);
        }   

        if(data == attackFront)
        {
            temp->create(Player_AttackFront.width, Player_AttackFront.height);
            temp->update(Player_AttackFront.pixel_data);
        }

        if(data == attackBack)
        {
            temp->create(Player_AttackBack.width, Player_AttackBack.height);
            temp->update(Player_AttackBack.pixel_data);
        }

        if(data == attackLeft)
        {
            temp->create(Player_AttackLeft.width, Player_AttackLeft.height);
            temp->update(Player_AttackLeft.pixel_data);
        }   

        if(data == attackRight)
        {
            temp->create(Player_AttackRight.width, Player_AttackRight.height);
            temp->update(Player_AttackRight.pixel_data);
        }

        if(data == THElightPillar)
        {
            temp->create(TheLight_Pillar.width, TheLight_Pillar.height);
            temp->update(TheLight_Pillar.pixel_data);
        }

        return temp;
    }


    enum ImageData
    {
        PlayerFront,
        PlayerBack,
        PlayerLeft,
        PlayerRight,
        Roll,
        OtherRoll,
        attackFront,
        attackBack,
        attackLeft,
        attackRight,
        THElightPillar,

    };

    void MakeAllTextures() // make sure to change this when adding textures
    {
        allTextures.reserve(10);
        for (int i = 0; i < 10; i++)
        {
            sf::Texture* temp = PassLoadedTexture(i);
            allTextures.push_back(temp);
        }
    }

    AssetManager()
    {
        MakeAllTextures();

    }

    std::vector<sf::Texture*> allTextures;
};
