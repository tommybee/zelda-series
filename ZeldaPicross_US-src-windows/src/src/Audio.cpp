/*

    Zelda Picross

    Copyright (C) 2010  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>

#include "Audio.h"

Audio Audio::instance=Audio();

Audio::Audio() : volume(0), musiqueId(0), playing(false) {
    SOUND = FSOUND_Init(44100, 32, 0);
    music = NULL;
//SOUND=0; // to remove -> hack for no sound mode
//setVolume(32);
//setVolson(32);
    if (SOUND) {
        previous_volume = -1;
        previous_volson = FSOUND_GetSFXMasterVolume();
        loadSounds();
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        FMUSIC_StopSong(music);
        FMUSIC_SetMasterVolume(music, previous_volume);
        FMUSIC_FreeSong(music);
        FSOUND_SetSFXMasterVolume(previous_volson);
        FSOUND_Close();
    }
}

Audio* Audio::getInstance() {
    return &instance;
}

void Audio::setVolume(int vol) {volume=vol*4;
    if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
    FMUSIC_SetMasterVolume(music, volume);}
void Audio::setVolson(int volson) {FSOUND_SetSFXMasterVolume(volson*4);}

void Audio::loadSounds() {
    sons = new FSOUND_SAMPLE*[16];
    
    sons[0] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/text.ogg",0,0,0); // lettres
    sons[1] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu1.ogg",0,0,0); // menu 1
    sons[2] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu2.ogg",0,0,0); // menu 2
    sons[3] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/menu3.ogg",0,0,0); // menu 3
    sons[4] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/surprise.ogg",0,0,0); // surprise
    sons[5] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/monte.ogg",0,0,0); // monte
    sons[6] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/descend.ogg",0,0,0); // descend
    sons[7] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/bomb.ogg",0,0,0); // bombe
    sons[8] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/textnext.ogg",0,0,0); // suite texte
    sons[9] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/textend.ogg",0,0,0); // fin texte
    sons[10] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/happy.ogg",0,0,0); // trouve objet
    sons[11] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/sword.ogg",0,0,0); // épée
    sons[12] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/Sword360.ogg",0,0,0); // spin
    sons[13] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/stamp.ogg",0,0,0); // pose bombe
    sons[14] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/danger.ogg",0,0,0); // danger
    sons[15] = FSOUND_Sample_Load(FSOUND_FREE, "data/sound/hurt.ogg",0,0,0); // link se blesse
    
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 16; i++) FSOUND_Sample_Free(sons[i]);
        delete[] sons;
    }
}

void Audio::playSound(int id, int chl) {
    if (SOUND) FSOUND_PlaySound(chl, sons[id]);
}

void Audio::stopSound() {
    if (SOUND) {FSOUND_StopSound(FSOUND_ALL); musiqueId=0;}
}

void Audio::playMusic(int id) {
    if (SOUND) {
        if (musiqueId != id || !playing) {
            musiqueId = id;
            FMUSIC_StopSong(music);
            FMUSIC_FreeSong(music);
            music = choixMusique(id);
            if (previous_volume == -1) previous_volume = FMUSIC_GetMasterVolume(music);
            FMUSIC_SetMasterVolume(music, volume);
            FMUSIC_SetLooping(music, 1);
            FMUSIC_PlaySong(music);
            playing = true;
        }
    }
}

void Audio::stopMusic() {
    if (SOUND) FMUSIC_StopSong(music);
    playing = false;
}

void Audio::replayMusic() {
    if (SOUND) FMUSIC_PlaySong(music);
    playing = true;
}

FMUSIC_MODULE* Audio::choixMusique(int id) {
    switch (id) {
        case 1 : return FMUSIC_LoadSong("data/music/Plaine.mid");
        case 2 : return FMUSIC_LoadSong("data/music/Home.mid");
        case 3 : return FMUSIC_LoadSong("data/music/Lac.mid");
        case 4 : return FMUSIC_LoadSong("data/music/Cocorico.mid");
        case 5 : return FMUSIC_LoadSong("data/music/Mont.mid");
        case 6 : return FMUSIC_LoadSong("data/music/BoisPerdus.mid");
        case 7 : return FMUSIC_LoadSong("data/music/Jeu.mid");
        case 8 : return FMUSIC_LoadSong("data/music/Chateau.mid");
        case 9 : return FMUSIC_LoadSong("data/music/Boss.mid");
        case 10 : return FMUSIC_LoadSong("data/music/DFinal.mid");
        case 11 : return FMUSIC_LoadSong("data/music/BossF.mid");
        case 12 : return FMUSIC_LoadSong("data/music/Zelda.mid");
        case 190 : return FMUSIC_LoadSong("data/music/Selection.mid");
        case 195 : return FMUSIC_LoadSong("data/music/Magasin.mid");
        case 200 : return FMUSIC_LoadSong("data/music/Titre.mid");
        case 210 : return FMUSIC_LoadSong("data/music/Debut.mid");
        case 220 : return FMUSIC_LoadSong("data/music/Mort.mid");
        case 230 : return FMUSIC_LoadSong("data/music/Fin.mid");
        default : return FMUSIC_LoadSong("data/music/Plaine.mid");
    }
}
