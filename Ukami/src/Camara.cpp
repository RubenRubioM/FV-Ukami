#include "Camara.h"
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
