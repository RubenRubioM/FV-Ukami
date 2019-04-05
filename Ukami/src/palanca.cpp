#include "palanca.h"

palanca::palanca()
{
    //ctor
    loadSprite();
    colocarSprite();
}

void palanca::loadTexture()
{
    texture = new sf::Texture;
    texture->loadFromFile("C:/Users/kezav/Desktop/Ukami/Ukami/tileset/closed_scroll.jpg");
}

void palanca::loadSprite()
{
    loadTexture();
    sprite = new sf::Sprite(*texture);
}

void palanca::colocarSprite()
{
    sprite->setOrigin(sprite->getTexture()->getSize().x / 2, sprite->getTexture()->getSize().y / 2);
    sprite->setPosition(0,0); //no lo veo, no se porque
}

void palanca::drawPalanca(sf::RenderWindow &window)
{
    window.draw(*sprite);
}

palanca::~palanca()
{
    //dtor
}
