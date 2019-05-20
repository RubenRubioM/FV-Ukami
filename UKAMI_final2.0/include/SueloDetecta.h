#ifndef SUELODETECTA_H
#define SUELODETECTA_H
#include <SFML/Graphics.hpp>

class SueloDetecta
{
public:
    SueloDetecta(int, float, float);
    void draw(sf::RenderWindow &window);

    sf::Sprite getSprite();

protected:
private:
    sf::Sprite sp_sueloDetecta;
    sf::Texture tex_sueloDetecta;
};

#endif // SUELODETECTA_H
