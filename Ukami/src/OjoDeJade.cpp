#include "OjoDeJade.h"

#include <iostream>

OjoDeJade::OjoDeJade(float x, float y)
{
    texture.loadFromFile("tileset/joya.png", sf::IntRect(5, 7, 20, 20));
    sprite.setTexture(texture);
    pos_x = x;
    pos_y = y;
    sprite.setPosition(x, y);
    sprite.scale(3.5f, 3.5f);
    sprite.rotate(90.f);
}

void OjoDeJade::dibujaOjoDeJade(sf::RenderWindow &window)
{
    window.draw(sprite);
}

sf::Sprite OjoDeJade::getSprite()
{
    return sprite;
}

OjoDeJade::~OjoDeJade()
{
    //dtor
}
