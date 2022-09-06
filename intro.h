#ifndef INTROS_H_INCLUDED
#define INTROS_H_INCLUDED

#include <conio2.h>

void abertura_mortalkongalo()
{
    char aviso[120] = "If you wanna skip the opening just press any key";
    caixaDeTexto(&aviso, LARGURA / 2 - 10, ALTURA / 2 - 4, 25, 12);
    confirmInput();

    play_song(LATITUDE_DES);
    initScreen();

    int posx = -22;
    int posy = 0;

    int tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;

    // HERBERT RICHERS
    int xlateral1 = 3, xlateral2 = 21, altura = 1;
    for (int i = 0; i < 50; i++)
    {
        if (kbhit())
        {
            return;
        }
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', DARKGRAY);
        drawSpriteBufferColorMaster(1, 1, &herbert, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(xlateral1, altura - i, &herbert_lateral, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(xlateral2, altura - i, &herbert_lateral, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(50);
    }

    if (kbhit())
    {
        return;
    }

    // SHELBY LTDA
    int pos_sx;
    for (int i = -80; i < 80; i++)
    {
        if (kbhit())
        {
            return;
        }

        pos_sx = (i * i) / 80;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', DARKGRAY);
        drawSpriteBufferColorMaster(1, 1, &linha, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(pos_sx, 1, &shelby, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(-pos_sx, 1, &ltda, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(45);
    }

    for (int i = -80; i < -60; i += 2)
    {
        if (kbhit())
        {
            return;
        }

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', DARKGRAY);
        drawSpriteBufferColorMaster(1, 1, &linha, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(i, 1, &glitch_white, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        Sleep(20);
        drawScreen();
    }
    textbackground(BLACK);
    clrscr();

    if (kbhit())
    {
        return;
    }

    // experimento mal sucedido
    drawSpriteColorScl(1, 1, &experimento, 1, 1);
    Sleep(1000);
    clrscr();
    if (kbhit())
    {
        return;
    }
    drawSpriteColorScl(1, 1, &sucedido, 1, 1);
    Sleep(1500);
    clrscr();
    if (kbhit())
    {
        return;
    }

    // galos selvagens
    drawSpriteColorScl(1, 1, &galus, 1, 1);
    Sleep(2000);
    clrscr();
    if (kbhit())
    {
        return;
    }

    // elemento radioativo
    drawSpriteColorScl(1, 1, &elemento, 1, 1);
    Sleep(1500);
    clrscr();
    if (kbhit())
    {
        return;
    }

    textbackground(DARKGRAY);
    clrscr();
    for (int i = 0; i < 6; i++)
    {
        drawSpriteColorScl(33, 1, &atomic[i], 1, 1);
        Sleep(400);
        clrscr();
        if (kbhit())
        {
            return;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        drawSpriteColorScl(-40, 1, &radioativo, 2, 1);
        drawSpriteColorScl(-40, 1, &pulsos[i], 2, 1);
        Sleep(500);
        clrscr();
        if (kbhit())
        {
            return;
        }
    }
    textbackground(BLACK);
    clrscr();

    // causou mutações
    drawSpriteColorScl(1, 1, &mutacoes, 1, 1);
    Sleep(2500);
    clrscr();
    if (kbhit())
    {
        return;
    }

    // gerou monstros
    drawSpriteColorScl(1, 1, &gerou, 1, 1);
    Sleep(700);
    clrscr();
    if (kbhit())
    {
        return;
    }

    // galos esquerda direira
    posx = -22;
    posy = 5;

    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;

    for (int i = 0; i < 100; i++)
    {
        if (kbhit())
        {
            return;
        }

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 5; j++)
        {
            drawSpriteMonoColorBufferMaster(posx + i - tam * j, posy, &galoSprites[j][0], 2, 1, 0, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(50);

        drawScreen();
    }

    // dois galos de frente
    for (int i = 0; i < 2; i++)
    {
        if (kbhit())
        {
            return;
        }

        int galo = 11;
        int posicao = -5;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(posicao, 2, &galoSprites[galo][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posicao + 5 + tam, 2, &galoSprites[galo + 1][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(250);
        clearScreen();
        clrscr();
        Sleep(250);
    }

    // o problema disso
    drawSpriteColorScl(1, 1, &problema, 1, 1);
    Sleep(1000);
    clrscr();

    Sleep(500);

    // dois galos de frente
    for (int i = 0; i < 2; i++)
    {
        if (kbhit())
        {
            return;
        }
        int galo = 11;
        int posicao = -5;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(posicao, 2, &galoSprites[galo][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posicao + 5 + tam, 2, &galoSprites[galo + 1][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(250);
        clearScreen();
        clrscr();
        Sleep(250);
    }

    // ocorreu no brasil
    drawSpriteColorScl(1, 1, &ocorreu, 1, 1);
    Sleep(350);
    clrscr();
    if (kbhit())
    {
        return;
    }
    drawSpriteColorScl(1, 1, &no, 1, 1);
    Sleep(200);
    clrscr();
    if (kbhit())
    {
        return;
    }
    drawSpriteColorScl(1, 1, &brasil, 1, 1);
    Sleep(350);
    clrscr();
    if (kbhit())
    {
        return;
    }

    // dois galos de frente
    for (int i = 0; i < 2; i++)
    {
        int galo = 11;
        int posicao = -5;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(posicao, 2, &galoSprites[galo][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posicao + 5 + tam, 2, &galoSprites[galo + 1][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(250);
        clearScreen();
        clrscr();
        Sleep(250);
        if (kbhit())
        {
            return;
        }
    }
    if (kbhit())
    {
        return;
    }

    Sleep(3000);
    if (kbhit())
    {
        return;
    }

    // galos esquerda direira
    posx = -22;
    posy = 0;

    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;
    for (int i = 0; i < 150; i++)
    {
        if (kbhit())
        {
            return;
        }
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 5; j++)
        {

            if (kbhit())
            {
                return;
            }

            drawSpriteBufferColorMaster(posx + i - tam * j, posy, &galoSprites[j][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(29);
        drawScreen();
    }

    if (kbhit())
    {
        return;
    }

    // dois galos viram
    for (int i = 0; i < 2; i++)
    {
        if (kbhit())
        {
            return;
        }

        int galo = 11;
        int posicao = -5;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(posicao, 2, &galoSprites[galo][i], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posicao + 5 + tam, 2, &galoSprites[galo + 1][i], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(250);
        clearScreen();
        clrscr();
        Sleep(250);
    }

    // dois palá dois pacá direita esquerda
    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;
    int movimento = 0;
    int posicionamentox = -22;
    int posicionamentoy = 0;
    for (int i = 0; i < 150; i++)
    {
        if (kbhit())
        {
            return;
        }
        posicionamentox += (i % 6) - 2;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 2; j++)
        {
            drawSpriteBufferColorMaster(-posicionamentox - movimento + tam * j, posy, &galoSprites[j][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(50);
        drawScreen();
    }

    // dois galos viram
    for (int i = 0; i < 2; i++)
    {
        if (kbhit())
        {
            return;
        }
        int galo = 11;
        int posicao = -5;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(posicao, 2, &galoSprites[galo][i], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posicao + 5 + tam, 2, &galoSprites[galo + 1][i], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(250);
        clearScreen();
        clrscr();
        Sleep(250);
    }

    // dois palá dois pacá direita esquerda
    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;
    movimento = 0;
    posicionamentox = -22;
    posicionamentoy = 0;
    for (int i = 0; i < 100; i++)
    {
        if (kbhit())
        {
            return;
        }
        posicionamentox += (i % 6) - 2;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 2; j++)
        {
            drawSpriteBufferColorMaster(-posicionamentox - movimento + tam * j, posy, &galoSprites[j][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(50);
        drawScreen();
    }

    // dois palá dois pacá direita esquerda
    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;
    movimento = 0;
    posicionamentox = -22;
    posicionamentoy = 0;
    for (int i = 0; i < 100; i++)
    {
        if (kbhit())
        {
            return;
        }
        posicionamentox += (i % 6) - 2;
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 2; j++)
        {
            drawSpriteBufferColorMaster(-posicionamentox - movimento + tam * j, posy, &galoSprites[j][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(50);
        drawScreen();
    }

    // galos direita esquerda
    posx = -22;
    posy = 0;
    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;
    for (int i = 0; i < 150; i++)
    {
        if (kbhit())
        {
            return;
        }
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 24; j++)
        {
            drawSpriteBufferColorMaster(-posx - i + tam * j, posy, &galoSprites[j][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(25);
        drawScreen();
    }

    // close nos galos
    for (int i = 0; i < 3; i++)
    {
        if (kbhit())
        {
            return;
        }
        int lado = i % 2;
        int galo = 11;
        int posicao = -5;
        int temp = 1000;

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(posicao, 2, &galoSprites[galo][lado], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posicao + 5 + tam, 2, &galoSprites[galo + 1][lado], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(temp);
        clearScreen();
        clrscr();
    }

    // galos esquerda direira
    posx = -22;
    posy = 0;
    tam = galoSprites[GALINHA_PINTADINHA][0].width * 2;
    for (int i = 0; i < 150; i++)
    {
        if (kbhit())
        {
            return;
        }
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        for (int j = 0; j < 5; j++)
        {

            drawSpriteBufferColorMaster(posx + i - tam * j, posy, &galoSprites[j][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        }
        Sleep(29);
        drawScreen();
    }
    if (kbhit())
    {
        return;
    }
    // logo do jogo
    textbackground(WHITE);
    clrscr();
    int xlogo = (LARGURA / 2) - (mortalKomgalo.width);
    int ylogo = 1;
    drawSpriteColorScl(xlogo, ylogo, &mortalKomgalo, 2, 1);
    Sleep(4500);
    textbackground(BLACK);
    clrscr();

    pause_song();
}

#endif 
