
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
    window->setFramerateLimit(240);

    personaje1 = Ninja1::getInstance();
    personaje2 = Ninja2::getInstance();

    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();

    //Dibujamos todos los sprites
    window->draw(*personaje1->getSprite());
    window->draw(*personaje2->getSprite());
    window->draw(personaje1->getSliderSigilo()[0]);
    window->draw(personaje1->getSliderSigilo()[1]);

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

        if(personaje1->getEnSigilo()){
            if(personaje1->getTiempoSigilo().getElapsedTime().asSeconds()>personaje1->getDuracionSigilo()){
                personaje1->desactivarSigilo();
            }else{
                personaje1->descargarSigilo(deltaTime.asSeconds());
            }

        }else if(!personaje1->getEnSigilo() && !personaje1->getSigiloMax()){
            personaje1->cargarSigilo(deltaTime.asSeconds());
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

                    case sf::Keyboard::Q:
                        //Para que no pueda entrar en sigilo cuando ya esta en sigilo
                        if(!personaje1->getEnSigilo() && personaje1->getSigiloMax()){
                            personaje1->activarSigilo();
                        }

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

sf::RenderWindow* Game::getWindow(){return window;}


Game::~Game()
{
    //dtor
}
