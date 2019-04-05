#include "Ninja1.h"
#define F 30.0f

Ninja1::Ninja1(float posx, float posy, b2World* world)
{
        cout<<"Creamos ninja"<<endl;
        texture.loadFromFile("tileset/ninja1.png");
        sprite.setTexture(texture);
        sprite.setScale(0.8, 0.8);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    // =========Cosas de box2D======
        b2BodyDef bodydef;
        bodydef.position.Set(posx / F, posy / F);
        bodydef.type = b2_dynamicBody;
        ninjaBody = world->CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((sprite.getGlobalBounds().width / 2.f) / F, (sprite.getGlobalBounds().height / 2.f) / F);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 0.5f;
        fixtureDef.friction = 5.0f;
        //fixtureDef.restitution = 1.f;
        fixtureDef.shape = &shape;
        ninjaBody->CreateFixture(&fixtureDef);

    // =============================
}

Ninja1::~Ninja1()
{
    //dtor
}

void Ninja1::updateMovement(View &view,float _deltaTime)
{

    //Comprobamos que puede volver a saltar
    cout << cdSalto.getElapsedTime().asSeconds() << endl;
    if(cdSalto.getElapsedTime().asSeconds() > 1.f){
        cdSalto.restart();
        saltando = false;
    }

    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = velocity*_deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        //ninjaBody->ApplyLinearImpulse(b2Vec2(200.f, 0),ninjaBody->GetPosition(), true);
    }

    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -velocity*_deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
        //ninjaBody->ApplyLinearImpulse(b2Vec2(-200.f, 0),ninjaBody->GetPosition(), true);
    }

    if(Keyboard::isKeyPressed(Keyboard::Space))
    {

        if(!saltando){
            ninjaBody->ApplyLinearImpulse(b2Vec2(0, -100.0f),ninjaBody->GetWorldCenter(), true);
            saltando = true;
        }

    }


    //cout<<"NinjaBody1 Y: "<<view.getCenter().y<<endl;

}


void Ninja1::drawNinja(RenderWindow &window)
{
    sprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F);
    window.draw(sprite);

    sf::RectangleShape r(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    r.setPosition(sprite.getPosition().x / 2.f,sprite.getPosition().y / 2.f);
    //window.draw(r);
}

Sprite Ninja1::getSprite()
{
    return sprite;
}
