#include "Caja.h"
#define F 30.0f

/*Método para cargar una caja en la posición que queramos
Se podría mejorar si le ponemos las coordenadas a los propios mapas y que el método
se encargue de cargarlos en las posiciones indicadas en Tiled*/
Caja::Caja(int posx, int posy, b2World* world)
{
    // Cargamos la textura y se la aplicamos al sprite
        cajaT.loadFromFile("tileset/box_box2d.png");
        cajaT.setSmooth(true);
        cajaS.setTexture(cajaT);
        cajaS.setOrigin(cajaS.getGlobalBounds().width / 2.f, cajaS.getGlobalBounds().height / 2.f);
        cajaS.setScale(0.15, 0.15);

    // =========Box2D Caja======
        b2BodyDef bodydef;
        bodydef.position.Set(posx / F, posy / F);
        bodydef.type = b2_staticBody;
        cajaB = world->CreateBody(&bodydef);

        b2PolygonShape shape;
        shape.SetAsBox((cajaS.getGlobalBounds().width / 2.f) / F, (cajaS.getGlobalBounds().height / 2.f) / F);

        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 5.0f;
        fixtureDef.restitution = 0.f;
        fixtureDef.shape = &shape;
        cajaB->CreateFixture(&fixtureDef);
}

Caja::~Caja()
{
    //dtor
}

void Caja::drawCaja(RenderWindow &window)
{
    // Dibujaremos el Collider de la Caja
    RectangleShape rs(Vector2f(cajaS.getGlobalBounds().width, cajaS.getGlobalBounds().height));
    rs.setOrigin(cajaS.getGlobalBounds().width / 2.f, cajaS.getGlobalBounds().height / 2.f);
    rs.setPosition(cajaB->GetPosition().x * F, cajaB->GetPosition().y * F);
    rs.setFillColor(sf::Color::Transparent);
    //rs.setOutlineColor(sf::Color::Yellow);
    //rs.setOutlineThickness(5);

    // Actualizamos la posición de la caja
    cajaS.setPosition(cajaB->GetPosition().x * F, cajaB->GetPosition().y * F);

    // Dibujamos el collider de la caja y la propia caja
    window.draw(rs);
    window.draw(cajaS);
}
