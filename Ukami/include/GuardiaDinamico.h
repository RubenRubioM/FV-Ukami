#ifndef GUARDIADINAMICO_H
#define GUARDIADINAMICO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "AnimatedSprite.h"
#include "Animation.h"
#include "AudioManager.h"

using namespace std;

class GuardiaDinamico
{
public:
    GuardiaDinamico(float, float);
    virtual ~GuardiaDinamico();

    bool getMoviendose();
    AnimatedSprite getSprite();
    sf::Sprite getVision();

    //Metodos
    void drawGuardiaDinamico(sf::RenderWindow &window);
    void updateGuardiaDinamico(float, sf::Clock, int);

private:
    sf::Texture *texture;
    sf::Texture texture2;
    sf::Texture texture3;
    sf::Sprite *sprite;
    Animation animacion;
    Animation animacion2;
    Animation *currentAnimation;
    sf::Texture tex_spotlight;
    sf::Sprite sp_spotlight;
    AnimatedSprite animatedSprite;
    sf::ConvexShape *triangle; //Vision
    float velocidad = 0.12;
    int metros = 0;
    int rango = 220; //Rango de distancia que anda
    sf::Clock relojFlotacion;
    bool subiendo = false;
};

#endif // GUARDIADINAMICO_H
