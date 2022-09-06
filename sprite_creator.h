#ifndef __SPRITE_H
#define __SPRITE_H

#include <stdio.h>

int width = 80;
int height = 24;

// STRUCT DO SPRITE
struct Sprite
{
    int width;
    int height;
    int hasColor;
    char *grid;
    int *color;
    int created;
};

// FUNCOES PARA INICIALIZACAO DE UMA STRUCT DE SPRITE
// RECEBE UMA STRING COM O CAMINHO DO SPRITE TEXTO
// E O ENDERECO DE UMA STRUCT DE SPRITE

// AS DUAS FUNCOES ALOCAM MEMORIA
// PORTANTO E RECOMENDAVEL CRIAR O SPRITE APENAS NO INICIO DO PROGRAMA
// EVITANDO VAZAMENTO DE MEMORIA

void spriteCreate(char *path, struct Sprite *spr);
void spriteCreateColor(char *path, struct Sprite *spr);

// FUNCOES QUE DESENHAM DIRETAMENTE NA TELA

// Lista de funções
void drawSprite(int x, int y, struct Sprite *spr);

void drawSpriteColor(int x, int y, struct Sprite *spr);

// Desenhar com escala
void drawSpriteScl(int x, int y, struct Sprite *spr, float xScale, float yScale);
void drawSpriteColorScl(int x, int y, struct Sprite *spr, float xScale, float yScale);

// DESENHAR ESCALA E BORDA
void drawSpriteSclBorder(int x, int y, struct Sprite *spr, float xScale, float yScale);
void drawSpriteColorSclBorder(int x, int y, struct Sprite *spr, float xScale, float yScale);

// DESENHAR COM APENAS UMA COR
void drawSpriteMonoColorScl(int x, int y, struct Sprite *spr, float xScale, float yScale, int color);
void drawSpriteMonoColorSclBorder(int x, int y, struct Sprite *spr, float xScale, float yScale, int color);

// FUNCAO COMPLETA COM TODAS AS OPCOES

// hasBorder DETERMINA A PRESENCA DE UMA BORDA AO REDOR DO SPRITE
// hasBorder = 1 COM BORDA              hasBorder = 0   SEM BORDA

// _borderColor DETERMINA A COR DA BORDA

// screenX1, screenX2, screenY1, screenY2 REPRESENTAM AS CORDENADAS DO ESPACO PARA DESENHAR O SPRITE
// COM ESSAS VARIAVEIS PODE-SE DELIMITAR UMA AREA ESPECIFICA NA QUAL O SPRITE FICARÁ VISIVEL
// PIXELS FORA DESSA AREA NAO SERAO DESENHADOS

void drawSpriteMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2);
void drawSpriteColorMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2);

// FUNCOES QUE DESENHAM NO ARRAY SCREEN

// ESSAS FUNCOES DESENHAM INDIRETAMENTE DENTRO DE UM ARRAY DA BIBLIOTECA SCREEN_DRAW
// PARA DESENHAR ESSE ARRAY E NECESSARIO USAR A FUNCAO drawScreen();
// TAMBEM RECOMENDA-SE USAR clearScreen(); ANTES DE UM TECHO DE CODIGO QUE IRA USAR ESSAS FUNCOES
void drawSpriteBufferMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2);
void drawSpriteBufferColorMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2);
void drawSpriteMonoColorBufferMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int internalColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2);

// Sprite Functions

// Sprite Functions
void drawSprite(int x, int y, struct Sprite *spr)
{

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    for (int i = 0; i < _hei; i++)
    {
        for (int j = 0; j < _wid; j++)
        {

            // POSICAO NO SPRITE
            int xx = j;
            int yy = i;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL CORRESPONDENTE
                int pixelIndex = xx + (_wid * yy);

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);

                    if (pixelChar == '@')
                    {
                        printf("█");
                    }
                    else if (pixelChar == 'a')
                    {
                        printf("▓");
                    }
                    else if (pixelChar == '}')
                    {
                        printf("▒");
                    }
                    else if (pixelChar == '?')
                    {
                        printf("░");
                    }
                    else if (pixelChar == '`')
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("%c", pixelChar);
                    }
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteColor(int x, int y, struct Sprite *spr)
{

    // USA FUNCAO ALTERNATIVA CASO O SPRITE NAO POSSUA COR
    if (!spr->hasColor)
    {
        return drawSprite(x, y, spr);
    }

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    for (int i = 0; i < _hei; i++)
    {
        for (int j = 0; j < _wid; j++)
        {

            // POSICAO NO SPRITE
            int xx = j;
            int yy = i;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = xx + (_wid * yy);

                char pixelChar = spr->grid[pixelIndex];
                int pixelColor = spr->color[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(pixelColor);

                    printf("█");
                }
            }
        }
    }
}

int indexCalc(int x, int y, int w, int h)
{
    if (x < 0)
    {
        return -1;
    }
    else if (x > w - 1)
    {
        return -1;
    }

    if (y < 0)
    {
        return -1;
    }
    else if (y > h - 1)
    {
        return -1;
    }

    return x + y * w;
}

int opaqueCheck(int x, int y, int w, int h, char *sp)
{
    int ind = indexCalc(x, y, w, h);
    if (ind != -1)
    {
        if (sp[ind] != ' ')
        {
            return 1;
        }
    }
    return 0;
}

int checkGrid(int x, int y, int w, int h, char *sp)
{
    int ind = indexCalc(x + 1, y, w, h);

    if (ind != -1)
    {
        if (sp[ind] != ' ')
        {
            return 1;
        }
    }

    ind = indexCalc(x - 1, y, w, h);
    if (ind != -1)
    {
        if (sp[ind] != ' ')
        {
            return 1;
        }
    }

    ind = indexCalc(x, y + 1, w, h);
    if (ind != -1)
    {
        if (sp[ind] != ' ')
        {
            return 1;
        }
    }

    ind = indexCalc(x, y - 1, w, h);
    if (ind != -1)
    {
        if (sp[ind] != ' ')
        {
            return 1;
        }
    }

    return 0;
}

// REFAZENDO DRAW SCALE

// Sprite Functions
void drawSpriteScl(int x, int y, struct Sprite *spr, float xScale, float yScale)
{
    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);

                    if (pixelChar == '@')
                    {
                        printf("█");
                    }
                    else if (pixelChar == 'a')
                    {
                        printf("▓");
                    }
                    else if (pixelChar == '}')
                    {
                        printf("▒");
                    }
                    else if (pixelChar == '?')
                    {
                        printf("░");
                    }
                    else if (pixelChar == '`')
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("%c", pixelChar);
                    }
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteColorScl(int x, int y, struct Sprite *spr, float xScale, float yScale)
{

    // USA FUNCAO ALTERNATIVA CASO O SPRITE NAO POSSUA COR
    if (!spr->hasColor)
    {
        return drawSpriteScl(x, y, spr, xScale, yScale);
    }

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];
                int pixelColor = spr->color[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(pixelColor);

                    printf("█");
                }
            }
        }
    }
}

void drawSpriteSclBorder(int x, int y, struct Sprite *spr, float xScale, float yScale)
{

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // ADQUIRINDO A COR ATUAL DO TEXTO
    struct text_info currentTextInfo;
    gettextinfo(&currentTextInfo);

    int currentColor = currentTextInfo.attribute;

    int drawBorder = 1;
    int borderColor = 15;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(currentColor);

                    if (pixelChar == '@')
                    {
                        printf("█");
                    }
                    else if (pixelChar == 'a')
                    {
                        printf("▓");
                    }
                    else if (pixelChar == '}')
                    {
                        printf("▒");
                    }
                    else if (pixelChar == '?')
                    {
                        printf("░");
                    }
                    else if (pixelChar == '`')
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("%c", pixelChar);
                    }

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        textcolor(borderColor);

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                gotoxy(pX, pY - ySign);
                                printf("█");
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                gotoxy(pX, pY + ySign);
                                printf("█");
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                gotoxy(pX - xSign, pY);
                                printf("█");
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                gotoxy(pX + xSign, pY);
                                printf("█");
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            textcolor(borderColor);
                            gotoxy(pX, pY);
                            printf("█");
                        }
                    }
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteColorSclBorder(int x, int y, struct Sprite *spr, float xScale, float yScale)
{

    if (!spr->hasColor)
    {
        return drawSpriteSclBorder(x, y, spr, xScale, yScale);
    }

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    int drawBorder = 1;
    int borderColor = 15;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];
                int pixelColor = spr->color[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(pixelColor);

                    printf("█");

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        textcolor(borderColor);

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                gotoxy(pX, pY - ySign);
                                printf("█");
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                gotoxy(pX, pY + ySign);
                                printf("█");
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                gotoxy(pX - xSign, pY);
                                printf("█");
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                gotoxy(pX + xSign, pY);
                                printf("█");
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            textcolor(borderColor);
                            gotoxy(pX, pY);
                            printf("█");
                        }
                    }
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2)
{
    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // ADQUIRINDO A COR ATUAL DO TEXTO
    struct text_info currentTextInfo;
    gettextinfo(&currentTextInfo);

    int currentColor = currentTextInfo.attribute;

    int drawBorder = hasBorder;
    int borderColor = _borderColor;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = _screenX1;
    int screenX2 = _screenX2;

    int screenY1 = _screenY1;
    int screenY2 = _screenY2;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(currentColor);

                    if (pixelChar == '@')
                    {
                        printf("█");
                    }
                    else if (pixelChar == 'a')
                    {
                        printf("▓");
                    }
                    else if (pixelChar == '}')
                    {
                        printf("▒");
                    }
                    else if (pixelChar == '?')
                    {
                        printf("░");
                    }
                    else if (pixelChar == '`')
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("%c", pixelChar);
                    }

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        textcolor(borderColor);

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                gotoxy(pX, pY - ySign);
                                printf("█");
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                gotoxy(pX, pY + ySign);
                                printf("█");
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                gotoxy(pX - xSign, pY);
                                printf("█");
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                gotoxy(pX + xSign, pY);
                                printf("█");
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            textcolor(borderColor);
                            gotoxy(pX, pY);
                            printf("█");
                        }
                    }
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteColorMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2)
{

    if (!spr->hasColor)
    {
        return drawSpriteMaster(x, y, spr, xScale, yScale, hasBorder, _borderColor, _screenX1, _screenY1, _screenX2, _screenY2);
    }

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    int drawBorder = hasBorder;
    int borderColor = _borderColor;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = min(max(_screenX1, 1), LARGURA);
    int screenX2 = min(max(_screenX2, 1), LARGURA);

    int screenY1 = min(max(_screenY1, 1), ALTURA);
    int screenY2 = min(max(_screenY2, 1), ALTURA);

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];
                int pixelColor = spr->color[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(pixelColor);

                    printf("█");

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        textcolor(borderColor);

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                gotoxy(pX, pY - ySign);
                                printf("█");
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                gotoxy(pX, pY + ySign);
                                printf("█");
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                gotoxy(pX - xSign, pY);
                                printf("█");
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                gotoxy(pX + xSign, pY);
                                printf("█");
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            textcolor(borderColor);
                            gotoxy(pX, pY);
                            printf("█");
                        }
                    }
                }
            }
        }
    }
}

// FUNCOES PARA DESENHAR NO ARRAY
// Sprite Functions
void drawSpriteBufferMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2)
{

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    // ADQUIRINDO A COR ATUAL DO TEXTO
    struct text_info currentTextInfo;
    gettextinfo(&currentTextInfo);

    int currentColor = currentTextInfo.attribute;

    int drawBorder = hasBorder;
    int borderColor = _borderColor;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = min(max(_screenX1, 1), LARGURA);
    int screenX2 = min(max(_screenX2, 1), LARGURA);

    int screenY1 = min(max(_screenY1, 1), ALTURA);
    int screenY2 = min(max(_screenY2, 1), ALTURA);

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    int index = (pX - 1) + ((pY - 1) * LARGURA);
                    screenPixels[index].pixel = pixelChar;
                    screenPixels[index].color = currentColor;

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                int _ind = (pX - 1) + (((pY - 1) - ySign) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                int _ind = (pX - 1) + (((pY - 1) + ySign) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                int _ind = ((pX - 1) - xSign) + ((pY - 1) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                int _ind = ((pX - 1) + xSign) + ((pY - 1) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            int _ind = (pX - 1) + ((pY - 1) * LARGURA);
                            screenPixels[_ind].pixel = '@';
                            screenPixels[_ind].color = borderColor;
                        }
                    }
                }
            }
        }
    }
}

// FUNCOES PARA DESENHAR NO ARRAY
// Sprite Functions
void drawSpriteBufferColorMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2)
{

    if (!spr->hasColor)
    {
        return drawSpriteBufferMaster(x, y, spr, xScale, yScale, hasBorder, _borderColor, _screenX1, _screenY1, _screenX2, _screenY2);
    }

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    int drawBorder = hasBorder;
    int borderColor = _borderColor;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = min(max(_screenX1, 1), LARGURA);
    int screenX2 = min(max(_screenX2, 1), LARGURA);

    int screenY1 = min(max(_screenY1, 1), ALTURA);
    int screenY2 = min(max(_screenY2, 1), ALTURA);

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];
                int pixelColor = spr->color[pixelIndex];

                if (pixelChar != ' ')
                {

                    int index = (pX - 1) + ((pY - 1) * LARGURA);
                    screenPixels[index].pixel = '@';
                    screenPixels[index].color = pixelColor;

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                int _ind = (pX - 1) + (((pY - 1) - ySign) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                int _ind = (pX - 1) + (((pY - 1) + ySign) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                int _ind = ((pX - 1) - xSign) + ((pY - 1) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                int _ind = ((pX - 1) + xSign) + ((pY - 1) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            int _ind = (pX - 1) + ((pY - 1) * LARGURA);
                            screenPixels[_ind].pixel = '@';
                            screenPixels[_ind].color = borderColor;
                        }
                    }
                }
            }
        }
    }
}

// FUNCOES PARA DESENHAR NO ARRAY
// Sprite Functions
void drawSpriteMonoColorBufferMaster(int x, int y, struct Sprite *spr, float xScale, float yScale, int hasBorder, int _borderColor, int internalColor, int _screenX1, int _screenY1, int _screenX2, int _screenY2)
{

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    int currentColor = internalColor;

    int drawBorder = hasBorder;
    int borderColor = _borderColor;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = min(max(_screenX1, 1), LARGURA);
    int screenX2 = min(max(_screenX2, 1), LARGURA);

    int screenY1 = min(max(_screenY1, 1), ALTURA);
    int screenY2 = min(max(_screenY2, 1), ALTURA);

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    int index = (pX - 1) + ((pY - 1) * LARGURA);
                    screenPixels[index].pixel = '@';
                    screenPixels[index].color = currentColor;

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                int _ind = (pX - 1) + (((pY - 1) - ySign) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                int _ind = (pX - 1) + (((pY - 1) + ySign) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                int _ind = ((pX - 1) - xSign) + ((pY - 1) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                int _ind = ((pX - 1) + xSign) + ((pY - 1) * LARGURA);
                                screenPixels[_ind].pixel = '@';
                                screenPixels[_ind].color = borderColor;
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            int _ind = (pX - 1) + ((pY - 1) * LARGURA);
                            screenPixels[_ind].pixel = '@';
                            screenPixels[_ind].color = borderColor;
                        }
                    }
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteMonoColorScl(int x, int y, struct Sprite *spr, float xScale, float yScale, int color)
{

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    int drawBorder = 1;
    int borderColor = 15;

    int internalColor = color;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(internalColor);

                    printf("█");
                }
            }
        }
    }
}

// Sprite Functions
void drawSpriteMonoColorSclBorder(int x, int y, struct Sprite *spr, float xScale, float yScale, int color)
{

    // TAMANHO DO SPRITE ORIGINAL
    int _wid = spr->width;
    int _hei = spr->height;

    int drawBorder = 1;
    int borderColor = 15;

    int internalColor = color;

    // SINAL DAS ESCALAS
    int xSign = (xScale < 0) ? -1 : 1;
    int ySign = (yScale < 0) ? -1 : 1;

    // LIMITES DA TELA
    int screenX1 = 1;
    int screenX2 = LARGURA;

    int screenY1 = 1;
    int screenY2 = ALTURA;

    // TAMANHO DO SPRITE NA TELA COM ESCALA
    int xExtends = _wid * xScale * xSign;
    int yExtends = _hei * yScale * ySign;

    for (int i = 0; i < yExtends; i++)
    {
        for (int j = 0; j < xExtends; j++)
        {

            // POSICAO NO SPRITE COM ESCALA
            int xx = j * xSign;
            int yy = i * ySign;

            // POSICAO DO PIXEL NA TELA
            int pX = x + xx;
            int pY = y + yy;

            // DETECTA SE O PIXEL ESTA DENTRO DOS LIMITES DA TELA
            if (!(pY > screenY2 || pY < screenY1 || pX > screenX2 || pX < screenX1))
            {

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];

                if (pixelChar != ' ')
                {

                    gotoxy(pX, pY);
                    textcolor(internalColor);

                    printf("█");

                    // DESENHA A BORDA NOS LIMITES DO SPRITE
                    // INIMIGA DE WALTER
                    if (drawBorder)
                    {

                        textcolor(borderColor);

                        if (i == 0)
                        {
                            if (!(pY - ySign > screenY2 || pY - ySign < screenY1))
                            {
                                gotoxy(pX, pY - ySign);
                                printf("█");
                            }
                        }

                        if (i == yExtends - 1)
                        {
                            if (!(pY + ySign > screenY2 || pY + ySign < screenY1))
                            {
                                gotoxy(pX, pY + ySign);
                                printf("█");
                            }
                        }

                        if (j == 0)
                        {
                            if (!(pX - xSign > screenX2 || pX - xSign < screenX1))
                            {
                                gotoxy(pX - xSign, pY);
                                printf("█");
                            }
                        }

                        if (j == xExtends - 1)
                        {
                            if (!(pX + xSign > screenX2 || pX + xSign < screenX1))
                            {
                                gotoxy(pX + xSign, pY);
                                printf("█");
                            }
                        }
                    }
                }
                else
                {
                    // DESENHA A BORDA NO INTERIOR DO SPRITE
                    if (drawBorder)
                    {
                        if (checkGrid(xx / xScale, yy / yScale, _wid, _hei, spr->grid))
                        {
                            textcolor(borderColor);
                            gotoxy(pX, pY);
                            printf("█");
                        }
                    }
                }
            }
        }
    }
}

void spriteCreate(char *path, struct Sprite *spr)
{

    // Abre o arquivo com do endereço path
    FILE *fp;
    fp = fopen(path, "r");

    char reader[128];
    int width = atoi(fgets(reader, 6, fp));
    int height = atoi(fgets(reader, 6, fp));

    // Aloca memória pro array
    // Pq ele n persiste quando a função acaba
    char *grid;
    grid = malloc(height * width * sizeof(char));

    // Leitura do arquivo linha por linha
    for (int i = 0; i < height; i++)
    {
        // Esse 16 a mais ajuda a lidar com erros na criação do sprite texto
        int extra = 100;
        char _line[width + extra + 2];

        // Preenche a linha com espaços vazios
        for (int w = 0; w < width + extra + 2; w++)
        {
            _line[w] = ' ';
        }

        // Pega uma linha do arquivo
        fgets(_line, width + extra + 2, fp);

        // int end = 0;
        for (int j = 0; j < width; j++)
        {
            char c = _line[j];
            *grid = c;
            grid++;
        }
    }

    fclose(fp);

    grid -= (width * height);

    spr->grid = grid;
    spr->width = width;
    spr->height = height;
    spr->created = 1;
}

void spriteCreateColor(char *path, struct Sprite *spr)
{

    // Abre o arquivo com do endereço path
    FILE *fp;
    fp = fopen(path, "r");

    char reader[128];
    int width = atoi(fgets(reader, 6, fp));
    int height = atoi(fgets(reader, 6, fp));

    // Aloca memória pro array
    // Pq ele n persiste quando a função acaba
    char *grid;
    grid = malloc(height * width * sizeof(char));

    int *color;
    color = malloc(height * width * sizeof(int));

    // Leitura do arquivo linha por linha
    for (int i = 0; i < height; i++)
    {
        // Esse 16 a mais ajuda a lidar com erros na criação do sprite texto
        int extra = 100;
        char _line[width + extra + 2];

        // Preenche a linha com espaços vazios
        for (int w = 0; w < width + extra + 2; w++)
        {
            _line[w] = ' ';
        }

        // Pega uma linha do arquivo
        fgets(_line, width + extra + 2, fp);

        // int end = 0;
        for (int j = 0; j < width; j++)
        {
            char c = _line[j];
            *grid = c;
            grid++;
        }
    }
    // Reseta o ponteiro pra posição inicial
    grid -= (width * height);

    // Lendo as cores
    for (int i = 0; i < height; i++)
    {
        // Esse 16 a mais ajuda a lidar com erros na criação do sprite texto
        int extra = 100;
        char _line[width + extra + 2];

        // Preenche a linha com espaços vazios
        for (int w = 0; w < width + extra + 2; w++)
        {
            _line[w] = ' ';
        }

        // Pega uma linha do arquivo
        fgets(_line, width + extra + 2, fp);

        // int end = 0;
        for (int j = 0; j < width; j++)
        {
            char c = _line[j];
            int col = 0;

            // Trasnforma os char em números de cor
            // Usa os char (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, :, ;, <, =, >, ?)
            if ((int)c > 47 || (int)c < 64)
            {
                col = ((int)c) - 48;
            }

            *color = col;
            color++;
        }
    }
    // Reseta o ponteiro pra posição inicial
    color -= (width * height);

    fclose(fp);

    // Sem cor
    spr->hasColor = 1;

    spr->grid = grid;
    spr->color = color;
    spr->width = width;
    spr->height = height;
    spr->created = 1;
}

#endif
