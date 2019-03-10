#ifndef NINJA_H
#define NINJA_H

#include "SFML/Graphics.hpp"
#include <iostream>
using namespace std;
class Ninja
{
    public:
        Ninja();
        virtual ~Ninja();


        //Getters
        int getDireccion();
        bool getMoviendose();
        float getVelocidad();
        sf::Sprite *getSprite();

        //Setters
        void setDireccion(int);
        void setMoviendose(bool);

        //Metodos
        virtual void moverse(float) = 0; //Metodo abstracto que definen las sublcases


    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose =false; //Dice si se esta moviendo o no
        float velocidad;
        sf::Texture *texture;
        sf::Sprite *sprite;

        //Metodos


};

#endif // NINJA_H
