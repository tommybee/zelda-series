/*

    Zelda Time to Triumph

    Copyright (C) 2007-2009  Vincent Jouillat

    Please send bugreports with examples or suggestions to www.zeldaroth.fr

*/

#include <sstream>
#include <fstream>
#include <iostream>

#include <SDL/SDL.h>

#include "Audio.h"

Audio::Audio() : musiqueId(0), specialId(0) {
    SOUND = true;
    music = NULL;
    
    if(SDL_InitSubSystem(SDL_INIT_AUDIO) == -1) SOUND = false;
    
    if (SOUND) {
        Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 2048);
        previous_volume = Mix_VolumeMusic(32);
        loadSounds();
        setVolson(32);
    }
}

Audio::~Audio() {
    if (SOUND) {
        freeSounds();
        Mix_PauseMusic();
        Mix_VolumeMusic(previous_volume);
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        Mix_CloseAudio();
    }
}

void Audio::setVolume(int volume) {
    if (SOUND) Mix_VolumeMusic(volume);
}

void Audio::setVolson(int volson) {
    if (SOUND) for (int i = 0; i < 44; i++) Mix_VolumeChunk(sons[i], volson);
}

void Audio::loadSounds() {
    sons = new Mix_Chunk*[44];

    sons[0] = Mix_LoadWAV("data/sound/text.ogg"); // lettres
    sons[1] = Mix_LoadWAV("data/sound/menu1.ogg"); // menu 1
    sons[2] = Mix_LoadWAV("data/sound/menu2.ogg"); // menu 2
    sons[3] = Mix_LoadWAV("data/sound/menu3.ogg"); // menu 3
    sons[4] = Mix_LoadWAV("data/sound/menu4.ogg"); // menu 4
    sons[5] = Mix_LoadWAV("data/sound/timewarp.ogg"); // time retour
    sons[6] = Mix_LoadWAV("data/sound/tombe.ogg"); // tombe (ennemi)
    sons[7] = Mix_LoadWAV("data/sound/hitenemy.ogg"); //shot 1
    sons[8] = Mix_LoadWAV("data/sound/killenemy.ogg"); // shot 2
    sons[9] = Mix_LoadWAV("data/sound/surprise.ogg"); // surprise
    sons[10] = Mix_LoadWAV("data/sound/monte.ogg"); // monte
    sons[11] = Mix_LoadWAV("data/sound/descend.ogg"); // descend
    sons[12] = Mix_LoadWAV("data/sound/chute.ogg"); // chute
    sons[13] = Mix_LoadWAV("data/sound/item.ogg"); // item
    sons[14] = Mix_LoadWAV("data/sound/rupee.ogg"); // rubis
    sons[15] = Mix_LoadWAV("data/sound/heart.ogg"); // coeur
    sons[16] = Mix_LoadWAV("data/sound/bomb.ogg"); // bombe
    sons[17] = Mix_LoadWAV("data/sound/textnext.ogg"); // suite texte
    sons[18] = Mix_LoadWAV("data/sound/textend.ogg"); // fin texte
    sons[19] = Mix_LoadWAV("data/sound/happy.ogg"); // trouve objet
    sons[20] = Mix_LoadWAV("data/sound/door.ogg"); // ouvre porte
    sons[21] = Mix_LoadWAV("data/sound/pics.ogg"); // pics contre mur
    sons[22] = Mix_LoadWAV("data/sound/sword.ogg"); // Epée
    sons[23] = Mix_LoadWAV("data/sound/SwordCharging.ogg"); // chargée
    sons[24] = Mix_LoadWAV("data/sound/Sword360.ogg"); // spin
    sons[25] = Mix_LoadWAV("data/sound/shoot.ogg"); // flèche
    sons[26] = Mix_LoadWAV("data/sound/hookshot.ogg"); // grappin
    sons[27] = Mix_LoadWAV("data/sound/stamp.ogg"); // pose bombe
    sons[28] = Mix_LoadWAV("data/sound/magic.ogg"); // magie
    sons[29] = Mix_LoadWAV("data/sound/burn.ogg"); // brËšle
    sons[30] = Mix_LoadWAV("data/sound/hammer.ogg"); // marteau
    sons[31] = Mix_LoadWAV("data/sound/plouf.ogg"); // plouf
    sons[32] = Mix_LoadWAV("data/sound/danger.ogg"); // danger
    sons[33] = Mix_LoadWAV("data/sound/hurt.ogg"); // link se blesse
    sons[34] = Mix_LoadWAV("data/sound/porte.ogg"); // porte objet
    sons[35] = Mix_LoadWAV("data/sound/lance.ogg"); // lance objet
    sons[36] = Mix_LoadWAV("data/sound/casse.ogg"); // casse objet
    sons[37] = Mix_LoadWAV("data/sound/charge.ogg"); // charge magie
    sons[38] = Mix_LoadWAV("data/sound/buisson.ogg"); // coupe buisson
    sons[39] = Mix_LoadWAV("data/sound/pousse.ogg"); // pousse caisse
	sons[40] = Mix_LoadWAV("data/sound/envol.ogg"); // chant envol
    sons[41] = Mix_LoadWAV("data/sound/inverse.ogg"); // hymne vide
    sons[42] = Mix_LoadWAV("data/sound/accelere.ogg"); // chant esprit
    sons[43] = Mix_LoadWAV("data/sound/splash.ogg"); // ...
}

void Audio::freeSounds() {
    if (SOUND) {
        for (int i = 0; i < 44; i++) Mix_FreeChunk(sons[i]);
        delete[] sons;
    }
}

void Audio::playSound(int id, int chl) {
    if (SOUND) Mix_PlayChannel(chl,sons[id],0);
}

void Audio::stopSound() {
    if (SOUND) {if (SOUND) Mix_HaltChannel(-1); musiqueId=0;}
}

void Audio::playMusic(int id) {
    if (SOUND) {
	if (id == 2 || id == 5 || id == 7 || id == 8 || id == 9 || id == 14) id = 1;
        if (id == 20 || id == 22 || id == 24) id = 17;
        if (id == 29) id = 19;
        if (id == 32 || id == 34 || id == 35 || id == 39 || id == 44) id = 31;
        if (id >= 61 && id <= 78) id = 61;
        if (id == 82 || id == 84 || id == 94 || id == 98 || id == 99
        || id == 101 || id == 107 || id == 108 || id == 109 || id == 112 
        || id == 117 || id == 118 || id == 122 || id == 128 || id == 129
        || id == 142 || id == 143 || id == 148 || id == 149) id = 81; //magasins
        if (id == 91 || id == 120 || id == 132) id = 85; //potions
        if (id == 102 || id == 136) id = 80; //bar
        if (id == 105 || id == 106 || id == 131 || id == 139 || id == 147) id = 95; //maire
        if (id == 152 || id == 153) id = 151; //temple temps
        if (musiqueId != id) {
	    musiqueId = id;            
            if (specialId == 0) {
		Mix_HaltMusic();
		Mix_FreeMusic(music);
		music = choixMusique(id);
		Mix_PlayMusic(music,-1);
		specialId = 0;
	    }
        }
    }
}

bool Audio::isSpecial() {return (specialId>0);}

void Audio::stopMusic() {
    if (SOUND) Mix_HaltMusic();
}

void Audio::replayMusic() {
    if (SOUND) Mix_PlayMusic(music,-1);
}

Mix_Music* Audio::choixMusique(int id) {
    switch (id) {
	case 1 : case 2 : case 7 : return Mix_LoadMUS("data/music/PlaineP.mid");
        case 3 : return Mix_LoadMUS("data/music/VilleCP.mid");
        case 4 : return Mix_LoadMUS("data/music/TerresS.mid");
        case 6 : return Mix_LoadMUS("data/music/BoisPerdus.mid");
        case 8 : return Mix_LoadMUS("data/music/CimetiereP.mid");
        case 10 : return Mix_LoadMUS("data/music/VillageMP.mid");
        case 11 : return Mix_LoadMUS("data/music/LacP.mid");
        case 12 : return Mix_LoadMUS("data/music/DesertP.mid");
        case 13 : return Mix_LoadMUS("data/music/Cocorico.mid");
        case 15 : return Mix_LoadMUS("data/music/MontP.mid");
        case 16 : return Mix_LoadMUS("data/music/Foret.mid");
        case 17 : return Mix_LoadMUS("data/music/Plaine.mid");
        case 18 : return Mix_LoadMUS("data/music/Cite.mid");
        case 19 : return Mix_LoadMUS("data/music/Chateau.mid");
        case 21 : return Mix_LoadMUS("data/music/Lanelle.mid");
        case 23 : return Mix_LoadMUS("data/music/Cimetiere.mid");
        case 25 : return Mix_LoadMUS("data/music/VillageM.mid");
        case 26 : return Mix_LoadMUS("data/music/Lac.mid");
        case 27 : return Mix_LoadMUS("data/music/Desert.mid");
        case 28 : return Mix_LoadMUS("data/music/VillageO.mid");
        case 30 : return Mix_LoadMUS("data/music/Mont.mid");
        case 31 : case 32 : case 34 : case 35 :
            return Mix_LoadMUS("data/music/Ombre.mid");
        case 33 : return Mix_LoadMUS("data/music/VilleF.mid");
        case 36 : return Mix_LoadMUS("data/music/BoisPerdusF.mid");
        case 37 : return Mix_LoadMUS("data/music/Cascades.mid");
        case 38 : return Mix_LoadMUS("data/music/CimetiereF.mid");
        case 40 : return Mix_LoadMUS("data/music/VillageMF.mid");
        case 41 : return Mix_LoadMUS("data/music/LacF.mid");
        case 42 : return Mix_LoadMUS("data/music/DesertF.mid");
        case 43 : return Mix_LoadMUS("data/music/VillageOF.mid");
        case 45 : return Mix_LoadMUS("data/music/MontF.mid");
        case 46 : return Mix_LoadMUS("data/music/Courage.mid");
        case 47 : return Mix_LoadMUS("data/music/Sagesse.mid");
        case 48 : return Mix_LoadMUS("data/music/Force.mid");
        case 49 : return Mix_LoadMUS("data/music/Abysses.mid");
        case 50 : return Mix_LoadMUS("data/music/PyramideF.mid");
        case 51 : return Mix_LoadMUS("data/music/PyramideP.mid");
        case 52 : return Mix_LoadMUS("data/music/Ordinn.mid");
        case 53 : return Mix_LoadMUS("data/music/Air.mid");
        case 54 : return Mix_LoadMUS("data/music/Glace.mid");
        case 55 : return Mix_LoadMUS("data/music/Feu.mid");
        case 56 : return Mix_LoadMUS("data/music/Titre.mid");
        case 57 : return Mix_LoadMUS("data/music/DFinal.mid");
        case 58 : return Mix_LoadMUS("data/music/Casino.mid");
        case 59 : return Mix_LoadMUS("data/music/Gemme.mid");
        case 60 : return Mix_LoadMUS("data/music/DestinationF.mid");
        case 61 : return Mix_LoadMUS("data/music/Cave.mid");
        case 79 : return Mix_LoadMUS("data/music/Home.mid");
        case 80 : return Mix_LoadMUS("data/music/Bar.mid");
        case 81 : return Mix_LoadMUS("data/music/Magasin.mid");
        case 83 : return Mix_LoadMUS("data/music/Maison.mid");
        case 85 : return Mix_LoadMUS("data/music/Potion.mid");
        case 89 : return Mix_LoadMUS("data/music/Jeu.mid");
        case 95 : return Mix_LoadMUS("data/music/Maire.mid");
        case 119 : return Mix_LoadMUS("data/music/Cafe.mid");
        case 144 : return Mix_LoadMUS("data/music/Sages.mid");
        case 150 : return Mix_LoadMUS("data/music/Opera.mid");
        case 151 : return Mix_LoadMUS("data/music/Epee.mid");
        case 154 : return Mix_LoadMUS("data/music/Prison.mid");
        case 155 : return Mix_LoadMUS("data/music/ChateauF.mid");
        case 218 : return Mix_LoadMUS("data/music/probleme.mid");
        case 219 : return Mix_LoadMUS("data/music/Epee.mid");
        case 180 : return Mix_LoadMUS("data/music/Titre.mid");
        case 190 : return Mix_LoadMUS("data/music/Selection.mid");
        case 199 : return Mix_LoadMUS("data/music/Nuit.mid");
        case 200 : return Mix_LoadMUS("data/music/Debut.mid");
        default : return Mix_LoadMUS("data/music/Maison.mid");
    }
}

void Audio::playSpecial(int id) {
    if (SOUND) {
        if (specialId != id) {
            Mix_HaltMusic();
            Mix_FreeMusic(music);
            music = choixSpecial(id);
            Mix_PlayMusic(music,-1);
            specialId=id;
        }    
    }
}

void Audio::stopSpecial() {
    if (!specialId) return;
    int tmp = musiqueId;
    musiqueId = 0;
    specialId = 0;
    playMusic(tmp);
}

Mix_Music* Audio::choixSpecial(int id) {
    switch (id) {
	case 1 : return Mix_LoadMUS("data/music/Boss.mid");
        case 2 : return Mix_LoadMUS("data/music/Mort.mid");
        case 3 : return Mix_LoadMUS("data/music/Epee.mid");
        case 4 : return Mix_LoadMUS("data/music/BossF.mid");
        case 5 : return Mix_LoadMUS("data/music/Fin.mid");
        case 6 : return Mix_LoadMUS("data/music/BossM.mid");
        case 7 : return Mix_LoadMUS("data/music/Area81.mid");
        case 8 : return Mix_LoadMUS("data/music/OniLink.mid");
        case 9 : return Mix_LoadMUS("data/music/probleme.mid");
        case 10 : return Mix_LoadMUS("data/music/Harpie.mid");
        case 11 : return Mix_LoadMUS("data/music/Crabe.mid");
        case 12 : return Mix_LoadMUS("data/music/Imp.mid");
        case 13 : return Mix_LoadMUS("data/music/Masamune.mid");
        case 14 : return Mix_LoadMUS("data/music/ZoraS.mid");
        case 15 : return Mix_LoadMUS("data/music/Marlag.mid");
        case 16 : return Mix_LoadMUS("data/music/Fantomas.mid");
        case 17 : return Mix_LoadMUS("data/music/Vampire.mid");
        case 18 : return Mix_LoadMUS("data/music/Araignee.mid");
        case 19 : return Mix_LoadMUS("data/music/Plumes.mid");
        case 20 : return Mix_LoadMUS("data/music/Garuda.mid");
        case 21 : return Mix_LoadMUS("data/music/Heckran.mid");
        case 22 : return Mix_LoadMUS("data/music/Sun.mid");
        case 23 : return Mix_LoadMUS("data/music/Orcus.mid");
        case 24 : return Mix_LoadMUS("data/music/Agahnim.mid");
        case 25 : return Mix_LoadMUS("data/music/Zelda.mid");
        case 26 : return Mix_LoadMUS("data/music/AgahnimFinal.mid");
        case 27 : return Mix_LoadMUS("data/music/GanondorfFinal.mid");
        case 28 : return Mix_LoadMUS("data/music/Quizz.mid");
        case 29 : return Mix_LoadMUS("data/music/FinalBattle.mid");
        default : return Mix_LoadMUS("data/music/Boss.mid");
    }
}

