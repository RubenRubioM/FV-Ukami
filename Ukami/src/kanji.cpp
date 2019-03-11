#include "kanji.h"

kanji::kanji(int resX, int resY, int kanjiSelected, string title)
{
    //ctor
    fps = 60;
    kanjiWindow = new sf::RenderWindow(sf::VideoMode(resX, resY), title);
    kanjiWindow->setFramerateLimit(fps);

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

    keyEvent = new sf::Event;

    gameLoop();


}

kanji::~kanji()
{
    //dtor
}

void kanji::loadFont()
{
    font1 = new sf::Font();
    font1->loadFromFile("./tipografia/ninjaNaruto/njnaruto.ttf");
}

void kanji::loadWinMessage()
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

void kanji::loadKanjiTextures(int idText)
{
    switch(idText)
    {
        case (0):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf1.png");
            break;
        }
        case (1):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf2.png");
            break;
        }
        case (2):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf3.png");
            break;
        }
        case (3):
        {
            kanjiTextures[idText]->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/circunf4.png");
            break;
        }
    }
}

void kanji::selectKanji(int idKanji)
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

void kanji::createKanjiTextures()
{
    for(int i = 0; i < 4; i++){
        kanjiTextures[i] = new sf::Texture;
        loadKanjiTextures(i);
    }
}

void kanji::kanjiSpritesPosition(sf::Sprite* kanjiSprite) //establecemos el origen de cada circunferencia a su centro y las colocamos en el centro de la pantalla
{
    kanjiSprite->setOrigin(kanjiSprite->getTexture()->getSize().x / 2.f, kanjiSprite->getTexture()->getSize().y / 2.f);
    kanjiSprite->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f);
}

void kanji::loadKanjiSprites()
{
    for(int i = 0; i < 4; i++){
        kanjiSprites[i] = new sf::Sprite(*kanjiTextures[i]);
        kanjiSpritesPosition(kanjiSprites[i]);
    }
}

void kanji::loadCorrectKanji()
{
    finalKanji = new sf::Texture;
    finalKanji->loadFromFile("./kanjiImages/" + kanjiName + "/puzzle/correct.png");
    correctKanji = new sf::Sprite(*finalKanji);
    correctKanji->setOrigin(correctKanji->getTexture()->getSize().x / 2.f, correctKanji->getTexture()->getSize().y / 2.f);
    correctKanji->setPosition(kanjiWindow->getSize().x / 2.f, kanjiWindow->getSize().y / 2.f);
}

void kanji::loadBackground()
{
    background = new sf::Texture;
    background->loadFromFile("./kanjiBackground/background.png");
    kanjiBack = new sf::Sprite(*background);
    kanjiBack->setScale((float)kanjiWindow->getSize().x / kanjiBack->getTexture()->getSize().x, (float)kanjiWindow->getSize().y / kanjiBack->getTexture()->getSize().y); //importante parsear a float para obtener justo la escala con decimales con tal de evitar problemas
}

bool kanji::checkRep(int n, int rango, int num[]) //con este metodo compruebo si el numero aleatorio generado ya se ha generado previamente o no
{
    bool estaRepe;
    for(int i = 0; i < rango; i++)
    {
        if(n == num[i])
        {
            estaRepe = true;
        }
        else
        {
            estaRepe = false;
        }
    }
    return estaRepe;
}

void kanji::genRandRotIndices(int *rot)
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

void kanji::doRotationToSprites() //le aplico las rotaciones a los sprites cargados
{
    genRandRotIndices(rotationsKanji);
    for(int i = 0; i < 4; i++)
    {
        kanjiSprites[i]->setRotation(kanjiSprites[i]->getRotation() - angle*rotationsKanji[i]); //para que tome como referencia de las rotaciones el giro a la derecha y no a la izquierda
    }
}

void kanji::render()
{

    kanjiWindow->clear();
    kanjiWindow->draw(*kanjiBack); //pinto el background
    renderSprites(); //pinto los sprites
    if(win) //si he ganado
    {

        kanjiWindow->draw(*correctKanji); //pinto el kanji en su forma correcta sin separar
        kanjiWindow->draw(*winText); //pinto el mensaje de has ganado.

    }
    kanjiWindow->display();

}

void kanji::renderSprites()
{
    for(int i = 0; i < 4; i++){
        kanjiWindow->draw(*kanjiSprites[i]);
    }
}

void kanji::updateKanji()
{
    while(kanjiWindow->pollEvent(*keyEvent))
    {
        int auxAngle;
        switch(keyEvent->type)
        {
            case sf::Event::Closed: //si se clica en el boton de cerrar la ventana
            {
                kanjiWindow->close();
                kanjiWindow = NULL;
                exit(1);
                break;
            }
            case sf::Event::KeyPressed:
            {
               if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) //si en el teclado esta presionada la tecla "Up", ejecuta estas instrucciones (Up es la flecha para arriba).
               {
                   if(!win)
                   {
                        if(n <= 0)
                        {
                            n = 0;
                        }
                        else
                        {
                            n = n - 1;
                        }
                   }
               }
               else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
               {
                   if(!win)
                   {
                        if(n >= 3)
                        {
                            n = 3;
                        }
                        else
                        {
                            n = n + 1;
                        }
                   }

               }
               else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
               {
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
               else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) //si has ganado el juego y pulsas la tecla enter se cierra la ventana
               {
                   if(win)
                   {
                        kanjiWindow->close();
                        kanjiWindow = NULL;
                        exit(1);
                   }
               }
               else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //se puede cerrar la ventana en cualquier momento pulsando la tecla escape
               {
                    kanjiWindow->close();
                    kanjiWindow = NULL;
                    exit(1);
               }

                if(!win) //mientras no se haya ganado, se comprueba si el kanji esta correcto o no
                {
                    checkKanji();
                }

               break;
            }
            default:
            {

            }
        }
    }

}

void kanji::gameLoop()
{

    while(kanjiWindow->isOpen())
    {
        updateKanji();
        render();
    }

}

void kanji::checkKanji()
{
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
    }
}
