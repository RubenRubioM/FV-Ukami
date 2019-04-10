#include "Puerta.h"

Puerta::Puerta()
{
    //ctor
    loadSprite();
    colocarSprite();
}

void Puerta::loadTexture()
{
    texture = new sf::Texture;
    texture->loadFromFile("tileset/door1.png");
    texture->setSmooth(true);
}

void Puerta::loadSprite()
{
    loadTexture();
    sprite = new sf::Sprite(*texture);
}

void Puerta::colocarSprite()
{
    sprite->setPosition(1800,620); //no lo veo, no se porque
}

void Puerta::drawPuerta(sf::RenderWindow &window)
{
    window.draw(*sprite);
}

Puerta::~Puerta()
{
    //dtor
}
