#include "Enemigo1.h"
#define F 30.0f


//Constructor del Enemigo1
Enemigo1::Enemigo1(float posx, float posy, b2World* world)
{

    metros=0;

    cout<<"Creamos enemigo 1"<<endl;
    texture = new sf::Texture;
    texture->loadFromFile("tileset/ninja2.png");
    texture->setSmooth(true);
    sprite = new sf::Sprite(*texture);
    sprite->setScale(0.8, 0.8);
    sprite->setOrigin(10+texture->getSize().x / 2.f, texture->getSize().y / 2.f);


    triangle = new sf::ConvexShape();
    triangle->setPointCount(3);



    // =========Cosas de box2D======
    b2BodyDef bodydef;
    bodydef.position.Set(posx / F, posy / F);
    bodydef.type = b2_dynamicBody;
    ninjaBody = world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox((sprite->getGlobalBounds().width / 2.f) / F, (sprite->getGlobalBounds().height / 2.f) / F);

    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.5f;
    fixtureDef.friction = 0.5f;
    fixtureDef.shape = &shape;
    ninjaBody->CreateFixture(&fixtureDef);

    // =============================

    // =========Vision======
    triangle->setFillColor(sf::Color(250,250,0));
    triangle->setPoint(0, sf::Vector2f(0, 0));
    triangle->setPoint(1, sf::Vector2f(250,50));
    triangle->setPoint(2, sf::Vector2f(250,-50));
    triangle->setPosition(posx,posy);
    triangle->setOrigin(0,0);
    // =============================

}

void Enemigo1::ia(float _deltaTime){

    if(metros < distanciaMaxima){ //LA DISTANCIA QUE PUEDE RECORRER
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = velocity*_deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        triangle->setRotation(0);
        triangle->move(vel.x*_deltaTime,0);
        metros++;
    }
    else{

        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -velocity*_deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        triangle->setRotation(180);
        triangle->move(vel.x*_deltaTime,0);
        metros++;
        if(metros > distanciaMaxima*2){ //DOBLE DE LA DISTANCIA
            metros=0;
        }
    }
}




Enemigo1::~Enemigo1()
{
    //dtor
}
