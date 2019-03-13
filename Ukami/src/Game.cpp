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
    personaje1->sliderVisto[0].setSize(sf::Vector2f(1000,10));
    enemigo1 = Enemigo1::getInstance();
    enemigo2 = Enemigo2::getInstance();

    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();

    //Dibujamos todos los sprites
    window->draw(*personaje1->getSprite());
    window->draw(*personaje2->getSprite());
    //window->draw(personaje1->getSliderSigilo()[0]);
    //window->draw(personaje1->getSliderSigilo()[1]);
    window->draw(personaje1->getSliderVisto()[0]);
    window->draw(personaje1->getSliderVisto()[1]);
    window->draw(*enemigo1->getSprite());
    window->draw(*enemigo1->getVista());
    window->draw(*enemigo2->getSprite());
    window->draw(*enemigo2->getVista());


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
        personaje2->moverse(deltaTime.asMilliseconds());


        sf::FloatRect shape1 = personaje1->sprite->getGlobalBounds(); //Guarda la posicion del ninja1
        sf::FloatRect shape4 = personaje2->sprite->getGlobalBounds(); //Guarda la posicion del ninja2
        sf::FloatRect shape2 = enemigo1->getVista()->getGlobalBounds(); //Guarda la posicion del rango de vista del enemigo1
        sf::FloatRect shape3 = enemigo2->getVista()->getGlobalBounds(); //Guarda la posicion del rango de vista del enemigo2
        personaje1->detectado(shape1, shape2, shape3); //Llama a la funcion de deteccion del ninja1
        personaje2->detectado(shape4, shape2, shape3); //Llama a la funcion de deteccion del ninja2


        //Si esta en sigilo entra y mientras se le acabe el sigilo va descargandolo
        if(personaje1->getEnSigilo()){
            if(personaje1->getTiempoSigilo().getElapsedTime().asSeconds()>personaje1->getDuracionSigilo()){
                personaje1->desactivarSigilo();
            }else{
                personaje1->descargarSigilo(deltaTime.asSeconds());
            }
        //Aqui entra cuando el sigilo se descarga por complejo y aun no se ha cargado entero
        }else if(!personaje1->getEnSigilo() && !personaje1->getSigiloMax()){
            personaje1->cargarSigilo(deltaTime.asSeconds());
        }

        //Si esta en sigilo entra y mientras se le acabe el sigilo va descargandolo
        if(personaje2->getEnSigilo()){
            if(personaje2->getTiempoSigilo().getElapsedTime().asSeconds()>personaje1->getDuracionSigilo()){
                personaje2->desactivarSigilo();
            }else{
                personaje2->descargarSigilo(deltaTime.asSeconds());
            }
        //Aqui entra cuando el sigilo se descarga por complejo y aun no se ha cargado entero
        }else if(!personaje2->getEnSigilo() && !personaje2->getSigiloMax()){
            personaje2->cargarSigilo(deltaTime.asSeconds());
        }

        enemigo1->moverse(deltaTime.asMilliseconds());
        enemigo2->moverse(deltaTime.asMilliseconds());
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

                    case sf::Keyboard::Right: //Presiona la D
                        personaje2->setDireccion(1);
                        personaje2->setMoviendose(true);
                        break;

                    case sf::Keyboard::Left: //Presiona la A
                        personaje2->setDireccion(-1);
                        personaje2->setMoviendose(true);
                        break;

                    case sf::Keyboard::C: //Presiona la D
                        enemigo1->setDireccion(1);
                        enemigo1->setMoviendose(true);
                        break;

                    case sf::Keyboard::Z: //Presiona la A
                        enemigo1->setDireccion(-1);
                        enemigo1->setMoviendose(true);
                        break;

                    case sf::Keyboard::E: //Presiona la D
                        enemigo2->setDireccion(1);
                        enemigo2->setMoviendose(true);
                        break;

                    case sf::Keyboard::Q: //Presiona la A
                        enemigo2->setDireccion(-1);
                        enemigo2->setMoviendose(true);
                        break;
                    case sf::Keyboard::P:
                    //Para que no pueda entrar en sigilo cuando ya esta en sigilo
                        if(!personaje1->getEnSigilo() && personaje1->getSigiloMax()){
                            personaje1->activarSigilo();
                        }

                    break;
                    case sf::Keyboard::O:
                    //Para que no pueda entrar en sigilo cuando ya esta en sigilo
                        if(!personaje2->getEnSigilo() && personaje2->getSigiloMax()){
                            personaje2->activarSigilo();
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
                    case sf::Keyboard::C:
                        enemigo1->setMoviendose(false);
                        break;

                    case sf::Keyboard::Z:
                        enemigo1->setMoviendose(false);
                        break;
                    case sf::Keyboard::E:
                        enemigo2->setMoviendose(false);
                        break;

                    case sf::Keyboard::Q:
                        enemigo2->setMoviendose(false);
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
