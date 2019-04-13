#include "Enemigo.h"

#define F 30.0f

Enemigo::Enemigo()
{
    //ctor
}

void Enemigo::drawEnemigo(RenderWindow &window)
{
    sprite->setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F );
    window.draw(*sprite);
    window.draw(*triangle);

}

//Getters
int Enemigo::getDireccion(){return direccion;}
bool Enemigo::getMoviendose(){return moviendose;}
float Enemigo::getVelocidad(){return velocity;}
sf::ConvexShape* Enemigo::getVista(){return triangle;}
sf::Sprite* Enemigo::getSprite(){return sprite;}


//Setters
void Enemigo::setMoviendose(bool _moviendose){moviendose = _moviendose;}

Enemigo::~Enemigo()
{
    //dtor
}
