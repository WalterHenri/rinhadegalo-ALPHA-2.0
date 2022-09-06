#ifndef SCREEN_DRAW_H_INCLUDED
#define SCREEN_DRAW_H_INCLUDED

// TENTATIVA DE IMPLEMENTACAO
struct PixelChar
{
    char pixel;
    int color;
};

struct PixelChar screenPixels[ALTURA * LARGURA];
struct PixelChar screenPixelsPrev[ALTURA * LARGURA];

void initScreen()
{
    int totalPixels = ALTURA * LARGURA;
    for (int i = 0; i < totalPixels; i++)
    {
        struct PixelChar p;

        p.color = BLACK;
        p.pixel = ' ';

        screenPixels[i] = p;
        screenPixelsPrev[i] = p;
    }
}

void clearScreen()
{
    int totalPixels = ALTURA * LARGURA;
    for (int i = 0; i < totalPixels; i++)
    {
        struct PixelChar p;

        p.color = BLACK;
        p.pixel = ' ';

        screenPixelsPrev[i] = p;
    }
}

void pointScreen(int x, int y, char pixel, int color)
{
    if (pixel != ' ')
    {
        if (!(y > ALTURA || y < 1 || x > LARGURA || x < 1))
        {
            screenPixels[(x - 1) + ((y - 1) * LARGURA)].pixel = pixel;
            screenPixels[(x - 1) + ((y - 1) * LARGURA)].color = color;
        }
    }
}

void drawRectScreen(int x, int y, int wid, int hei, char pixel, int color)
{
    for (int i = 0; i < hei; i++)
    {
        for (int j = 0; j < wid; j++)
        {
            int yy = y + i;
            int xx = x + j;
            if (!(yy > ALTURA || yy < 1 || xx > LARGURA || xx < 1))
            {
                screenPixels[(xx - 1) + ((yy - 1) * LARGURA)].pixel = pixel;
                screenPixels[(xx - 1) + ((yy - 1) * LARGURA)].color = color;
            }
        }
    }
}

void drawScreen()
{
    int totalPixels = ALTURA * LARGURA;
    for (int i = 0; i < ALTURA; i++)
    {
        for (int j = 0; j < LARGURA; j++)
        {
            int index = j + (i * LARGURA);
            struct PixelChar pixelNow = screenPixels[index];
            struct PixelChar pixelPrev = screenPixelsPrev[index];

            if (pixelNow.pixel != ' ')
            {
                if (!(pixelNow.pixel == pixelPrev.pixel && pixelNow.color == pixelPrev.color))
                {
                    gotoxy(j + 1, i + 1);
                    textcolor(pixelNow.color);
                    textbackground(pixelNow.color);
                    char pixelChar = pixelNow.pixel;
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

    // ESVAZIA O ARRAY NOVO E POE O NOVO NO VELHO
    for (int i = 0; i < totalPixels; i++)
    {
        screenPixelsPrev[i] = screenPixels[i];

        struct PixelChar p;

        p.color = BLACK;
        p.pixel = ' ';

        screenPixels[i] = p;
    }
}

#endif // SCREEN_DRAW_H_INCLUDED
