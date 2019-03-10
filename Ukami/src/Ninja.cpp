#include "Ninja.h"

Ninja::Ninja()
{
    //ctor
}



void Ninja::moverse(float _deltaTime){

    if(moviendose){
        sprite->move(direccion*velocidad* _deltaTime,0);
    }

}


void Ninja::activarSigilo(){
    setEnSigilo(true);
    tiempoSigilo.restart();
    sprite->setColor(sf::Color(255,255,255,75));

}

void Ninja::desactivarSigilo(){
    sprite->setColor(sf::Color(255,255,255,255));
    setEnSigilo(false);

    //Reiniciamos el reloj para que ahora haga otros 5 segundos para cargalo
    tiempoSigilo.restart();

}


void Ninja::descargarSigilo(float _deltaTime){
    sigiloMax = false;

    float tiempoDeSigiloTrascurrido = getTiempoSigilo().getElapsedTime().asSeconds();
    float decremento = maxSigilo-(tiempoDeSigiloTrascurrido*(maxSigilo/duracionSigilo));

    sliderSigilo[0].setSize(sf::Vector2f(decremento,10));
}

void Ninja::cargarSigilo(float _deltaTime){
    float tiempoDeSigiloTrascurrido = getTiempoSigilo().getElapsedTime().asSeconds();
    float incremento = (tiempoDeSigiloTrascurrido*(maxSigilo/recargaSigilo));

    //Si llenamos el sigilo lo indicamos
    if(incremento >=maxSigilo){
        sigiloMax = true;
    }
    sliderSigilo[0].setSize(sf::Vector2f(incremento,10));

}
//Getters
int Ninja::getDireccion(){return direccion;}
bool Ninja::getMoviendose(){return moviendose;}
float Ninja::getVelocidad(){return velocidad;}
bool Ninja::getEnSigilo(){return enSigilo;}
bool Ninja::getSigiloMax(){return sigiloMax;}
float Ninja::getDuracionSigilo(){return duracionSigilo;}
sf::Clock Ninja::getTiempoSigilo(){return tiempoSigilo;}
sf::Sprite* Ninja::getSprite(){return sprite;}
sf::RectangleShape* Ninja::getSliderSigilo(){return sliderSigilo;}

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
void Ninja::setEnSigilo(bool _enSigilo){enSigilo = _enSigilo;}

Ninja::~Ninja()
{
    //dtor
}
