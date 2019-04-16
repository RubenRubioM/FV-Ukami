#include "Ninja2.h"
#define F 30.0f

Ninja2::Ninja2(float posx, float posy, b2World* world)
{
       cout<<"Creamos ninja"<<endl;
        texture.loadFromFile("tileset/ninja2.png");
        texture.setSmooth(true);
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
        fixtureDef.friction = 0.5f;
        fixtureDef.shape = &shape;
        ninjaBody->CreateFixture(&fixtureDef);

    // =============================
}

Ninja2::~Ninja2()
{
    //dtor
}

void Ninja2::updateMovement(View &view, float _deltaTime,sf::Clock frameClock)
{

    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = velocity*10;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
    }

    if(Keyboard::isKeyPressed(Keyboard::A))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -velocity*10;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
    }

    if(Keyboard::isKeyPressed(Keyboard::W))
    {

        ninjaBody->ApplyLinearImpulse(b2Vec2(0, -30.0f),ninjaBody->GetWorldCenter(), true);
    }



}


void Ninja2::drawNinja(RenderWindow &window)
{
    sprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F );
    //sf::RectangleShape r(Vector2f(sprite.getGlobalBounds().width, sprite.getGlobalBounds().height));
    //r.setPosition(sprite.getPosition().x,sprite.getPosition().y);
    //window.draw(r);
    window.draw(sprite);

}

Sprite Ninja2::getSprite()
{
    return sprite;
}

