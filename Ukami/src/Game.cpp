#include "Game.h"

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

    //SFMLDebugDraw debugDrawInstance(window);
    //mapa.getb2World()->SetDebugDraw(&debugDrawInstance);
    //debugDrawInstance.SetFlags(debugDrawInstance::e_shapeBit);

    while (window.isOpen())
    {
        Event event;
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
        ninja1.updateMovement(view);
        ninja1.drawNinja(window);
        // ======================

        // ========Ninja2=========
        ninja2.updateMovement(view);
        ninja2.drawNinja(window);
        // ======================
        //mapa.getb2World()->DrawDebugData();
        window.display();
    }
}

Game::~Game()
{
    //dtor
}
