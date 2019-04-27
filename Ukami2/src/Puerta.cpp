#include "Puerta.h"
#define F 30.0f

Puerta::Puerta(int x, int y, b2World* world)
{
    texture.loadFromFile("tileset/door1.png");
    texture.setSmooth(true);

    sprite.setTexture(texture);
    // 1800-620
    sprite.setPosition(x,y);

      // =========Cosas de box2D======
    b2BodyDef bodydef;
    bodydef.position.Set(x / F, (y+100) / F);
    bodydef.type = b2_kinematicBody;
    puertaBody = world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox((sprite.getGlobalBounds().width - 350 / 2.f) / F, (sprite.getGlobalBounds().height - 500 / 2.f) / F );
    //shape.SetAsBox((233 / 2.f) / F, (176 / 2.f) / F);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 5.0f;
    puertaBody->CreateFixture(&fixtureDef);
    // =============================
}

void Puerta::drawPuerta(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Puerta::ocultarPuerta()
{
    // Con esto haremos desactivar el body de la puerta en el mundo Box2D
    puertaBody->SetActive(false);

    // Vamos a ocultar el sprite de la puerta
    sprite.setScale(0, 0);
}

Puerta::~Puerta()
{
    //dtor
}
