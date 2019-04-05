#include "Game.h"
#include "palanca.h"

#define F 30.0f

Game *Game::unicaInstancia = 0;

Game::Game()
{
    // Definimos una ventana
    RenderWindow window(VideoMode(1280, 720), "Ukami");
    // Definimos una vista
    View view;
    view.setSize(1920, 1080);

    // Inicializamos nuestro mapa para luego dibujarlo.
    Map mapa;
    mapa.initMap("Ukami.tmx");

    // Creamos un ninja
    Ninja1 ninja1(400.f, 700.f, mapa.getb2World());
    Ninja2 ninja2(400.f, 200.f, mapa.getb2World());

    palanca *pal = new palanca();

    //SFMLDebugDraw debugDrawInstance(window);
    //mapa.getb2World()->SetDebugDraw(&debugDrawInstance);
    //debugDrawInstance.SetFlags(debugDrawInstance::e_shapeBit);

    sf::Clock deltaClock;
    sf::Time deltaTime;
    while (window.isOpen())
    {
        Event event;
        deltaTime = deltaClock.restart();
        cout << deltaTime.asMilliseconds() << endl;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        // Le asignamos a nuesro viewport la view
        window.setView(view);

        // Funcion para dibujar nuestro mapa
        mapa.drawMap(window);

         // ========Ninja1=========
        ninja1.updateMovement(view, deltaTime.asMilliseconds());
        ninja1.drawNinja(window);
        // ======================

        // ========Ninja2=========
        ninja2.updateMovement(view, deltaTime.asMilliseconds());
        ninja2.drawNinja(window);
        // ======================

        //=======View============
        updateView(ninja1, ninja2, view);

        pal->drawPalanca(window);
        //=======================
        //mapa.getb2World()->DrawDebugData();
        window.display();
    }
}

Game::~Game()
{
    //dtor
}

void Game::updateView(Ninja1 ninja1, Ninja2 ninja2, View &view)
{

    if(ninja1.getSprite().getPosition().x > ninja2.getSprite().getPosition().x)
    {
        // Si sobrepasa los 960px, la cámara se ajusta a Ninja1
        if(ninja1.getSprite().getPosition().x > 960)
            view.setCenter(ninja1.getSprite().getPosition().x, view.getSize().y / 2);
    }else if(ninja2.getSprite().getPosition().x > ninja1.getSprite().getPosition().x)
    {
        // Si sobrepasa los 960px, la cámara se ajusta a Ninja2
        if(ninja2.getSprite().getPosition().x > 960)
            view.setCenter(ninja2.getSprite().getPosition().x, view.getSize().y / 2);
    }else
        view.setCenter(view.getSize().x / 2, view.getSize().y / 2);
}
