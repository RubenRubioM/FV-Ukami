#include "Ninja1.h"
#define F 100.0

Ninja1::Ninja1(float posx, float posy, b2World* world)
{
        cout<<"Creamos ninja"<<endl;
        texture.loadFromFile("tileset/box_box2d.png");
        sprite.setTexture(texture);
        sprite.setOrigin(posx, posy);
        sprite.setScale(0.06, 0.06);

    // =========Cosas de box2D======
        b2BodyDef bodydef;
        bodydef.position.Set(posx / F, posy / F);
        bodydef.type = b2_dynamicBody;
        ninjaBody = world->CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((sprite.getGlobalBounds().width / 2.f) / F, (sprite.getGlobalBounds().height / 2.f) / F);

        cout<<"Anchura: "<<((sprite.getGlobalBounds().width / 2.f) / F)<<endl;
        cout<<"Altura: "<<((sprite.getGlobalBounds().height / 2.f) / F)<<endl;
        b2FixtureDef fixtureDef;
        fixtureDef.density = 10.0f;
        fixtureDef.friction = 10.f;
        //fixtureDef.restitution = 1.f;
        fixtureDef.shape = &shape;
        ninjaBody->CreateFixture(&fixtureDef);

    // =============================
}

Ninja1::~Ninja1()
{
    //dtor
}

void Ninja1::updateMovement(View &view)
{
    moviendose = false;

    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = 4.f;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        //ninjaBody->ApplyLinearImpulse(b2Vec2(200.f, 0),ninjaBody->GetPosition(), true);
        moviendose = true;
    }

    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -4.f;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        moviendose = true;
        //ninjaBody->ApplyLinearImpulse(b2Vec2(-200.f, 0),ninjaBody->GetPosition(), true);
    }

    if(Keyboard::isKeyPressed(Keyboard::Space))
    {
        cout<<"Mass: "<<ninjaBody->GetMass()<<endl;
        ninjaBody->ApplyLinearImpulse(b2Vec2(0, -0.8f),ninjaBody->GetWorldCenter(), true);
    }


    // Esto es para updatear la posición la camara que sigue al ninja
    if(ninjaBody->GetPosition().x > 960)
        view.setCenter(ninjaBody->GetPosition().x, view.getSize().y / 2.f);
    else
        view.setCenter(view.getSize().x / 2, view.getSize().y / 2.f);
}


void Ninja1::drawNinja(RenderWindow &window)
{
    sprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F + 20);
    window.draw(sprite);
}

Sprite Ninja1::getSprite()
{
    return sprite;
}
