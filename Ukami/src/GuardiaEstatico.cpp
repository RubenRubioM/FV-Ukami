#include "GuardiaEstatico.h"

GuardiaEstatico::GuardiaEstatico(float _x, float _y)
{
     velocidad = 0.3;
    xInicial = _x;
    texture = new sf::Texture();

    texture->loadFromFile("tileset/ninja2.png");
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(_x,_y); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(0.8f,0.8f);
}

void GuardiaEstatico::moverse(float _deltaTime){

    /*
        Creo que funciona desactivando el efecto de silbido solo en un sitio porque como al moverse siempre se pasa un poco la posicion destino entonces entra igualmente
    */

    //Detectamos si va hacia la derecha o hacia la izquierda
    if(posicionDestino > sprite->getPosition().x){
        //hacia la derecha
        direccionDestino = 1;

        sprite->move(direccionDestino*velocidad*_deltaTime,0);
    }else if(posicionDestino < sprite->getPosition().x){
        //hacia la izquierda
        if(direccionDestino==1){
            //Aqui solo entra 1 vez cuando ha llegado al sitio ya que ponemos moviendose = false y en el update no vuelve a entrar con esa condicion
            moviendose = false;

            //Aqui en un futuro podemos poner un if para ver si el guardia es estatico o dinamico y asi el dinamico no tendria que esperar antes de volver
            if(!volviendo){
                cout << "Ha llegado al punto del silbido" << endl;
                activarRelojDeEspera();
            }else{
                cout << "Ha vuelto a la posicion original" << endl;
            }
            volviendo = false;



        }
        direccionDestino = -1;

        sprite->move(direccionDestino*velocidad*_deltaTime,0);
    }
}

void GuardiaEstatico::activarRelojDeEspera(){
    //Reiniciamos el reloj, le decimo que no se mueva, le decimos que esta esperando y le decimos que su proxima posicion sera de la que viene
    tiempoAntesDeVolver.restart();
    moviendose = false;
    esperando = true;
    posicionDestino = xInicial;
}

void GuardiaEstatico::drawNinjaEstatico(sf::RenderWindow &window){
    window.draw(*sprite);
}


//Getters
bool GuardiaEstatico::getMoviendose(){return moviendose;}
bool GuardiaEstatico::getEsperando(){return esperando;}
bool GuardiaEstatico::getVolviendo(){return volviendo;}
float GuardiaEstatico::getPosicionDestino(){return posicionDestino;}
float GuardiaEstatico::getVelocidad(){return velocidad;}
float GuardiaEstatico::getxInicial(){return xInicial;}
sf::Sprite* GuardiaEstatico::getSprite(){return sprite;}
sf::Clock GuardiaEstatico::getTiempoAntesDeVolver(){return tiempoAntesDeVolver;}


//Setters
void GuardiaEstatico::setPosicionDestino(float _x){posicionDestino = _x;}
void GuardiaEstatico::setEsperando(bool _esperando){esperando = _esperando;}
void GuardiaEstatico::setMoviendose(bool _silbido){moviendose = _silbido;}
void GuardiaEstatico::setVolviendo(bool _volviendo){volviendo = _volviendo;}

GuardiaEstatico::~GuardiaEstatico()
{
    //dtor
}
