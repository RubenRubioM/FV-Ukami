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
        sf::Texture *luz;
        sf::Sprite *vista;

        //Getters
        int getDireccion();
        bool getMoviendose();
        float getVelocidad();
        sf::Sprite *getSprite();
        sf::Sprite *getVista();

        //Setters
        void setDireccion(int);
        void setMoviendose(bool);

        //Metodos
        virtual void moverse(float) = 0; //Metodo abstracto que definen las sublcases
        virtual void detectado(bool) = 0; //Metodo abstracto que definen las sublcases


    protected:

        //Varialbes
        int direccion = 1; //1-> derecha / -1-> izquierda
        bool moviendose =false; //Dice si se esta moviendo o no
        float velocidad;


        //Metodos


};

#endif // Enemigo_H
