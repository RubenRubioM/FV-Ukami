#include "Ninja2.h"
Ninja2* Ninja2::unicaInstancia=0;


Ninja2::Ninja2()
{
    velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/adventurer-Sheet.png",sf::IntRect(0,0,48,43));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(40,200); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(2.f,2.f);
    sprite->setColor(sf::Color::Yellow);

}

Ninja2::~Ninja2()
{
    //dtor
}
