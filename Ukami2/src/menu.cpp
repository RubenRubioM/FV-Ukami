#include "menu.h"

menu* menu::menuUnico = 0;



menu* menu::getInstance(sf::RenderWindow &window, sf::Event &eventGame)
{
    if(menuUnico == 0){
        menuUnico = new menu(window,eventGame);
    }
    return menuUnico;
}

menu::menu(sf::RenderWindow &window, sf::Event &eventGame)
{
    //ctor
    mostrarMenu = 0;
    separacion = 100;
    actual = 0;
    presionado = 0;
    idMenu = 0;
    cont = 0;


    ventanaMenu = &window;
    evento = &eventGame;

    vistaMenu = new sf::View();
    vistaMenu->setSize(1280,720);
    vistaMenu->setCenter(vistaMenu->getSize().x / 2, vistaMenu->getSize().y / 2);

    cargarFondo();
    cargarFuente();
    cargarMensaje();
    cargarMensajesConsola();
    cargarMenu();



}

menu::~menu()
{
    //dtor
}

void menu::cargarFuente()
{
    fuente = new sf::Font();
    fuente->loadFromFile("./tipografia/ninjaNaruto/njnaruto.ttf");
}

void menu::cargarFondo()
{
    texturaFondo = new sf::Texture;
    texturaFondo->loadFromFile("tileset/menu.png");
    fondo = new sf::Sprite(*texturaFondo);
    fondo->setScale((float)ventanaMenu->getSize().x / fondo->getTexture()->getSize().x, (float)ventanaMenu->getSize().y / fondo->getTexture()->getSize().y);
}

void menu::cargarMensaje()
{
    string msj = "Pulsa   M   para  ver  el  menu";
    mensaje = new sf::Text();
    mensaje->setFont(*fuente);
    mensaje->setString(msj);
    mensaje->setCharacterSize(50);
    mensaje->setOrigin(mensaje->getGlobalBounds().width / 2.0, mensaje->getGlobalBounds().height / 2.0);
    mensaje->setPosition(ventanaMenu->getSize().x / 2.0, ventanaMenu->getSize().y / 2.0);
}

void menu::rellenarArrayMensajesConsolaMI(int indice)
{
    switch (indice)
    {
        case (0):
        {
            mensajesConsolaMI[indice] = "¡A jugar!";
            break;
        }
        case (1):
        {
            mensajesConsolaMI[indice] = "Ver Selector de Niveles";
            break;
        }
        case (2):
        {
            mensajesConsolaMI[indice] = "Ver Mejoras";
            break;
        }
        case (3):
        {
            mensajesConsolaMI[indice] = "Salimos";
            break;
        }
    }
}

void menu::rellenarArrayMensajesConsolaSelectNivel(int indice)
{
    switch (indice)
    {
        case (0):
        {
            mensajesConsolaSelectNiv[indice] = "Vemos Niveles";
            break;
        }
        case (1):
        {
            mensajesConsolaSelectNiv[indice] = "Vemos Estadisticas";
            break;
        }
    }
}

void menu::rellenarArrayMensajesConsolaNivel(int indice)
{
    switch (indice)
    {
        case (0):
        {
            mensajesConsolaNivel[indice] = "Nivel 1";
            break;
        }
        case (1):
        {
            mensajesConsolaNivel[indice] = "Nivel 2";
            break;
        }
        case (2):
        {
            mensajesConsolaNivel[indice] = "Nivel 3";
            break;
        }
    }
}

void menu::rellenarArrayMensajesConsolaEstad(int indice)
{
    switch (indice)
    {
        case (0):
        {
              string line;
              ifstream myfile ("stats/muertes");
              if (myfile.is_open())
              {
                while ( getline (myfile,line) )
                {
                  muertes = line;
                }
                myfile.close();
              }
            mensajesConsolaEstad[indice] = "Has muerto > "+muertes+"veces";
            break;
        }
        case (1):
        {
            mensajesConsolaEstad[indice] = "Estadistica 2";
            break;
        }
        case (2):
        {
            mensajesConsolaEstad[indice] = "Estadistica 3";
            break;
        }
    }
}

void menu::rellenarArrayMensajesConsolaMejoras(int indice)
{
    switch (indice)
    {
        case (0):
        {
            mensajesConsolaMej[indice] = "Mejora 1";
            break;
        }
        case (1):
        {
            mensajesConsolaMej[indice] = "Mejora 2";
            break;
        }
        case (2):
        {
            mensajesConsolaMej[indice] = "Mejora 3";
            break;
        }
        case (3):
        {
            mensajesConsolaMej[indice] = "Mejora 4";
            break;
        }
    }
}

void menu::cargarMensajesConsola()
{
    for(int i = 0; i < 4; i++)
    {
        rellenarArrayMensajesConsolaMI(i);
    }
    for(int i = 0; i < 2; i++)
    {
        rellenarArrayMensajesConsolaSelectNivel(i);
    }
    for(int i = 0; i < 4; i++)
    {
        rellenarArrayMensajesConsolaNivel(i);
    }
    for(int i = 0; i < 4; i++)
    {
        rellenarArrayMensajesConsolaEstad(i);
    }
    for(int i = 0; i < 5; i++)
    {
        rellenarArrayMensajesConsolaMejoras(i);
    }
}

void menu::rellenarArrayTextoMenu(int indice)
{
    switch (indice)
    {
        case (0):
        {
            textoMenuInicial[indice] = "Nueva Partida / Continuar";
            textoMenuSelectNivel[indice] = "Niveles";
            //Lee el fichero y muestra el dato
              string line;
              ifstream myfile ("stats/nivel1");
              if (myfile.is_open())
              {
                while ( getline (myfile,line) )
                {
                  nivel1 = line;
                }
                myfile.close();
              }
              if(nivel1=="1")
                textoMenuNiveles[indice] = "Nivel 1 (COMPLETADO)";
              else
                textoMenuNiveles[indice] = "Nivel 1";
            //Lee el fichero y muestra el dato
              line;
              ifstream muert ("stats/muertes");
              if (muert.is_open())
              {
                while ( getline (muert,line) )
                {
                  muertes = line;
                }
                muert.close();
              }
            textoMenuEstad[indice] = "Has muerto  "+muertes+" veces";

            textoMenuMejoras[indice] = "Mejora 1";
            break;
        }
        case (1):
        {
            textoMenuInicial[indice] = "Selector de Niveles";
            textoMenuSelectNivel[indice] = "Estadisticas";
            //Lee el fichero y muestra el dato
            string line;
              ifstream myfile ("stats/nivel2");
              if (myfile.is_open())
              {
                while ( getline (myfile,line) )
                {
                  nivel2 = line;
                }
                myfile.close();
              }
              if(nivel2=="1")
                textoMenuNiveles[indice] = "Nivel 2 (COMPLETADO)";
              else
                textoMenuNiveles[indice] = "Nivel 2";

            //Lee el fichero y muestra el dato
              line;
              ifstream kanj ("stats/kanjisresueltos");
              if (kanj.is_open())
              {
                while ( getline (kanj,line) )
                {
                  kanjis = line;
                }
                kanj.close();
              }
            textoMenuEstad[indice] = "Has completado  "+kanjis+" kanjis";

            textoMenuMejoras[indice] = "Mejora 2";
            break;
        }
        case (2):
        {
            textoMenuInicial[indice] = "Mejoras";
            //Lee el fichero y muestra el dato
            string line;
              ifstream myfile ("stats/nivel3");
              if (myfile.is_open())
              {
                while ( getline (myfile,line) )
                {
                  nivel3 = line;
                }
                myfile.close();
              }
              if(nivel3=="1")
                textoMenuNiveles[indice] = "Nivel 3 (COMPLETADO)";
              else
                textoMenuNiveles[indice] = "Nivel 3";

            //Lee el fichero y muestra el dato
              line;
              ifstream temp ("stats/tiempo");
              if (temp.is_open())
              {
                while ( getline (temp,line) )
                {
                  tiempo = line;
                }
                temp.close();
              }
            int tiempoaux = stoi(tiempo);
            int aux2 = tiempoaux/60;

            textoMenuEstad[indice] = "Has jugado  "+to_string(aux2)+" minutos";

            textoMenuMejoras[indice] = "Mejora 3";
            break;
        }
        case (3):
        {
            textoMenuInicial[indice] = "Salir a Escritorio";
            textoMenuMejoras[indice] = "Mejora 4";
            break;
        }
    }
}

void menu::cargarTextoMenu()
{
    for(int i = 0; i < 4; i++)
    {
        rellenarArrayTextoMenu(i);
    }
}

void menu::cargarMenu()
{
    cargarTextoMenu();
    for(int i = 0; i < 4; i++)
    {
        menuInicial[i] = new sf::Text();
        menuInicial[i]->setFont(*fuente);
        menuInicial[i]->setString(textoMenuInicial[i]);
        menuInicial[i]->setOrigin(menuInicial[i]->getGlobalBounds().width / 2.0, menuInicial[i]->getGlobalBounds().height / 2.0);
        menuInicial[i]->setPosition(ventanaMenu->getSize().x / 2.0, ventanaMenu->getSize().y / 4.0 + separacion * i);
        menuInicial[i]->setColor(sf::Color(255,255,255));

    }
    for(int i = 0; i < 2; i++)
    {
        menuSelectNivel[i] = new sf::Text();
        menuSelectNivel[i]->setFont(*fuente);
        menuSelectNivel[i]->setString(textoMenuSelectNivel[i]);
        menuSelectNivel[i]->setOrigin(menuSelectNivel[i]->getGlobalBounds().width / 2.0, menuSelectNivel[i]->getGlobalBounds().height / 2.0);
        menuSelectNivel[i]->setPosition(ventanaMenu->getSize().x / 2.0, ventanaMenu->getSize().y / 4.0 + separacion * i);
        menuSelectNivel[i]->setColor(sf::Color(255,255,255));
    }
    for(int i = 0; i < 3; i++)
    {
        menuNiveles[i] = new sf::Text();
        menuNiveles[i]->setFont(*fuente);
        menuNiveles[i]->setString(textoMenuNiveles[i]);
        menuNiveles[i]->setOrigin(menuNiveles[i]->getGlobalBounds().width / 2.0, menuNiveles[i]->getGlobalBounds().height / 2.0);
        menuNiveles[i]->setPosition(ventanaMenu->getSize().x / 2.0, ventanaMenu->getSize().y / 4.0 + separacion * i);
        menuNiveles[i]->setColor(sf::Color(255,255,255));
    }
    for(int i = 0; i < 3; i++)
    {
        menuEstad[i] = new sf::Text();
        menuEstad[i]->setFont(*fuente);
        menuEstad[i]->setString(textoMenuEstad[i]);
        menuEstad[i]->setOrigin(menuEstad[i]->getGlobalBounds().width / 2.0, menuEstad[i]->getGlobalBounds().height / 2.0);
        menuEstad[i]->setPosition(ventanaMenu->getSize().x / 2.0, ventanaMenu->getSize().y / 4.0 + separacion * i);
        menuEstad[i]->setColor(sf::Color(255,255,255));
    }
    for(int i = 0; i < 4; i++)
    {
        menuMejoras[i] = new sf::Text();
        menuMejoras[i]->setFont(*fuente);
        menuMejoras[i]->setString(textoMenuMejoras[i]);
        menuMejoras[i]->setOrigin(menuMejoras[i]->getGlobalBounds().width / 2.0, menuMejoras[i]->getGlobalBounds().height / 2.0);
        menuMejoras[i]->setPosition(ventanaMenu->getSize().x / 2.0, ventanaMenu->getSize().y / 4.0 + separacion * i);
        menuMejoras[i]->setColor(sf::Color(255,255,255));
    }
}

int menu::drawMenu()
{
    int devolucion = -1;
    ventanaMenu->setView(*vistaMenu);
    devolucion = actualizarMenu();
    ventanaMenu->draw(*fondo);
    renderMenu(idMenu);

    return devolucion;
}

void menu::copiarTextArray(sf::Text* origen [4], sf::Text* destino [4])
{
    for(int i = 0; i < 4; i++)
    {
        destino[i] = new sf::Text();
        destino[i]->setFont(*fuente);
        destino[i]->setString(origen[i]->getString());
        destino[i]->setOrigin(origen[i]->getOrigin());
        destino[i]->setPosition(origen[i]->getPosition());
        destino[i]->setColor(origen[i]->getColor());
    }
}

void menu::vaciarTextArray(sf::Text* textArray [4])
{
    for(int i = 0; i < 4; i++)
    {
        textArray[i] = NULL;
    }
}

void menu::renderMenu(int queMenu)
{
    sf::Text* menuAPintar [4];
    int tam;
    vaciarTextArray(menuAPintar);
    if(queMenu == 0)
    {
        copiarTextArray(menuInicial, menuAPintar);
        tam = 4;
    }
    else if(queMenu == 1)
    {
        copiarTextArray(menuSelectNivel, menuAPintar);
        tam = 2;
    }
    else if(queMenu == 2)
    {
        copiarTextArray(menuNiveles, menuAPintar);
        tam = 3;
    }
    else if(queMenu == 3)
    {
        copiarTextArray(menuEstad, menuAPintar);
        tam = 3;
    }
    else
    {
        copiarTextArray(menuMejoras, menuAPintar);
        tam = 4;
    }
    hoverMenu(menuAPintar);
    for(int i = 0; i < tam; i++)
    {
        ventanaMenu->draw(*menuAPintar[i]);
    }
}

void menu::hoverMenu(sf::Text* menuAPintar [4])
{
    sf::Color hover(197, 36, 36);
    menuAPintar[actual]->setColor(hover);
    //menuAPintar[actual]->setOutlineColor(sf::Color::Black);
    //menuAPintar[actual]->setOutlineThickness(3);
}

int menu::actualizarMenu()
{
    int devolucion = -1;
    sf::Text* menuActual [4];
    memcpy(menuActual, menuInicial, 4);

    if(tiempoEntreTeclas.getElapsedTime().asSeconds()>0.2f){

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::M))
                {
                    tiempoEntreTeclas.restart();
                    mostrarMenu++;
                    if(mostrarMenu > 2)
                    {
                        mostrarMenu = 1;
                        presionado = 0;
                        actual = 0;
                    }
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
                {
                    tiempoEntreTeclas.restart();
                    actual--;
                    if((idMenu == 0 || idMenu == 4) && actual < 0)
                    {
                        actual = 3;
                    }
                    else if(idMenu == 1 && actual < 0)
                    {
                        actual = 1;
                    }
                    else if((idMenu == 2 || idMenu == 3) && actual < 0)
                    {
                        actual = 2;
                    }
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
                {
                    tiempoEntreTeclas.restart();
                    actual++;
                    if((idMenu == 0 || idMenu == 4) && actual > 3)
                    {
                        actual = 0;
                    }
                    else if(idMenu == 1 && actual > 1)
                    {
                        actual = 0;
                    }
                    else if((idMenu == 2 || idMenu == 3) && actual > 2)
                    {
                        actual = 0;
                    }
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                {
                    tiempoEntreTeclas.restart();
                    if(idMenu == 0)
                    {
                        cont = 0;


                    }
                    else
                    {
                        cont = 2;

                    }

                    if(idMenu ==0 && actual==0){
                        cout << "entra" << endl;
                        devolucion = 0;
                    }
                    if(idMenu == 0 && actual == 1)
                    {
                        actual = 0;
                        idMenu = 1;
                        cont = 1;
                    }
                    else if(idMenu == 1 && actual == 0)
                    {
                        actual = 0;
                        idMenu = 2;
                        cont = 1;
                    }
                    else if(idMenu == 1 && actual == 1)
                    {
                        actual = 0;
                        idMenu = 3;
                        cont = 1;
                    }
                    else if(idMenu == 0 && actual == 2)
                    {
                        actual = 0;
                        idMenu = 4;
                        cont = 1;
                    }
                    else if(idMenu == 0 && actual == 3)
                    {
                        presionado = actual;
                        escribirPorConsola();
                        ventanaMenu->close();
                        ventanaMenu = NULL;
                        exit(1);
                    }
                    presionado = actual;
                    escribirPorConsola();
                }
                else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
                {
                    tiempoEntreTeclas.restart();
                    idMenu = 0;
                    presionado = 0;
                    actual = 0;
                }

    }
    return devolucion;

}

void menu::escribirPorConsola()
{
    if(idMenu == 0)
    {
        cout << mensajesConsolaMI[presionado] << endl;
    }
    else if(idMenu == 1)
    {
        if(cont == 2)
        {
            cout << mensajesConsolaSelectNiv[presionado] << endl;
        }
        else
        {
            cout << mensajesConsolaMI[1] << endl;
        }
    }
    else if(idMenu == 2)
    {
        if(cont == 2)
        {
            cout << mensajesConsolaNivel[presionado] << endl;
        }
        else
        {
            cout << "Lista de Niveles" << endl;
        }
    }
    else if(idMenu == 3)
    {
        if(cont == 2)
        {
            cout << mensajesConsolaEstad[presionado] << endl;
        }
        else
        {
            cout << "Lista de Estadisticas" << endl;
        }
    }
    else
    {
        if(cont == 2)
        {
            cout << mensajesConsolaMej[presionado] << endl;
        }
        else
        {
            cout << mensajesConsolaMI[2] << endl;
        }
    }
}

int menu::getNivel(){return nivel;}
