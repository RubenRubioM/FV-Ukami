#include "Ninja1.h"
#define F 30.0f

Ninja1::Ninja1(float posx, float posy, b2World* world)
{
    cout<<"Creamos ninja 1"<<endl;
    texture.loadFromFile("tileset/ninja1_move_right.png");
    texture.setSmooth(true);

    texture2.loadFromFile("tileset/ninja1_move_left.png");
    texture2.setSmooth(true);

    textureDash.loadFromFile("tileset/ninja1_dash.png");
    textureDash.setSmooth(true);

    walkingAnimationRight = *new Animation();
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

    walkingAnimationLeft = *new Animation();
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

    dashAnimationRight.setSpriteSheet(textureDash);
    dashAnimationRight.addFrame(sf::IntRect(0, 0, 232, 176));

    currentAnimation = new Animation();
    currentAnimation = &walkingAnimationRight;
    noKeyWasPressed = true;

    animatedSprite = *new AnimatedSprite();

    // =========Cosas de box2D======
    b2BodyDef bodydef;
    bodydef.position.Set(posx / F, posy / F);
    bodydef.type = b2_dynamicBody;
    ninjaBody = world->CreateBody(&bodydef);

    shape.SetAsBox((150 / 2.f) / F, (140 / 2.f) / F);

    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0;
    fixtureDef.restitution = 0;
    fixtureDef.shape = &shape;
    ninjaBody->CreateFixture(&fixtureDef);

    // ======= Colider ficticio porque no va el de la animacion =======
    boxCollider = new sf::RectangleShape(sf::Vector2f(walkingAnimationLeft.getFrame(0).width - 75,walkingAnimationLeft.getFrame(0).height));
    boxCollider->setOrigin(boxCollider->getSize().x/2.f,boxCollider->getSize().y/2.f);
    boxCollider->setPosition(700,400);
    boxCollider->setFillColor(sf::Color::Transparent);
    //boxCollider->setOutlineColor(sf::Color::Green);
    //boxCollider->setOutlineThickness(5);

    // =============================

     //Slider del sigilo

    sliderSigilo[0].setSize(sf::Vector2f(maxSigilo,5));
    sliderSigilo[0].setFillColor(sf::Color::Blue);
    sliderSigilo[0].setPosition(sf::Vector2f(110,100));
    sliderSigilo[1].setSize(sf::Vector2f(maxSigilo,5));
    sliderSigilo[1].setFillColor(sf::Color::Transparent);
    sliderSigilo[1].setOutlineColor(sf::Color::Blue);
    sliderSigilo[1].setOutlineThickness(3);
    sliderSigilo[1].setPosition(sf::Vector2f(110,100));



     //Slider del Dash
    sliderDash[0].setSize(sf::Vector2f(maxDash,10));
    sliderDash[0].setFillColor(sf::Color::Red);
    sliderDash[0].setPosition(sf::Vector2f(100,100));
    sliderDash[1].setSize(sf::Vector2f(maxDash,10));
    sliderDash[1].setFillColor(sf::Color::Transparent);
    sliderDash[1].setOutlineColor(sf::Color::White);
    sliderDash[1].setOutlineThickness(3);
    sliderDash[1].setPosition(sf::Vector2f(100,100));

    //Slider de la vida
    sliderVida = new sf::RectangleShape();
    sliderVida->setSize(sf::Vector2f(maxVida,20));
    sliderVida->setFillColor(sf::Color::Blue);
    sliderVida->setPosition(sf::Vector2f(79,60));
}

Ninja1::~Ninja1()
{
    //dtor
}

void Ninja1::updateMovement(View &view, float _deltaTime,sf::Clock frameClock)
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

    //Si esta en Dash entra y mientras se le acabe el Dash va descargandolo
    if(enDash){
        if(tiempoDash.getElapsedTime().asSeconds()>duracionDash){
            desactivarDash();
        }else{
            descargarDash(_deltaTime);
        }
    //Aqui entra cuando el Dash se descarga por completo y aun no se ha cargado entero
    }else if(!enDash && !dashMax){
        cargarDash(_deltaTime);
    }


    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        currentAnimation = &walkingAnimationRight;
        noKeyWasPressed = false;

        // Movemos al Ninja
        ninjaBody->SetLinearVelocity(b2Vec2(10, ninjaBody->GetLinearVelocity().y));
    }

    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        currentAnimation = &walkingAnimationLeft;
        noKeyWasPressed = false;

        // Movemos al Ninja
        ninjaBody->SetLinearVelocity(b2Vec2(-10, ninjaBody->GetLinearVelocity().y));
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

    if(Keyboard::isKeyPressed(Keyboard::K)){
        if(tiempoEntreTeclas.getElapsedTime().asSeconds()>3.f){
            tiempoEntreTeclas.restart();
            cout<<"Hemos pulsado a la K"<<endl;
            //Para que no pueda entrar en Dash cuando ya esta en Dash
            if(!enDash && dashMax){
                activarDash();
                        currentAnimation = &dashAnimationRight;
                noKeyWasPressed = false;
            }
        }

    }

    animatedSprite.play(*currentAnimation);

    // if no key was pressed stop the animation
    if (noKeyWasPressed)
    {
        // No har� ninguna animaci�n
        animatedSprite.stop();
        // Haremos que su velocidad lineal sea 0 para que no deslice
        if(!enDash)
            ninjaBody->SetLinearVelocity(b2Vec2(0,ninjaBody->GetLinearVelocity().y));

    }
    noKeyWasPressed = true;

    // update AnimatedSprite
    animatedSprite.update(frameTime);


}


void Ninja1::drawNinja(RenderWindow &window)
{
    animatedSprite.setOrigin(animatedSprite.getGlobalBounds().width / 2.f, animatedSprite.getGlobalBounds().height / 2.f);
    animatedSprite.setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F );
    window.draw(animatedSprite);

    boxCollider->setPosition(ninjaBody->GetPosition().x * F, ninjaBody->GetPosition().y * F );
    //Quitar esto cuando no queramos ver las hitboxes
    window.draw(*boxCollider);

}

AnimatedSprite Ninja1::getSprite()
{
    return animatedSprite;
}

/*DASHHHHHHHHHHHHHHHHHHHHHHHHHHH*/
//Se llama cuando presionas el Dash
void Ninja1::activarDash(){
    cout<<"Activamos DASH"<<endl;
    enDash = true;

    b2Fixture *fixtureA = ninjaBody->GetFixtureList();
    ninjaBody->DestroyFixture(fixtureA);

    shape.SetAsBox((150 / 2.f) / F, (50 / 2.f) / F);
    fixtureDef.shape = &shape;
    ninjaBody->CreateFixture(&fixtureDef);

    ninjaBody->ApplyLinearImpulse(b2Vec2(250.f, 0),ninjaBody->GetWorldCenter(), true);

    tiempoDash.restart(); //Reiniciamos el reloj para que se vaya desgastando el Dash

}

//Cuando acaba el tiempo de (duracionDash) se llama para desactivarlo
void Ninja1::desactivarDash(){
    enDash = false;

            b2Fixture *fixtureB = ninjaBody->GetFixtureList();
        ninjaBody->DestroyFixture(fixtureB);

        shape2.SetAsBox((150 / 2.f) / F, (140 / 2.f) / F);
        fixtureDef.shape = &shape2;
        ninjaBody->CreateFixture(&fixtureDef);

    //Reiniciamos el reloj para que ahora haga otros (recargaDash) segundos para cargalo
    tiempoDash.restart();
currentAnimation = &walkingAnimationRight;
}

//Va ejecutandose cada frame mientras que activas el Dash hasta que el tiempo trascurrido sea igual a duracionDash
//Y va decrementando la barra de Dash
void Ninja1::descargarDash(float _deltaTime){
    dashMax = false;

    float tiempoDeDashTrascurrido = tiempoDash.getElapsedTime().asSeconds();
    float decremento = maxDash-(tiempoDeDashTrascurrido*(maxDash/duracionDash));

    sliderDash[0].setSize(sf::Vector2f(decremento,10));
}

//Va ejecutandose cada frame mientras que no este en Dash y el Dash no este al maximo
//Y va aumentando el slider interior del Dash
void Ninja1::cargarDash(float _deltaTime){
    float tiempoDeDashTrascurrido = tiempoDash.getElapsedTime().asSeconds();
    float incremento = (tiempoDeDashTrascurrido*(maxDash/recargaDash));

    //Si llenamos el Dash actulizamos la variable de dashMax
    if(incremento >=maxDash){
        dashMax = true;
    }
    sliderDash[0].setSize(sf::Vector2f(incremento,10));

}