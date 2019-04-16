#ifndef PUERTA_H
#define PUERTA_H

#include "Box2D/Box2D.h";
#include <SFML/Graphics.hpp>

class Puerta
{
    public:
        Puerta(int x, int y, b2World* world);
        virtual ~Puerta();
        void drawPuerta(sf::RenderWindow & window);
        void ocultarPuerta();
    protected:

    private:
        sf::Texture texture;
        sf::Sprite sprite;

        b2Body *puertaBody;
};

#endif // PUERTA_H
