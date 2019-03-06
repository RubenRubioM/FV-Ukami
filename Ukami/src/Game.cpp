
#include "Game.h"

#include <iostream>
#include <math.h>



using namespace std;

Game::Game(int x, int y, string title)
{

    window = new sf::RenderWindow(sf::VideoMode(x,y),title);
    event = new sf::Event();

    //GameLoop, infinity iterations
    gameLoop();
}

void Game::draw(){
    window->clear();

    //Dibujamos todos los sprites


    window->display();
}

//Function that executes once per frame
void Game::gameLoop(){

    while(window->isOpen()){
        eventsLoop();
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
                        cout << "ASDASD";
                        break;

                    case sf::Keyboard::A: //Presiona la A

                        break;

                    default:
                        break;


                }//End KeyPressed event
                break;


            //Levanta la tecla
            case sf::Event::KeyReleased:
                switch(event->key.code){

                    case sf::Keyboard::D:

                        break;

                    case sf::Keyboard::A:

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


Game::~Game()
{
    //dtor
}
