#ifndef __SONGS_H
#define __SONGS_H

#include <stdio.h>
#include <MMSystem.h>
#include <string.h>

typedef enum songs_ID
{

    MK_THEME,
    FATALITY,
    TECLADO_LINDINHO,
    FINISH_HIM,
    FINISH_HER,
    YOU_SUCK,
    WELL_DONE,
    EXCELLENT,
    FATALITY_BACKGROUND,
    SCREAM,
    PLAYER1WINS,
    PLAYER2WINS,
    FLAWLESS_VICTORY,
    ROUND_1,
    ROUND_2,
    ROUND_3,
    PUMPED_UP_KICKS,
    FIGHT,
    HINO,
    LATITUDE_DES,
    WHATSAPP_RINGTONE,
    CONTINUAR,
    MAP1,
    MAP2,
    MAP3,
    MAP4,
    MAP5,
    CREDITOS

} songs_ID;

char song_path[28][50];

void iniciar_sons()
{

    strcpy(song_path[MK_THEME], "GaloSongs\\mk.wav");
    strcpy(song_path[FATALITY], "GaloSongs\\fatality.wav");
    strcpy(song_path[TECLADO_LINDINHO], "GaloSongs\\Teclado.wav");
    strcpy(song_path[FINISH_HIM], "GaloSongs\\FinishHim.wav");
    strcpy(song_path[FINISH_HER], "GaloSongs\\FinishHer.wav");
    strcpy(song_path[YOU_SUCK], "GaloSongs\\YouSuck.wav");
    strcpy(song_path[WELL_DONE], "GaloSongs\\WellDone.wav");
    strcpy(song_path[EXCELLENT], "GaloSongs\\Excellent.wav");
    strcpy(song_path[FATALITY_BACKGROUND], "GaloSongs\\Fatality_Background.wav");
    strcpy(song_path[SCREAM], "GaloSongs\\Fatality_Scream.wav");
    strcpy(song_path[PLAYER1WINS], "GaloSongs\\Player_1_Wins.wav");
    strcpy(song_path[PLAYER2WINS], "GaloSongs\\Player_2_Wins.wav");
    strcpy(song_path[FLAWLESS_VICTORY], "GaloSongs\\Flawless_Victory.wav");
    strcpy(song_path[ROUND_1], "GaloSongs\\Round_1.wav");
    strcpy(song_path[ROUND_2], "GaloSongs\\Round_2.wav");
    strcpy(song_path[ROUND_3], "GaloSongs\\Round_3.wav");
    strcpy(song_path[PUMPED_UP_KICKS], "GaloSongs\\pumped-up-kicks.wav");
    strcpy(song_path[FIGHT], "GaloSongs\\fight.wav");
    strcpy(song_path[HINO], "GaloSongs\\hino_galista.wav");
    strcpy(song_path[LATITUDE_DES], "GaloSongs\\Opening.wav");
    strcpy(song_path[CONTINUAR], "GaloSongs\\continuar.wav");
    strcpy(song_path[MAP1], "GaloSongs\\The Bank.wav");
    strcpy(song_path[MAP2], "GaloSongs\\The Living Forest.wav");
    strcpy(song_path[MAP3], "GaloSongs\\The rooftop.wav");
    strcpy(song_path[MAP4], "GaloSongs\\The Subway.wav");
    strcpy(song_path[MAP5], "GaloSongs\\The Wastelands.wav");
    strcpy(song_path[CREDITOS], "GaloSongs\\creditos.wav");
}

int song_is_enable;

void enable_songs()
{
    song_is_enable = 1;
}

void disable_songs()
{
    pause_song();
    song_is_enable = 0;
}

int __song_is_enable()
{
    return song_is_enable;
}

void play_song(songs_ID som)
{
    if (__song_is_enable())
        PlaySound(TEXT(song_path[som]), NULL, SND_ASYNC);
}

void loop_song(songs_ID som)
{
    if (__song_is_enable())
    {
        PlaySound(TEXT(song_path[som]), NULL, SND_LOOP | SND_ASYNC);
    }
}

void pause_song()
{
    PlaySound(NULL, NULL, 0);
}

/// MADE IN BY "THE  BEST ROOSTER BRAZIL"

// PROPS TO EQUIPE LABIRINTO_CEREBRAL 2020.2
// USE COM SABEDORIA

#endif // __SONGS_H
