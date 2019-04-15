#ifndef NINJA_H
#define NINJA_H

#include <SFML/Graphics.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Map.h"
#include "Box2D/Box2D.h";
#include <iostream>
#include <vector>
#include <map>
#include "AnimatedSprite.h"
#include "Animation.h"

using namespace tinyxml2;
using namespace std;
using namespace sf;

class Ninja
{
    public:
        Ninja();


        virtual ~Ninja();

    protected:
         bool saltando = false;
        float impulsoSalto = 500.f;
        float velocity = .5f;

        sf::Clock cdSalto;

        //sf::Texture texture;
        sf::Sprite sprite;

        Texture texture;
        Texture texture2;

        b2Body *ninjaBody;
        Animation walkingAnimationRight;
        Animation walkingAnimationLeft;
        Animation* currentAnimation;
        AnimatedSprite animatedSprite;
        bool noKeyWasPressed;
        b2PolygonShape shape;
        b2FixtureDef fixtureDef;

    private:
};

#endif // NINJA_H
