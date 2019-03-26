
#include "Game.h"

#include <iostream>
#include <math.h>
#include <algorithm>

#define UPDATE_TICK 66.6666

using namespace std;

Game* Game::unicaInstancia=0;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();
    window->setFramerateLimit(90);

    personaje1 = Ninja1::getInstance();

    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();

    //Dibujamos todos los sprites
    window->draw(*personaje1->getSprite());

    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    while(window->isOpen()){
        deltaTime = deltaClock.restart();


        eventsLoop();

        if(updateClock.getElapsedTime().asMilliseconds()>UPDATE_TICK){
            tiempoDesdeIA = updateClock.restart();

            personaje1->nuevoEstado(personaje1->getNewX(),personaje1->getSprite()->getPosition().y);
            personaje1->setNewX(personaje1->getNewX()+5);
        }

        float percentTick2 = (float)updateClock.getElapsedTime().asMilliseconds()/(float)UPDATE_TICK;
        float percentTick = min(1.f,percentTick2);

        //personaje1->moverse(deltaTime.asMilliseconds());
        personaje1->moverseInterpolado(deltaTime.asMilliseconds(),percentTick);
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

sf::RenderWindow* Game::getWindow(){return window;}


Game::~Game()
{
    //dtor
}
