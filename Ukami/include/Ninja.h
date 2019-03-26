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
        float getNewX();
        sf::Sprite *getSprite();

        //Setters
        void setDireccion(int);
        void setMoviendose(bool);
        void setNewX(float);

        //Metodos
        void moverse(float); //Metodo abstracto que definen las sublcases
        void moverseInterpolado(float,float);
        void nuevoEstado(float, float);


    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose = false; //Dice si se esta moviendo o no
        float velocidad;
        float newX = 0;
        float lastX = 0;
        float lastY;
        sf::Texture *texture;
        sf::Sprite *sprite;

        //Metodos


};

#endif // NINJA_H
