#ifndef NINJA2_H
#define NINJA2_H

#include "Ninja.h"

class Ninja2 : public Ninja
{
public:
    Ninja2(float posx, float posy, b2World *world);
    void updateMovement(View &view, float, sf::Clock);
    void drawNinja(RenderWindow &window);
    void setTrepando(bool);
    void setAnimationPull(int);
    AnimatedSprite getSprite();
    bool trepando;
    bool arrastrando;
    int velocidad;
    int direccionSaltar;
    int direccionArrastrar;
    virtual ~Ninja2();

protected:
private:
    sf::Texture texture3;
    sf::Texture texture4;
    sf::Texture texture5;
    sf::Texture texture_pull_left;
    sf::Texture texture_pull_right;
    sf::Clock cdTrepar;
    Animation treparAnimation;
    Animation sigiloAnimationRight;
    Animation sigiloAnimationLeft;
    Animation pullAnimationLeft;
    Animation pullAnimationRight;
};

#endif // NINJA2_H
