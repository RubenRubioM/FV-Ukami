#include "GuardiaDinamico.h"
#define F 30.0f

GuardiaDinamico::GuardiaDinamico(float posx, float posy)
{


    cout<<"Creamos guardia dinamico"<<endl;
    texture = new sf::Texture();
    texture->loadFromFile("tileset/guardian1.png");
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(10+texture->getSize().x / 2.f, texture->getSize().y / 2.f);
    sprite->setPosition(posx,posy);
    sprite->scale(0.4f,0.4f);




    // =============================

    // ==== Triangulo de vision ====
    triangle = new sf::ConvexShape();
    triangle->setPointCount(3);
    triangle->setFillColor(sf::Color(250,250,0,150));
    triangle->setOutlineThickness(2);
    triangle->setOutlineColor(sf::Color::Red);
    triangle->setPoint(0, sf::Vector2f(0, 0));
    triangle->setPoint(1, sf::Vector2f(250,100));
    triangle->setPoint(2, sf::Vector2f(250,-80));
    triangle->setPosition(posx+50,posy-20);
    triangle->setOrigin(0,0);
}

void GuardiaDinamico::updateGuardiaDinamico(float _deltaTime){

    if(metros<rango){ //LA DISTANCIA QUE PUEDE RECORRER
        //Hacia la derecha
        sprite->setTextureRect(sf::IntRect(0,0,sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        sprite->move(velocidad*_deltaTime,0);
        triangle->setRotation(0);
        //triangle->move(velocidad*_deltaTime,0);
        triangle->setPosition(sprite->getPosition().x + 80, sprite->getPosition().y);
        metros++;
    }
    else{
        //Hacia la izquierda
        sprite->setTextureRect(sf::IntRect(sprite->getTexture()->getSize().x,0,-sprite->getTexture()->getSize().x,sprite->getTexture()->getSize().y));
        sprite->move(-velocidad*_deltaTime,0);
        triangle->setRotation(180);
        //triangle->move(-velocidad*_deltaTime,0);
        triangle->setPosition(sprite->getPosition().x -80, sprite->getPosition().y);
        metros++;
        if(metros>rango*2){ //DOBLE DE LA DISTANCIA
            metros=0;
        }
    }
}


void GuardiaDinamico::drawGuardiaDinamico(sf::RenderWindow &window){

    window.draw(*sprite);
    window.draw(*triangle);
}



sf::ConvexShape* GuardiaDinamico::getVision(){return triangle;}

GuardiaDinamico::~GuardiaDinamico()
{
    //dtor
}
