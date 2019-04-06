#include "Ninja2.h"
#define F 30.0f

Ninja2::Ninja2(float posx, float posy, b2World* world)
{
       cout<<"Creamos ninja"<<endl;
        texture.loadFromFile("tileset/ninja2.png");
        sprite.setTexture(texture);
        sprite.setScale(0.8, 0.8);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
    // =========Cosas de box2D======
        b2BodyDef bodydef;
        bodydef.position.Set(posx / F, posy / F);
        bodydef.type = b2_dynamicBody;
        ninjaBody = world->CreateBody(&bodydef);
        ninjaBody->SetLinearDamping(0);

        b2PolygonShape shape;
        shape.SetAsBox((sprite.getGlobalBounds().width / 2.f) / F, (sprite.getGlobalBounds().height / 2.f) / F);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 10.f;
        fixtureDef.friction = 20.f;
        fixtureDef.restitution = 0.f;
        fixtureDef.shape = &shape;
        ninjaBody->CreateFixture(&fixtureDef);

    // =============================

    //Slider del sigilo
    sliderSigilo[0].setSize(sf::Vector2f(maxSigilo,10));
    sliderSigilo[0].setFillColor(sf::Color::Red);
    sliderSigilo[0].setPosition(sf::Vector2f(200,100));
    sliderSigilo[1].setSize(sf::Vector2f(maxSigilo,10));
    sliderSigilo[1].setFillColor(sf::Color::Transparent);
    sliderSigilo[1].setOutlineColor(sf::Color::White);
    sliderSigilo[1].setOutlineThickness(3);
    sliderSigilo[1].setPosition(sf::Vector2f(200,100));
}

Ninja2::~Ninja2()
{
    //dtor
}

void Ninja2::updateMovement(View &view, float _deltaTime)
{


    //Comprobamos que puede volver a saltar

    if(cdSalto.getElapsedTime().asSeconds() > 1.5f){
        cdSalto.restart();
        saltando = false;
    }

    //Si esta en sigilo entra y mientras se le acabe el sigilo va descargandolo
    if(enSigilo){
        if(tiempoSigilo.getElapsedTime().asSeconds()>duracionSigilo){
            desactivarSigilo();
        }else{
            descargarSigilo(_deltaTime);
        }
    //Aqui entra cuando el sigilo se descarga por complejo y aun no se ha cargado entero
    }else if(!enSigilo && !sigiloMax){
        cargarSigilo(_deltaTime);
    }

    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = velocity * _deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);

    }

    if(Keyboard::isKeyPressed(Keyboard::A))
    {
        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -velocity * _deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);

    }

    if(Keyboard::isKeyPressed(Keyboard::Space))
    {

        if(!saltando){
            ninjaBody->ApplyLinearImpulse(b2Vec2(0, -impulsoSalto),ninjaBody->GetWorldCenter(), true);
            saltando = true;
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::P)){

        //Para que no pueda entrar en sigilo cuando ya esta en sigilo
        if(!enSigilo && sigiloMax){
            activarSigilo();
        }
    }



}


void Ninja2::drawNinja(RenderWindow &window)
{
    sprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F );
    window.draw(sprite);

    //Dibujamos los sliders del sigilo
    window.draw(sliderSigilo[0]);
    window.draw(sliderSigilo[1]);

}

Sprite Ninja2::getSprite()
{
    return sprite;
}

