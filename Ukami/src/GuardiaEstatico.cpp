#include "GuardiaEstatico.h"

GuardiaEstatico::GuardiaEstatico(float _x, float _y)
{
    velocidad = 0.3;
    xInicial = _x;

    texture2.loadFromFile("tileset/enemigo.png");
    texture2.setSmooth(true);

    texture3.loadFromFile("tileset/guardian_move_right.png");
    texture3.setSmooth(true);

    texture4.loadFromFile("tileset/guardian_move_left.png");
    texture4.setSmooth(true);

    animacion = *new Animation();
    animacion.setSpriteSheet(texture2);
    animacion.addFrameInitial(sf::IntRect(0, 0, 142, 142));
    animacion.addFrame(sf::IntRect(142, 0, 142, 142));
    animacion.addFrame(sf::IntRect(284, 0, 142, 142));
    animacion.addFrame(sf::IntRect(426, 0, 142, 142));
    animacion.addFrame(sf::IntRect(568, 0, 142, 142));
    animacion.addFrame(sf::IntRect(710, 0, 142, 142));
    animacion.addFrame(sf::IntRect(856, 0, 142, 142));
    animacion.addFrame(sf::IntRect(994, 0, 142, 142));
    animacion.addFrame(sf::IntRect(1136, 0, 142, 142));

    animacion2 = *new Animation();
    animacion2.setSpriteSheet(texture3);
    animacion2.addFrameInitial(sf::IntRect(0, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(183, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(366, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(549, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(732, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(915, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(1098, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(1281, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(1464, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(1647, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(1830, 0, 183, 142));
    animacion2.addFrame(sf::IntRect(2013, 0, 183, 142));

    animacion3 = *new Animation();
    animacion3.setSpriteSheet(texture4);
    animacion3.addFrameInitial(sf::IntRect(2013, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(1830, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(366, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(1647, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(1464, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(1281, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(1098, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(915, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(732, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(366, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(183, 0, 183, 142));
    animacion3.addFrame(sf::IntRect(0, 0, 183, 142));

    currentAnimation = new Animation();
    currentAnimation = &animacion;

    animatedSprite = *new AnimatedSprite();
    animatedSprite.setOrigin(161 / 2.f, 204 / 2.f);
    animatedSprite.setPosition(_x, _y);
    animatedSprite.setScale(1.4f, 1.4f);
    // ==== Triangulo de vision ====
    triangle = new sf::ConvexShape();
    triangle->setPointCount(3);
    triangle->setFillColor(sf::Color(250, 250, 125, 70));
    triangle->setPoint(0, sf::Vector2f(0, 0));
    triangle->setPoint(1, sf::Vector2f(250, 100));
    triangle->setPoint(2, sf::Vector2f(250, -80));
    triangle->setOrigin(0, 0);
    triangle->setRotation(180);

    tex_spotlight.loadFromFile("tileset/spotlight.png");
    sp_spotlight.setTexture(tex_spotlight);
    sp_spotlight.setOrigin(280, sp_spotlight.getPosition().y / 2);
    sp_spotlight.setPosition(_x - 40, _y - 210);
    posx_INIT = _x;
    posy_INIT = _y;
}

void GuardiaEstatico::moverse(float _deltaTime)
{

    /*
        Creo que funciona desactivando el efecto de silbido solo en un sitio porque como al moverse siempre se pasa un poco la posicion destino entonces entra igualmente
    */

    //Detectamos si va hacia la derecha o hacia la izquierda
    if (posicionDestino > animatedSprite.getPosition().x)
    {
        AudioManager *audio = AudioManager::getInstance();
        AudioManager::getInstance()->guardia1();
        //hacia la derecha
        direccionDestino = 1;

        currentAnimation = &animacion2;

        animatedSprite.move(direccionDestino * velocidad * _deltaTime, 0);
        sp_spotlight.setRotation(180);
        sp_spotlight.setPosition(animatedSprite.getPosition().x + 110, animatedSprite.getPosition().y + 60);
    }

    if (posicionDestino < animatedSprite.getPosition().x)
    {
        AudioManager *audio = AudioManager::getInstance();
        AudioManager::getInstance()->guardia1();
        //hacia la izquierda
        currentAnimation = &animacion3;

        if (direccionDestino == 1)
        {
            //Aqui solo entra 1 vez cuando ha llegado al sitio ya que ponemos moviendose = false y en el update no vuelve a entrar con esa condicion
            moviendose = false;

            //Aqui en un futuro podemos poner un if para ver si el guardia es estatico o dinamico y asi el dinamico no tendria que esperar antes de volver
            if (!volviendo)
            {
                sp_spotlight.setRotation(0);
                sp_spotlight.setPosition(animatedSprite.getPosition().x - 30, animatedSprite.getPosition().y - 210);
                cout << "Ha llegado al punto del silbido" << endl;
                activarRelojDeEspera();
            }
            else
            {
                cout << "Ha vuelto a la posicion original" << endl;
                haRegresado = true;
                currentAnimation = &animacion;
                sp_spotlight.setRotation(0);
                sp_spotlight.setPosition(posx_INIT - 40, posy_INIT - 210);
            }

            volviendo = false;
        }
        direccionDestino = -1;

        animatedSprite.move(direccionDestino * velocidad * _deltaTime, 0);

        if (!haRegresado && moviendose)
        {
            sp_spotlight.setPosition(animatedSprite.getPosition().x - 70, animatedSprite.getPosition().y - 180);
        }
    }
}

void GuardiaEstatico::activarRelojDeEspera()
{
    //Reiniciamos el reloj, le decimo que no se mueva, le decimos que esta esperando y le decimos que su proxima posicion sera de la que viene
    tiempoAntesDeVolver.restart();
    moviendose = false;
    esperando = true;
    posicionDestino = xInicial;
    currentAnimation = &animacion;
}

void GuardiaEstatico::update(sf::Clock frameClock)
{
    sf::Time frameTime = frameClock.restart();

    animatedSprite.play(*currentAnimation);

    animatedSprite.update(frameTime);
}

void GuardiaEstatico::drawGuardiaEstatico(sf::RenderWindow &window)
{
    window.draw(sp_spotlight);
    window.draw(animatedSprite);
}

//Getters
bool GuardiaEstatico::getMoviendose() { return moviendose; }
bool GuardiaEstatico::getEsperando() { return esperando; }
bool GuardiaEstatico::getVolviendo() { return volviendo; }
float GuardiaEstatico::getPosicionDestino() { return posicionDestino; }
float GuardiaEstatico::getVelocidad() { return velocidad; }
float GuardiaEstatico::getxInicial() { return xInicial; }
AnimatedSprite GuardiaEstatico::getSprite() { return animatedSprite; }
sf::Clock GuardiaEstatico::getTiempoAntesDeVolver() { return tiempoAntesDeVolver; }
sf::Sprite GuardiaEstatico::getVision() { return sp_spotlight; }

//Setters
void GuardiaEstatico::setPosicionDestino(float _x) { posicionDestino = _x; }
void GuardiaEstatico::setEsperando(bool _esperando) { esperando = _esperando; }
void GuardiaEstatico::setMoviendose(bool _silbido) { moviendose = _silbido; }
void GuardiaEstatico::setVolviendo(bool _volviendo) { volviendo = _volviendo; }
void GuardiaEstatico::setHaRegresado(bool _haRegresado) { haRegresado = _haRegresado; }

GuardiaEstatico::~GuardiaEstatico()
{
    //dtor
}
