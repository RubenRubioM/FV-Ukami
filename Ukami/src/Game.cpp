
#include "Game.h"

#include <iostream>
#include <math.h>
#include <algorithm>

#define UPDATE_TICK 1000.0/15.0

/*

    La camara solo se mueve cuando un personaje este en getCenter()*2 o este en getCenter()*2- CamaraXSize
    Camara de 800 en X si esta en 1000, sus bordes seran 200 y 1000
    Ej: Si el centro de la camara esta en 1000, entonces los limites seran (500*2) y 500*2-800 ---> 1000 2000

    16/03 - Una vez se si estan en el borde de la ventana o no deberia comprobar si estan a la maxima distancia o no
            y despues si lo estan deberia comprobar si se van a mover hacia la direccion que pueden o la que no pueden


*/

using namespace std;

Game* Game::unicaInstancia=0;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();
    window->setFramerateLimit(240);
    bgTexture = new sf::Texture();
    bgTexture->loadFromFile("Assets/bg.png");
    background = new sf::Sprite(*bgTexture);

    personaje1 = Ninja1::getInstance();
    personaje2 = Ninja2::getInstance();

    camara = Camara::getInstance();


    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();
    window->setView(*camara->getView());

    //Dibujamos todos los sprites
    window->draw(*background);
    window->draw(*personaje1->getSprite());
    window->draw(*personaje2->getSprite());


    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    sf::Clock deltaClock;
    while(window->isOpen()){
        deltaTime = deltaClock.restart();

        eventsLoop();

        personaje1->moverse(deltaTime.asMilliseconds());
        personaje2->moverse(deltaTime.asMilliseconds());
        /*
            Ahora lo que quiero hacer es que si uno esta en el borde el otro personaje se mueva igualmente
        */
        if(comprobarDistanciaEntrePersonajes()<camara->getCamaraXSize()){
          camara->moverCamara((personaje1->getSprite()->getPosition().x+personaje2->getSprite()->getPosition().x)/2);
        }else{

            //Los personajes estan en la distancia maxima, ahora comprobamos quien esta en la izquierda y quien en la derecha para setear posiciones
            if(personaje1->getSprite()->getPosition().x>personaje2->getSprite()->getPosition().x){
                //El personaje1 esta en la derecha

                if(personaje2->getMoviendose() && personaje2->getDireccion()==-1){
                    //Arrastramos hacia la izquierda
                    personaje1->getSprite()->setPosition(personaje2->getSprite()->getPosition().x+camara->getCamaraXSize()-2,personaje1->getSprite()->getPosition().y);

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



        draw();
    }
}

void Game::eventsLoop(){

    while(window->pollEvent(*event)){

        switch(event->type){

            //Presiona la tecla
            case sf::Event::KeyPressed:
                switch(event->key.code){

                    case sf::Keyboard::Escape:

                        window->close();
                        break;

                    case sf::Keyboard::W: //Presiona la W

                        break;

                    case sf::Keyboard::D: //Presiona la D
                        personaje1->setDireccion(1);
                        personaje1->setMoviendose(true);

                        break;

                    case sf::Keyboard::A: //Presiona la A
                        personaje1->setDireccion(-1);
                        personaje1->setMoviendose(true);
                        break;

                    case sf::Keyboard::Right:
                        personaje2->setDireccion(1);
                        personaje2->setMoviendose(true);
                        break;

                    case sf::Keyboard::Left:
                        personaje2->setDireccion(-1);
                        personaje2->setMoviendose(true);
                        break;

                    default:
                        break;


                }//End KeyPressed event
                break;


            //Levanta la tecla
            case sf::Event::KeyReleased:
                switch(event->key.code){

                    case sf::Keyboard::D:
                        personaje1->setMoviendose(false);
                        break;

                    case sf::Keyboard::A:
                        personaje1->setMoviendose(false);
                        break;
                    case sf::Keyboard::Right:
                        personaje2->setMoviendose(false);
                        break;
                    case sf::Keyboard::Left:
                        personaje2->setMoviendose(false);
                        break;

                }//End KeyReleased event
                break;

            //Hit close button
            case sf::Event::Closed:

                window->close();
                break;



        }//End switch event type


    }//End events loop


}

float Game::comprobarDistanciaEntrePersonajes(){
    float resultado = 0;

    resultado = fabs(personaje1->getSprite()->getPosition().x - personaje2->getSprite()->getPosition().x);

    return resultado;
}

sf::RenderWindow* Game::getWindow(){return window;}


Game::~Game()
{
    //dtor
}
