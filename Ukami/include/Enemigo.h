#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
class Enemigo
{
    public:
        Enemigo();
        virtual ~Enemigo();
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::Sprite *vista;
        sf::ConvexShape *triangle;

        //Getters
        int getDireccion();
        bool getMoviendose();
        float getVelocidad();
        sf::Sprite *getSprite();
        sf::ConvexShape *getVista();

        //Setters
        void setMoviendose(bool);

        //Metodos
        virtual void setDireccion(int) = 0;
        virtual void moverse(float) = 0; //Funcion para moverse


    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose =false; //Dice si se esta moviendo o no
        float velocidad;


        //Metodos


};

#endif // Enemigo_H
