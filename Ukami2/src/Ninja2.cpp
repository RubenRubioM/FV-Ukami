#include "Ninja2.h"
#define F 30.0f

Ninja2::Ninja2(float posx, float posy, b2World* world)
{
    cout<<"Creamos ninja 2"<<endl;
    texture.loadFromFile("tileset/ninja2_move_right.png");
    texture.setSmooth(true);

    texture2.loadFromFile("tileset/ninja2_move_left.png");
    texture2.setSmooth(true);

    walkingAnimationRight.setSpriteSheet(texture);
    walkingAnimationRight.addFrameInitial(sf::IntRect(0, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(233, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(466, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(696, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(932, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(1165, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(1398, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(1631, 0, 233, 176));
    walkingAnimationRight.addFrame(sf::IntRect(1864, 0, 233, 176));

    walkingAnimationLeft.setSpriteSheet(texture2);
    walkingAnimationLeft.addFrameInitial(sf::IntRect(1864, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(1631, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(1398, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(1165, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(932, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(696, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(466, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(233, 0, 233, 176));
    walkingAnimationLeft.addFrame(sf::IntRect(0, 0, 233, 176));


    currentAnimation = &walkingAnimationRight;
    noKeyWasPressed = true;

    // =========Cosas de box2D======
    b2BodyDef bodydef;
    bodydef.position.Set(posx / F, posy / F);
    bodydef.type = b2_dynamicBody;
    ninjaBody = world->CreateBody(&bodydef);
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 5.0f;

    shape.SetAsBox((233 / 2.f) / F, (176 / 2.f) / F);
    fixtureDef.shape = &shape;
    ninjaBody->CreateFixture(&fixtureDef);
    // =============================

    // =============================
}

Ninja2::~Ninja2()
{
    //dtor
}

void Ninja2::updateMovement(View &view, float _deltaTime,sf::Clock frameClock)
{

    sf::Time frameTime = frameClock.restart();

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
        currentAnimation = &walkingAnimationRight;
        noKeyWasPressed = false;

        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = velocity*_deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
    }

    if(Keyboard::isKeyPressed(Keyboard::A))
    {
        currentAnimation = &walkingAnimationLeft;
        noKeyWasPressed = false;

        b2Vec2 vel = ninjaBody->GetLinearVelocity();
        vel.x = -velocity*_deltaTime;
        vel.y = ninjaBody->GetLinearVelocity().y;
        ninjaBody->SetLinearVelocity(vel);
    }

    if(Keyboard::isKeyPressed(Keyboard::W))
    {
        if(!saltando){
            ninjaBody->ApplyLinearImpulse(b2Vec2(0, -impulsoSalto),ninjaBody->GetWorldCenter(), true);
            saltando = true;
        }
    }

    if(Keyboard::isKeyPressed(Keyboard::R)){
        //Para que no pueda entrar en sigilo cuando ya esta en sigilo
        if(!enSigilo && sigiloMax){
            activarSigilo();
        }
    }



    animatedSprite.play(*currentAnimation);

    // if no key was pressed stop the animation
    if (noKeyWasPressed)
    {
        animatedSprite.stop();
    }
    noKeyWasPressed = true;

    // update AnimatedSprite
    animatedSprite.update(frameTime);


}


void Ninja2::drawNinja(RenderWindow &window)
{

    animatedSprite.setOrigin(animatedSprite.getGlobalBounds().width / 2.f, animatedSprite.getGlobalBounds().height / 2.f);
    cout << "ASD" << endl;
    animatedSprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F );
    window.draw(animatedSprite);


}

AnimatedSprite Ninja2::getSprite()
{
    return animatedSprite;
}

