#include "GuardiaDinamico.h"
#define F 30.0f

GuardiaDinamico::GuardiaDinamico(float posx, float posy)
{

    cout << "Creamos guardia dinamico" << endl;

    texture2.loadFromFile("tileset/guardian2_move_right.png");
    texture2.setSmooth(true);

    texture3.loadFromFile("tileset/guardian2_move_left.png");
    texture3.setSmooth(true);

    animacion = *new Animation();
    animacion.setSpriteSheet(texture2);
    animacion.addFrameInitial(sf::IntRect(0, 0, 305, 300));
    animacion.addFrame(sf::IntRect(305, 0, 305, 300));
    animacion.addFrame(sf::IntRect(610, 0, 305, 300));
    animacion.addFrame(sf::IntRect(915, 0, 305, 300));
    animacion.addFrame(sf::IntRect(1220, 0, 305, 300));
    animacion.addFrame(sf::IntRect(1525, 0, 305, 300));
    animacion.addFrame(sf::IntRect(1830, 0, 305, 300));
    animacion.addFrame(sf::IntRect(2135, 0, 305, 300));
    animacion.addFrame(sf::IntRect(2440, 0, 305, 300));
    animacion.addFrame(sf::IntRect(2745, 0, 305, 300));
    animacion.addFrame(sf::IntRect(3050, 0, 305, 300));
    animacion.addFrame(sf::IntRect(3355, 0, 305, 300));
    animacion.addFrame(sf::IntRect(3660, 0, 305, 300));
    animacion.addFrame(sf::IntRect(3965, 0, 305, 300));

    animacion2 = *new Animation();
    animacion2.setSpriteSheet(texture3);
    animacion2.addFrameInitial(sf::IntRect(3965, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(3660, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(3355, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(3050, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(2745, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(2440, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(2135, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(1830, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(1525, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(1220, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(915, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(610, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(305, 0, 305, 300));
    animacion2.addFrame(sf::IntRect(0, 0, 305, 300));

    currentAnimation = new Animation();
    currentAnimation = &animacion;

    animatedSprite = *new AnimatedSprite();
    animatedSprite.setOrigin(161 / 2.f, 204 / 2.f);
    animatedSprite.setPosition(posx, posy);
    animatedSprite.setScale(0.85f, 0.85f);

    // =============================

    tex_spotlight.loadFromFile("tileset/spotlight2.png");
    sp_spotlight.setTexture(tex_spotlight);
    sp_spotlight.setOrigin(280, sp_spotlight.getPosition().y / 2);
    sp_spotlight.setScale(1.0f, 0.65f);
}

void GuardiaDinamico::updateGuardiaDinamico(float _deltaTime, sf::Clock frameClock, int guardiaCerca)
{
    sf::Time frameTime = frameClock.restart();

    if(guardiaCerca == 1){
        AudioManager *audio = AudioManager::getInstance();
        AudioManager::getInstance()->guardia2();
    }

    if (metros < rango)
    { //LA DISTANCIA QUE PUEDE RECORRER
        //Hacia la derecha

        currentAnimation = &animacion;
        animatedSprite.move(velocidad * _deltaTime, 0);

        sp_spotlight.setRotation(180);
        sp_spotlight.setPosition(animatedSprite.getPosition().x + 125, animatedSprite.getPosition().y + 55);
        metros++;
    }
    else
    {
        //Hacia la izquierda

        currentAnimation = &animacion2;
        animatedSprite.move(-velocidad * _deltaTime, 0);
        sp_spotlight.setRotation(0);
        sp_spotlight.setPosition(animatedSprite.getPosition().x + 5, animatedSprite.getPosition().y - 110);
        metros++;
        if (metros > rango * 2)
        { //DOBLE DE LA DISTANCIA
            metros = 0;
        }
    }

    animatedSprite.play(*currentAnimation);

    animatedSprite.update(frameTime);
}

void GuardiaDinamico::drawGuardiaDinamico(sf::RenderWindow &window)
{
    window.draw(sp_spotlight);
    window.draw(animatedSprite);
}

sf::Sprite GuardiaDinamico::getVision() { return sp_spotlight; }
AnimatedSprite GuardiaDinamico::getSprite() { return animatedSprite; }

GuardiaDinamico::~GuardiaDinamico()
{
    //dtor
}
