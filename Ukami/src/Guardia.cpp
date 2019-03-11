#include "Guardia.h"

Guardia::Guardia(float _x, float _y)
{
     velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Guardia.png",sf::IntRect(0,0,32,32));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(_x,_y); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(2.f,2.f);
}

void Guardia::moverseAlSilbido(float _deltaTime){

    /*
        Creo que funciona desactivando el efecto de silbido solo en un sitio porque como al moverse siempre se pasa un poco la posicion destino entonces entra igualmente
    */

    //Detectamos si va hacia la derecha o hacia la izquierda
    if(posicionSilbido > sprite->getPosition().x){
        //hacia la derecha
        direccionDelSilbido = 1;

        sprite->move(direccionDelSilbido*velocidad*_deltaTime,0);
    }else if(posicionSilbido < sprite->getPosition().x){
        //hacia la izquierda
        if(direccionDelSilbido==1){
            efectoSilbido = false;
            cout << "Ha llegado al punto del silbido" << endl;
        }
        direccionDelSilbido = -1;

        sprite->move(direccionDelSilbido*velocidad*_deltaTime,0);
    }
}

//Getters
bool Guardia::getEfectoSilbido(){return efectoSilbido;}
float Guardia::getPosicionSilbido(){return posicionSilbido;}
float Guardia::getAntiguaX(){return antiguaX;}
float Guardia::getVelocidad(){return velocidad;}
sf::Sprite* Guardia::getSprite(){return sprite;}


//Setters
void Guardia::setPosicionSilbido(float _x){posicionSilbido = _x;}
void Guardia::setAntiguaX(float _x){antiguaX = _x;}

void Guardia::setEfectoSilbido(bool _silbido){efectoSilbido = _silbido;}

Guardia::~Guardia()
{
    //dtor
}
