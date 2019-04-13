#include "Game.h"
#define F 30.0f

Game *Game::unicaInstancia = 0;

struct Palanca{
    sf::Sprite* palancaSprite;
    sf::Texture* palancaTexture;

    void inicializar(){
        palancaTexture = new sf::Texture();
        palancaTexture->loadFromFile("tileset/lever.png");
        palancaSprite = new sf::Sprite(*palancaTexture);
        palancaSprite->setOrigin(palancaTexture->getSize().x/2.f , palancaTexture->getSize().y/2.f);
        palancaSprite->setScale(0.2,0.2);

    }
};

Game::Game()
{

    // Definimos una ventana
    RenderWindow window(VideoMode(1280, 720), "Ukami");
    window.setFramerateLimit(60);
    // Definimos una vista
    View view;
    view.setSize(1920, 1080);
    view.setCenter(view.getSize().x / 2, view.getSize().y / 2);

    // Inicializamos nuestro mapa para luego dibujarlo.
    Map mapa;
    mapa.initMap("map1.tmx");

    // Creamos los ninja
    ninja1 = new Ninja1(400.f, 900.f, mapa.getb2World());
    ninja2 = new Ninja2(400.f, 400.f, mapa.getb2World());

    //Creamos los Enemigos
    enemigoCercano = 0;
    enemigos.push_back(new Enemigo1(600.f, 900.f, mapa.getb2World()));
    enemigos.push_back(new Enemigo1(900.f, 400.f, mapa.getb2World()));


    Puerta *pu = new Puerta();

    // ==== Inicializamos palanca ====
    Palanca palanca1;
    palanca1.inicializar();
    palanca1.palancaSprite->setPosition(700,440);


    //creamos el evento para poder pasarselo al kanji
    Event event;

    Kanji* kanji = new Kanji(0,"ukami",window, event); //creamos el kanji de ukami

    hud = Hud::getInstance();

    while (window.isOpen())
    {

        deltaTime = deltaClock.restart();
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            //Activar y desactivar los fps
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
                if(mostrarFPS){
                    mostrarFPS = false;
                }else{
                    mostrarFPS = true;
                }
            }
        }

        window.clear();
        // Le asignamos a nuesro viewport la view
        window.setView(view);

        if(estado==0){
            // Funcion para dibujar nuestro mapa
            mapa.drawMap(window);

            //=======View============
            updateView(*ninja1, *ninja2, view);

             // ========Ninja1=========
            ninja1->updateMovement(view, deltaTime.asMilliseconds(), frameClock);
            ninja1->drawNinja(window);
            // ======================

            // ========Ninja2=========
            ninja2->updateMovement(view, deltaTime.asMilliseconds());
            ninja2->drawNinja(window);

            //========Enemigos=========
            for(int i=0; i<enemigos.size(); i++){
                enemigos.at(i)->ia(deltaTime.asMilliseconds());
                enemigos.at(i)->drawEnemigo(window);
            }

            // ======================
            pu->drawPuerta(window);
            window.draw(*palanca1.palancaSprite);

            //=======HUD============
            //El HUD debe dibujarse siempre al final (a excepcion de los minijuegos que no tienen o tendras otro hud)
            hud->drawSigilo(window, ninja1->getSliderSigilo());
        }




        //=======Kanji============
        //TODO: tendremos que hacer un patron state mas adelante
        if(estado==1){
            if(kanji->updateKanji()){
                estado = 0;
                palanca1.palancaSprite->setScale(0,0);
            }
            kanji->drawKanji();

        }


        //Aqui es buen sitio para comprobar si colisiona con cosas creo yo
        if(ninja2->getSprite().getGlobalBounds().intersects(palanca1.palancaSprite->getGlobalBounds())){
            cout << "Colisiona" << endl;
            estado=1;
        }


        //En cualquier estado se dibujaran los FPS
        calcularFPS();
        if(mostrarFPS){
            hud->drawFPS(window);
        }

        window.display();
    }
}

Game::~Game()
{
    //dtor
}

void Game::calcularFPS(){

    //Calculamos los fps
    if(fpsClock.getElapsedTime().asSeconds()>=1.f){
        hud->updateFPS(contadorFPS);
        contadorFPS = 0;
        fpsClock.restart();
    }else{
        contadorFPS++;
    }


}


Enemigo* Game::enemigoMasCercano(){
    float distanciaMinima = 999999;
    float distancia = 0;
    float powX = 0;
    float powY = 0;
    Enemigo* guardiaCercano;

    //Recorremos todos los guardas y calculamos cual esta mas cerca
    for(int i=0; i < enemigos.size();i++){
        powX = pow(ninja1->getSprite().getPosition().x-(enemigos.at(i)->getSprite()->getPosition().x),2);
        powY = pow(ninja1->getSprite().getPosition().y-(enemigos.at(i)->getSprite()->getPosition().y),2);

        distancia = fabs(sqrt(powX+powY));
        cout << "Distancia entre Ninja 1 y Enemigo " << i << " ->" << distancia << endl;

        //Se devuelve el guardia mas cercano
        if(distancia < distanciaMinima){

            guardiaCercano = enemigos.at(i);
            distanciaMinima = distancia;
        }

    }

    return guardiaCercano;
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
