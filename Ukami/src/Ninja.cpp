#include "Ninja.h"

Ninja::Ninja()
{
    mejorarSigilo();
}

//Se llama cuando presionas el sigilo
void Ninja::activarSigilo(){
    enSigilo = true;
    tiempoSigilo.restart(); //Reiniciamos el reloj para que se vaya desgastando el sigilo
    animatedSprite.setColor(sf::Color(255,255,255,75));

}

//Cuando acaba el tiempo de (duracionSigilo) se llama para desactivarlo
void Ninja::desactivarSigilo(){
    animatedSprite.setColor(sf::Color(255,255,255,255));
    enSigilo = false;

    //Reiniciamos el reloj para que ahora haga otros (recargaSigilo) segundos para cargalo
    tiempoSigilo.restart();

}

//Va ejecutandose cada frame mientras que activas el sigilo hasta que el tiempo trascurrido sea igual a duracionSigilo
//Y va decrementando la barra de sigilo
void Ninja::descargarSigilo(float _deltaTime){
    sigiloMax = false;

    float tiempoDeSigiloTrascurrido = tiempoSigilo.getElapsedTime().asSeconds();
    float decremento = maxSigilo-(tiempoDeSigiloTrascurrido*(maxSigilo/duracionSigilo));

    sliderSigilo[0].setSize(sf::Vector2f(decremento,5));
}

//Va ejecutandose cada frame mientras que no este en sigilo y el sigilo no este al maximo
//Y va aumentando el slider interior del sigilo
void Ninja::cargarSigilo(float _deltaTime){
    float tiempoDeSigiloTrascurrido = tiempoSigilo.getElapsedTime().asSeconds();
    float incremento = (tiempoDeSigiloTrascurrido*(maxSigilo/recargaSigilo));

    //Si llenamos el sigilo actulizamos la variable de sigiloMax
    if(incremento >=maxSigilo){
        sigiloMax = true;
    }
    sliderSigilo[0].setSize(sf::Vector2f(incremento,5));

}

void Ninja::mejorarSigilo(){
 int sg;
  string line;
  ifstream myfile ("skills/sigilo");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
      sg = stoi(line);
    }
    myfile.close();
  }
  if(sg==0){
    duracionSigilo=2.5;
  }
  else if(sg==1){
    duracionSigilo=3;
  }
  else if(sg==2){
    duracionSigilo=3.5;
  }
  else if(sg==3){
    duracionSigilo=4;
  }
}

void Ninja::cargarVida(float _deltaTime){
    if(sliderVida->getSize().x<maxVida){
        vidaActual = sliderVida->getSize().x + (0.1*_deltaTime);
        if(vidaActual>maxVida) vidaActual=maxVida;
        sliderVida->setSize(sf::Vector2f(vidaActual, sliderVida->getSize().y));
    }


}

void Ninja::descargarVida(float _deltaTime){
    if(sliderVida->getSize().x>0){
        vidaActual = sliderVida->getSize().x - (0.2*_deltaTime);
        if(vidaActual<=0) vidaActual=1;
        sliderVida->setSize(sf::Vector2f(vidaActual, sliderVida->getSize().y));
    }

}

sf::RectangleShape* Ninja::getSliderSigilo(){return sliderSigilo;}
sf::RectangleShape* Ninja::getSliderVida(){return sliderVida;}
sf::RectangleShape* Ninja::getBoxCollider(){return boxCollider;}
bool Ninja::getEnSigilo(){return enSigilo;}
float Ninja::getVidaActual(){return vidaActual;}
bool Ninja::getSiendoDetectado(){return siendoDetectado;}

void Ninja::setSiendoDetectado(bool _siendoDetectado){
    siendoDetectado = _siendoDetectado;
}

Ninja::~Ninja()
{
    //dtor
}
