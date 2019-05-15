#include "Enredadera.h"

Enredadera::Enredadera()
{
    //ctor
}

Enredadera::~Enredadera()
{
    //dtor
}

void Enredadera::crearEnredadera(int posx, int posy)
{
    enredaderaT.loadFromFile("tileset/enredadera.png");
    enredaderaS.setTexture(enredaderaT);
    enredaderaS.setOrigin(enredaderaT.getSize().x / 2.f , enredaderaT.getSize().y / 2.f);
    enredaderaS.setScale(1,1);
    enredaderaS.setPosition(posx, posy);
}

void Enredadera::drawEnredadera(RenderWindow &window)
{
    window.draw(enredaderaS);
}

void Enredadera::hideEnredadera()
{
    enredaderaS.setScale(0,0);
}

Sprite Enredadera::getSprite()
{
    return enredaderaS;
}
