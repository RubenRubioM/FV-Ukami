#ifndef OJOJADE_H
#define OJOJADE_H

#include <SFML/Graphics.hpp>

class OjoJade
{
public:
    OjoJade();
    virtual ~OjoJade();
    void draw(sf::RenderWindow &window);
    void update(float);
    sf::Sprite getSprite();

protected:
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
};

#endif // OJOJADE_H
