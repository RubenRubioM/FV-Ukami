#include "Palanca.h"

Palanca::Palanca()
{
    //ctor
}

Palanca::~Palanca()
{
    //dtor
}

void Palanca::crearPalanca(int posx, int posy)
{
    palancaT.loadFromFile("tileset/lever.png");
    palancaS.setTexture(palancaT);
    palancaS.setOrigin(palancaT.getSize().x / 2.f , palancaT.getSize().y / 2.f);
    palancaS.setScale(0.2,0.2);
    palancaS.setPosition(posx, posy);
}

void Palanca::drawPalanca(RenderWindow &window)
{
    window.draw(palancaS);
}

void Palanca::hidePalanca()
{
    palancaS.setScale(0,0);
}

Sprite Palanca::getSprite()
{
    return palancaS;
}
