#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <MMSystem.h>
#include <conio2.h>
#include <locale.h>
#include <string.h>

int one_player_mode;

#include <math.h>

#define PI 3.1415926535

#define ALTURA 24
#define LARGURA 80

#include "desenhos.h"

#include "screen_draw.h"

#include "sprite_creator.h"
#include "som.h"

#define N_DE_MAPAS 10

struct Sprite galoSniper;
struct Sprite galoAquatico;
struct Sprite galoSprites[28][2];
struct Sprite sprFatality;
struct Sprite fundos[N_DE_MAPAS];
struct Sprite sprSetas[5];

struct Sprite alfaNumSprites[36];

struct Sprite bulletBill;
struct Sprite galoBazooka;
struct Sprite explosion;
struct Sprite entrada;
struct Sprite sprFinish;
struct Sprite flawless;
struct Sprite sombra;
struct Sprite jordan;
struct Sprite galoColumbine;
struct Sprite atkSprites[7];
struct Sprite atkSpritesSmall[1];

struct Sprite herbert;
struct Sprite herbert_lateral;
struct Sprite shelby;
struct Sprite linha;
struct Sprite ltda;
struct Sprite brasil;
struct Sprite elemento;
struct Sprite experimento;
struct Sprite galus;
struct Sprite gerou;
struct Sprite mutacoes;
struct Sprite no;
struct Sprite ocorreu;
struct Sprite problema;
struct Sprite sucedido;
struct Sprite glitch_black;
struct Sprite glitch_white;
struct Sprite atomic[6];
struct Sprite pulsos[6];
struct Sprite radioativo;

struct Sprite slashEffect[8];
struct Sprite sprWaveEffect;
struct Sprite sprGun;

struct Sprite sprRound;
struct Sprite numbers[3];
struct Sprite sprfight;

struct Sprite Blood;
struct Sprite SongNote;

struct Sprite sprNulo;

struct Sprite mortalKomgalo;
struct Sprite telaEmOleo;
struct Sprite menu;
struct Sprite pressenter;

struct Sprite light;

int fundoDefinido;

float sinAprox[360];

void initSinAprox()
{
    for (int i = 0; i < 360; i++)
    {
        sinAprox[i] = sin(2 * PI * ((float)i / 360));
    }
}

struct ConfiguracoesBatalha
{
    int fundo;
    int hasBorder;
    int borderColor;
};

struct ConfiguracoesBatalha configBatalha;

char confirmInput();

#include "struct_galos.h"
#include "animacoes.h"
#include "batalhaDeGalo.h"
#include "intro.h"

//Tela inicial da the best rooster Brazil
void tela_inicial()
{
    int cont = 0;
    //Enquando não tiver uma tecla pressionada, faça isso
    while (!(kbhit()))
    {
        drawSpriteBufferColorMaster(1, 1, &telaEmOleo, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(LARGURA / 2 - pressenter.width / 2, ALTURA - 6, &pressenter, 1, 1, 1, cont, 1, 1, LARGURA, ALTURA);
        cont++;

        if (cont == 15)
        {
            cont = 0;
        }
        Sleep(200);
        drawScreen();
    }
    getch();
}

int main()
{

    system("MODE con cols=80 lines=24");
    system("chcp 65001");
    system("title The best rooster Brazil");
    srand(time(NULL));

    one_player_mode = 1;

    //Abre arquivos, carrega sprites, sons, galos e tudo
    iniciar_ataques();
    iniciar_status();
    iniciarSprites();
    iniciar_sons();
    enable_songs();
    initScreen();
    initSinAprox();

    abertura_mortalkongalo();
    getch();

    play_song(HINO);

    tela_inicial();

    // VARIAVEIS PARA A BATALHA
    configBatalha.fundo = 0;
    configBatalha.hasBorder = 0;
    configBatalha.borderColor = 15;

    while (1)
    {

        // VARIAVEIS PARA A BATALHA
        configBatalha.fundo = 0;
        configBatalha.hasBorder = 0;
        configBatalha.borderColor = 15;

        if (!menu_inicial())
        {
            return 0;
        }

        if (game_mode() == -1)
        {
            continue;
        }

        clrscr();

        desenharBorda();

        loop_song(MK_THEME);

        textcolor(WHITE);
        textbackground(LIGHTGRAY);

        int fundo_escolhido[2];

        struct galo_status galo1 = escolher_galo();
        fundo_escolhido[0] = selecionar_fundo();

        struct galo_status galo2;

        if (one_player_mode)
        {

            galo2 = galos[rand() % 28];
            fundo_escolhido[1] = fundo_escolhido[0];
        }
        else
        {

            galo2 = escolher_galo();
            fundo_escolhido[1] = selecionar_fundo();
        }

        // Essas variaveis v�o guardar os galos para reiniciar seus valores na rematch
        struct galo_status __guardarGalo1 = galo1;
        struct galo_status __guardarGalo2 = galo2;

        placar1 = 0;
        placar2 = 0;

        fundoDefinido = fundo_escolhido[rand() % 2];

        clrscr();
        char fundinho[200] = "And the background is gonna be ...";
        Sleep(500);
        caixaDeTexto(&fundinho,LARGURA/2,ALTURA/2,35,10);

        drawSpriteColorScl(5, 3, &fundos[fundoDefinido], 1, 1);

        Sleep(5000);

        do
        {
            galo1 = __guardarGalo1;
            galo2 = __guardarGalo2;
            configBatalha.fundo = fundoDefinido;

            pause_song();

            int result = batalha(galo1, galo2);
            system("cls");
            switch (result)
            {
            case 0:
                printf("empate");
                break;
            case 1:
                placar1++;
                fatality(1, galo1, galo2);
                break;
            case 2:
                placar2++;
                fatality(2, galo2, galo1);
                break;
            }
        } while (rematch());
    }
}

void iniciarSprites()
{
    for (int i = 0; i < 28; i++)
    {
        for (int j = 0; j < 2; j++)
        {

            struct Sprite _spr;
            galoSprites[i][j] = _spr;

            char path[26] = "GaloSprites\\galo000_0.txt";

            if (i < 10)
            {

                path[18] = (char)(48 + i);
            }
            else if (i < 100)
            {

                path[18] = (char)(48 + (i % 10));
                path[17] = (char)(48 + (int)floor(i / 10));
            }
            else if (i < 1000)
            {

                path[18] = (char)(48 + (i % 10));
                path[17] = (char)(48 + (((int)floor(i / 10)) % 10));
                path[16] = (char)(48 + ((int)floor(i / 100)));
            }

            path[20] = (char)(48 + j);

            spriteCreateColor(path, &galoSprites[i][j]);
        }
    }

    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 1; j++)
        {

            struct Sprite _spr;
            atkSprites[i] = _spr;

            char path[31] = "AttackSprites\\attack000_0.txt";

            if (i < 10)
            {

                path[22] = (char)(48 + i);
            }
            else if (i < 100)
            {

                path[22] = (char)(48 + (i % 10));
                path[21] = (char)(48 + (int)floor(i / 10));
            }
            else if (i < 1000)
            {

                path[22] = (char)(48 + (i % 10));
                path[21] = (char)(48 + (((int)floor(i / 10)) % 10));
                path[20] = (char)(48 + ((int)floor(i / 100)));
            }

            path[24] = (char)(48 + j);

            spriteCreateColor(path, &atkSprites[i]);
        }
    }

    for (int i = 0; i < 36; i++)
    {
        for (int j = 0; j < 1; j++)
        {

            struct Sprite _spr;
            alfaNumSprites[i] = _spr;

            char path[34] = "AlfabetoSprites\\alfaNum000_0.txt";

            if (i < 10)
            {

                path[25] = (char)(48 + i);
            }
            else if (i < 100)
            {

                path[25] = (char)(48 + (i % 10));
                path[24] = (char)(48 + (int)floor(i / 10));
            }
            else if (i < 1000)
            {

                path[25] = (char)(48 + (i % 10));
                path[24] = (char)(48 + (((int)floor(i / 10)) % 10));
                path[23] = (char)(48 + ((int)floor(i / 100)));
            }

            path[27] = (char)(48 + j);

            spriteCreateColor(path, &alfaNumSprites[i]);
        }
    }

    spriteCreateColor("AttackSprites\\atkOvo.txt", &atkSpritesSmall[0]);

    spriteCreateColor("AttackSprites\\wave.txt", &sprWaveEffect);
    spriteCreateColor("AttackSprites\\gun.txt", &sprGun);

    spriteCreateColor("AttackSprites\\slash1.txt", &slashEffect[0]);
    spriteCreateColor("AttackSprites\\slash2.txt", &slashEffect[1]);
    spriteCreateColor("AttackSprites\\slash3.txt", &slashEffect[2]);
    spriteCreateColor("AttackSprites\\slash4.txt", &slashEffect[3]);
    spriteCreateColor("AttackSprites\\slash5.txt", &slashEffect[4]);
    spriteCreateColor("AttackSprites\\slash6.txt", &slashEffect[5]);
    spriteCreateColor("AttackSprites\\slash7.txt", &slashEffect[6]);
    spriteCreateColor("AttackSprites\\slash8.txt", &slashEffect[7]);

    spriteCreateColor("Cenarios\\background0.txt", &fundos[0]);
    spriteCreateColor("Cenarios\\background1.txt", &fundos[1]);
    spriteCreateColor("Cenarios\\background2.txt", &fundos[2]);
    spriteCreateColor("Cenarios\\background3.txt", &fundos[3]);
    spriteCreateColor("Cenarios\\background4.txt", &fundos[4]);
    spriteCreateColor("Cenarios\\background5.txt", &fundos[5]);
    spriteCreateColor("Cenarios\\background6.txt", &fundos[6]);
    spriteCreateColor("Cenarios\\background7.txt", &fundos[7]);
    spriteCreateColor("Cenarios\\background8.txt", &fundos[8]);
    spriteCreateColor("Cenarios\\background9.txt", &fundos[9]);

    spriteCreateColor("Cenarios\\mortalkomgalo000_0.txt", &mortalKomgalo);
    spriteCreateColor("Cenarios\\tela_em_oleo000_0.txt", &telaEmOleo);
    spriteCreateColor("Cenarios\\menu000_0.txt", &menu);

    spriteCreateColor("Animacoes\\blood.txt", &Blood);
    spriteCreateColor("Animacoes\\songNote.txt", &SongNote);

    spriteCreateColor("Animacoes\\fatality.txt", &sprFatality);
    spriteCreateColor("Animacoes\\FinishHim.txt", &sprFinish);

    spriteCreateColor("Animacoes\\setaUp.txt", &sprSetas[0]);
    spriteCreateColor("Animacoes\\setaDown.txt", &sprSetas[1]);
    spriteCreateColor("Animacoes\\setaLeft.txt", &sprSetas[2]);
    spriteCreateColor("Animacoes\\setaRight.txt", &sprSetas[3]);
    spriteCreateColor("Animacoes\\error.txt", &sprSetas[4]);

    spriteCreateColor("GaloSprites\\explosion.txt", &explosion);
    spriteCreateColor("GaloSprites\\galoBazooka.txt", &galoBazooka);
    spriteCreateColor("GaloSprites\\bulletBill.txt", &bulletBill);
    spriteCreateColor("Animacoes\\entradaFinish.txt", &entrada);
    spriteCreateColor("Animacoes\\Flawless.txt", &flawless);
    spriteCreateColor("Animacoes\\sombra.txt", &sombra);
    spriteCreateColor("Animacoes\\jordan.txt", &jordan);
    spriteCreateColor("Animacoes\\galo_columbine.txt", &galoColumbine);

    spriteCreateColor("Animacoes\\1.txt", &numbers[0]);
    spriteCreateColor("Animacoes\\2.txt", &numbers[1]);
    spriteCreateColor("Animacoes\\3.txt", &numbers[2]);

    spriteCreateColor("Animacoes\\fight.txt", &sprfight);
    spriteCreateColor("Animacoes\\round.txt", &sprRound);

    spriteCreateColor("Animacoes\\herbert.txt", &herbert);
    spriteCreateColor("Animacoes\\herbert_lateral.txt", &herbert_lateral);
    spriteCreateColor("Animacoes\\shelby.txt", &shelby);
    spriteCreateColor("Animacoes\\linha.txt", &linha);
    spriteCreateColor("Animacoes\\ltda.txt", &ltda);
    spriteCreateColor("Animacoes\\brasil.txt", &brasil);
    spriteCreateColor("Animacoes\\elemento.txt", &elemento);
    spriteCreateColor("Animacoes\\experimento.txt", &experimento);
    spriteCreateColor("Animacoes\\galus.txt", &galus);
    spriteCreateColor("Animacoes\\gerou.txt", &gerou);
    spriteCreateColor("Animacoes\\mutacoes.txt", &mutacoes);
    spriteCreateColor("Animacoes\\no.txt", &no);
    spriteCreateColor("Animacoes\\ocorreu.txt", &ocorreu);
    spriteCreateColor("Animacoes\\problema.txt", &problema);
    spriteCreateColor("Animacoes\\sucedido.txt", &sucedido);
    spriteCreateColor("Animacoes\\glitch_white.txt", &glitch_white);
    spriteCreateColor("Animacoes\\glitch_black.txt", &glitch_black);
    spriteCreateColor("Animacoes\\atomic0.txt", &atomic[0]);
    spriteCreateColor("Animacoes\\atomic1.txt", &atomic[1]);
    spriteCreateColor("Animacoes\\atomic2.txt", &atomic[2]);
    spriteCreateColor("Animacoes\\atomic3.txt", &atomic[3]);
    spriteCreateColor("Animacoes\\atomic4.txt", &atomic[4]);
    spriteCreateColor("Animacoes\\atomic5.txt", &atomic[5]);
    spriteCreateColor("Animacoes\\pulsos0.txt", &pulsos[0]);
    spriteCreateColor("Animacoes\\pulsos1.txt", &pulsos[1]);
    spriteCreateColor("Animacoes\\pulsos2.txt", &pulsos[2]);
    spriteCreateColor("Animacoes\\pulsos3.txt", &pulsos[3]);
    spriteCreateColor("Animacoes\\pulsos4.txt", &pulsos[4]);
    spriteCreateColor("Animacoes\\radioativo.txt", &radioativo);
    spriteCreateColor("Animacoes\\pressEnter.txt", &pressenter);
    spriteCreateColor("Animacoes\\lightning.txt", &light);
    spriteCreateColor("spriteNulo.txt", &sprNulo);
}

//Retorna 0 para sair
int menu_inicial()
{
    while (1)
    {
        textbackground(BLACK);
        clrscr();
        drawSpriteColor(1, 1, &menu);
        int x = TAMANHO_COLUNAS / 2 - 7;
        int y = TAMANHO_LINHAS / 2 - 4;
        textcolor(WHITE);

        gotoxy(x, y);
        printf("Start");
        gotoxy(x, y + 2);
        printf("Walktrought");
        gotoxy(x, y + 4);
        printf("Options");
        gotoxy(x, y + 6);
        printf("Exit");

        char op;
        int opcao = 1;
        int tam = 15;
        y--;

        quadrado_sem_espacos(tam, 3, x - 1, y);

        do
        {

            op = getch();

            if (op == 'W' || op == 'w' || op == KEY_UP)
            {
                if (opcao > 1)
                {
                    opcao--;
                    textcolor(BLACK);
                    //Apaga o quadrado
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    y -= 2;
                    textcolor(WHITE);
                    //Desenha um quadrado ao redor da palavra
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == 'S' || op == 's' || op == KEY_DOWN)
            {
                if (opcao < 4)
                {
                    opcao++;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    textcolor(WHITE);
                    y += 2;
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == KEY_ENTER)
            {
                break;
            }

        } while (1);

        if (opcao == 1)
        {
            return 1;
        }
        else if (opcao == 2)
        {
            historia();
        }
        else if (opcao == 3)
        {
            menu_de_opcoes();
            drawSpriteColor(1, 1, &menu);
        }
        else
        {
            return 0;
        }
    }
}

void menu_de_opcoes()
{

    while (1)
    {
        drawSpriteColor(1, 1, &menu);
        int x = TAMANHO_COLUNAS / 2 - 7;
        int y = TAMANHO_LINHAS / 2 - 4;

        textcolor(WHITE);
        gotoxy(x, y);

        if (__song_is_enable())
        {
            printf("Sound: On");
        }
        else
        {
            printf("Sound: Off");
        }

        gotoxy(x, y + 2);
        printf("Help");
        gotoxy(x, y + 4);
        printf("Credits");
        gotoxy(x, y + 6);
        printf("Back");

        y--;

        char op;
        int opcao = 1;
        int tam = 18;
        //Mesmo esquema de quadrados
        quadrado_sem_espacos(tam, 3, x - 1, y);

        do
        {

            op = getch();

            if (op == 'W' || op == 'w' || op == KEY_UP)
            {
                if (opcao > 1)
                {
                    opcao--;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    y -= 2;
                    textcolor(WHITE);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == 'S' || op == 's' || op == KEY_DOWN)
            {
                if (opcao < 4)
                {
                    opcao++;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    textcolor(WHITE);
                    y += 2;
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == KEY_ENTER)
            {
                break;
            }

        } while (1);

        if (opcao == 1)
        {
            if (__song_is_enable())
            {
                disable_songs();
            }
            else
            {
                enable_songs();
            }
        }
        else if (opcao == 2)
        {
            char textin[300] = "Use W - A - S - D to move things and select, press enter to confirm  and ESC to come back, have a wonderfull gameplay my friend :) ";
            caixaDeTexto(&textin, 19, 3, LARGURA - 2 - 29, 10);
            confirmInput();
        }
        else if (opcao == 3)
        {
            clrscr();
            desenhar_quadrado(LARGURA, ALTURA, 1, 1);
            int countext = 20;
            int y = 3;
            play_song(CREDITOS);
            char textin[1500] = "CAST\nGalo de Tenis		VENILSON		\nGalo de Calca		LUCAS		\nGalo Topete 		WALTER		\nGalo Aquatico		HERMES		\nGalo Twitter 		ELON MUSK		\nGalo Emo		NELSON		\nGalo Militar		ROCKY		\nGalo Antonio 		INACIO ANTONIO		\nGalo Slime		QUEIROZ		\nGalo Mandrake 		UMENOR DE SP		\nGalo sniper		EDSON		\nGalo magico		RONALDINHO		\nGalo Pirata		JACK SPEAROW		\nGalinha Pintadinha	ANA CLAUDIA			\nGalo Brocador		KAUA BROCADOR		\nGalo Minecraft		STEVE		\nGalo faqueiro		TRAMONTINA		\nPica Pau		WOODPECKER		\nPiu Piu		LOONEY TUNES		\nLouro Jose		TOM VEIGA		\nJoao Frango		GRACIAS		\nGalo Whatsapp		HENRIQUE		\nUrubu do Pix		AGIOTINHA		\nGalo Fenomeno		RONALDO		\nGalo da Sadia		LEQUETREQUE		\nGalo Careca		ALOPECIO		\nGalo Carijo		CARIJO		\nGalo da Peste		BULBONICO		\n\n\n\n\n\n\n				\n	  EFEITOS SONOROS			\n   Marcos Vinicius Mota Menezes				\n				\n	 GERENTE AUDIO VISUAL			\n   Kaua de Oliveira Santos Menezes				\n				\n	GERENTE DE MIDIAS SOCIAS			\n   Jose Adryel de Almeida Melo				\n				\n	     ROTEIRISTA			\n   Marcos Vinicius Santana Oliveira				\n				\n	    DIRETOR GERAL			\n   Walter Henrique dos Santos Anjos				\n				\n	    UMA CRIACAO			\n	    Shelby.LTDA			\n				\n    DIGA SIM A PL 1037/2020				\n\nRedes sociais\n\nInstagram: @thebestroosterbrazil\n\nTwitter: https://www.twitter.com/BestRooster\0";
            for (int i = 0; i < 1500; i++)
            {

                if (y > 20)
                {
                    y = 3;
                    clrscr();
                }

                if (textin[i] == '\0')
                {
                    break;
                }
                else if (textin[i] == '\n')
                {
                    y++;
                    countext = 20;
                    Sleep(50);
                }
                else
                {
                    gotoxy(countext, y);
                    printf("%c", textin[i]);
                    Sleep(1);
                    countext++;
                }
            }
            confirmInput();
            pause_song();
            play_song(HINO);
        }

        else
        {
            return;
        }
    }

    return;
}

int selecionar_fundo()
{

    char mapas[10][50];
    strcpy(mapas[0], "Galo's palace");
    strcpy(mapas[1], "Woodpecker house's");
    strcpy(mapas[2], "Solid Yellow");
    strcpy(mapas[3], "Solid Blue");
    strcpy(mapas[4], "Solid Gray");
    strcpy(mapas[5], "Carira");
    strcpy(mapas[6], "Dubai");
    strcpy(mapas[7], "I LOVE Itabaiana");
    strcpy(mapas[8], "Petrobras Little Boat");
    strcpy(mapas[9], "Windows Xp");

    int fundo = 0;

    while (1)
    {

        textbackground(BLACK);
        clrscr();

        drawSpriteColorScl(5, 3, &fundos[fundo], 0.9, 0.9);
        textcolor(WHITE);
        gotoxy(TAMANHO_COLUNAS / 2 - (strlen("SELECT MAP\0") / 2), 1);
        printf("SELECT MAP");
        gotoxy(TAMANHO_COLUNAS / 2 - (strlen(mapas[fundo]) / 2), 22);
        printf("%s", mapas[fundo]);

        gotoxy(15, 24);
        printf("[S] Next  [A] Previous  [ENTER] Select [R] Random");

        while (1)
        {
            char op = getch();
            if (op == 'a' || op == 'A' || op == KEY_LEFT)
            {
                if (fundo == 0)
                {
                    fundo = N_DE_MAPAS - 1;
                }
                else
                {
                    fundo--;
                }
                break;
            }
            else if (op == 'd' || op == 'D' || op == KEY_RIGHT)
            {
                if (fundo == N_DE_MAPAS - 1)
                {
                    fundo = 0;
                }
                else
                {
                    fundo++;
                }
                break;
            }
            else if (op == KEY_ENTER)
            {
                return fundo;
            }
            //Escolhe um mapa random
            else if (op == 'R' || op == 'r')
            {
                return rand() % N_DE_MAPAS;
            }
        }
    }
}

//Retorna o game mode
int game_mode()
{

    while (1)
    {
        int opcao = 1;
        textbackground(BLACK);
        clrscr();
        drawSpriteColor(1, 1, &menu);

        int x = TAMANHO_COLUNAS / 2 - 7;
        int y = TAMANHO_LINHAS / 2 - 4;
        textcolor(WHITE);

        gotoxy(x, y);
        printf("Singleplayer");
        gotoxy(x, y + 2);
        printf("Multiplayer");
        gotoxy(x, y + 4);
        printf("Training mode");
        gotoxy(x, y + 6);
        printf("Back");
        char op;

        int tam = 15;
        y--;
        quadrado_sem_espacos(tam, 3, x - 1, y);

        do
        {

            op = getch();

            if (op == 'W' || op == 'w' || op == KEY_UP)
            {
                if (opcao > 1)
                {
                    opcao--;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    y -= 2;
                    textcolor(WHITE);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == 'S' || op == 's' || op == KEY_DOWN)
            {
                if (opcao < 4)
                {
                    opcao++;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    textcolor(WHITE);
                    y += 2;
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == KEY_ENTER)
            {
                break;
            }

        } while (1);

        if (opcao == 1)
        {
            one_player_mode = 1;
            return 1;
        }
        else if (opcao == 2)
        {
            one_player_mode = 0;
            return 1;
        }
        else if (opcao == 4)
        {
            return -1;
        }
        else if (opcao == 3)
        {
            training_mode();
        }
    }
}

void historia()
{
    char textin[3000] = "The origin of the cockfight dates back to distant periods of history, originating in ancient Greece where fights between birds served to stimulate the fighting spirit of warriors, and with the advancement of the Greek empire this practice was spreading throughout western Europe. including where later on would be Portugal, which also joined the practice with its navigators encouraging them in their travels, and in one of them they arrived in Brazil, bringing with them all European culture during colonization. For a long time, cockfights were restricted to nobles and mill owners, and over time it became popular among the lower classes, but during the Getulist era in Brazil the sport began to be reprimanded and in 1961 it was banned in general by Janio Quadros, and from here on, the fighting roosters began to be on the margins of our society, being done in hiding with small championships organized by the CBG (Brazilian Confederation of Roosters) and being condemned by part of the population. Normally, 5 regional championships are held and a national one that includes the best from each region. But this year, a mad scientist who studies roosters created 14 genetically modified roosters and started making attacks across the territory, in order to end all this tyranny, CBG challenged the mad scientist in a competition, named by the press as The Best Rooster Brazil , who will decide who has the best rooster in Brazil, the CBG with its natural roosters or this scientist with the monster roosters. The teams are already assembled and there are 14 of the best roosters ever seen. The normal team: TENNIS ROOSTER, PANTS ROOSTER AND... The Monster team: PEST ROOSTER, SLIME ROOSTER AND... time to fight and choose the direction of this competition after all who will be THE BEST ROOSTER BRAZIL!";
    caixaDeTexto(&textin, 19, 3, LARGURA - 2 - 29, 10);
    confirmInput();
}

int rematch()
{
    while (1)
    {
        int opcao = 1;
        textbackground(BLACK);
        clrscr();
        drawSpriteColor(1, 1, &menu);

        int x = TAMANHO_COLUNAS / 2 - 7;
        int y = TAMANHO_LINHAS / 2 - 4;
        textcolor(WHITE);

        gotoxy(x, y);
        printf("Rematch");
        gotoxy(x, y + 2);
        printf("Back to menu");
        char op;

        int tam = 15;
        y--;
        quadrado_sem_espacos(tam, 3, x - 1, y);

        do
        {

            op = getch();

            if (op == 'W' || op == 'w' || op == KEY_UP)
            {
                if (opcao > 1)
                {
                    opcao--;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    y -= 2;
                    textcolor(WHITE);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == 'S' || op == 's' || op == KEY_DOWN)
            {
                if (opcao < 2)
                {
                    opcao++;
                    textcolor(BLACK);
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                    textcolor(WHITE);
                    y += 2;
                    quadrado_sem_espacos(tam, 3, x - 1, y);
                }
            }
            else if (op == KEY_ENTER)
            {
                break;
            }

        } while (1);

        if (opcao == 1)
        {
            is_rematch = 1;
            return 1;
        }
        if (opcao == 2)
        {
            is_rematch = 0;
            return 0;
        }
    }
}

void training_mode()
{

    double lvl = 1;
    int acertos = 0;
    while (minigame(lvl) == 1)
    {
        //Aumenta a dificuldade toda hr
        lvl += 0.4;
        acertos++;
    }
    textcolor(WHITE);
    gotoxy(10, 17);
    printf("Your score: %d", acertos);
    gotoxy(10, 19);
    system("pause");
}
