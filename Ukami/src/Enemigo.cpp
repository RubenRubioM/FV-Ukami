#include "Enemigo.h"

Enemigo::Enemigo()
{
    //ctor
}


//Getters
int Enemigo::getDireccion(){return direccion;}
bool Enemigo::getMoviendose(){return moviendose;}
float Enemigo::getVelocidad(){return velocidad;}
sf::Sprite* Enemigo::getSprite(){return sprite;}
sf::Sprite* Enemigo::getVista(){return vista;}


//Setters
void Enemigo::setDireccion(int _dir){
    direccion = _dir;

    //Flipeamos el sprite
    if(direccion==-1){
        sprite->setTextureRect(sf::IntRect(sprite->getTexture()->getSize().x,0,-sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        vista->setScale(-1,1);
    }else{
        sprite->setTextureRect(sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        vista->setScale(1,1);
    }
}
void Enemigo::setMoviendose(bool _moviendose){moviendose = _moviendose;}

Enemigo::~Enemigo()
{
    //dtor
}
