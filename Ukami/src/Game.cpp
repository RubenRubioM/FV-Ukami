#include "Game.h"
#define F 30.0f
#define distanciaMaximaHastaGuardia 1000

Game *Game::unicaInstancia = 0;

/*
        TO-DO
En el menu tenemos una variable que es el nivel que deberiamos cambiarla y leerla desde el game.cpp

*/

struct Palanca{
    sf::Sprite* palancaSprite;
    sf::Texture* palancaTexture;
    sf::Texture* bocadilloTexture;
    sf::Sprite* bocadilloSprite;

    void inicializar(){
        palancaTexture = new sf::Texture();
        palancaTexture->loadFromFile("tileset/lever.png");
        palancaSprite = new sf::Sprite(*palancaTexture);
        palancaSprite->setOrigin(palancaTexture->getSize().x/2.f , palancaTexture->getSize().y/2.f);
        palancaSprite->setScale(0.2,0.2);

        bocadilloTexture = new sf::Texture();
        bocadilloTexture->loadFromFile("tileset/interfaz-letra-e-bocadillo.png");
        bocadilloSprite = new sf::Sprite(*bocadilloTexture);
        bocadilloSprite->setOrigin(bocadilloTexture->getSize().x/2.f,bocadilloTexture->getSize().y/2.f);
        bocadilloSprite->setScale(0.4,0.4);
        bocadilloSprite->setColor(sf::Color(255,255,255,200));

    }

    void colocarBocadillo(){
        bocadilloSprite->setPosition(palancaSprite->getPosition().x + 60, palancaSprite->getPosition().y - 20);
        cout<<bocadilloSprite->getPosition().x<<endl;
        cout<<"Bocadillo creado"<<endl;
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
    ninja2 = new Ninja2(5200.f, 500.f, mapa.getb2World());

    Puerta pu(1800, 620, mapa.getb2World());
    Puerta pu2(4200,120,mapa.getb2World());
    Puerta pu3(6200,940,mapa.getb2World());

    OjoDeJade ojo1(4760.f, 300.f);
    OjoDeJade ojo2(4760.f, 800.f);

    // ==== Inicializamos palanca ====
    Palanca palanca1;
    palanca1.inicializar();
    palanca1.palancaSprite->setPosition(1500,110);
    palanca1.colocarBocadillo();

    Palanca palanca2;
    palanca2.inicializar();
    palanca2.palancaSprite->setPosition(4000,940);
    palanca2.colocarBocadillo();

    Palanca palanca3;
    palanca3.inicializar();
    palanca3.palancaSprite->setPosition(5200,130);
    palanca3.colocarBocadillo();



    Enredadera enredadera1;
    enredadera1.crearEnredadera(4760, 315);
    // ==== CAJA =====
    Caja caja(1200, 450, mapa.getb2World());

    menu* menu = menu::getInstance(window,event);




    //Enemigos
    guardiaEstaticoCercano = 0;
    GuardiaEstatico* g = new GuardiaEstatico(3500,375);
    GuardiaEstatico* g2 = new GuardiaEstatico(5800,400);
    guardiasEstaticos.push_back(g);
    numGuardias++;
    guardiasEstaticos.push_back(g2);
    numGuardias++;


    GuardiaDinamico* gd = new GuardiaDinamico(5000,370);
    guardiasDinamicos.push_back(gd);
    numGuardias++;

    //Kanji
    Kanji* kanji = new Kanji(0,"ukami",window, event); //creamos el kanji de ukami

    nivel = menu->getNivel();

    hud = Hud::getInstance();
    sf::Clock tiempoEntreTeclas;
    sf::Clock tiempoGameOver;
    while (window.isOpen())
    {

    tiempoJugado = tiempoDeJuego.getElapsedTime().asMilliseconds();


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



        // ================= JUEGO NORMAL =======================
        // Estado 0 es para mostrar el juego normal
        if(estado==0){
            if(nivel==1){
                // Funcion para dibujar nuestro mapa
                mapa.drawMap(window);
                //=======View============
                updateView(*ninja1, *ninja2, view);

                // ========Ninja1=========

                //Actualiza las mejoras

                ninja1->mejorarSigilo();
                ninja1->mejorarDuracionDash();
                ninja1->mejorarVelocidad();
                //Al comienzo de cada frame ponemos que no estan siendo detectados para luego a lo largo de las comprobaciones cambiar o no
                ninja1->setSiendoDetectado(false);
                ninja2->setSiendoDetectado(false);
                 if(Keyboard::isKeyPressed(Keyboard::L)){
                    //Solo se llama al silbido si el guardia ha llegado ya (mas tarde implementarmeos un CD de la habilidad en el mismo if)
                    guardiaEstaticoCercano = guardiaEstaticoMasCercano();
                    if(guardiaEstaticoCercano != 0 && !guardiaEstaticoCercano->getMoviendose()){

                        guardiaEstaticoCercano->setMoviendose(true);
                        guardiaEstaticoCercano->setPosicionDestino(ninja1->getSprite().getPosition().x); //Le decimos que tiene que ir hasta el X del personaje que silba
                    }
                }
                enredadera1.drawEnredadera(window);
                ojo1.dibujaOjoDeJade(window);
                ojo2.dibujaOjoDeJade(window);
                if(!mapa.getTransicionando()){
                    ninja1->updateMovement(view, deltaTime.asMilliseconds(), frameClock);
                    ninja1->drawNinja(window);
                    // ======================

                    // ========Ninja2=========

                    //=======Actualiza las mejoras

                    ninja2->mejorarSigilo();
                    ninja2->mejorarVelocidad();
                    ninja2->updateMovement(view, deltaTime.asMilliseconds(), frameClock);
                    ninja2->drawNinja(window);
                }

                //==========OJO DE JADE==========
                ojo1.dibujaOjoDeJade(window);
                ojo2.dibujaOjoDeJade(window);



                //========Enemigos=========

                //Movimiento para el guardia al que le has silbado
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

                if(!mapa.getTransicionando()){
                    //Dibujamos todos los guardias estaticos
                    for(int i=0; i<guardiasEstaticos.size();i++){
                        guardiasEstaticos.at(i)->drawGuardiaEstatico(window);
                    }

                    //Dibujamos todos los guardias dinamicos
                    for(int i=0; i<guardiasDinamicos.size();i++){
                        guardiasDinamicos.at(i)->updateGuardiaDinamico(deltaTime.asMilliseconds());
                        guardiasDinamicos.at(i)->drawGuardiaDinamico(window);
                    }
                }


                //Comprobamos colisiones de los personajes y las visiones de los enemigos y si consiguen el ojo de jade
                if(ninja2->getBoxCollider()->getGlobalBounds().intersects(ojo1.getSprite().getGlobalBounds())
                    && ninja1->getBoxCollider()->getGlobalBounds().intersects(ojo2.getSprite().getGlobalBounds())
                   && !muerto)
                {
                    //Ojo de jade conseguido
                    cout<<"HAS GANADO\n";
                    ganado = true;
                    nivelCompleto("1");
                }

                for(int i=0; i<guardiasEstaticos.size();i++){
                    // == Ninja 1 ==
                    if(ninja1->getBoxCollider()->getGlobalBounds().intersects(guardiasEstaticos.at(i)->getVision()->getGlobalBounds()) && !ninja1->getEnSigilo()){
                        cout << "Detectado " << endl;
                        ninja1->setSiendoDetectado(true);
                    }

                    // == Ninja 2 ==
                    if(ninja2->getBoxCollider()->getGlobalBounds().intersects(guardiasEstaticos.at(i)->getVision()->getGlobalBounds()) && !ninja2->getEnSigilo()){
                        cout << "Detectado " << endl;
                        ninja2->setSiendoDetectado(true);
                    }
                }

                for(int i=0; i<guardiasDinamicos.size();i++){
                    // == Ninja 1 ==
                    if(ninja1->getBoxCollider()->getGlobalBounds().intersects(guardiasDinamicos.at(i)->getVision()->getGlobalBounds()) && !ninja1->getEnSigilo()){
                        cout << "Detectado " << endl;
                        ninja1->setSiendoDetectado(true);
                    }

                    // == Ninja 2 ==
                    if(ninja2->getBoxCollider()->getGlobalBounds().intersects(guardiasDinamicos.at(i)->getVision()->getGlobalBounds()) && !ninja2->getEnSigilo()){
                        cout << "Detectado " << endl;
                        ninja2->setSiendoDetectado(true);
                    }
                }


                //Siempre al final de todas las posibles colisiones subimos o bajamos la vida
                if(ninja1->getSiendoDetectado()){
                    ninja1->descargarVida(deltaTime.asMilliseconds());
                }else{
                    ninja1->cargarVida(deltaTime.asMilliseconds());
                }

                if(ninja2->getSiendoDetectado()){
                    ninja2->descargarVida(deltaTime.asMilliseconds());
                }else{
                    ninja2->cargarVida(deltaTime.asMilliseconds());
                }

                if(!mapa.getTransicionando()){
                    // =========PUERTA Y PALANCA=============
                    pu.drawPuerta(window);
                    pu2.drawPuerta(window);
                    pu3.drawPuerta(window);
                    window.draw(*palanca1.palancaSprite);
                    window.draw(*palanca2.palancaSprite);
                    window.draw(*palanca3.palancaSprite);

                    //Aqui es buen sitio para comprobar si colisiona con cosas creo yo
                    if(!mapa.getTransicionando()){
                        if(ninja2->getBoxCollider()->getGlobalBounds().intersects(palanca1.palancaSprite->getGlobalBounds())){
                            if(Keyboard::isKeyPressed(Keyboard::E)){
                                estado=1;
                            }

                            window.draw(*palanca1.bocadilloSprite);
                        }

                        if(ninja2->getBoxCollider()->getGlobalBounds().intersects(enredadera1.getSprite().getGlobalBounds())){
                            if(Keyboard::isKeyPressed(Keyboard::E)){
                                ninja2->setTrepando(true);
                            }
                        }

                        if(ninja1->getBoxCollider()->getGlobalBounds().intersects(palanca2.palancaSprite->getGlobalBounds())){
                            if(Keyboard::isKeyPressed(Keyboard::E)){
                                estado=1;
                            }

                            window.draw(*palanca2.bocadilloSprite);
                        }

                        if(ninja2->getBoxCollider()->getGlobalBounds().intersects(palanca3.palancaSprite->getGlobalBounds())){
                            if(Keyboard::isKeyPressed(Keyboard::E)){
                                estado=1;
                            }

                            window.draw(*palanca3.bocadilloSprite);
                        }



                    }
                    // ========== CAJA ===========
                    caja.drawCaja(window);

                    //=======HUD============
                    hud->drawHUD(window);
                    hud->drawSigilo(window, ninja1->getSliderSigilo(),ninja2->getSliderSigilo());
                    hud->drawVida(window,ninja1->getSliderVida(),ninja2->getSliderVida(),ninja1->getVidaActual(),ninja2->getVidaActual());
                }


//Aqui es buen sitio para comprobar si colisiona con cosas creo yo
                if(!mapa.getTransicionando()){
                    if(ninja2->getBoxCollider()->getGlobalBounds().intersects(palanca1.palancaSprite->getGlobalBounds())){
                        if(Keyboard::isKeyPressed(Keyboard::E)){
                            estado=1;
                        }

                        window.draw(*palanca1.bocadilloSprite);
                    }

                    if(ninja2->getBoxCollider()->getGlobalBounds().intersects(palanca2.palancaSprite->getGlobalBounds()) && Keyboard::isKeyPressed(Keyboard::E)){
                        cout << "Colisiona" << endl;
                        estado=1;
                    }
                }

            }else if(nivel==2){

            }




        } //Final del estado de juego




        //=======Kanji============
        //TODO: tendremos que hacer un patron state mas adelante
        if(estado==1){
            // Comprobamos si hemos ganado el kanji
            if(kanji->updateKanji()){
                if(numKanjisResueltos==0){
                    //Primer kanji
                    pu.ocultarPuerta();
                    mapa.empezarTransicion();
                    palanca1.palancaSprite->setScale(0,0);
                    //delete kanji;
                    kanji = NULL;
                    kanji = new Kanji(1,"kanji",window,event);

                }else if(numKanjisResueltos==1){
                    pu2.ocultarPuerta();
                    mapa.empezarTransicion();
                    palanca2.palancaSprite->setScale(0,0);
                    //delete kanji;
                    kanji = NULL;
                    kanji = new Kanji(2,"kanji",window,event);
                }else if(numKanjisResueltos==2){
                    pu3.ocultarPuerta();
                    mapa.empezarTransicion();
                    palanca3.palancaSprite->setScale(0,0);
                    //delete kanji;
                    kanji = NULL;
                    kanji = new Kanji(2,"kanji",window,event);
                }

                estado = 0;
                kanjisCompletos();
                numKanjisResueltos++;
            }
            kanji->drawKanji();
            nivelCompleto("1");

        }

        // Estado 2 es para mostrar el menu
        if(estado==2){
                muerto=false;
                ganado = false;
            if(menu->drawMenu()==0){
                //Aqui entra cuando le das a reanudar
                estado=0;
                mapa.empezarTransicion();

                tiempoGameOver.restart();

                //TO-DO: Un metodo en menu que devuelva varialbes como nivel seleccionado, mejora evolucionada, etc.. Y actualizarlas aqui en el game.cpp
            }

        }


        //cout<<ninja1->getVidaActual()<<"\n";
        if(ninja1->getVidaActual()==1 || ninja2->getVidaActual()==1)
        {
            muerto = true;
        }
        if(muerto){
            float tiempoStark = tiempoGameOver.getElapsedTime().asMilliseconds();
            if(tiempoStark < 20000)
            {
                window.draw(hud->getTextGameOver());
            }

            cout << "Tiempo Stark -> " <<tiempoStark <<endl;
            if(tiempoStark > 20000)
            {
                //tiempoGameOver.restart();
                //tiempoGameOver = new sf::Clock();
                muertes();

                estado = 2;
            }
        }
        if(ganado)
        {
            float tiempoGanado = tiempoGameOver.getElapsedTime().asMilliseconds();
            if(tiempoGanado < 20000)
            {
                window.draw(hud->getTextGanado());
            }

            cout<<"Tiempo ganado -> " << tiempoGanado<<endl;
            if(tiempoGanado > 20000)
               {
                //tiempoGameOver.restart();
                //tiempoGameOver = new sf::Clock();
                   estado = 2;
               }
        }




        //En cualquier estado se dibujaran los FPS
        calcularFPS();
        if(mostrarFPS){
            if(!mapa.getTransicionando()){
                hud->drawFPS(window);
            }

        }

        if(tiempoJugado>1000){
            tiempo();
            tiempoDeJuego.restart();
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

void Game::nivelCompleto(string n){
  ofstream stats;
  stats.open ("stats/nivel"+n);
  stats << "1";
  stats.close();
}

void Game::kanjisCompletos(){
  int total;
  string line;
  ifstream myfile ("stats/kanjisresueltos");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
      total = stoi(line)+1;
    }
    myfile.close();
  }
  cout << total <<endl;
    ofstream suma;
    suma.open ("stats/kanjisresueltos");
    suma << total;
    suma.close();
}

void Game::muertes(){
  int total;
  string line;
  ifstream myfile ("stats/muertes");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      cout << line << '\n';
      total = stoi(line)+1;
    }
    myfile.close();
  }
  cout << total <<endl;
    ofstream suma;
    suma.open ("stats/muertes");
    suma << total;
    suma.close();
}

void Game::tiempo(){
  int total;
  string line;
  ifstream myfile ("stats/tiempo");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      total = stoi(line)+tiempojugado;
    }
    myfile.close();
  }

    ofstream suma;
    suma.open ("stats/tiempo");
    suma << total;
    suma.close();

}


GuardiaEstatico* Game::guardiaEstaticoMasCercano(){
    float distanciaMinima = 999999;
    float distancia = 0;
    float powX = 0;
    float powY = 0;
    GuardiaEstatico* guardiaCercano = NULL;

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
