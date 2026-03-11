#pragma once
#include <SFML/Graphics.hpp>
#include <string>

namespace DINZAI
{
    class SpriteSheet
    {
    public:
        // Make the sprite
        SpriteSheet(std::string fileLocation, int numXFrames, int numYFrames, float animationTime)
        {
            spriteSheetTexture->loadFromFile(fileLocation);

            spriteSheetSize.width = spriteSheetTexture->getSize().x;
            spriteSheetSize.height = spriteSheetTexture->getSize().y;

            theSprite.setTexture(*spriteSheetTexture);
            theSprite.setTextureRect(spriteSheetSize);
            SetFrameCount(numXFrames, numYFrames);
            SetAnimTime(animationTime);
            SetSprite();
        }
        SpriteSheet(sf::Texture *temp, int numXFrames, int numYFrames, float animationTime, int beginFrame, int endFrame)
        {
            startFrame = beginFrame;
            limitFrame = endFrame;

            spriteSheetTexture = temp;
            spriteSheetTexture->setSmooth(false);

            spriteSheetSize.width = spriteSheetTexture->getSize().x;
            spriteSheetSize.height = spriteSheetTexture->getSize().y;

            theSprite.setTexture(*spriteSheetTexture);
            theSprite.setTextureRect(spriteSheetSize);
            SetFrameCount(numXFrames, numYFrames);
            SetAnimTime(animationTime);
            SetSprite();
        }
        // animate the sprite
        void Animate()
        {
            if (animClock.getElapsedTime().asSeconds() > animTime)
            {
                SetSprite();
                frameCount++;
                animClock.restart();
            }
        }

        sf::Sprite* GetSprite()
        {
            return &theSprite;
        }

        void SetPosition(float x, float y)
        {
            theSprite.setPosition(sf::Vector2f(x, y));
        }

        void SetScale(float x, float y)
        {
            theSprite.setScale(sf::Vector2f(x, y));
        }

        // Draw the sprite
        void Draw(sf::RenderWindow &window)
        {
            window.draw(theSprite);
        }

    private:
        // this sets the image's width, height, depending on the frame
        void SetSprite()
        {
            if (frameCount < limitFrame && frameCount >= startFrame)
            {

                frameCount = frameCount % totalFrames;

                int x = (frameCount % columns) * frameWidth;
                int y = (frameCount / columns) * frameHeight;

                spriteSheetSize.left = x;
                spriteSheetSize.top = y;
                spriteSheetSize.width = frameWidth;
                spriteSheetSize.height = frameHeight;

                theSprite.setTextureRect(spriteSheetSize);
            }
            else
            {
                frameCount = startFrame;
                int x = (frameCount % columns) * frameWidth;
                int y = (frameCount / columns) * frameHeight;

                spriteSheetSize.left = x;
                spriteSheetSize.top = y;
                spriteSheetSize.width = frameWidth;
                spriteSheetSize.height = frameHeight;

                theSprite.setTextureRect(spriteSheetSize);
            }
        }

        // this takes in information to determine the following values
        void SetFrameCount(int numberOfXFrames, int numberOfYFrames)
        {

            frameWidth = spriteSheetSize.width / numberOfXFrames;
            frameHeight = spriteSheetSize.height / numberOfYFrames;

            columns = spriteSheetSize.width / frameWidth;
            rows = spriteSheetSize.height / frameHeight;

            totalFrames = columns * rows;
        }

        // this sets the speed of the animation
        void SetAnimTime(float amount)
        {
            animTime = amount;
        }

        sf::Texture* spriteSheetTexture;
        sf::IntRect spriteSheetSize;
        sf::Sprite theSprite;
        sf::Clock animClock;

        int startFrame = 0;
        int limitFrame = 0;

        float animTime = 0;

        int frameCount = 0;
        int frameWidth;
        int frameHeight;
        int columns;
        int rows;
        int totalFrames;
    };

}