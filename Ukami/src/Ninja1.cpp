#include "Ninja1.h"
#include <iostream>
#include <Game.h>
Ninja1* Ninja1::unicaInstancia=0;

//Constructor del ninja1
Ninja1::Ninja1()
{
    velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/adventurer-Sheet.png",sf::IntRect(0,0,48,43));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(40,40); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(2.f,2.f);




}

void Ninja1::moverse(float _deltaTime){

    if(moviendose){

        sprite->move(direccion*velocidad* _deltaTime,0);
    }

}

Ninja1::~Ninja1()
{
    //dtor
}
