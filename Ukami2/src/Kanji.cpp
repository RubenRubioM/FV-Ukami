<<<<<<< HEAD:Ukami2/src/Kanji.cpp
#include "Kanji.h"

Kanji::Kanji(int kanjiSelected, string title, sf::RenderWindow &window, sf::Event &eventGame)
{
    cout << "==== Creamos el kanji ====" << endl;
    kanjiWindow = &window;
    kanjiView = new sf::View();
    kanjiView->setSize(1280,720);
    kanjiView->setCenter(kanjiView->getSize().x / 2, kanjiView->getSize().y / 2);
    for(int i = 0; i < 4; i++)
    {
        correctKanjiArray[i] = 0;
    }

    angle = 30;

    n = 0;

    win = false;

    loadFont();
    loadWinMessage();

    if(kanjiSelected > 2){
        kanjiSelected = 0;
    }

    selectKanji(kanjiSelected);
    loadBackground();
    createKanjiTextures();
    loadKanjiSprites();

    doRotationToSprites();

    loadCorrectKanji();
}

void Kanji::loadFont()
{
    font1 = new sf::Font();
    font1->loadFromFile("./tipografia/ninjaNaruto/njnaruto.ttf");
}

void Kanji::loadWinMessage()
{
    string winMessage = "Has ganado!";
    winText = new sf::Text();
    winText->setFont(*font1);
    winText->setString(winMessage);
    winText->setCharacterSize(100);
    winText->setColor(sf::Color::Green);
    winText->setOrigin(winText->getGlobalBounds().width / 2.f, winText->getGlobalBounds().height / 2.0f); //establezco el origen de coordenadas al centro del texto
    winText->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f); //coloco el texto en el centro de la pantalla
}

void Kanji::loadKanjiTextures(int idText)
{
    switch(idText)
    {
        case (0):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf1.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
        case (1):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf2.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
        case (2):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf3.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
        case (3):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf4.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
    }
}

void Kanji::selectKanji(int idKanji)
{
    switch (idKanji)
    {
        case (0):
        {
            kanjiName = "ukami";
            break;
        }
        case (1):
        {
            kanjiName = "mononobe";
            break;
        }
        case (2):
        {
            kanjiName = "onmitsu";
            break;
        }
    }

    if (kanjiName.empty())
    {
        kanjiName = "ukami";
    }
}

void Kanji::createKanjiTextures()
{
    for(int i = 0; i < 4; i++){
        kanjiTextures[i] = new sf::Texture;
        loadKanjiTextures(i);
    }
}

void Kanji::kanjiSpritesPosition(sf::Sprite* kanjiSprite) //establecemos el origen de cada circunferencia a su centro y las colocamos en el centro de la pantalla
{
    kanjiSprite->setOrigin(kanjiSprite->getTexture()->getSize().x / 2.f, kanjiSprite->getTexture()->getSize().y / 2.f);
    kanjiSprite->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f);
}

void Kanji::loadKanjiSprites()
{
    for(int i = 0; i < 4; i++){
        kanjiSprites[i] = new sf::Sprite(*kanjiTextures[i]);

        kanjiSpritesPosition(kanjiSprites[i]);
    }
}

void Kanji::loadCorrectKanji()
{
    finalKanji = new sf::Texture;
    finalKanji->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/correct.png");
    correctKanji = new sf::Sprite(*finalKanji);
    correctKanji->setOrigin(correctKanji->getTexture()->getSize().x / 2.f, correctKanji->getTexture()->getSize().y / 2.f);
    correctKanji->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f);
}

void Kanji::loadBackground()
{
    background = new sf::Texture;
    background->loadFromFile("./kanjiBackground/background.png");
    kanjiBack = new sf::Sprite(*background);
    kanjiBack->setScale((float)kanjiWindow->getSize().x / kanjiBack->getTexture()->getSize().x, (float)kanjiWindow->getSize().y / kanjiBack->getTexture()->getSize().y); //importante parsear a float para obtener justo la escala con decimales con tal de evitar problemas
}

bool Kanji::checkRep(int n, int rango, int num[]) //con este metodo compruebo si el numero aleatorio generado ya se ha generado previamente o no
{
    bool estaRepe = false;
    for(int i = 0; i < rango; i++)
    {
        if(n == num[i])
        {
            estaRepe = true;
            break;
        }
    }
    return estaRepe;
}

void Kanji::genRandRotIndices(int *rot)
{
    srand(time(NULL));
    int rango = 360/angle - 2; //el rango se corresponde al numero de rotaciones que puede haber en la circunferencia. Se calcula diviendo los 360 grados que forma el circulo entre el angulo escogido menos 2 para evitar que no se tenga que girar la circunferencia 0 veces ni una sola vez para completar el puzzle. Des ta manera, evitamos que el numero de rotaciones caiga justo en 12 ya que es lo mismo que no tener que girar nada y restringimos el numero de veces en los que solo se tenga que rotar 1 vez al numero 1 solamente, ya que si fuera 11 el numero de rotaciones, solo habria que girar 1 vez la circunferencia al igual que cuando el numero de rotaciones es 1.
    if(rango < 3) //si a la hora de establecer al angulo de rotacion obtienes un valor que se corresponda con un numero menor que 3 (hay que hacerlo a partir de 3 debido al menos 2 que le aplico al rango), se pone el valor del angulo y del rango por defecto (esto hay que evitarlo ya que si yo voy a crear un vector de tamanyo 0, el programa dara error ya que el minimo permitido es tamanyo 1)
    {
        angle = 30;
        rango = 10;
    }
    int n, num[rango];
    for(int i=0; i<rango; i++)
    {
        do
            n = 1 + rand() % rango;
        while(checkRep(n, rango, num));
        num[i] = n;
    }
    for(int j = 0; j < 4; j++)
    {
        rot[j] = num[j];
    }
}

void Kanji::doRotationToSprites() //le aplico las rotaciones a los sprites cargados
{
    genRandRotIndices(rotationsKanji);
    for(int i = 0; i < 4; i++)
    {
        kanjiSprites[i]->setRotation(kanjiSprites[i]->getRotation() - angle*rotationsKanji[i]); //para que tome como referencia de las rotaciones el giro a la derecha y no a la izquierda
    }
}

void Kanji::drawKanji()
{

    kanjiWindow->setView(*kanjiView);
    kanjiWindow->draw(*kanjiBack); //pinto el background

    // ==== Renderizamos los sprites ====
    for(int i = 0; i < 4; i++){
        kanjiWindow->draw(*kanjiSprites[i]);
    }

    if(win) //si he ganado
    {

        kanjiWindow->draw(*correctKanji); //pinto el kanji en su forma correcta sin separar
        kanjiWindow->draw(*winText); //pinto el mensaje de has ganado.

    }
}

bool Kanji::updateKanji() //no se crea ningun estado adicional porque al manejar mas de un estado aunque uno sea un puntero al otro, se gestiona mal y no funciona como deberia por el tiempo que tarda en llegar la informacion del evento actualizada al nuevo evento creado
{

    bool devolucion = false;
    int auxAngle;

    if(tiempoEntreTecla.getElapsedTime().asSeconds()>0.2f){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //si en el teclado esta presionada la tecla "Up", ejecuta estas instrucciones (Up es la flecha para arriba).
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(n <= 0) //si estoy en la primera circunferencia (la mas externa), y le vuelvo a dar a la flecha de arriba, me voy a la ultima circunferencia (la mas interna).
                {
                    n = 3;
                }
                else
                {
                    n = n - 1;
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(n >= 3) //si estoy en la ultima circunferencia (la mas interna), y le vuelvo a dar a la flecha de abajo, me voy a la primera circunferencia (la mas externa).
                {
                    n = 0;
                }
                else
                {
                    n = n + 1;
                }
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(kanjiSprites[n]->getRotation() - angle <= 0)
                {
                    auxAngle = kanjiSprites[n]->getRotation() - angle + 360;
                }
                else
                {
                    auxAngle = kanjiSprites[n]->getRotation() - angle;
                }
                if(auxAngle == 360) //como con la flecha izquierda soy capaz de llegar a 360 grados, pongo el valor de auxAngle a 0 cuando ocurra esta situacion, ya que 360 grados es lo mismo que 0 grados en uno de los 2 sentidos de la circunferencia.
                {
                    auxAngle = 0;
                }
                rotationsKanji[n] = auxAngle/angle; //actualizo el valor de las rotaciones que posee la circunferencia actual seleccionada. Angle, se corresponde con un valor de 30 grados-
                kanjiSprites[n]->setRotation(auxAngle);
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(kanjiSprites[n]->getRotation() + angle >= 360)
                {
                    auxAngle = kanjiSprites[n]->getRotation() + angle - 360;
                }
                else
                {
                    auxAngle = kanjiSprites[n]->getRotation() + angle;
                }
                rotationsKanji[n] = auxAngle/angle;
                kanjiSprites[n]->setRotation(auxAngle);
            }

        }
    }


    if(checkKanji() && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        devolucion = true;
    }

    return devolucion;

}

bool Kanji::checkKanji()
{
    bool devolucion = false;
    int cont = 0;
    for(int i = 0; i < 4; i++)
    {
        if(correctKanjiArray[i] == rotationsKanji[i])
        {
            cont++;
        }
    }

    if(cont == 4)
    {
        cout << "¡Has ganado!" << endl;
        win = true;
        devolucion = true;

        //TODO: aqui se cambiara el evento pzra que se vuelve al mapa del juego
    }

    return devolucion;
}

Kanji::~Kanji()
{
    delete font1;
    delete winText;
    delete[] kanjiTextures;
    delete[] kanjiSprites;
    delete background;
    delete kanjiBack;
    delete correctKanji;
    delete kanjiWindow;
    delete kanjiView;
}
=======
#include "Kanji.h"

Kanji::Kanji(int kanjiSelected, string title, sf::RenderWindow &window, sf::Event &eventGame)
{
    cout << "==== Creamos el kanji ====" << endl;
    kanjiWindow = &window;
    kanjiView = new sf::View();
    kanjiView->setSize(1280,720);
    kanjiView->setCenter(kanjiView->getSize().x / 2, kanjiView->getSize().y / 2);
    for(int i = 0; i < 4; i++)
    {
        correctKanjiArray[i] = 0;
    }

    angle = 30;

    n = 0;

    win = false;

    loadFont();
    loadWinMessage();

    if(kanjiSelected > 2){
        kanjiSelected = 0;
    }

    selectKanji(kanjiSelected);
    loadBackground();
    createKanjiTextures();
    loadKanjiSprites();

    doRotationToSprites();

    loadCorrectKanji();
}

void Kanji::loadFont()
{
    font1 = new sf::Font();
    font1->loadFromFile("./tipografia/ninjaNaruto/njnaruto.ttf");
}

void Kanji::loadWinMessage()
{
    string winMessage = "Has ganado!";
    winText = new sf::Text();
    winText->setFont(*font1);
    winText->setString(winMessage);
    winText->setCharacterSize(100);
    winText->setColor(sf::Color::Green);
    winText->setOrigin(winText->getGlobalBounds().width / 2.f, winText->getGlobalBounds().height / 2.0f); //establezco el origen de coordenadas al centro del texto
    winText->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f); //coloco el texto en el centro de la pantalla
}

void Kanji::loadKanjiTextures(int idText)
{
    switch(idText)
    {
        case (0):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf1.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
        case (1):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf2.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
        case (2):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf3.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
        case (3):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf4.png");
            kanjiTextures[idText]->setSmooth(true);
            break;
        }
    }
}

void Kanji::selectKanji(int idKanji)
{
    switch (idKanji)
    {
        case (0):
        {
            kanjiName = "ukami";
            break;
        }
        case (1):
        {
            kanjiName = "mononobe";
            break;
        }
        case (2):
        {
            kanjiName = "onmitsu";
            break;
        }
    }

    if (kanjiName.empty())
    {
        kanjiName = "ukami";
    }
}

void Kanji::createKanjiTextures()
{
    for(int i = 0; i < 4; i++){
        kanjiTextures[i] = new sf::Texture;
        loadKanjiTextures(i);
    }
}

void Kanji::kanjiSpritesPosition(sf::Sprite* kanjiSprite) //establecemos el origen de cada circunferencia a su centro y las colocamos en el centro de la pantalla
{
    kanjiSprite->setOrigin(kanjiSprite->getTexture()->getSize().x / 2.f, kanjiSprite->getTexture()->getSize().y / 2.f);
    kanjiSprite->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f);
}

void Kanji::loadKanjiSprites()
{
    for(int i = 0; i < 4; i++){
        kanjiSprites[i] = new sf::Sprite(*kanjiTextures[i]);

        kanjiSpritesPosition(kanjiSprites[i]);
    }
}

void Kanji::loadCorrectKanji()
{
    finalKanji = new sf::Texture;
    finalKanji->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/correct.png");
    correctKanji = new sf::Sprite(*finalKanji);
    correctKanji->setOrigin(correctKanji->getTexture()->getSize().x / 2.f, correctKanji->getTexture()->getSize().y / 2.f);
    correctKanji->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f);
}

void Kanji::loadBackground()
{
    background = new sf::Texture;
    background->loadFromFile("./kanjiBackground/background.png");
    kanjiBack = new sf::Sprite(*background);
    kanjiBack->setScale((float)kanjiWindow->getSize().x / kanjiBack->getTexture()->getSize().x, (float)kanjiWindow->getSize().y / kanjiBack->getTexture()->getSize().y); //importante parsear a float para obtener justo la escala con decimales con tal de evitar problemas
}

bool Kanji::checkRep(int n, int rango, int num[]) //con este metodo compruebo si el numero aleatorio generado ya se ha generado previamente o no
{
    bool estaRepe = false;
    for(int i = 0; i < rango; i++)
    {
        if(n == num[i])
        {
            estaRepe = true;
            break;
        }
    }
    return estaRepe;
}

void Kanji::genRandRotIndices(int *rot)
{
    srand(time(NULL));
    int rango = 360/angle - 2; //el rango se corresponde al numero de rotaciones que puede haber en la circunferencia. Se calcula diviendo los 360 grados que forma el circulo entre el angulo escogido menos 2 para evitar que no se tenga que girar la circunferencia 0 veces ni una sola vez para completar el puzzle. Des ta manera, evitamos que el numero de rotaciones caiga justo en 12 ya que es lo mismo que no tener que girar nada y restringimos el numero de veces en los que solo se tenga que rotar 1 vez al numero 1 solamente, ya que si fuera 11 el numero de rotaciones, solo habria que girar 1 vez la circunferencia al igual que cuando el numero de rotaciones es 1.
    if(rango < 3) //si a la hora de establecer al angulo de rotacion obtienes un valor que se corresponda con un numero menor que 3 (hay que hacerlo a partir de 3 debido al menos 2 que le aplico al rango), se pone el valor del angulo y del rango por defecto (esto hay que evitarlo ya que si yo voy a crear un vector de tamanyo 0, el programa dara error ya que el minimo permitido es tamanyo 1)
    {
        angle = 30;
        rango = 10;
    }
    int n, num[rango];
    for(int i=0; i<rango; i++)
    {
        do
            n = 1 + rand() % rango;
        while(checkRep(n, rango, num));
        num[i] = n;
    }
    for(int j = 0; j < 4; j++)
    {
        rot[j] = num[j];
    }
}

void Kanji::doRotationToSprites() //le aplico las rotaciones a los sprites cargados
{
    genRandRotIndices(rotationsKanji);
    for(int i = 0; i < 4; i++)
    {
        kanjiSprites[i]->setRotation(kanjiSprites[i]->getRotation() - angle*rotationsKanji[i]); //para que tome como referencia de las rotaciones el giro a la derecha y no a la izquierda
    }
}

void Kanji::drawKanji()
{

    kanjiWindow->setView(*kanjiView);
    kanjiWindow->draw(*kanjiBack); //pinto el background

    // ==== Renderizamos los sprites ====
    for(int i = 0; i < 4; i++){
        kanjiWindow->draw(*kanjiSprites[i]);
    }

    if(win) //si he ganado
    {

        kanjiWindow->draw(*correctKanji); //pinto el kanji en su forma correcta sin separar
        kanjiWindow->draw(*winText); //pinto el mensaje de has ganado.

    }
}

bool Kanji::updateKanji() //no se crea ningun estado adicional porque al manejar mas de un estado aunque uno sea un puntero al otro, se gestiona mal y no funciona como deberia por el tiempo que tarda en llegar la informacion del evento actualizada al nuevo evento creado
{

    bool devolucion = false;
    int auxAngle;

    if(tiempoEntreTecla.getElapsedTime().asSeconds()>0.2f){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //si en el teclado esta presionada la tecla "Up", ejecuta estas instrucciones (Up es la flecha para arriba).
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(n <= 0) //si estoy en la primera circunferencia (la mas externa), y le vuelvo a dar a la flecha de arriba, me voy a la ultima circunferencia (la mas interna).
                {
                    n = 3;
                }
                else
                {
                    n = n - 1;
                }
            }
        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(n >= 3) //si estoy en la ultima circunferencia (la mas interna), y le vuelvo a dar a la flecha de abajo, me voy a la primera circunferencia (la mas externa).
                {
                    n = 0;
                }
                else
                {
                    n = n + 1;
                }
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(kanjiSprites[n]->getRotation() - angle <= 0)
                {
                    auxAngle = kanjiSprites[n]->getRotation() - angle + 360;
                }
                else
                {
                    auxAngle = kanjiSprites[n]->getRotation() - angle;
                }
                if(auxAngle == 360) //como con la flecha izquierda soy capaz de llegar a 360 grados, pongo el valor de auxAngle a 0 cuando ocurra esta situacion, ya que 360 grados es lo mismo que 0 grados en uno de los 2 sentidos de la circunferencia.
                {
                    auxAngle = 0;
                }
                rotationsKanji[n] = auxAngle/angle; //actualizo el valor de las rotaciones que posee la circunferencia actual seleccionada. Angle, se corresponde con un valor de 30 grados-
                kanjiSprites[n]->setRotation(auxAngle);
            }

        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            tiempoEntreTecla.restart();
            if(!win)
            {
                if(kanjiSprites[n]->getRotation() + angle >= 360)
                {
                    auxAngle = kanjiSprites[n]->getRotation() + angle - 360;
                }
                else
                {
                    auxAngle = kanjiSprites[n]->getRotation() + angle;
                }
                rotationsKanji[n] = auxAngle/angle;
                kanjiSprites[n]->setRotation(auxAngle);
            }

        }
    }


    if(checkKanji() && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
    {
        devolucion = true;
    }

    return devolucion;

}

bool Kanji::checkKanji()
{
    bool devolucion = false;
    int cont = 0;
    for(int i = 0; i < 4; i++)
    {
        if(correctKanjiArray[i] == rotationsKanji[i])
        {
            cont++;
        }
    }

    if(cont == 4)
    {
        cout << "¡Has ganado!" << endl;
        win = true;
        devolucion = true;

        //TODO: aqui se cambiara el evento pzra que se vuelve al mapa del juego
    }

    return devolucion;
}

Kanji::~Kanji()
{
    delete font1;
    delete winText;
    delete[] kanjiTextures;
    delete[] kanjiSprites;
    delete background;
    delete kanjiBack;
    delete correctKanji;
    delete kanjiWindow;
    delete kanjiView;
}
>>>>>>> 57f57d12db4eb9365f2d2aa12be8212bd48b0e7c:Ukami/src/Kanji.cpp
