#include "Ninja.h"
#include <cmath>
#define F 100.0

Ninja::Ninja()
{

}

Ninja::~Ninja()
{
    //dtor
}

void Ninja::updateMovement(View &view)
{

    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = 4.f;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        //ninjaBody->ApplyLinearImpulse(b2Vec2(200.f, 0),ninjaBody->GetPosition(), true);
    }

    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -4.f;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);

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


void Ninja::drawNinja(RenderWindow &window)
{
    sprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F + 20);
    window.draw(sprite);
}
