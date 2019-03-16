#include "Ninja.h"

Ninja::Ninja()
{
    //ctor
}


//Getters
int Ninja::getDireccion(){return direccion;}
bool Ninja::getMoviendose(){return moviendose;}
float Ninja::getVelocidad(){return velocidad;}
sf::Sprite* Ninja::getSprite(){return sprite;}


void Ninja::moverse(float _deltaTime){

    if(moviendose){
        sprite->move(direccion*velocidad* _deltaTime,0);
    }

}



//Setters
void Ninja::setDireccion(int _dir){
    direccion = _dir;

    //Flipeamos el sprite
    if(direccion==-1){
        sprite->setTextureRect(sf::IntRect(sprite->getTexture()->getSize().x,0,-sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
    }else{
        sprite->setTextureRect(sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
    }
}
void Ninja::setMoviendose(bool _moviendose){moviendose = _moviendose;}

Ninja::~Ninja()
{
    //dtor
}
