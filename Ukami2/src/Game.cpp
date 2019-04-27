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

    //creamos el evento para poder pasarselo al kanji
    Event event;

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

    Puerta pu(1800, 620, mapa.getb2World());

    // ==== Inicializamos palanca ====
    Palanca palanca1;
    palanca1.inicializar();
    palanca1.palancaSprite->setPosition(700,440);


    menu* menu = menu::getInstance(window,event);




    //Enemigos
    guardiaEstaticoCercano = 0;
    GuardiaEstatico* g = new GuardiaEstatico(900,900);
    guardiasEstaticos.push_back(g);

    //Kanji
    Kanji* kanji = new Kanji(0,"ukami",window, event); //creamos el kanji de ukami

    hud = Hud::getInstance();
    sf::Clock tiempoEntreTeclas;
    while (window.isOpen())
    {




        deltaTime = deltaClock.restart();
        while (window.pollEvent(event))
        {
            if(tiempoEntreTeclas.getElapsedTime().asSeconds()>0.5f){
                if (event.type == Event::Closed)
                window.close();

                //Activar y desactivar los fps
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::F4)){
                    tiempoEntreTeclas.restart();
                    if(mostrarFPS){
                        mostrarFPS = false;
                    }else{
                        mostrarFPS = true;
                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                    tiempoEntreTeclas.restart();
                    if(estado==2){
                        estado=0;
                        cout << "Estado -> " << estado  << endl;
                    }else{

                        estado=2;
                        cout << "Estado -> " << estado  << endl;
                    }
                }
            }

        }

        window.clear();
        // Le asignamos a nuesro viewport la view
        window.setView(view);



        // Estado 0 es para mostrar el juego normal
        if(estado==0){
            // Funcion para dibujar nuestro mapa
            mapa.drawMap(window);

            //=======View============
            updateView(*ninja1, *ninja2, view);

            // ========Ninja1=========

             if(Keyboard::isKeyPressed(Keyboard::R)){
                //Solo se llama al silbido si el guardia ha llegado ya (mas tarde implementarmeos un CD de la habilidad en el mismo if)
                guardiaEstaticoCercano = guardiaEstaticoMasCercano();
                if(guardiaEstaticoCercano != 0 && !guardiaEstaticoCercano->getMoviendose()){

                    guardiaEstaticoCercano->setMoviendose(true);
                    guardiaEstaticoCercano->setPosicionDestino(ninja1->getSprite().getPosition().x); //Le decimos que tiene que ir hasta el X del personaje que silba
                }
            }


            ninja1->updateMovement(view, deltaTime.asMilliseconds(), frameClock);
            ninja1->drawNinja(window);
            // ======================

            // ========Ninja2=========
            ninja2->updateMovement(view, deltaTime.asMilliseconds(), frameClock);
            ninja2->drawNinja(window);



            //========Enemigos=========

            if(guardiaEstaticoCercano != 0){
                //Se mueve a la posicion donde le dices
                if(guardiaEstaticoCercano->getMoviendose() && !guardiaEstaticoCercano->getEsperando()){
                    guardiaEstaticoCercano->setHaRegresado(false);
                    guardiaEstaticoCercano->moverse(deltaTime.asMilliseconds());
                }

                //Despues de esperar un TIEMPO_DE_ESPERA vuelve a la posicion original
                if(guardiaEstaticoCercano->getEsperando() && guardiaEstaticoCercano->getTiempoAntesDeVolver().getElapsedTime().asSeconds() > TIEMPO_DE_ESPERA){
                   //Vuelve a la posicion inicial

                    guardiaEstaticoCercano->setPosicionDestino(guardiaEstaticoCercano->getxInicial()); //La posicion destino será la posición inicial
                    guardiaEstaticoCercano->setMoviendose(true);
                    guardiaEstaticoCercano->setEsperando(false);
                    guardiaEstaticoCercano->setVolviendo(true);
                }
            }

            g->drawNinjaEstatico(window);




            // =========PUERTA Y PALANCA=============
            pu.drawPuerta(window);
            window.draw(*palanca1.palancaSprite);

            //=======HUD============
            hud->drawHUD(window);
            hud->drawSigilo(window, ninja1->getSliderSigilo());
        }




        //=======Kanji============
        //TODO: tendremos que hacer un patron state mas adelante
        if(estado==1){
            // Comprobamos si hemos ganado el kanji
            if(kanji->updateKanji()){
                pu.ocultarPuerta();
                estado = 0;
                palanca1.palancaSprite->setScale(0,0);
                //delete kanji;
                kanji = NULL;
                kanji = new Kanji(1,"kanji",window,event);
            }
            kanji->drawKanji();

        }

        // Estado 2 es para mostrar el menu
        if(estado==2){
            if(menu->drawMenu()==0){
                estado=0;
            }

        }


        //Aqui es buen sitio para comprobar si colisiona con cosas creo yo

        if(ninja2->getBoxCollider()->getGlobalBounds().intersects(palanca1.palancaSprite->getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::E)){
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


GuardiaEstatico* Game::guardiaEstaticoMasCercano(){
    float distanciaMinima = 999999;
    float distancia = 0;
    float powX = 0;
    float powY = 0;
    GuardiaEstatico* guardiaCercano;

    //Recorremos todos los guardas y calculamos cual esta mas cerca
    for(int i=0; i < guardiasEstaticos.size();i++){
        powX = pow(ninja1->getSprite().getPosition().x-(guardiasEstaticos.at(i)->getSprite()->getPosition().x),2);
        powY = pow(ninja1->getSprite().getPosition().y-(guardiasEstaticos.at(i)->getSprite()->getPosition().y),2);

        distancia = fabs(sqrt(powX+powY));
        cout << "Distancia entre Ninja 1 y Guardia " << i << " ->" << distancia << endl;

        //Se devuelve el guardia mas cercano
        if(distancia < distanciaMinima){

            guardiaCercano = guardiasEstaticos.at(i);
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


void Game::setEstado(int state)
{
    estado = state;
}
