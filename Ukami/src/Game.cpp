/*

    TODO:

    1) Falta añadir el sonido cuando silbas
    2) Falta el reloj para que pasado un tiempo vuelva a su posicion original

*/
#include "Game.h"

#include <iostream>
#include <math.h>
#include <algorithm>

#define UPDATE_TICK 1000.0/15.0

using namespace std;

Game* Game::unicaInstancia=0;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();
    window->setFramerateLimit(10);
    guardiaCercano = 0;
    personaje1 = Ninja1::getInstance();
    guardias.push_back(new Guardia(200.f,200.f));
    guardias.push_back(new Guardia(900.f,200.f));




    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();

    //Dibujamos todos los sprites
    window->draw(*personaje1->getSprite());
    window->draw(*guardias[0]->getSprite());
    window->draw(*guardias[1]->getSprite());
    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    sf::Clock deltaClock;
    while(window->isOpen()){
        deltaTime = deltaClock.restart();
        //cout << deltaTime.asMilliseconds() << endl;

        eventsLoop();
        personaje1->moverse(deltaTime.asMilliseconds());

        if(guardiaCercano != 0 && guardiaCercano->getEfectoSilbido()){

            guardiaCercano->moverseAlSilbido(deltaTime.asMilliseconds());
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

                    case sf::Keyboard::R:
                        guardiaCercano = guardiaMasCercano();
                        guardiaCercano->setEfectoSilbido(true);
                        guardiaCercano->setAntiguaX(guardiaCercano->getSprite()->getPosition().x); //Le decimos que guarde la posicion donde estaba antes de moverse para despues volver
                        guardiaCercano->setPosicionSilbido(personaje1->getSprite()->getPosition().x); //Le decimos que tiene que ir hasta el X del personaje que silba
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
                    case sf::Keyboard::W:

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


Guardia* Game::guardiaMasCercano(){
    float distanciaMinima = 999999;
    float distancia = 0;
    float powX = 0;
    float powY = 0;
    Guardia* guardiaCercano;

    //Recorremos todos los guardas y calculamos cual esta mas cerca
    for(int i=0; i < guardias.size();i++){
        powX = pow(personaje1->getSprite()->getPosition().x-(guardias.at(i)->getSprite()->getPosition().x),2);
        powY = pow(personaje1->getSprite()->getPosition().y-(guardias.at(i)->getSprite()->getPosition().y),2);

        distancia = fabs(sqrt(powX+powY));
        cout << "Distancia entre Ninja 1 y Guardia " << i << " ->" << distancia << endl;

        //Se devuelve el guardia mas cercano
        if(distancia < distanciaMinima){

            guardiaCercano = guardias.at(i);
            distanciaMinima = distancia;
        }

    }

    return guardiaCercano;
}

sf::RenderWindow* Game::getWindow(){return window;}


Game::~Game()
{
    //dtor
}
