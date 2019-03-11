#ifndef GUARDIA_H
#define GUARDIA_H

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Guardia
{
    public:
        Guardia(float, float);
        virtual ~Guardia();

        float getVelocidad();
        float getAntiguaX();
        float getPosicionSilbido();
        bool getEfectoSilbido();

        void moverseAlSilbido(float);
        sf::Sprite *getSprite();

        //Setters
        void setPosicionSilbido(float);
        void setAntiguaX(float);
        void setEfectoSilbido(bool);

    private:
        bool efectoSilbido = false;
        float velocidad;
        float antiguaX; //La posicion donde esta originalmente antes de ir al silbido
        float posicionSilbido; //Posicion donde tiene que ir cuando le silban
        int direccionDelSilbido; //Direccion donde le pilla el silbido 1 o -1
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::Clock tiempoAntesDeVolver; //Tiempo que pasa en el sitio hasta que vuelve al sitio donde estaba despues del silbido
};

#endif // GUARDIA_H
