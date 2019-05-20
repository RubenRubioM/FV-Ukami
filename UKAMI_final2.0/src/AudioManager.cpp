#include "AudioManager.h"
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

AudioManager* AudioManager::unicaInstancia = 0;

/*Para utilizarlo:

    AudioManager *audio = AudioManager::getInstance();
    AudioManager::getInstance()->respirar();

*/
AudioManager::AudioManager()
{

    menu0_b.loadFromFile("sounds/menu0.ogg");
    menu1_b.loadFromFile("sounds/menu1.ogg");
    menu2_b.loadFromFile("sounds/menu2.ogg");

    dash_b.loadFromFile("sounds/dash.ogg");
    sigilo_b.loadFromFile("sounds/sigilo.ogg");
    palanca_b.loadFromFile("sounds/palanca.ogg");
    silbido_b.loadFromFile("sounds/silbido.ogg");
    caminar1_b.loadFromFile("sounds/caminar1.ogg");
    detection1_b.loadFromFile("sounds/detection1.ogg");
    guardia1_b.loadFromFile("sounds/guardia1.ogg");
    guardia2_b.loadFromFile("sounds/guardia2.ogg");
    grass1_b.loadFromFile("sounds/grass1.ogg");
    drag_b.loadFromFile("sounds/drag.ogg");
    kanji_b.loadFromFile("sounds/kanji.ogg");
    kanji2_b.loadFromFile("sounds/kanji2.ogg");
    kanjiWIN_b.loadFromFile("sounds/kanjiWIN.ogg");
    coin_b.loadFromFile("sounds/coin.ogg");
    win_b.loadFromFile("sounds/win.ogg");
    gameover_b.loadFromFile("sounds/gameover.ogg");

    menu0_sound.setBuffer(menu0_b);
    menu1_sound.setBuffer(menu1_b);
    menu2_sound.setBuffer(menu2_b);
    dash_sound.setBuffer(dash_b);
    caminar1_sound.setBuffer(caminar1_b);
    sigilo_sound.setBuffer(sigilo_b);
    palanca_sound.setBuffer(palanca_b);
    silbido_sound.setBuffer(silbido_b);
    grass1_sound.setBuffer(grass1_b);
    detection1_sound.setBuffer(detection1_b);
    guardia1_sound.setBuffer(guardia1_b);
    guardia2_sound.setBuffer(guardia2_b);
    drag_sound.setBuffer(drag_b);
    kanji_sound.setBuffer(kanji_b);
    kanji2_sound.setBuffer(kanji2_b);
    kanjiWIN_sound.setBuffer(kanjiWIN_b);
    coin_sound.setBuffer(coin_b);
    win_sound.setBuffer(win_b);
    gameover_sound.setBuffer(gameover_b);

    menu_music.openFromFile("sounds/menu.ogg");
    menu_music.setLoop(true);
    nivel1_music.openFromFile("sounds/nivel1.ogg");
    nivel1_music.setLoop(true);
}

AudioManager::~AudioManager()
{
    //dtor
}

void AudioManager::dash()
{
    if (dash_sound.getStatus() == SoundSource::Stopped)
        dash_sound.play();
}
void AudioManager::guardia1()
{
    if (guardia1_sound.getStatus() == SoundSource::Stopped)
        guardia1_sound.play();
}
void AudioManager::guardia2()
{
    if (guardia2_sound.getStatus() == SoundSource::Stopped)
        guardia2_sound.play();
}

void AudioManager::win()
{
    if (win_sound.getStatus() == SoundSource::Stopped)
        win_sound.play();
}

void AudioManager::gameover()
{
    if (gameover_sound.getStatus() == SoundSource::Stopped)
        gameover_sound.play();
}

void AudioManager::caminar1()
{
    if (caminar1_sound.getStatus() == SoundSource::Stopped)
        caminar1_sound.play();
}
void AudioManager::grass1()
{
    if (grass1_sound.getStatus() == SoundSource::Stopped)
        grass1_sound.play();
}
void AudioManager::drag()
{
    if (drag_sound.getStatus() == SoundSource::Stopped)
        drag_sound.play();
}
void AudioManager::coin()
{
    coin_sound.play();
}
void AudioManager::kanjiWIN()
{
        kanjiWIN_sound.play();
}
void AudioManager::kanji1()
{
        kanji_sound.play();
}
void AudioManager::kanji2()
{
        kanji2_sound.play();
}
void AudioManager::climb1()
{
    if (climb1_sound.getStatus() == SoundSource::Stopped)
        climb1_sound.play();
}
void AudioManager::menu0()
{
    menu0_sound.play();
}
void AudioManager::menu1()
{
    menu1_sound.play();
}
void AudioManager::menu2()
{
    menu2_sound.play();
}
void AudioManager::detection1()
{
    if (detection1_sound.getStatus() == SoundSource::Stopped)
        detection1_sound.play();
}
void AudioManager::palanca()
{
    if (palanca_sound.getStatus() == SoundSource::Stopped)
        palanca_sound.play();
}

void AudioManager::silbido()
{
    if (silbido_sound.getStatus() == SoundSource::Stopped)
        silbido_sound.play();
}

void AudioManager::sigilo()
{
    if (sigilo_sound.getStatus() == SoundSource::Stopped)
        sigilo_sound.play();
}
void AudioManager::menu()
{
    if (menu_music.getStatus() == SoundSource::Stopped)
        menu_music.play();
    else {
        menu_music.stop();
    }
}
void AudioManager::play_music_menu()
{
    menu_music.play();
}
void AudioManager::stop_music_menu()
{
    menu_music.stop();
}
void AudioManager::stop_sound_guardian2()
{
    guardia2_sound.stop();
}
void AudioManager::stop_music_nivel1()
{
    nivel1_music.stop();
}

void AudioManager::stop_sound_grass1()
{
    grass1_sound.stop();
}

void AudioManager::nivel(int i)
{
    if (i == 1) {
        nivel1_music.play();
    }
}
