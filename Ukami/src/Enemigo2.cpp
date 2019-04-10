#include "Enemigo2.h"
#include <iostream>
#include <Game.h>
Enemigo2* Enemigo2::unicaInstancia=0;

//Constructor del Enemigo2
Enemigo2::Enemigo2()
{
    velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/sprites.png",sf::IntRect(0*75, 2*75, 75, 75));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(800,400); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0



    triangle = new sf::ConvexShape();
    triangle->setPointCount(3);

    // define the position of the triangle's points
    triangle->setPoint(0, sf::Vector2f(sprite->getPosition().x, sprite->getPosition().y));
    triangle->setPoint(1, sf::Vector2f(sprite->getPosition().x+50, sprite->getPosition().y+250));
    triangle->setPoint(2, sf::Vector2f(sprite->getPosition().x-50, sprite->getPosition().y+250));

}

void Enemigo2::setDireccion(int _dir){
}


void Enemigo2::moverse(float _deltaTime){
}

Enemigo2::~Enemigo2()
{
    //dtor
}
