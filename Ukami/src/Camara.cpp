#include "Camara.h"
#include <cmath>
Camara* Camara::unicaInstancia=0;

Camara::Camara()
{
    camara = new sf::View(sf::FloatRect(0,0,camaraXSize,camaraYSize));
}

void Camara::moverCamara(float _x){
    camara->setCenter(_x,camaraYSize/2);
}

void Camara::bloquear(){
    bloqueada = true;
}
void Camara::desbloquear(){
    bloqueada = false;
}

sf::View* Camara::getView(){return camara;}
float Camara::getCamaraXSize(){return camaraXSize;}
float Camara::getCamaraYSize(){return camaraYSize;}
int Camara::getCamaraPosX(){return camaraPosX;}
int Camara::getCamaraPosY(){return camaraPosY;}

void Camara::setCoordenadas(int _x, int _y){
    camaraPosX = _x;
    camaraPosY = _y;
}
Camara::~Camara()
{
    //dtor
}

void Camara::comprobarCamara(Ninja1 personaje1, Ninja2 personaje2, View &view)
{
        if(fabs(personaje1.getSprite().getPosition().x - personaje2.getSprite().getPosition().x) < view.getSize().x){
            view.setCenter((personaje1.getSprite().getPosition().x + personaje2.getSprite().getPosition().x) / 2, view.getCenter().y);
        }else{

            //Los personajes estan en la distancia maxima, ahora comprobamos quien esta en la izquierda y quien en la derecha para setear posiciones
            if(personaje1.getSprite().getPosition().x > personaje2.getSprite().getPosition().x){
                //El personaje1 esta en la derecha

                if(personaje2.getMoviendose() && personaje2.getDireccion() == -1){
                    //Arrastramos hacia la izquierda
                    personaje1.getSprite().setPosition(personaje2->getSprite()->getPosition().x+camara->getCamaraXSize()-2,personaje1->getSprite()->getPosition().y);

                }else{
                   personaje2->getSprite()->setPosition((personaje1->getSprite()->getPosition().x-camara->getCamaraXSize())+2,personaje2->getSprite()->getPosition().y);
                }


            }else{

                if(personaje1->getMoviendose() && personaje1->getDireccion()==-1){
                    //Arrastramos hacia la izquierda
                    personaje2->getSprite()->setPosition(personaje1->getSprite()->getPosition().x+camara->getCamaraXSize()-2,personaje2->getSprite()->getPosition().y);

                }else{
                   personaje1->getSprite()->setPosition((personaje2->getSprite()->getPosition().x-camara->getCamaraXSize())+2,personaje1->getSprite()->getPosition().y);
                }



            }


        }
}
