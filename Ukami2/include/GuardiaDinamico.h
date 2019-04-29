#ifndef GUARDIADINAMICO_H
#define GUARDIADINAMICO_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Box2D/Box2D.h";

using namespace std;

class GuardiaDinamico
{
    public:
        GuardiaDinamico(float,float, b2World* world);
        virtual ~GuardiaDinamico();

        bool getMoviendose();
        sf::Sprite *getSprite();
        sf::ConvexShape* getVision();

        //Metodos
        void drawGuardiaDinamico(sf::RenderWindow &window);
        void updateGuardiaDinamico(float);

    private:
        sf::Texture *texture;
        sf::Sprite *sprite;
        sf::ConvexShape *triangle; //Vision
        b2Body *ninjaBody;
        float velocidad = 0.3;
        int metros = 0;
        int rango = 30; //Rango de distancia que anda

};

#endif // GUARDIADINAMICO_H
