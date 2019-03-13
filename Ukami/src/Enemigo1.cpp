#include "Enemigo1.h"
#include <iostream>
#include <Game.h>
Enemigo1* Enemigo1::unicaInstancia=0;

//Constructor del Enemigo1
Enemigo1::Enemigo1()
{
    velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/sprites.png",sf::IntRect(0*75, 2*75, 75, 75));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(400,40); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0

    luz = new sf::Texture();

    luz->loadFromFile("Assets/Adventurer/luz.png");
    vista = new sf::Sprite(*luz);
    vista->setOrigin(0/2,100/2);
    vista->setPosition(sprite->getPosition().x, sprite->getPosition().y);



}

void Enemigo1::moverse(float _deltaTime){

    if(moviendose){

        sprite->move(direccion*velocidad* _deltaTime,0);
        vista->move(direccion*velocidad* _deltaTime,0);
    }

}

void Enemigo1::detectado(bool detectado){

    if(detectado){

    }

}

Enemigo1::~Enemigo1()
{
    //dtor
}
