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
sf::ConvexShape* Enemigo::getVista(){return triangle;}


//Setters
void Enemigo::setMoviendose(bool _moviendose){moviendose = _moviendose;}

Enemigo::~Enemigo()
{
    //dtor
}
