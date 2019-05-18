#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System.hpp>
#include "tinyxml2.h"
#include "TextureHolder.h"
#include "Map.h"
#include "Ninja.h"
#include "Ninja1.h"
#include "Ninja2.h"
#include <iostream>
#include <vector>
#include <map>
#include "Box2D/Box2D.h"

using namespace std;
using namespace sf;

class AudioManager
{
public:
    static AudioManager *getInstance()
    {
        if (unicaInstancia == 0)
            unicaInstancia = new AudioManager();
        return unicaInstancia;
    }
    virtual ~AudioManager();

    void caminar1();
    void dash();
    void palanca();
    void silbido();
    void sigilo();
    void grass1();
    void climb1();
    void menu();
    void menu0();
    void menu1();
    void menu2();
    void coin();
    void kanji1();
    void kanji2();
    void kanjiWIN();
    void guardia1();
    void guardia2();
    void detection1();
    void win();
    void gameover();
    void drag();
    void play_music_menu();
    void stop_music_menu();
    void stop_sound_guardian2();
    void stop_music_nivel1();
    void stop_sound_grass1();
    void nivel(int i);

protected:
private:
    AudioManager();
    static AudioManager *unicaInstancia;

    SoundBuffer caminar1_b,
        dash_b,
        menu0_b,
        menu1_b,
        menu2_b,
        climb1_b,
        palanca_b,
        silbido_b,
        sigilo_b,
        menu_b,
        detection1_b,
        guardia1_b,
        guardia2_b,
        grass1_b,
        coin_b,
        drag_b,
        nivel1_b,
        kanji_b,
        kanji2_b,
        kanjiWIN_b,
        win_b,
        gameover_b;

    Sound caminar1_sound,
        sigilo_sound,
        menu0_sound,
        menu1_sound,
        menu2_sound,
        climb1_sound,
        dash_sound,
        palanca_sound,
        detection1_sound,
        coin_sound,
        guardia1_sound,
        guardia2_sound,
        grass1_sound,
        drag_sound,
        silbido_sound,
        kanji_sound,
        kanji2_sound,
        kanjiWIN_sound,
        win_sound,
        gameover_sound;

    Music menu_music, nivel1_music;
};

#endif // AUDIOMANAGER_H
