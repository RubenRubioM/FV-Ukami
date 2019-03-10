#include "Ninja1.h"
#include <iostream>
#include <Game.h>
Ninja1* Ninja1::unicaInstancia=0;

//Constructor del ninja1
Ninja1::Ninja1()
{
    velocidad = 0.3;

    texture = new sf::Texture();
    texture->loadFromFile("Assets/Adventurer/adventurer-Sheet.png",sf::IntRect(0,0,48,43));
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(sprite->getTexture()->getSize().x/2.f,sprite->getTexture()->getSize().y/2.f);
    sprite->setPosition(40,40); //We set origin to 16,16 so now we have to spawn him at 16,16 instead of 0,0
    sprite->scale(2.f,2.f);

    //Slider del sigilo
    sliderSigilo[0].setSize(sf::Vector2f(maxSigilo,10));
    sliderSigilo[0].setFillColor(sf::Color::Red);
    sliderSigilo[0].setPosition(sf::Vector2f(100,100));
    sliderSigilo[1].setSize(sf::Vector2f(maxSigilo,10));
    sliderSigilo[1].setFillColor(sf::Color::Transparent);
    sliderSigilo[1].setOutlineColor(sf::Color::White);
    sliderSigilo[1].setOutlineThickness(3);
    sliderSigilo[1].setPosition(sf::Vector2f(100,100));

}


Ninja1::~Ninja1()
{
    //dtor
}
