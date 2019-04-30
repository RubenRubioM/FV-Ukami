#include "GuardiaDinamico.h"
#define F 30.0f

GuardiaDinamico::GuardiaDinamico(float posx, float posy, b2World* world)
{


    cout<<"Creamos guardia dinamico"<<endl;
    texture = new sf::Texture();
    texture->loadFromFile("tileset/ninja2.png");
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setOrigin(10+texture->getSize().x / 2.f, texture->getSize().y / 2.f);
    sprite->setPosition(posx,posy);




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
        //b2Vec2 vel = ninjaBody->GetLinearVelocity();
        //vel.x = velocidad;
        //vel.y = ninjaBody->GetLinearVelocity().y;
        //ninjaBody->SetLinearVelocity(vel);
        sprite->move(velocidad*_deltaTime,0);
        triangle->setRotation(0);
        triangle->move(velocidad*_deltaTime,0);
        metros++;
    }
    else{

        //b2Vec2 vel = ninjaBody->GetLinearVelocity();
        //vel.x = -velocidad;
        //vel.y = ninjaBody->GetLinearVelocity().y;
        //ninjaBody->SetLinearVelocity(vel);
        sprite->move(-velocidad*_deltaTime,0);
        triangle->setRotation(180);
        triangle->move(-velocidad*_deltaTime,0);
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
