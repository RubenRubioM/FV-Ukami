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

//Se llama cuando presionas el sigilo
void Ninja::activarSigilo(){
    setEnSigilo(true);
    tiempoSigilo.restart(); //Reiniciamos el reloj para que se vaya desgastando el sigilo
    sprite->setColor(sf::Color(255,255,255,75));

}

//Cuando acaba el tiempo de (duracionSigilo) se llama para desactivarlo
void Ninja::desactivarSigilo(){
    sprite->setColor(sf::Color(255,255,255,255));
    setEnSigilo(false);

    //Reiniciamos el reloj para que ahora haga otros (recargaSigilo) segundos para cargalo
    tiempoSigilo.restart();

}

//Va ejecutandose cada frame mientras que activas el sigilo hasta que el tiempo trascurrido sea igual a duracionSigilo
//Y va decrementando la barra de sigilo
void Ninja::descargarSigilo(float _deltaTime){
    sigiloMax = false;

    float tiempoDeSigiloTrascurrido = getTiempoSigilo().getElapsedTime().asSeconds();
    float decremento = maxSigilo-(tiempoDeSigiloTrascurrido*(maxSigilo/duracionSigilo));

    sliderSigilo[0].setSize(sf::Vector2f(decremento,10));
}

//Va ejecutandose cada frame mientras que no este en sigilo y el sigilo no este al maximo
//Y va aumentando el slider interior del sigilo
void Ninja::cargarSigilo(float _deltaTime){
    float tiempoDeSigiloTrascurrido = getTiempoSigilo().getElapsedTime().asSeconds();
    float incremento = (tiempoDeSigiloTrascurrido*(maxSigilo/recargaSigilo));

    //Si llenamos el sigilo actulizamos la variable de sigiloMax
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
