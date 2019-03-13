#include "Ninja2.h"
#include <iostream>
#include <Game.h>
Ninja2* Ninja2::unicaInstancia=0;


Ninja2::Ninja2()
{
    velocidad = 0.3;

    texture = new sf::Texture();

    texture->loadFromFile("Assets/Adventurer/adventurer-Sheet.png",sf::IntRect(0,0,48,43));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(40,400); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(2.f,2.f);
}


void Ninja2::moverse(float _deltaTime){

    if(moviendose){

        sprite->move(direccion*velocidad* _deltaTime,0);
    }

}

//int veces=0; //Esto es temporal para pruebas, luego hay que meterlo como variable al ninja

//Recibe por parametro las posiciones del nina (s1) y de la vista del enemigo (s2)
void Ninja2::detectado(sf::FloatRect s1, sf::FloatRect s2, sf::FloatRect s3){


        if(!this->enSigilo){
            if (s1.intersects(s2))
            {
                //veces++; //Temporal
                std::cout << "Por Enemigo1; Has sido detectado " << "veces" << std::endl;
                restaVisto(1);
            }

            if (s1.intersects(s3))
            {

                std::cout << "Por Enemigo2; Has sido detectado " << "veces" << std::endl;
                restaVisto(1);
            }
        }
}

Ninja2::~Ninja2()
{
    //dtor
}
