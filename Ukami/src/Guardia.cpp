#include "Guardia.h"

Guardia::Guardia(float _x, float _y)
{
     velocidad = 0.3;
    xInicial = _x;
    texture = new sf::Texture();

    texture->loadFromFile("Assets/Guardia.png",sf::IntRect(0,0,32,32));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(_x,_y); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(2.f,2.f);
}

void Guardia::moverse(float _deltaTime){

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

void Guardia::activarRelojDeEspera(){
    //Reiniciamos el reloj, le decimo que no se mueva, le decimos que esta esperando y le decimos que su proxima posicion sera de la que viene
    tiempoAntesDeVolver.restart();
    moviendose = false;
    esperando = true;
    posicionDestino = xInicial;
}


//Getters
bool Guardia::getMoviendose(){return moviendose;}
bool Guardia::getEsperando(){return esperando;}
bool Guardia::getVolviendo(){return volviendo;}
float Guardia::getPosicionDestino(){return posicionDestino;}
float Guardia::getVelocidad(){return velocidad;}
float Guardia::getxInicial(){return xInicial;}
sf::Sprite* Guardia::getSprite(){return sprite;}
sf::Clock Guardia::getTiempoAntesDeVolver(){return tiempoAntesDeVolver;}


//Setters
void Guardia::setPosicionDestino(float _x){posicionDestino = _x;}
void Guardia::setEsperando(bool _esperando){esperando = _esperando;}
void Guardia::setMoviendose(bool _silbido){moviendose = _silbido;}
void Guardia::setVolviendo(bool _volviendo){volviendo = _volviendo;}

Guardia::~Guardia()
{
    //dtor
}
