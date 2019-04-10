#include "Palanca.h"

Palanca::Palanca()
{
    texture.loadFromFile("/tileset/door1.png");
    sprite.setTexture(texture);
    sprite.setScale(1005, 1005);
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2.f, sprite.getTexture()->getSize().y / 2.f);
    sprite.setPosition(120,50); //no lo veo, no se porque
}

void Palanca::drawPalanca(sf::RenderWindow &window)
{
    window.draw(sprite);
}

Palanca::~Palanca()
{
    //dtor
}
