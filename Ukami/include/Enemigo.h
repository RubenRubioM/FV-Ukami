#ifndef ENEMIGO_H
#define ENEMIGO_H


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

class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();

        //Getters
        int getDireccion();
        bool getMoviendose();
        float getVelocidad();
        sf::Sprite *getSprite();
        sf::ConvexShape *getVista();

        //Setters
        void setMoviendose(bool);
        void drawEnemigo(sf::RenderWindow &window);
        virtual void ia(float) = 0;


    protected:
        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose = false; //Dice si se esta moviendo o no
        float velocity = 0.1f;

        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::Sprite *vista;
        sf::ConvexShape *triangle;

        b2Body *ninjaBody;

};

#endif // ENEMIGO_H
