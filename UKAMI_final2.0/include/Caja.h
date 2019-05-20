#ifndef CAJA_H
#define CAJA_H

#include "Box2D/Box2D.h";
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

class Caja
{
public:
    Caja(int posx, int posy, b2World *world);
    virtual ~Caja();
    Sprite getSprite();
    void moverCaja(int sent);
    void detenerCaja();
    void drawCaja(RenderWindow &window);
    void drawBocadilloCaja(RenderWindow &window, int, int);

protected:
private:
    // Sprite y texture de la caja
    Sprite cajaS;
    Texture cajaT;
    b2FixtureDef fixtureDef;

    sf::Texture *bocadilloTexture;
    sf::Sprite *bocadilloSprite;
    // Body de la caja
    b2Body *cajaB;
};

#endif // CAJA_H
