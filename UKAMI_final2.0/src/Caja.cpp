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
    bodydef.type = b2_dynamicBody;
    cajaB = world->CreateBody(&bodydef);

    b2PolygonShape shape;
    shape.SetAsBox((cajaS.getGlobalBounds().width / 2.f) / F, (cajaS.getGlobalBounds().height / 2.f) / F);

    fixtureDef;
    fixtureDef.density = 1000.0f;
    fixtureDef.friction = 5.0f;
    fixtureDef.restitution = 0.f;
    fixtureDef.shape = &shape;
    cajaB->CreateFixture(&fixtureDef);
    // ================================

    //==========Bocadillo Interfaz================
    bocadilloTexture = new sf::Texture();
    bocadilloTexture->loadFromFile("tileset/interfaz-letra-arrastrar-empujar-caja.png");
    bocadilloSprite = new sf::Sprite(*bocadilloTexture);
    bocadilloSprite->setOrigin(bocadilloTexture->getSize().x / 2.f, bocadilloTexture->getSize().y / 2.f);
    bocadilloSprite->setScale(0.4, 0.4);
    bocadilloSprite->setColor(sf::Color(255, 255, 255, 200));
}

Caja::~Caja()
{
    //dtor
}

void Caja::moverCaja(int sent)
{
    fixtureDef.density = 1.0f;
    if (sent == 0) //se mueve para la derecha
    {
        cajaB->SetLinearVelocity(b2Vec2(+7, cajaB->GetLinearVelocity().y));
    }
    else //se mueve para la izquierda
    {
        cajaB->SetLinearVelocity(b2Vec2(-7, cajaB->GetLinearVelocity().y));
    }
}

void Caja::detenerCaja()
{
    fixtureDef.density = 1000.0f;
    cajaB->SetLinearVelocity(b2Vec2(0, cajaB->GetLinearVelocity().y));
}

void Caja::drawBocadilloCaja(RenderWindow& window, int posx, int posy)
{
    bocadilloSprite->setPosition(posx - 10, posy - 140);
    window.draw(*bocadilloSprite);
}

void Caja::drawCaja(RenderWindow& window)
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

Sprite Caja::getSprite()
{
    return cajaS;
}
