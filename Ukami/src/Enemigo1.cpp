#include "Enemigo1.h"
#include <iostream>
#include <Game.h>
#include "Enemigo.h"

Enemigo1* Enemigo1::unicaInstancia=0;

//Constructor del Enemigo1
Enemigo1::Enemigo1()
{
    velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/sprites.png",sf::IntRect(0*75, 2*75, 75, 75));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(200,40); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0

    /*luz = new sf::Texture();

    luz->loadFromFile("Assets/Adventurer/luz.png");
    vista = new sf::Sprite(*luz);
    vista->setOrigin(0/2,100/2);
    vista->setPosition(sprite->getPosition().x, sprite->getPosition().y);*/

    triangle = new sf::ConvexShape();
    triangle->setPointCount(3);

    // define the position of the triangle's points
    triangle->setPoint(0, sf::Vector2f(0, 0));
    triangle->setPoint(1, sf::Vector2f(250,50));
    triangle->setPoint(2, sf::Vector2f(250,-50));
    triangle->setPosition(sprite->getPosition().x, sprite->getPosition().y);
    triangle->setOrigin(0,0);

}

void Enemigo1::setDireccion(int _dir){
    direccion = _dir;

    if(direccion==-1){
        sprite->setTextureRect(sf::IntRect(sprite->getTexture()->getSize().x,0,-sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        triangle->setRotation(180);
    }else{
        sprite->setTextureRect(sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        triangle->setRotation(0);
    }
}


void Enemigo1::moverse(float _deltaTime){

    if(moviendose){

        sprite->move(direccion*velocidad* _deltaTime,0);
        triangle->move(direccion*velocidad* _deltaTime,0);
    }

}

Enemigo1::~Enemigo1()
{
    //dtor
}
