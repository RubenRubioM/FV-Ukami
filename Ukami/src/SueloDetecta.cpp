#include "SueloDetecta.h"

SueloDetecta::SueloDetecta(int tipo, float x, float y)
{
    if (tipo == 1)
    {
        tex_sueloDetecta.loadFromFile("tileset/sueloDetecta1.png");
    }
    if (tipo == 2)
    {
        tex_sueloDetecta.loadFromFile("tileset/sueloDetecta2.png");
    }
    if (tipo == 3)
    {
        tex_sueloDetecta.loadFromFile("tileset/sueloDetecta3.png");
    }

    tex_sueloDetecta.setSmooth(true);
    sp_sueloDetecta.setTexture(tex_sueloDetecta);
    sp_sueloDetecta.setPosition(x, y);
}

void SueloDetecta::draw(sf::RenderWindow &window)
{
    window.draw(sp_sueloDetecta);
}

sf::Sprite SueloDetecta::getSprite()
{
    return sp_sueloDetecta;
}
