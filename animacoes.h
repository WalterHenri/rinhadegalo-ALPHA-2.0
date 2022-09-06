#ifndef ANIMACOES_H_INCLUDED
#define ANIMACOES_H_INCLUDED

/****************************************************************************************

 STRUCT E FUNCOES DE PARTICULAS DE LINHA
 COM ESSES RECURSOS PODE-SE CRIAR, ATUALIZAR E DESENHAR
 PONTOS OU LINHAS DE CORES DETERMINADAS COM POSICOES
 VELOCIDADES E ACELERACOES DESEJADAS

 PRIMEIRO DEVE-SE CRIAR UM ARRAY DA STRUCT LINEPARTICLE
 DEPOIS DEVE-SE INICIALIZAR ESSE ARRAY USANDO INITLINEPARTICLES();
 AGORA BASTA CRIAR PARTICULAS USANDO A FUNCAO CREATELINEPARTICLE();
 ESSA FUNCAO RETORNA O ID DA PARTICULA NO ARRAY, ASSIM PODE-SE MUDAR
 VALORES MANUALMENTE COMO A VELOCIDADE, A COR, ATRITO ETC
 PARA ATUALIZAR A POSICAO DAS PARTICULAS DENTRO DO ARRAY DEVE-SE USAR
 UPDATELINEPARTICLES();   E PARA DESENHA-LAS DRAWLINEPARTICLES();
 TODAS AS FUNCOES MENCIONADAS RECEBEM PELO MENOS O ENDEREÇO DO ARRAY DE PARTICULAS
 E O TAMANHO DESSE ARRAY

****************************************************************************************/

/*
EX:

int maximoDeParticulas = 30;
struct LineParticle particulas[maximoDeParticulas];

initLineParticles(&particulas, maximoDeParticulas);

int partIndex = createLineParticles(&particulas, maximoDeParticulas, 1, 1, 4, 1, RED, 100);

particulas[partIndex].hspd = 4;
particulas[partIndex].vacc = 0.2;

int frames = 400;

clearScreen();
for(int i = 0; i < frames; i++){
   drawRectScreen(1, 1, LARGURA, ALTURA, '@', BLACK);

   updateLineParticles(&particulas, maximoDeParticulas);
   drawLineParticles(&particulas, maximoDeParticulas);

   drawScreen();
   Sleep(100);
}

*/

struct LineParticle
{
    float x; // POSICAO X ATUAL
    float y; // POSICAO Y ATUAL

    float x2;
    float y2;

    int color;

    float hspd; // VELOCIDADE HORIZONTAL
    float vspd; // VELOCIDADE VERTICAL

    float hspd2; // VELOCIDADE HORIZONTAL 2
    float vspd2; // VELOCIDADE VERTICAL   2

    float hacc;
    float vacc;

    float damp; // ATRITO

    int life;   // FRAMES RESTANTES DE VIDA PRO OBJETO APOS TOCAR O CHAO
    int ground; // SE JA TOCOU NO CHAO

    // int visible;
    int active; // SE O "OBJETO" ESTA ATIVO
};

int createLineParticle(struct LineParticle *partList, int partMax, float x, float y, float x2, float y2, int color, int life)
{
    int i;
    for (i = 0; i < partMax; i++)
    {
        if (!partList[i].active)
        {
            partList[i].active = 1;
            partList[i].x = x;
            partList[i].y = y;
            partList[i].x2 = x2;
            partList[i].y2 = y2;
            partList[i].color = color;
            partList[i].life = life;
            partList[i].hspd = 0;
            partList[i].vspd = 0;
            partList[i].hspd2 = 0;
            partList[i].vspd2 = 0;
            partList[i].hacc = 0;
            partList[i].vacc = 0;
            partList[i].ground = 0;
            partList[i].damp = 1;
            return i;
        }
    }
    return -1;
}

void initLineParticles(struct LineParticle *partList, int partMax)
{
    for (int i = 0; i < partMax; i++)
    {
        partList[i].active = 0;
        partList[i].x = 0;
        partList[i].y = 0;
        partList[i].x2 = 0;
        partList[i].y2 = 0;
        partList[i].color = 0;
        partList[i].life = 0;
        partList[i].hspd = 0;
        partList[i].vspd = 0;
        partList[i].hspd2 = 0;
        partList[i].vspd2 = 0;
        partList[i].hacc = 0;
        partList[i].vacc = 0;
        partList[i].ground = 0;
        partList[i].damp = 1;
    }
}

void updateLineParticles(struct LineParticle *partList, int partMax)
{
    for (int i = 0; i < partMax; i++)
    {
        if (partList[i].active)
        {

            partList[i].hspd += partList[i].hacc;
            partList[i].vspd += partList[i].vacc;
            partList[i].hspd2 += partList[i].hacc;
            partList[i].vspd2 += partList[i].vacc;

            partList[i].hspd *= partList[i].damp;
            partList[i].vspd *= partList[i].damp;
            partList[i].hspd2 *= partList[i].damp;
            partList[i].vspd2 *= partList[i].damp;

            partList[i].x += partList[i].hspd;
            partList[i].x2 += partList[i].hspd2;

            partList[i].y += partList[i].vspd;
            partList[i].y2 += partList[i].vspd2;

            if (partList[i].life > 0)
            {
                partList[i].life--;
            }
            else
            {
                partList[i].active = 0;
            }

            if (partList[i].y > ALTURA + 10 && partList[i].y2 > ALTURA + 10)
            {
                partList[i].active = 0;
            }
        }
    }
}

void drawLineParticles(struct LineParticle *partList, int partMax, int screenX1, int screenY1, int screenX2, int screenY2)
{
    for (int i = 0; i < partMax; i++)
    {
        if (partList[i].active)
        {

            int x1 = partList[i].x;
            int x2 = partList[i].x2;
            int y1 = partList[i].y;
            int y2 = partList[i].y2;

            int color = partList[i].color;

            int difX = x2 - x1;
            int difY = y2 - y1;

            int difXMod = abs(difX);
            int difYMod = abs(difY);

            if (difXMod > difYMod)
            {
                if (x1 > x2)
                {
                    int temp = x1;
                    x1 = x2;
                    x2 = temp;
                }

                // if(x1 > screenX1)
                x1 = max(x1, screenX1);
                x2 = min(x2, screenX2);

                difX = x2 - x1;

                if (!(y1 > screenY2 || y1 < screenY1))
                {
                    for (int j = 0; j < difX + 1; j++)
                    {
                        pointScreen(x1, y1, '@', color);
                        x1++;
                    }
                }
            }
            else
            {
                if (y1 > y2)
                {
                    int temp = y1;
                    y1 = y2;
                    y2 = temp;
                }

                // if(x1 > screenX1)
                y1 = max(y1, screenY1);
                y2 = min(y2, screenY2);

                difY = y2 - y1;

                if (!(x1 > screenX2 || x1 < screenX1))
                {
                    for (int j = 0; j < difY + 1; j++)
                    {
                        pointScreen(x1, y1, '@', color);
                        y1++;
                    }
                }
            }
        }
    }
}

void drawDiagonalLineParticles(struct LineParticle *partList, int partMax, int screenX1, int screenY1, int screenX2, int screenY2)
{
    for (int i = 0; i < partMax; i++)
    {
        if (partList[i].active)
        {

            int x1 = partList[i].x;
            int x2 = partList[i].x2;
            int y1 = partList[i].y;
            int y2 = partList[i].y2;

            int color = partList[i].color;

            int difX = x2 - x1;
            int difY = y2 - y1;

            int difXMod = (difX > 0) ? difX : -difX;
            int difYMod = (difY > 0) ? difY : -difY;

            if (difXMod > difYMod)
            {
                if (x1 > x2)
                {
                    int temp = x1;
                    x1 = x2;
                    x2 = temp;

                    temp = y1;
                    y1 = y2;
                    y2 = temp;
                }

                difX = x2 - x1;
                difY = y2 - y1;

                int xx = x1;
                float yy = y1;

                float slope;
                if (difX == 0)
                {
                    slope = 0;
                }
                else
                {
                    slope = ((float)difY) / ((float)difX);
                }

                for (int j = 0; j < difXMod + 1; j++)
                {
                    if (!(yy > screenY2 || yy < screenY1 || xx > screenX2 || xx < screenX1))
                    {
                        pointScreen(xx, yy, '@', color);
                    }
                    xx++;
                    yy += slope;
                }
            }
            else
            {
                if (y1 > y2)
                {
                    int temp = x1;
                    x1 = x2;
                    x2 = temp;

                    temp = y1;
                    y1 = y2;
                    y2 = temp;
                }

                difX = x2 - x1;
                difY = y2 - y1;

                float xx = x1;
                int yy = y1;

                float slope;
                if (difY == 0)
                {
                    slope = 0;
                }
                else
                {
                    slope = ((float)difX) / ((float)difY);
                }

                for (int j = 0; j < difYMod + 1; j++)
                {
                    if (!(yy > screenY2 || yy < screenY1 || xx > screenX2 || xx < screenX1))
                    {
                        pointScreen(xx, yy, '@', color);
                    }
                    yy++;
                    xx += slope;
                }
            }
        }
    }
}

void spriteToLineParticles(struct LineParticle *partList, int partMax, struct Sprite *spr, int x, int y, float xScale, float yScale)
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

                // PIXEL E COR CORRESPONDENTE
                int pixelIndex = ((int)(xx / xScale)) + ((int)(_wid * (int)((yy / yScale))));

                char pixelChar = spr->grid[pixelIndex];
                int pixelColor = spr->color[pixelIndex];

                if (pixelChar != ' ')
                {

                    int ind = createLineParticle(partList, partMax, pX, pY, pX, pY, pixelColor, 150);
                    if (ind != -1)
                    {
                        partList[ind].vacc = 0.2;
                        partList[ind].damp = 0.9;
                    }
                }
            }
        }
    }
}

void explosionLineParticle(struct LineParticle *partList, int partMax, int x, int y)
{
    for (int i = 0; i < partMax; i++)
    {
        if (partList[i].active)
        {
            int px = (partList[i].x + partList[i].x2) / 2;
            int py = (partList[i].y + partList[i].y2) / 2;

            int dx = x - px;
            int dy = y - py;

            float dist = sqrt(dx * dx + dy * dy);

            float pCos = dx / dist;
            float pSin = dy / dist;

            if (dist < 20)
            {
                float randSpd = 2 + ((20 - dist) / 10) + (float)(rand() % 10) / 10;
                partList[i].hspd += randSpd * pCos;
                partList[i].vspd -= randSpd * pSin;
                partList[i].hspd2 += randSpd * pCos;
                partList[i].vspd2 -= randSpd * pSin;
                // partList[i].x2 += 1;
            }
        }
    }
}

struct SpriteParticle
{
    float x; // POSICAO X ATUAL
    float y; // POSICAO Y ATUAL

    float xAdjust; // POSICAO X ATUAL
    float yAdjust; // POSICAO Y ATUAL

    float xScale;
    float yScale;

    float sprXOff;
    float sprYOff;

    struct Sprite *spr;

    float hspd; // VELOCIDADE HORIZONTAL
    float vspd; // VELOCIDADE VERTICAL

    float hacc;
    float vacc;

    float damp; // ATRITO

    int life;   // FRAMES RESTANTES DE VIDA PRO OBJETO APOS TOCAR O CHAO
    int ground; // SE JA TOCOU NO CHAO

    // int visible;
    int active; // SE O "OBJETO" ESTA ATIVO
};

int createSpriteParticle(struct SpriteParticle *partList, int partMax, float x, float y, float xScale, float yScale, struct Sprite *spr, int life)
{
    int i;
    for (i = 0; i < partMax; i++)
    {
        if (!partList[i].active)
        {
            partList[i].active = 1;
            partList[i].x = x;
            partList[i].y = y;
            partList[i].xAdjust = 0;
            partList[i].yAdjust = 0;
            partList[i].xScale = xScale;
            partList[i].yScale = yScale;
            partList[i].sprXOff = 0;
            partList[i].sprYOff = 0;
            partList[i].spr = spr;
            partList[i].life = life;
            partList[i].hspd = 0;
            partList[i].vspd = 0;
            partList[i].hacc = 0;
            partList[i].vacc = 0;
            partList[i].ground = 0;
            partList[i].damp = 0.98;
            return i;
        }
    }
    return -1;
}

void initSpriteParticles(struct SpriteParticle *partList, int partMax)
{
    for (int i = 0; i < partMax; i++)
    {
        partList[i].active = 0;
        partList[i].x = 0;
        partList[i].y = 0;
        partList[i].xAdjust = 0;
        partList[i].yAdjust = 0;
        partList[i].sprXOff = 0;
        partList[i].sprYOff = 0;
        partList[i].xScale = 1;
        partList[i].yScale = 1;
        partList[i].spr = &sprNulo;
        partList[i].life = 0;
        partList[i].hspd = 0;
        partList[i].vspd = 0;
        partList[i].hacc = 0;
        partList[i].vacc = 0;
        partList[i].ground = 0;
        partList[i].damp = 1;
    }
}

void updateSpriteParticles(struct SpriteParticle *partList, int partMax)
{
    for (int i = 0; i < partMax; i++)
    {
        if (partList[i].active)
        {

            partList[i].hspd += partList[i].hacc;
            partList[i].vspd += partList[i].vacc;

            partList[i].hspd *= partList[i].damp;
            partList[i].vspd *= partList[i].damp;

            partList[i].xAdjust = -partList[i].sprXOff * (partList[i].xScale - 1);
            partList[i].yAdjust = -partList[i].sprYOff * (partList[i].yScale - 1);

            float hspd = partList[i].hspd;
            float vspd = partList[i].vspd;

            partList[i].x += hspd;
            partList[i].y += vspd;

            if (partList[i].life > 0)
            {
                partList[i].life--;
            }
            else
            {
                partList[i].active = 0;
            }
        }
    }
}

void drawSpriteParticles(struct SpriteParticle *partList, int partMax, int screenX1, int screenY1, int screenX2, int screenY2)
{
    for (int i = 0; i < partMax; i++)
    {
        if (partList[i].active)
        {

            drawSpriteBufferColorMaster(partList[i].x + partList[i].xAdjust, partList[i].y + partList[i].yAdjust, partList[i].spr, partList[i].xScale, partList[i].yScale, 0, 0, screenX1, screenY1, screenX2, screenY2);
        }
    }
}

int rectCollision(int x1, int y1, int wid1, int hei1, int x2, int y2, int wid2, int hei2)
{

    if (!(x2 + wid2 - x1 > 0 && x1 + wid1 - x2 > 0))
    {
        return 0;
    }

    if (!(y2 + hei2 - y1 > 0 && y1 + hei1 - y2 > 0))
    {
        return 0;
    }

    return 1;
}

void fatality(int player, struct galo_status winner, struct galo_status loser)
{
    int a;
    if (!one_player_mode)
    {
        finish(winner.id, loser.id);
        a = miniGayme();
    }
    else
    {
        a = 1;
    }

    if (a == 1)
    {
        switch (winner.id)
        {

        case GALO_DE_CALCA:
            fatalityKalsa(loser.id);
            break;
        case GALO_SNIPER:
            fatalitySniper(loser.id);
            break;
        case GALO_DE_TENIS:
            fatalityTenis(loser.id);
            break;
        case GALO_PIRATA:
            fatalityPirata(winner.id, loser.id);
            break;
        case GALO_FAQUEIRO:
            fatalityPirata(winner.id, loser.id);
            break;
        case GALO_DA_PESTE:
            fatalityPeste(loser.id);
            break;
        default:
            fatalityDefault(winner.id, loser.id);
            break;
        }
    }
    else
    {

        if (player == 1)
        {

            play_song(PLAYER1WINS);
        }
        else
        {

            play_song(PLAYER2WINS);
        }
    }
}

void finish(int winnerId, int loserId)
{

    int xWinner = 3;
    int yWinner = ALTURA - galoSprites[winnerId][0].height - 3;

    int xLoser = LARGURA - galoSprites[loserId][0].width - 6;
    int yLoser = ALTURA - galoSprites[winnerId][0].height - 9;

    drawSpriteColor(1, 1, &entrada);
    drawSpriteColorScl(xWinner, yWinner, &galoSprites[winnerId][0], 2, 1);
    drawSpriteColorScl(xLoser, yLoser, &galoSprites[loserId][0], 2, 1);

    sleep(2);

    pause_song();

    if (!(galos[loserId].tipo == FEMEA))
    {
        play_song(FINISH_HIM);
        drawSpriteColor(1, 1, &sprFinish);
        sleep(2);
        pause_song();
    }
    else
    {
        play_song(FINISH_HER);
        sleep(2);
        pause_song();
    }
}

void desenharfatality()
{

    play_song(PLAYER1WINS);

    Sleep(2500);

    pause_song();

    clrscr();

    int fheight = sprFatality.height;
    int fwidth = sprFatality.width;

    int fx = width / 2 - sprFatality.width / 2;
    int fy = 4;

    play_song(FATALITY);
    drawSpriteColor(fx, fy, &sprFatality);

    for (int i = 0; i < 8; i++)
    {

        // desenhar sangue do f
        textcolor(RED);
        gotoxy(9, 10 + i / 2);
        printf("█");

        // desenhar sangue do t
        textcolor(RED);
        gotoxy(24, 7 + i);
        printf("█");
        gotoxy(24, 7 + i - 1);
        printf(" ");

        textcolor(RED);
        gotoxy(31, 5 + i / 4);
        printf("█");

        if (i < 5)
        {
            textcolor(RED);
            gotoxy(60, 10 + i);
            printf("█");
            gotoxy(60, 10 + i - 1);
            printf(" ");
        }

        // desenhar mais sangue ai
        gotoxy(42, 10 + i / 4);
        printf("█");

        gotoxy(65, 10 + i / 4);
        printf("█");

        gotoxy(70, 6 + i);
        printf("█");
        gotoxy(70, 6 + i - 1);
        printf(" ");

        gotoxy(39, 10 + i / 4);
        printf("█");

        if (i < 4)
        {
            gotoxy(54, 6 + i / 2);
            printf("█");
        }
        Sleep(200);
    }

    pause_song();

    play_song(FLAWLESS_VICTORY);

    drawSpriteColor(width / 2 - flawless.width / 2, fy + fheight + 2, &flawless);

    Sleep(1700);

    pause_song();
}

int miniGayme()
{
    clrscr();
    desenharBorda();

    int up = 0;
    int down = 1;
    int left = 2;
    int right = 3;

    int vetor[6];

    for (int i = 0; i < 6; i++)
    {
        vetor[i] = rand() % 4;
        drawSpriteColor(2 + 12 * i, 2, &sprSetas[vetor[i]]);
        Beep(100 * i, 100);
        Sleep(300);
    }
    Sleep(100);
    desenharBorda();

    for (int i = 0; i < 6; i++)
    {

        char a;
        int b = 100;

        while (b == 100)
        {
            a = getch();

            if (a == 'w')
            {
                b = up;
            }
            else if (a == 's')
            {
                b = down;
            }
            else if (a == 'a')
            {
                b = left;
            }
            else if (a == 'd')
            {
                b = right;
            }
            else
            {
                b = 100;
            }
        }
        if (vetor[i] == b)
        {
            drawSpriteColor(2 + 12 * i, 2, &sprSetas[b]);
            Beep(100 * i, 100);
        }
        else
        {
            drawSpriteColor(2 + 12 * i, 2, &sprSetas[4]);
            play_song(YOU_SUCK);
            Sleep(1500);
            pause_song();
            return -1;
        }

        Sleep(300);
    }

    play_song(WELL_DONE);
    Sleep(1500);
    pause_song();

    desenharBorda();

    return 1;
}

int minigame(double level)
{
    clrscr();
    desenharBorda();

    int up = 0;
    int down = 1;
    int left = 2;
    int right = 3;

    int vetor[6];

    for (int i = 0; i < 6; i++)
    {
        vetor[i] = rand() % 4;
        drawSpriteColor(2 + 12 * i, 2, &sprSetas[vetor[i]]);
        Beep(100 * i, 100);
        Sleep((int)300 / level);
    }
    Sleep(100);
    desenharBorda();

    for (int i = 0; i < 6; i++)
    {

        char a;
        int b = 100;

        while (b == 100)
        {
            a = getch();

            if (a == 'w')
            {
                b = up;
            }
            else if (a == 's')
            {
                b = down;
            }
            else if (a == 'a')
            {
                b = left;
            }
            else if (a == 'd')
            {
                b = right;
            }
            else
            {
                b = 100;
            }
        }
        if (vetor[i] == b)
        {
            drawSpriteColor(2 + 12 * i, 2, &sprSetas[b]);
            Beep(100 * i, 100);
        }
        else
        {
            drawSpriteColor(2 + 12 * i, 2, &sprSetas[4]);
            play_song(YOU_SUCK);
            Sleep(1500);
            pause_song();
            return -1;
        }

        Sleep(300);
    }

    play_song(WELL_DONE);
    Sleep(1500);
    pause_song();

    desenharBorda();

    return 1;
}
void fatalityPeste(int galo2){


    int sprWid = galoSprites[galo2][1].width * 2;
    int sprHei = galoSprites[galo2][1].height;

    int pestex = 2;
    int pestey = ALTURA - 4 - sprHei;

    int galox = LARGURA / 2;
    int galoy = ALTURA - 4 - sprHei;

    int ypeste = 1;

    loop_song(SCREAM);

    for(int i = galox; i < sprWid + galox; i ++){
        for(int j = galoy; j < sprHei + galoy; j ++){
            drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
            drawRectScreen(1,ALTURA - 4,LARGURA,5,'@',GREEN);
            drawSpriteBufferColorMaster(pestex,pestey,&galoSprites[GALO_DA_PESTE][0],2,1,0,0,1,1,LARGURA,ALTURA);
            drawSpriteBufferColorMaster(galox,galoy,&galoSprites[galo2][0],2,1,0,0,1,1,LARGURA,ALTURA);
            drawSpriteMonoColorBufferMaster(galox,galoy,&galoSprites[galo2][0],2,1,0,0,BLACK,galox,galoy,i,j);
            drawScreen();
        }
        Sleep(100);
    }
    for(int i = 0; i < 4; i ++){

        drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
        drawRectScreen(1,ALTURA - 4,LARGURA,5,'@',GREEN);
        drawSpriteBufferColorMaster(pestex,pestey,&galoSprites[GALO_DA_PESTE][0],2,1,0,0,1,1,LARGURA,ALTURA);
        drawSpriteMonoColorBufferMaster(galox,galoy,&galoSprites[galo2][0],2,1,0,0,BLACK,1,1,LARGURA,ALTURA);
        if(i%2 == 0){
            drawRectScreen(1,1,LARGURA,ALTURA,'@',BLACK);
            drawSpriteBufferColorMaster(LARGURA/2,1,&light,1 + i/2,1 + i/2,0,0,1,1,LARGURA,ALTURA);
        }
        drawScreen();
        Sleep(300);
    }
    pause_song();

        drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
        drawRectScreen(1,ALTURA - 4,LARGURA,5,'@',GREEN);
        drawSpriteBufferColorMaster(pestex,pestey,&galoSprites[GALO_DA_PESTE][0],2,1,0,0,1,1,LARGURA,ALTURA);
        drawScreen();
        Sleep(1000);

        desenharfatality();

}

void fatalitySniper(int galo2)
{

    play_song(FATALITY_BACKGROUND);

    int sprWid = galoSprites[galo2][1].width * 2;
    int sprHei = galoSprites[galo2][1].height;

    int x = 2;
    int y = 5;
    int x2 = LARGURA - sprWid - 2;
    int y2 = 5;

    int bX = x + (19 * 2);
    int bY = y + 4;
    int prevX = bX;
    int prevY = bY;

    drawSpriteColorScl(x, y, &galoSprites[GALO_SNIPER][0], 2, 1);
    drawSpriteColorScl(x2, y2, &galoSprites[galo2][1], 2, 1);

    Sleep(600);

    clrscr();

    drawSpriteColorScl(x, y, &galoBazooka, 1, 1);
    drawSpriteColorScl(x2, y2, &galoSprites[galo2][1], 2, 1);

    Sleep(600);

    for (int i = 0; i < 10; i++)
    {

        drawSpriteMonoColorScl(prevX, prevY, &bulletBill, 1, 1, BLACK);
        drawSpriteColorScl(bX, bY, &bulletBill, 1, 1);

        drawSpriteColorScl(x - i * 0.2, y, &galoBazooka, 1, 1);

        prevX = bX;
        prevY = bY;

        bX += 1;

        Sleep(100);
    }

    pause_song();
    play_song(SCREAM);

    for (int i = 0; i < 5; i++)
    {

        float scl = 1 + (((i)) / 5);
        drawSpriteColorScl(x2, y2, &explosion, scl, scl);
        Sleep(200);
    }

    Sleep(500);

    pause_song();

    desenharfatality();
}

void fatalityPirata(int galo1, int galo2)
{
    play_song(FATALITY_BACKGROUND);

    int sprWid = galoSprites[galo2][0].width;
    int sprHei = galoSprites[galo2][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1][0];
    sprGalos[1] = &galoSprites[galo2][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    int ordem = 0;
    int ordem2 = 1;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    galosX[ordem2] = -20;

    // int fundoSelecionado = configBatalha.fundo;

    int maxBlood = 100;
    struct LineParticle blood[maxBlood];
    initLineParticles(&blood, maxBlood);

    int sleepTime = 20;

    for (int i = 0; i < 50; i++)
    {

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA);
        // drawSpriteBufferColorMaster(-5, -5, &slashEffect[(i/4)%8], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA);

        if (i > 40)
        {
            drawRectScreen(1, 1, LARGURA, ALTURA, '@', BLACK);
        }

        drawScreen();
        Sleep(sleepTime);
    }

    galosX[ordem] = LARGURA - 20;
    float xEscorrega = 4;
    float yEscorrega = 0;
    float yEscorregaSpd = 0;
    float xEscorregaSpd = 0.3;
    int cutHei = sprHei / 1.5;

    int _sprWid = sprGalos[ordem2]->width;
    int _sprHei = sprGalos[ordem2]->height;

    for (int i = 0; i < _sprWid; i++)
    {
        if (opaqueCheck(i, cutHei, _sprWid, _sprHei, sprGalos[ordem2]->grid))
        {
            int posX = galosBaseX[ordem2] + galosX[ordem2];
            int posY = galosBaseY[ordem2] + galosY[ordem2];
            int index = createLineParticle(&blood, maxBlood, posX + (i * 2), posY + cutHei, posX + (i * 2), posY + cutHei, RED, 400);
            float vspdBlood = 0.001 + ((float)(rand() % 500)) / 25000;
            blood[index].vspd2 = vspdBlood;

            index = createLineParticle(&blood, maxBlood, posX + (i * 2) + 1, posY + cutHei, posX + (i * 2) + 1, posY + cutHei, RED, 400);
            vspdBlood = 0.001 + ((float)(rand() % 500)) / 25000;
            blood[index].vspd2 = vspdBlood;
        }
    }

    for (int i = 0; i < 35; i++)
    {
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', BLACK);
        drawSpriteBufferColorMaster(-5, -5, &slashEffect[(i * 8 / 35) % 8], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawScreen();
        Sleep(sleepTime);
    }

    Sleep(sleepTime * 5);

    int grounded = 0;

    for (int i = 0; i < 300; i++)
    {

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        yEscorregaSpd += 0.005;
        xEscorregaSpd *= 0.99;
        // yEscorregaSpd *= 0.98;

        xEscorrega += xEscorregaSpd;
        if (!grounded)
        {
            yEscorrega += yEscorregaSpd;
        }
        int posX = galosBaseX[ordem2] + galosX[ordem2];
        int posY = galosBaseY[ordem2] + galosY[ordem2];

        if (yEscorrega + posY + cutHei > ALTURA - 6)
        {
            yEscorrega = ALTURA - 6 - posY - cutHei;
            yEscorregaSpd *= -0.6;

            int bloodStains = (rand() % 6) + 1;
            int off = 8;
            int xStart = posX - xEscorrega + off * 2;
            int yStart = posY + cutHei + yEscorrega;

            int escorregaSign = (yEscorregaSpd > 0) ? 1 : -1;
            if (escorregaSign * yEscorregaSpd < 0.1)
            {
                grounded = 1;
            }

            for (int j = 0; j < bloodStains; j++)
            {
                int xx = rand() % ((sprWid * 2) - (off * 2));
                int yy = rand() % 2;
                createLineParticle(&blood, maxBlood, xStart + xx, yStart + yy, xStart + xx + 2 - rand() % 5, yStart + yy, RED, 400);
            }
        }

        if (grounded)
        {
            if (rand() % 20 == 0)
            {
                int bloodStains = (rand() % 3) + 1;
                int off = 8;
                int xStart = posX - xEscorrega + off * 2;
                int yStart = posY + cutHei + yEscorrega;

                for (int j = 0; j < bloodStains; j++)
                {
                    int xx = rand() % ((sprWid * 2) - (off * 2));
                    int yy = rand() % 2;
                    createLineParticle(&blood, maxBlood, xStart + xx, yStart + yy, xStart + xx + 2 - rand() % 5, yStart + yy, RED, 400);
                }
            }
        }

        drawSpriteBufferColorMaster(posX, posY, sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, posY + cutHei + 1, LARGURA, ALTURA);
        updateLineParticles(&blood, maxBlood);
        drawLineParticles(&blood, maxBlood, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(posX - xEscorrega, posY + yEscorrega, sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, posY + yEscorrega + cutHei);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA);

        drawScreen();
        Sleep(sleepTime);
    }
    pause_song();
    textbackground(WHITE);
    desenharfatality();
}

void fatalityKalsa(int galo2)
{
    play_song(FATALITY_BACKGROUND);

    int xSombra = LARGURA / 2 - sombra.width / 2;
    int ySombra = ALTURA - 2 - sombra.height;

    int xKalsa = xSombra + 2;
    int yKalsa = ALTURA - 4 - galoSprites[GALO_DE_CALCA][0].height;

    int prevX = xKalsa;
    int prevY = yKalsa;

    textbackground(LIGHTGRAY);

    drawSpriteColor(xSombra, ySombra, &sombra);
    Sleep(1000);

    drawSpriteMonoColorScl(xKalsa, yKalsa, &galoSprites[GALO_DE_CALCA][0], 2, 1, BLACK);
    Sleep(2000);

    pause_song();
    play_song(TECLADO_LINDINHO);

    drawSpriteColorScl(xKalsa, yKalsa, &galoSprites[GALO_DE_CALCA][0], 2, 1);

    sleep(1);
    for (int cont = 0; cont < 2; cont++)
    {

        if (cont == 0)
        {
            for (int i = 0; i < 15; i++)
            {

                textbackground(i);

                drawSpriteMonoColorScl(prevX, prevY, &galoSprites[GALO_DE_CALCA][0], 2, 1, i);
                drawSpriteMonoColorScl(prevX - 3, prevY, &galoSprites[GALO_DE_CALCA][0], 2, 1, i);
                drawSpriteColorScl(xKalsa + i, yKalsa, &galoSprites[GALO_DE_CALCA][0], 2, 1);

                prevX = xKalsa + i;

                Sleep(200);
                system("cls");
            }
        }
        else
        {
            play_song(TECLADO_LINDINHO);
            for (int i = 0; i < 15; i++)
            {

                textbackground(i);

                drawSpriteMonoColorScl(prevX, prevY, &galoSprites[GALO_DE_CALCA][1], 2, 1, i);
                drawSpriteMonoColorScl(prevX + 3, prevY, &galoSprites[GALO_DE_CALCA][1], 2, 1, i);
                drawSpriteColorScl(xKalsa - i, yKalsa, &galoSprites[GALO_DE_CALCA][1], 2, 1);

                prevX = xKalsa - i;

                Sleep(200);
                system("cls");
            }
        }
    }

    float xscale;
    float yscale;

    int xgalo;
    int ygalo;

    pause_song();
    play_song(SCREAM);
    for (int i = -10; i < 30; i++)
    {

        xscale = 2 + 0.3 * i;
        yscale = 1 - 0.1 * i;

        ygalo = ALTURA / 2 - 4 - galoSprites[galo2][0].height * abs(yscale) / 2;
        xgalo = LARGURA / 2 - 4 - galoSprites[galo2][0].width * abs(xscale) / 2;
        drawSpriteColorScl(xgalo, ygalo, &galoSprites[galo2][0], xscale, yscale);

        Sleep(100);
        clrscr();
    }

    pause_song();
    desenharfatality();
}

void fatalityTenis(int galo2)
{

    textbackground(YELLOW);
    system("cls");

    play_song(FATALITY_BACKGROUND);

    int tenisx = 2;
    int tenisy = ALTURA - 4 - galoSprites[GALO_DE_TENIS][0].height;

    int galox = LARGURA / 2;
    int galoy = ALTURA - 4 - galoSprites[galo2][0].height;

    int ytenis = 1;
    int ymax = ALTURA - 4 - jordan.height;

    initScreen();
    drawRectScreen(1, 1, LARGURA, ALTURA, '@', YELLOW);

    drawSpriteBufferColorMaster(tenisx, tenisy, &galoSprites[GALO_DE_TENIS][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

    drawSpriteBufferColorMaster(galox, galoy, &galoSprites[galo2][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

    drawScreen();

    float scaley = 1;
    int yAdjust = 0;

    int i;

    for (i = -(ymax)-30; i < ymax + 1; i++)
    {

        if (i + jordan.height >= galoy + 5)
        {
            scaley /= 1.1;
            yAdjust = -galoSprites[galo2][0].height * (scaley - 1);
        }
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', YELLOW);

        drawSpriteBufferColorMaster(tenisx, tenisy, &galoSprites[GALO_DE_TENIS][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawSpriteBufferColorMaster(galox, galoy + yAdjust, &galoSprites[galo2][0], 2, scaley, 0, 0, 1, 1, LARGURA, ALTURA);

        drawSpriteBufferColorMaster(galox, i, &jordan, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawScreen();
        Sleep(100);
    }
    pause_song();
    play_song(PUMPED_UP_KICKS);

    for (int j = 0; j < 3; j++)
    {
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', YELLOW);
        drawSpriteBufferColorMaster(galox, i, &jordan, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(tenisx, tenisy + j, &galoSprites[GALO_DE_TENIS][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawScreen();
        Sleep(50);
    }
    for (int j = 0; j < 3; j++)
    {
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', YELLOW);
        drawSpriteBufferColorMaster(galox, i, &jordan, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(tenisx, tenisy - j, &galoSprites[GALO_DE_TENIS][1], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawScreen();
        Sleep(50);
    }

    int jump = 0;

    int columbineX = tenisx - galoSprites[GALO_DE_TENIS][0].width * 2;

    for (int k = 0; k < 120; k++)
    {

        jump = abs((k % 6) - 3);

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', YELLOW);
        drawSpriteBufferColorMaster(galox, i, &jordan, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawSpriteBufferColorMaster(tenisx + k, tenisy + jump, &galoSprites[GALO_DE_TENIS][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawSpriteBufferColorMaster(columbineX + k, tenisy + 2, &galoColumbine, 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawScreen();
        Sleep(50);
    }
    int newy = tenisy - galoSprites[GALO_DE_TENIS][1].height;

    for (int k = 120; k > -40; k--)
    {

        jump = abs((abs(k) % 6) - 3);

        drawRectScreen(1, 1, LARGURA, ALTURA, '@', YELLOW);
        drawSpriteBufferColorMaster(galox, i, &jordan, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawSpriteBufferColorMaster(tenisx + k, newy + jump, &galoSprites[GALO_DE_TENIS][1], 4, 2, 0, 0, 1, 1, LARGURA, ALTURA);

        drawSpriteBufferColorMaster(columbineX + k, tenisy + 2, &galoColumbine, 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);

        drawScreen();
        Sleep(50);
    }

    int fheight = sprFatality.height;
    int fwidth = sprFatality.width;

    int fx = width / 2 - sprFatality.width / 2;
    int fy = 4;

    drawSpriteMonoColorScl(fx, fy, &sprFatality, 1, 1, 5);

    for (int i = 0; i < 8; i++)
    {

        // desenhar sangue do f
        textcolor(RED);
        gotoxy(9, 10 + i / 2);
        printf("█");

        // desenhar sangue do t
        textcolor(RED);
        gotoxy(24, 7 + i);
        printf("█");
        gotoxy(24, 7 + i - 1);
        printf(" ");

        textcolor(RED);
        gotoxy(31, 5 + i / 4);
        printf("█");

        if (i < 5)
        {
            textcolor(RED);
            gotoxy(60, 10 + i);
            printf("█");
            gotoxy(60, 10 + i - 1);
            printf(" ");
        }

        // desenhar mais sangue ai
        gotoxy(42, 10 + i / 4);
        printf("█");

        gotoxy(65, 10 + i / 4);
        printf("█");

        gotoxy(70, 6 + i);
        printf("█");
        gotoxy(70, 6 + i - 1);
        printf(" ");

        gotoxy(39, 10 + i / 4);
        printf("█");

        if (i < 4)
        {
            gotoxy(54, 6 + i / 2);
            printf("█");
        }
        Sleep(200);
    }
    Sleep(2000);
    pause_song();
}

void fatalityDefault(int galo1,int galo2){

    int sprWid = galoSprites[galo2][1].width*2;
    int sprHei = galoSprites[galo2][1].height;

    int x = LARGURA/2 - sprWid/2 - sprWid/2;
    int y = ALTURA - 6 - sprHei;
    int x2 = LARGURA/2 - sprWid/2 + sprWid/2;
    int y2 = y;

    int backx = x;
    int backy = y;

    int x4;
    int y4;

    play_song(FATALITY_BACKGROUND);

    initScreen();

    drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);

    drawSpriteBufferColorMaster(x,y,&galoSprites[galo1][0],2,1,0,0,1,1,LARGURA,ALTURA);
    drawSpriteBufferColorMaster(x2,y2,&galoSprites[galo2][1],2,1,0,0,1,1,LARGURA,ALTURA);

    drawScreen();

    //ganhando impulso
    for(int i = 0; i < 4; i ++){
        drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
        drawSpriteBufferColorMaster(x - i,y,&galoSprites[galo1][0],2,1,0,0,1,1,LARGURA,ALTURA);
        drawSpriteBufferColorMaster(x2,y2,&galoSprites[galo2][1],2,1,0,0,1,1,LARGURA,ALTURA);

        drawScreen();
        Sleep(100);
    }
    //indo em direcao do inimigo enquanto ele corre
    int prevX = x - 4;
    int x3 = x2;

    for(int i = 0; i < 40; i ++)
    {
        drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
        backx = prevX;
        prevX += i;
        x3 = x2  + i;
        if(prevX >= x3)
        {
            break;
        }
        drawSpriteMonoColorBufferMaster(backx,y,&galoSprites[galo1][0],2,1,0,0,LIGHTBLUE,1,1,LARGURA,ALTURA);
        drawSpriteBufferColorMaster(prevX,y,&galoSprites[galo1][0],2,1,0,0,1,1,LARGURA,ALTURA);
        drawSpriteBufferColorMaster(x3,y,&galoSprites[galo2][0],2,1,0,0,1,1,LARGURA,ALTURA);
        drawScreen();

        Sleep(100);

    }
    pause_song();
    play_song(SCREAM);


    for(int i = 0; i < 10; i ++)
    {
        drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
        drawSpriteBufferColorMaster(prevX,y,&galoSprites[galo1][0],2,1,0,0,1,1,LARGURA,ALTURA);
        drawSpriteBufferColorMaster(x3 + i,y,&galoSprites[galo2][0],2,1,0,0,1,1,LARGURA,ALTURA);

        drawScreen();

    Sleep(100);
    }
    for(int i = 0; i < 24; i ++)
    {
        drawRectScreen(1,1,LARGURA,ALTURA,'@',LIGHTGRAY);
        drawSpriteBufferColorMaster(prevX,y,&galoSprites[galo1][i%2],2,1,0,0,1,1,LARGURA,ALTURA);
        drawSpriteBufferColorMaster(70 - i, i,&Blood,2,1,0,0,1,1,LARGURA,ALTURA);

        drawScreen();

    Sleep(100);
    }

    pause_song();
    clearScreen();

    desenharfatality();
}
void fatalityWhatsapp(int galo2)
{
    play_song(FATALITY_BACKGROUND);

    int sprWid = galoSprites[galo2][1].width * 2;
    int sprHei = galoSprites[galo2][1].height;

    int x = 2;
    int y = 8;
    int x2 = LARGURA - sprWid - 10;
    int y2 = 5;

    int bX = x + (19 * 2);
    int bY = y + 4;
    int prevX = bX;
    int prevY = bY;

    pause_song();
    for (int i = 0; i < 3; i++)
    {
        drawRectScreen(1, 1, LARGURA, ALTURA, '@', LIGHTGRAY);
        drawSpriteBufferColorMaster(x + i, y, &galoSprites[GALO_WHATSAPP][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        drawSpriteBufferColorMaster(x + i + (rand() % 5), (rand() % 4 + 1), &SongNote, 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        play_song(WHATSAPP_RINGTONE);
        drawSpriteBufferColorMaster(x2 + i, y2 + 6, &galoSprites[galo2][0], 2, 1, 0, 0, 1, 1, LARGURA, ALTURA);
        Sleep(2000);
        drawScreen();
    }
}

// DESENHANDO OS ATAQUES

void ataqueStatus(struct galo_status *galo1, struct galo_status *galo2, int ordem, int isBuff)
{
    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    int fundoSelecionado = configBatalha.fundo;

    int sleepTime = 50;

    int maxLines = 50;
    struct LineParticle lines[maxLines];

    initLineParticles(&lines, maxLines);

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int ordem2 = (ordem + 1) % 2;

    int lineColor;

    if (isBuff == 1)
    {
        lineColor = LIGHTBLUE;
    }
    else if (isBuff == 0)
    {
        lineColor = RED;
    }
    else
    {
        lineColor = LIGHTGREEN;
    }

    float gravity = (isBuff == 1) ? -0.1 : 0.1;

    int yLineStart = (isBuff == 1) ? ALTURA : -8;

    for (int i = 0; i < 50; i++)
    {

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        if (i < 20 && i % 2 == 0)
        {
            for (int j = 0; j < 1; j++)
            {

                int x1 = ((LARGURA / 2) * ordem) + rand() % (LARGURA / 2);
                int y1 = yLineStart + rand() % 2;
                int x2 = x1 + 1;
                int y2 = y1 + 2 + rand() % 2;
                int lineId = createLineParticle(&lines, maxLines, x1, y1, x2, y2, lineColor, 20 + rand() % 10);
                if (lineId != -1)
                {
                    lines[lineId].vacc = gravity;
                }
            }
        }

        updateLineParticles(&lines, maxLines);
        drawLineParticles(&lines, maxLines, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime / 2);
    }
}

void ataqueFisicoGenerico(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    float g1X = 0;
    float g1Y = 0;
    float g1XScl = 1;
    float g1YScl = 1;

    float g2X = 0;
    float g2Y = 0;
    float g2XScl = 1;
    float g2YScl = 1;

    int gId1 = galo1->id;
    int gId2 = galo2->id;

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int g1BaseX = 2;
    int g1BaseY = ALTURA - 5 - sprHei;

    int g2BaseX = LARGURA - (sprWid * 2);
    int g2BaseY = ALTURA - 5 - sprHei;

    struct Sprite *sprGalo1 = &galoSprites[galo1->id][0];
    struct Sprite *sprGalo2 = &galoSprites[galo2->id][1];

    float sprXOff = 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    int fundoSelecionado = configBatalha.fundo;

    int sleepTime = 40;

    clearScreen();
    caixaDeDialogo();

    if (ordem == 0)
    {
        for (int i = 0; i < 10; i++)
        {
            g1X += 3;

            drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g2BaseX + g2X, g2BaseY + g2Y, sprGalo2, g2XScl * 2, g2YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g1BaseX + g1X, g1BaseY + g1Y, sprGalo1, g1XScl * 2, g1YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            // desenhaBarraDeVida(galo1, galo2);

            drawScreen();
            Sleep(sleepTime);
        }

        Sleep(300);

        for (int i = 0; i < 15; i++)
        {
            g1X -= 2;
            g2X = -1 + ((i % 4) / 2) * 2;

            drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g2BaseX + g2X, g2BaseY + g2Y, sprGalo2, g2XScl * 2, g2YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g1BaseX + g1X, g1BaseY + g1Y, sprGalo1, g1XScl * 2, g1YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            // desenhaBarraDeVida(galo1, galo2);

            drawScreen();
            Sleep(sleepTime);
        }
    }
    else
    {
        for (int i = 0; i < 10; i++)
        {
            g2X -= 3;

            drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g2BaseX + g2X, g2BaseY + g2Y, sprGalo2, g2XScl * 2, g2YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g1BaseX + g1X, g1BaseY + g1Y, sprGalo1, g1XScl * 2, g1YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            // desenhaBarraDeVida(galo1, galo2);
            // caixaDeDialogo();
            drawScreen();
            Sleep(sleepTime);
        }

        Sleep(300);

        for (int i = 0; i < 15; i++)
        {
            g2X += 2;
            g1X = -1 + ((i % 4) / 2) * 2;

            drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g2BaseX + g2X, g2BaseY + g2Y, sprGalo2, g2XScl * 2, g2YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            drawSpriteBufferColorMaster(g1BaseX + g1X, g1BaseY + g1Y, sprGalo1, g1XScl * 2, g1YScl, hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            // desenhaBarraDeVida(galo1, galo2);
            // caixaDeDialogo();
            drawScreen();
            Sleep(sleepTime);
        }
    }
}

void __ervaDaninhaAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{
    ataqueStatus(galo1, galo2, ordem, 0);
    Sleep(100);
    ataqueStatus(galo1, galo2, ordem, 1);
    Sleep(40);
}

void __gingadoAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    struct Sprite *sprAtk = &atkSprites[3];

    float sprXOff = 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int ordem2 = (ordem + 1) % 2;

    for (int i = 0; i < 8; i++)
    {

        galosX[ordem] += ((i % 2) * 2) - 1;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 10);
    }

    Sleep(20);

    ataqueStatus(galo1, galo2, ordem, 1);
    Sleep(40);
}

void __olharMalignoAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    int fundoSelecionado = configBatalha.fundo;

    int ordem2 = (ordem + 1) % 2;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();

    int yAdjust = 4;

    for (int i = 0; i < 10; i++)
    {

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        int time = i;
        drawRectScreen(1, 1, LARGURA, time - yAdjust, '@', BLACK);
        drawRectScreen(1, ALTURA - (time + yAdjust), LARGURA, time + yAdjust + 1, '@', BLACK);
        // drawRectScreen(1, ALTURA - 1, LARGURA, 1, '@', RED);

        drawScreen();
        Sleep(100);
    }

    Sleep(400);

    for (int i = 0; i < 5; i++)
    {

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        int time = 10 - i * 2;
        drawRectScreen(1, 1, LARGURA, time - yAdjust, '@', BLACK);
        drawRectScreen(1, ALTURA - (time + yAdjust), LARGURA, time + yAdjust, '@', BLACK);

        drawScreen();
        Sleep(50);
    }

    ataqueStatus(galo1, galo2, (ordem + 1) % 2, 0);
    Sleep(40);
}

void __surfarAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    struct Sprite *sprAtk = &atkSprites[3];

    float sprXOff = 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int atkSprWid = (sprAtk->width) * 2;
    int atkSprHei = sprAtk->height;

    int sign = (ordem == 0) ? 1 : -1;

    float atkScl = 2;

    int atkBaseX = (LARGURA / 2) - sign * ((LARGURA + (atkSprWid * atkScl)) / 2);
    int atkBaseY = ALTURA - 6;

    int atkX = 0;
    int atkY = 0;

    int atkAddX = 0;
    int atkAddY = 1;

    int ordem2 = (ordem + 1) % 2;

    for (int i = 0; i < 60; i++)
    {

        atkAddX += sign * 2;

        atkX = atkAddX - ((atkSprWid * atkScl) / 2) + atkSprWid * atkScl * ordem;
        atkY = atkAddY - (atkSprHei * atkScl);

        atkScl += (0.025 / 2);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        if (i > 30)
        {
            galosX[ordem2] += sign * 2;
        }

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * atkScl * sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    float voltaX = 0;
    float galoPosSave = galosX[ordem2];

    for (int i = 0; i < 16; i++)
    {

        atkAddX += sign * 2;

        atkX = atkAddX - ((atkSprWid * atkScl) / 2) + atkSprWid * atkScl * ordem;
        atkY = atkAddY - (atkSprHei * atkScl);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        voltaX += sign * 3.5;

        galosX[ordem2] = (int)(galoPosSave - voltaX);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * atkScl * sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    Sleep(sleepTime * 10);
}

void __voarAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    // struct Sprite *sprAtk = &atkSprites[5];

    float sprXOff = (ordem == 0) ? sprWid - 5 : 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    float sign = (ordem == 0) ? 1 : -1;

    int ordem2 = (ordem + 1) % 2;

    float flySpd = 3;

    for (int i = 0; i < 64; i++)
    {

        // galosX[ordem2] = (rand()%((int)shakePower))-(shakePower/2);

        if (i < 24)
        {
            galosY[ordem] += -1;
        }
        else
        {
            if (flySpd > 0)
            {
                flySpd -= 0.25;
            }
            galosY[ordem] += flySpd;
            galosX[ordem] += sign * 2 + sign * (6 - (flySpd * 2));
        }

        if (i > 32)
        {
            galosX[ordem2] += sign * 3;
        }

        // shakePower += 0.2;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosY[ordem2] = 0;
    galosX[ordem2] = sign * 40;
    galosY[ordem] = -sprHei - 10;
    galosX[ordem] = -sign * 10;
    Sleep(sleepTime * 6);

    for (int i = 0; i < sprHei + 10; i++)
    {

        // galosY[ordem2] -= 1;
        galosY[ordem] += 1;

        if (i > sprHei - 10)
        {
            galosX[ordem] += sign / 2;
            galosX[ordem2] -= sign * 2;
        }

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 10);
}

void __esporaGiratoriaAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem){


    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;


    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];


    sprGalos[0] =  &galoSprites[galo1->id][0];
    sprGalos[1] =  &galoSprites[galo2->id][1];


    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;




    //struct Sprite *sprAtk = &atkSprites[5];




    float sprXOff = (ordem == 0) ? 5 : sprWid-5;


    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;


    float sign = (ordem == 0) ? 1:-1;


    int ordem2 = (ordem+1)%2;

    float jumpY = 3;
    float jumpPower = 2;
    float vspd = -jumpPower;
    float hspd = 3*sign;
    float gravity = 0.12;

    float turnTimer = 0;

    int direction = 1;

    int xAdjust = 0;

    for(int i = 0; i < 80; i++){

        turnTimer += min((float)(i*i)/6400, 1);
        if(turnTimer > 1){
            turnTimer = 0;
            direction *= -1;
        }


        xAdjust = -((direction-1)/2)*(sprXOff)*4;


        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA-6);


        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2]*2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);


        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem] + xAdjust, galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem]*2*direction, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);

        drawScreen();
        Sleep(sleepTime);
    }


    for(int i = 0; i < 64; i++){

        turnTimer++;
        if(turnTimer  > 1){
            turnTimer = 0;
            direction *= -1;
        }


        vspd += gravity;



        galosY[ordem] =  min(galosY[ordem] + vspd, 0);
        galosX[ordem] += hspd;


        if(i > 20){
            galosX[ordem2] += sign*6;
        }

       // shakePower += 0.2;


        xAdjust = -((direction-1)/2)*(sprXOff)*4;


        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA-6);


        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2]*2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);


        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem] + xAdjust, galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem]*2*direction, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);

        drawScreen();
        Sleep(sleepTime);
    }

    galosY[ordem]= 0;

    direction = 1;

    for(int i = 0; i < 64; i++){



        float invI = 64-i;
        turnTimer += min((float)(invI*invI)/4096, 1);
        if(turnTimer > 1){
            turnTimer = 0;
            direction *= -1;
        }


        //galosY[ordem] += vspd;
        galosX[ordem] -= hspd;


        //galosX[ordem2] = (rand()%((int)shakePower))-(shakePower/2);

        /*
        if(i < 24){
            galosY[ordem] += -1;
        } else {
            if(flySpd > 0){
                flySpd -= 0.25;
            }
            galosY[ordem] += flySpd;
            galosX[ordem] += sign*2 + sign*(6-(flySpd*2));
        }
        */


        if(i > 20){
            galosX[ordem2] -= sign*6;
        }


       // shakePower += 0.2;


        xAdjust = -((direction-1)/2)*(sprXOff)*4;


        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA-6);


        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2]*2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);


        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem] + xAdjust, galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem]*2*direction, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);

        drawScreen();
        Sleep(sleepTime);
    }



    /*
    galosY[ordem2] = 0;
    galosX[ordem2] = sign*40;
    galosY[ordem] = -sprHei - 10;
    galosX[ordem] = -sign*10;
    Sleep(sleepTime*6);

    for(int i = 0; i < sprHei+10; i++){


        //galosY[ordem2] -= 1;
        galosY[ordem] += 1;

        if(i > sprHei-10){
            galosX[ordem] += sign/2;
            galosX[ordem2] -= sign*2;
        }


        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA-6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2]*2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem]*2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);

        drawScreen();
        Sleep(sleepTime*2);
    }



    */


    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA-6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2]*2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem]*2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA-6);



    drawScreen();

    Sleep(sleepTime*10);

}




void __sangueAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    // struct Sprite *sprAtk = &atkSprites[5];

    float sprXOff = (ordem == 0) ? sprWid - 5 : 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int sign = (ordem == 0) ? 1 : -1;

    int ordem2 = (ordem + 1) % 2;

    int maxParticles = 80;
    struct LineParticle particles[maxParticles];

    initLineParticles(&particles, maxParticles);

    for (int i = 0; i < maxParticles; i++)
    {
        int index = createLineParticle(&particles, maxParticles, i + 1, -1, i + 1, -1, RED, 300);
        if (index != -1)
        {
            particles[index].vspd = 0.02 + ((float)(rand() % 100)) / 600;
            particles[index].damp = 1;
        }
    }

    for (int i = 0; i < 300; i++)
    {

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        updateLineParticles(&particles, maxParticles);
        drawLineParticles(&particles, maxParticles, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 10);
}

void __thanosAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    // struct Sprite *sprAtk = &atkSprites[5];

    float sprXOff = (ordem == 0) ? sprWid - 5 : 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int sign = (ordem == 0) ? 1 : -1;

    int ordem2 = (ordem + 1) % 2;

    int shakeX = 0;
    int shakeY = 0;

    float shakePower = 1;
    int exploded = 0;

    int maxParticles = 700;
    struct LineParticle particles[maxParticles];

    initLineParticles(&particles, maxParticles);

    for (int i = 0; i < 130; i++)
    {

        galosX[ordem2] = (rand() % ((int)shakePower)) - (shakePower / 2);
        galosY[ordem2] = ((rand() % ((int)shakePower)) - (shakePower / 2)) / 2;

        shakePower += 0.2;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        if (!exploded)
        {
            drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            if (i > 70)
            {
                exploded = 1;
                spriteToLineParticles(&particles, maxParticles, sprGalos[ordem2], galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2]);
                explosionLineParticle(&particles, maxParticles, galosBaseX[ordem2] + galosX[ordem2] + (sprXOff * 2), galosBaseY[ordem2] + galosY[ordem2] + (sprHei / 2));
            }
        }
        else
        {
            updateLineParticles(&particles, maxParticles);
            drawLineParticles(&particles, maxParticles, 1, 1, LARGURA, ALTURA - 6);
        }

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosY[ordem2] = sprHei + 10;
    galosX[ordem2] = 0;

    for (int i = 0; i < sprHei + 10; i++)
    {

        galosY[ordem2] -= 1;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 10);
}

void __atirarAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    int galosId[2];

    galosId[0] = galo1->id;
    galosId[1] = galo2->id;

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    struct Sprite *sprAtk = &sprGun;

    float sprXOff = 8;
    float sprYOff = 8;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int atkSprWid = (sprAtk->width) * 2;
    int atkSprHei = sprAtk->height;

    int sign = (ordem == 0) ? 1 : -1;

    float atkScl = 1;

    int pipeOutOffset = 12;

    int atkBaseX = galosBaseX[ordem] + ordem * (atkSprWid);
    int atkBaseY = galosBaseY[ordem];

    int atkX = 0;
    int atkY = -40;

    float atkPipeBaseX = -sign * atkSprWid + ordem * (LARGURA);
    float atkPipeBaseY = ALTURA - 5;
    float atkPipeX = 0;
    float atkPipeY = 0;

    float pipeRiseSpd = 1.2;

    int ordem2 = (ordem + 1) % 2;

    int partMax = 150;
    struct LineParticle part[partMax];
    initLineParticles(&part, partMax);

    float shakeIntensity = 2;

    if (galosId[ordem] != GALO_SNIPER)
    {
        for (int i = 0; i < 40; i++)
        {

            atkY++;
            drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

            drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

            drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

            drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * sign, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

            drawScreen();
            Sleep(sleepTime * 2);
        }
    }

    for (int i = 0; i < 80; i++)
    {

        // shakeIntensity *= 0.9;

        int shake = shakeIntensity;

        galosX[ordem] = 0;
        if (shake != 0)
        {
            galosX[ordem] = (rand() % (shake)) - (shakeIntensity / 2);
        }

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        updateLineParticles(&part, partMax);
        drawLineParticles(&part, partMax, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * sign, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        if (i % 2 == 0)
        {
            int xx = galosBaseX[ordem] + galosX[ordem] + sprWid * ordem2;
            int yy = galosBaseY[ordem] + galosY[ordem] + (sprHei / 2) + (rand() % 2) + 1;
            int index = createLineParticle(&part, partMax, xx, yy, xx - sign * 2, yy, BLACK, 40);
            if (index != -1)
            {
                part[index].hspd = sign * 6;
                part[index].hspd2 = sign * 6;
                float radiate = ((float)(rand() % 100) - 50) / 10000;
                part[index].vspd = radiate;
                part[index].vspd2 = radiate;
                part[index].damp = 1;
            }
        }

        if (rand() % 2 == 0 && i % 2 == 1)
        {
            int bloodShot = 3 + rand() % 10;
            for (int j = 0; j < bloodShot; j++)
            {
                int xx = galosBaseX[ordem2] + galosX[ordem2] + (ordem * sprWid * 2) + (sign * (sprWid));
                int yy = galosBaseY[ordem2] + galosY[ordem2] + (sprHei / 1.5) + (rand() % 2);
                int index = createLineParticle(&part, partMax, xx, yy, xx - sign, yy, RED, 40);
                if (index != -1)
                {
                    float randHspd = sign * (1 + ((float)(rand() % 200) / 100));
                    part[index].hspd = randHspd;
                    part[index].hspd2 = randHspd;
                    float randVspd = ((float)(rand() % 100) - 50) / 25;
                    part[index].vspd = randVspd;
                    part[index].vspd2 = randVspd;

                    part[index].vacc = 0.2;
                    part[index].damp = 0.98;
                }
            }
        }

        // drawSpriteBufferColorMaster(atkPipeX+atkPipeBaseX, atkPipeY+atkPipeBaseY, sprAtk, 2*sign, 1, 0, 0, 1, 1, LARGURA, ALTURA-6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    if (galosId[ordem] != GALO_SNIPER)
    {
        for (int i = 0; i < 40; i++)
        {

            atkY--;
            drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

            drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

            drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

            drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * sign, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

            drawScreen();
            Sleep(sleepTime * 2);
        }
    }

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 10);
}

void __jogarOvoAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    int galosId[2];

    galosId[0] = galo1->id;
    galosId[1] = galo2->id;

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    struct Sprite *sprAtk = &atkSprites[6];

    float sprXOff = 8;
    float sprYOff = 8;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int atkSprWid = (sprAtk->width) * 2;
    int atkSprHei = sprAtk->height;

    int sign = (ordem == 0) ? 1 : -1;

    float atkScl = 1;

    int pipeOutOffset = 12;

    int atkBaseX = (LARGURA / 2) - sign * (-2 * pipeOutOffset + (LARGURA + (atkSprWid * atkScl)) / 2) - sign * 5;
    int atkBaseY = ALTURA - 5 - pipeOutOffset;

    int atkX = 0;
    int atkY = 0;

    float atkAddX = 0;
    float atkAddY = 0;

    float atkPipeBaseX = -sign * atkSprWid + ordem * (LARGURA);
    float atkPipeBaseY = ALTURA - 5;
    float atkPipeX = 0;
    float atkPipeY = 0;

    float pipeRiseSpd = 1.2;

    int ordem2 = (ordem + 1) % 2;

    int eggsMax = 20;
    struct SpriteParticle eggs[eggsMax];
    initSpriteParticles(&eggs, eggsMax);

    int partMax = 150;
    struct LineParticle part[partMax];
    initLineParticles(&part, partMax);

    float shakeIntensity = 1;

    for (int i = 0; i < 80; i++)
    {

        if (i < 10)
        {
            atkPipeX += sign * pipeRiseSpd * 2;
            atkPipeY -= pipeRiseSpd;
        }
        else if (i > 69)
        {
            atkPipeX -= sign * pipeRiseSpd * 2;
            atkPipeY += pipeRiseSpd;
        }

        if (i > 10 && i < 50 && i % 5 == 1)
        {

            struct Sprite *sprRand = (rand() % 3 == 0) ? &atkSprites[1] : &atkSpritesSmall[0];
            int index = createSpriteParticle(&eggs, eggsMax, atkBaseX, atkBaseY, 2 * atkScl, atkScl, sprRand, 40);
            if (index != -1)
            {
                float angVar = (PI / 24);
                float angle = (PI / 6) + (((float)((rand() % 100) - 50)) / 50) * angVar;
                float spd = ((float)(rand() % 20) / 10) + 3.5;
                eggs[index].hspd = sign * cos(angle) * spd;
                eggs[index].vspd = -sin(angle) * spd;
                eggs[index].vacc = 0.2;
                eggs[index].sprXOff = 0;
                eggs[index].sprYOff = 0;
            }
        }

        shakeIntensity *= 0.9;

        int shake = shakeIntensity;

        galosX[ordem2] = 0;
        if (shake != 0)
        {
            galosX[ordem2] = (rand() % (shake)) - (shakeIntensity / 2);
        }

        // drawSpriteBufferColorMaster(atkX+atkBaseX, atkY+atkBaseY, sprAtk, 2*atkScl*sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA-6);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        for (int j = 0; j < eggsMax; j++)
        {
            if (eggs[j].active)
            {
                int ww = (eggs[j].spr->width);
                int hh = eggs[j].spr->height / 2;
                int xx = eggs[j].x + ww / 2;
                int yy = eggs[j].y + hh / 2;

                // drawRectScreen(xx, yy, ww, hh, '@', GREEN);

                // int gHei = galoMedidas[galosId[ordem2]][ordem2][0];
                // nt gWid = galoMedidas[galosId[ordem2]][ordem2][1]*2;
                int gHei = sprHei / 1.5;
                int gWid = sprWid / 1.5;
                // int gX = galosBaseX[ordem2] + galoMedidas[galosId[ordem2]][ordem2][2] - gWid;
                // int gY = galosBaseY[ordem2] + sprHei - gHei;
                int gX = galosBaseX[ordem2] + (sprWid * ordem2) + gWid / 4;
                int gY = galosBaseY[ordem2] + sprHei - gHei;

                // drawRectScreen(gX, gY, gWid, gHei, '@', RED);

                if (rectCollision(xx, yy, ww, hh, gX, gY, gWid, gHei))
                {
                    eggs[j].active = 0;
                    shakeIntensity = min(shakeIntensity + 3, 10);
                    spriteToLineParticles(&part, partMax, eggs[j].spr, xx, yy, 1, 0.5);
                    explosionLineParticle(&part, partMax, xx + ww / 2, yy + hh / 2);
                }
            }
        }

        // int gHei = galoMedidas[galosId[ordem2]][ordem2][0];
        // int gWid = galoMedidas[galosId[ordem2]][ordem2][1]*2;
        // int gX = galosBaseX[ordem2] + galoMedidas[galosId[ordem2]][ordem2][2] - gWid;
        //  int gY = sprHei - gHei;

        // drawRectScreen(galosBaseX[ordem2] + gX, galosBaseY[ordem2] + gY, gWid, gHei, '@', RED);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        updateSpriteParticles(&eggs, eggsMax);
        drawSpriteParticles(&eggs, eggsMax, 1, 1, LARGURA, ALTURA - 6);
        updateLineParticles(&part, partMax);
        drawLineParticles(&part, partMax, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(atkPipeX + atkPipeBaseX, atkPipeY + atkPipeBaseY, sprAtk, 2 * sign, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 10);
}

void __almaPenadaAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    struct Sprite *sprAtk = &atkSprites[5];

    float sprXOff = (ordem == 0) ? sprWid - 5 : 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int atkSprWid = (sprAtk->width) * 2;
    int atkSprHei = sprAtk->height;

    int sign = (ordem == 0) ? 1 : -1;

    float atkScl = 1;

    int atkBaseX = (LARGURA / 2) - sign * ((LARGURA + (atkSprWid * atkScl)) / 2);
    int atkBaseY = ALTURA - 6;

    int atkX = 0;
    int atkY = 0;

    float atkAddX = 0;
    float atkAddY = 0;

    int ordem2 = (ordem + 1) % 2;

    float vacc = 0.1;
    float vspd = 0;

    int haunted = 0;

    float sclChange = 0.0625;
    float sclState = 0;
    float sclSpd = 0;

    for (int i = 0; i < 80; i++)
    {

        if (i < 38)
        {
            atkAddX += sign * 2;

            if (atkAddY > 2)
            {
                atkAddY = 2;
                vspd = 0;
                vacc *= -1;
            }
            else if (atkAddY < -2)
            {
                atkAddY = -2;
                vspd = 0;
                vacc *= -2;
            }

            vspd += vacc;
            atkAddY += vspd;
            // atkScl += 0.01;
        }
        else
        {
            haunted = 1;
            atkAddY -= 1;
            // atkAddX += sign*2;
        }

        atkX = atkAddX - ((atkSprWid * atkScl) / 2) + atkSprWid * atkScl * ordem;
        atkY = atkAddY - (atkSprHei * atkScl) - i / 7;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        if (i > 38)
        {

            sclState += sclChange;
            sclState = max(min(sclState, 1.8), -0.8);
            galosYScl[ordem2] = 1 + sclState;
            galosXScl[ordem2] = 1 - (sclState / 2);
        }

        galosY[ordem2] = -sprHei * (galosYScl[ordem2] - 1);
        galosX[ordem2] = -2 * (sprXOff) * (galosXScl[ordem2] - 1);

        if (haunted == 0)
        {
            drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        }
        else
        {
            drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], 1, 15, 1, 1, LARGURA, ALTURA - 6);
        }

        drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * atkScl * sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    // float voltaY = 0;
    // float galoPosSave = galosY[ordem2];

    for (int i = 0; i < 50; i++)
    {

        // atkAddX += sign*2;
        // atkAddY -= 1;

        sclSpd -= (sclState) / 4;
        sclSpd *= 0.97;
        sclState += sclSpd;
        sclState = max(min(sclState, 2 - ((float)i / 25)), -0.8 + (0.8 * (float)i / 50));

        galosYScl[ordem2] = 1 + sclState;
        galosXScl[ordem2] = 1 - (sclState / 2);

        galosY[ordem2] = -sprHei * (galosYScl[ordem2] - 1);
        galosX[ordem2] = -2 * (sprXOff) * (galosXScl[ordem2] - 1);

        // atkX = atkAddX - ((atkSprWid*atkScl)/2) + atkSprWid*atkScl*ordem;
        // atkY = atkAddY - (atkSprHei*atkScl);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        // voltaY -= 3.5;

        // galosY[ordem2] = (int)(galoPosSave-voltaY);

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(atkX + atkBaseX, atkY + atkBaseY, sprAtk, 2 * atkScl * sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 10);
}

void __cantarAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    struct Sprite *sprAtk = &atkSprites[0];

    float sprXOff = (ordem == 0) ? sprWid - 5 : 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    int atkSprWid = (sprAtk->width) * 2;
    int atkSprHei = sprAtk->height;

    int sign = (ordem == 0) ? 1 : -1;

    float atkScl = 1;

    int atkBaseX = (LARGURA / 2) - sign * ((LARGURA + (atkSprWid * atkScl)) / 2);
    int atkBaseY = ALTURA - 6;

    int atkX = 0;
    int atkY = 0;

    float atkAddX = 0;
    float atkAddY = 0;

    int ordem2 = (ordem + 1) % 2;

    int xShake = 0;

    for (int i = 0; i < 120; i++)
    {

        atkAddX += sign * 2;

        atkX = atkAddX - ((atkSprWid * atkScl) / 2) + atkSprWid * atkScl * ordem;
        atkY = atkAddY - (atkSprHei * atkScl);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

        galosY[ordem2] = -sprHei * (galosYScl[ordem2] - 1);
        galosX[ordem2] = -2 * (sprXOff) * (galosXScl[ordem2] - 1) + xShake;

        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        for (int j = 0; j < 5; j++)
        {
            int hoverY = sinAprox[(i * 8 + j * 90) % 360] * 3;
            drawSpriteBufferColorMaster(atkX + atkBaseX - sign * j * atkSprWid, atkY + atkBaseY + hoverY, sprAtk, 2 * atkScl * sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        }

        if (i > 30)
        {
            float waveWid = sprWaveEffect.width * 2;
            drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2] + (sprWid * 2 - waveWid) * ordem2 + sign * waveWid / 5, galosBaseY[ordem2] + galosY[ordem2], &sprWaveEffect, galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
            xShake = ((i % 4) - 2) / 2;
        }

        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime);
    }

    // float voltaY = 0;
    // float galoPosSave = galosY[ordem2];

    galosYScl[ordem2] = 1;
    galosXScl[ordem2] = 1;

    galosY[ordem2] = 0;
    galosX[ordem2] = 0;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);

    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();

    Sleep(sleepTime * 2);

    ataqueStatus(galo1, galo2, ordem2, 0);
}

void __penaDeMorteAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{
    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    float sprXOff = 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    int yAdd = 0;
    int xAdd = 0;

    struct Sprite *sprAtk = &atkSprites[2];

    int atkSprWid = (sprAtk->width) * 2;
    int atkSprHei = sprAtk->height;

    int sign = (ordem == 0) ? 1 : -1;

    float atkScl = 1;

    int atkBaseX = (LARGURA / 2) + sign * ((LARGURA - 30) / 2);
    int atkBaseY = -atkSprHei;

    int atkX = 0;
    int atkY = 0;

    int atkAddX = 0;
    int atkAddY = 0;

    int ordem2 = (ordem + 1) % 2;

    float atkVspd = 0;

    int ground = 0;

    int bloodPartMax = 100;
    struct LineParticle blood[bloodPartMax];

    initLineParticles(&blood, bloodPartMax);

    const float pi = 3.1415;

    for (int i = 0; i < 50; i++)
    {

        if (ground)
        {
            atkVspd += 0.2;
            updateLineParticles(&blood, bloodPartMax);
        }
        else
        {
            if (atkY < ALTURA - 6 - atkSprHei)
            {
                atkVspd += 0.25;
            }
            else
            {
                atkY = ALTURA - 6 - atkSprHei;
                atkVspd *= -0.1;
                ground = 1;

                for (int j = 0; j < bloodPartMax; j++)
                {
                    int x = atkBaseX + ((rand() % 10) - 5);
                    int y = ALTURA - 7 + rand() % 3;
                    float spdRatio = 1 / ((((float)(rand() % 10)) / 120) + 1);
                    float angle = 2 * pi * (((float)(rand() % 180)) / 360);
                    float spd = (rand() % 2) + 3;
                    float hspd = cos(angle) * spd;
                    float vspd = -sin(angle) * spd;
                    float hspd2 = cos(angle) * spd * spdRatio;
                    float vspd2 = -sin(angle) * spd * spdRatio;

                    int ind = createLineParticle(&blood, bloodPartMax, x, y, x, y, RED, 20 + (rand() % 20));
                    blood[ind].hspd = hspd;
                    blood[ind].vspd = vspd;
                    blood[ind].hspd2 = hspd;
                    blood[ind].vspd2 = vspd;
                    blood[ind].vacc = 0.2;
                    blood[ind].damp = 0.9;
                }
            }
        }

        atkAddY += atkVspd;

        atkX = atkBaseX + atkAddX - ((atkSprWid * atkScl) / 2) + atkSprWid * atkScl * ordem;
        atkY = atkBaseY + atkAddY - (atkSprHei * atkScl);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(atkX, atkY, sprAtk, 2 * atkScl * sign, atkScl, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawLineParticles(&blood, bloodPartMax, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 2);
    }

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();
    Sleep(sleepTime * 3);
}

void __pisotearAnim(struct galo_status *galo1, struct galo_status *galo2, int ordem)
{

    int sprWid = galoSprites[galo1->id][0].width;
    int sprHei = galoSprites[galo1->id][0].height;

    int galosX[2];
    int galosY[2];
    float galosXScl[2];
    float galosYScl[2];
    int galosBaseX[2];
    int galosBaseY[2];
    struct Sprite *sprGalos[2];

    sprGalos[0] = &galoSprites[galo1->id][0];
    sprGalos[1] = &galoSprites[galo2->id][1];

    galosX[0] = 0;
    galosY[0] = 0;
    galosXScl[0] = 1;
    galosYScl[0] = 1;

    galosX[1] = 0;
    galosY[1] = 0;
    galosXScl[1] = 1;
    galosYScl[1] = 1;

    galosBaseX[0] = 2;
    galosBaseY[0] = ALTURA - 5 - sprHei;

    galosBaseX[1] = LARGURA - (sprWid * 2);
    galosBaseY[1] = ALTURA - 5 - sprHei;

    float sprXOff = (ordem == 0) ? 5 : sprWid - 5;

    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    clearScreen();
    caixaDeDialogo();

    int ordem2 = (ordem + 1) % 2;

    int sign = (ordem == 0) ? 1 : -1;

    int sleepTime = 20;
    int fundoSelecionado = configBatalha.fundo;

    // Lembrando que a escala X é 2 naturalmente
    // Efeito de crescer do Mario
    int yAdd = 0;
    int xAdd = 0;

    for (int i = 0; i < 6; i++)
    {
        galosXScl[ordem] = 1 + ((float)(i % 3) / 2);
        galosYScl[ordem] = galosXScl[ordem];

        galosY[ordem] = -sprHei * (galosYScl[ordem] - 1);
        galosX[ordem] = -2 * (sprXOff) * (galosXScl[ordem] - 1);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 5);
    }

    galosXScl[ordem] = 2;
    galosYScl[ordem] = 2;

    Sleep(sleepTime * 10);

    // Pulo
    for (int i = 0; i < 8; i++)
    {

        if (i == 0)
        {
            galosYScl[ordem] = 1;
        }
        else if (i == 1)
        {
            Sleep(sleepTime * 10);
        }
        else
        {
            galosYScl[ordem] = 2;
            yAdd -= 4;
            xAdd += 1 * sign;
        }

        int yAdjust = -sprHei * (galosYScl[ordem] - 1);
        int xAdjust = -2 * (sprXOff) * (galosXScl[ordem] - 1);

        galosY[ordem] = yAdjust + yAdd;
        galosX[ordem] = xAdjust + xAdd;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime);
    }

    Sleep(sleepTime * 20);

    float baseDif = galosBaseX[ordem2] - galosBaseX[ordem];
    yAdd = -32;
    xAdd = baseDif;

    // Queda

    for (int i = 0; i < 8; i++)
    {

        yAdd += 4;
        xAdd += 1 * sign;

        int yAdjust = -sprHei * (galosYScl[ordem] - 1);
        int xAdjust = -2 * (sprXOff) * (galosXScl[ordem] - 1);

        galosY[ordem] = yAdjust + yAdd;
        galosX[ordem] = xAdjust + xAdd;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime);
    }

    yAdd = 0;

    baseDif += 8 * sign;
    xAdd = baseDif;
    galosYScl[ordem2] = 0.5;
    galosY[ordem2] = -sprHei * (galosYScl[ordem2] - 1);

    Sleep(sleepTime * 20);

    // Volta
    for (int i = 0; i < 8; i++)
    {

        xAdd -= (baseDif) / 8;

        int yAdjust = -sprHei * (galosYScl[ordem] - 1);
        int xAdjust = -2 * (sprXOff) * (galosXScl[ordem] - 1);

        galosY[ordem] = yAdjust + yAdd;
        galosX[ordem] = xAdjust + xAdd;

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime);
    }

    for (int i = 0; i < 6; i++)
    {
        galosXScl[ordem] = 1 + ((float)((5 - i) % 3) / 2);
        galosYScl[ordem] = galosXScl[ordem];

        galosY[ordem] = -sprHei * (galosYScl[ordem] - 1);
        galosX[ordem] = -2 * (sprXOff) * (galosXScl[ordem] - 1);

        drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
        drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

        drawScreen();
        Sleep(sleepTime * 5);
    }

    Sleep(sleepTime * 30);

    galosYScl[ordem] = 1;
    galosXScl[ordem] = 1;
    galosYScl[ordem2] = 1;

    galosY[ordem2] = -sprHei * (galosYScl[ordem2] - 1);

    int yAdjust = -sprHei * (galosYScl[ordem] - 1);
    int xAdjust = -2 * (sprXOff) * (galosXScl[ordem] - 1);

    galosY[ordem] = yAdjust + yAdd;
    galosX[ordem] = xAdjust + xAdd;

    drawSpriteBufferColorMaster(1, 1, &fundos[fundoSelecionado], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem2] + galosX[ordem2], galosBaseY[ordem2] + galosY[ordem2], sprGalos[ordem2], galosXScl[ordem2] * 2, galosYScl[ordem2], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);
    drawSpriteBufferColorMaster(galosBaseX[ordem] + galosX[ordem], galosBaseY[ordem] + galosY[ordem], sprGalos[ordem], galosXScl[ordem] * 2, galosYScl[ordem], hasBorder, borderColor, 1, 1, LARGURA, ALTURA - 6);

    drawScreen();
    Sleep(sleepTime * 30);
}

void (*animacoes[])(struct galo_status *atacante, struct galo_status *alvo, int ordem) = {
    ataqueFisicoGenerico,  // bater asas
    ataqueFisicoGenerico,  // poeira
    ataqueFisicoGenerico,  // bicada
    __cantarAnim,          // Cantar
    ataqueFisicoGenerico,  // arranhar
    __voarAnim,            // voar
    __atirarAnim,          // atirar
    ataqueFisicoGenerico,  // bidoDeAco
    ataqueFisicoGenerico,  // furia
    __olharMalignoAnim,    // olharMaligno
    __jogarOvoAnim,        // jogar_ovo
    ataqueFisicoGenerico,  // Ataque de asa
    ataqueFisicoGenerico,  // bico_broca
    ataqueFisicoGenerico,  // sky_atack
    ataqueFisicoGenerico,  // aero egg
    __gingadoAnim,         // gingado
    ataqueFisicoGenerico,  // au_da_capoeira
    __esporaGiratoriaAnim, // Espora_giratoria
    ataqueFisicoGenerico,  // cortar
    ataqueFisicoGenerico,  // picar
    ataqueFisicoGenerico,  // esguicho
    ataqueFisicoGenerico,  // cloaca de ferro
    __pisotearAnim,        // pisotear
    ataqueFisicoGenerico,  // chicote_de_cinto
    __penaDeMorteAnim,     // pena_de_morte
    ataqueFisicoGenerico,  // vingarde
    __almaPenadaAnim,      // alma penada
    __surfarAnim,          // surf
    ataqueFisicoGenerico,  // enxada
    __thanosAnim,          // cancelar
    __ervaDaninhaAnim,     // erva
    ataqueFisicoGenerico   // ladrao

};

#endif // ANIMACOES_H_INCLUDED
