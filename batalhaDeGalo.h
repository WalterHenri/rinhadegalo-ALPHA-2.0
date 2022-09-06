#ifndef BATALHADEGALO_H_INCLUDED
#define BATALHADEGALO_H_INCLUDED

//***************************DECLARACAO DE FUNCOES****************************************//

float randfloat(float a, float b);

//Quando é uma revanche, tem uma condição especial. O placar é mostrado na tela
int is_rematch;
int placar1;
int placar2;

//***************************************************************************************//

//*****variáveis gráficas****

int xMenuWid = LARGURA - 2;
int xMenu = 2;
int yMenu = ALTURA - 4;

int xStartAtk = 3;
int yStartAtk = ALTURA - 3;
int espVert = 1;
int espLat = 18;

int corTexto = WHITE;

//*****************************

/// retorno 0 empate, retorno 1 vitoria do galo 1, retorno 2 vitoria do galo 2

int batalha(struct galo_status galo1, struct galo_status galo2)
{

    textbackground(LIGHTGRAY);
    system("cls");

    // contar  as vitorias
    int placar[2] = {0};

    // CONTAR ROUNDS
    int round = 1;

    novoRound(galo1.id, galo2.id, round);

    loop_song(22 + (fundoDefinido % 5));

    //4 rounds
    while (round < 4)
    {

        // OPCOES DOS ATKS
        int opcaoAtaque1;
        int opcaoAtaque2;

        // DESENHAR as SPRITES dos GALOS
        clearScreen();
        desenharBatalha(galo1.id, galo2.id);
        drawScreen();
        barraDeHpGalos(&galo1, &galo2);

        // CAIXA DE DIALOGO
        textcolor(corTexto);
        caixaDeDialogo();


        int opcaoPlayer1;
        int opcaoPlayer2;

        opcaoPlayer1 = menuPrincipal(galo1);

        while (opcaoPlayer1 == -2)
        {
            desenharBatalha(galo1.id, galo2.id);
            drawScreen();
            barraDeHpGalos(&galo1, &galo2);
            textcolor(corTexto);
            caixaDeDialogo();
            opcaoPlayer1 = menuPrincipal(galo1);
        }

        if (opcaoPlayer1 == -1)
        {
            return 0;
        }
        else if (opcaoPlayer1 == -3)
        {
            return 2;
        }

        caixaDeDialogo();
        //No modo single player, a maquina joga uma atk aleatorio
        if (one_player_mode)
        {
            opcaoPlayer2 = rand() % 4;
        }
        else
        {
            opcaoPlayer2 = menuPrincipal(galo2);
        }

        while (opcaoPlayer2 == -2)
        {
            //Tentativa de empate
            desenharBatalha(galo1.id, galo2.id);
            drawScreen();
            barraDeHpGalos(&galo1, &galo2);
            textcolor(corTexto);
            caixaDeDialogo();
            opcaoPlayer2 = menuPrincipal(galo1);
        }

        if (opcaoPlayer2 == -1)
        {
            return 0;
        }
        //Desistir
        else if (opcaoPlayer2 == -3)
        {
            return 1;
        }

        int ataque1 = galo1.atks[opcaoPlayer1].id;
        int ataque2 = galo2.atks[opcaoPlayer2].id;

        int brigaResult = briga(&galo1, &galo2, ataque1, ataque2);

        // RESULTADO DA BRIGA
        if (brigaResult == 1)
        {
            // RESETANDO GALOS
            galo1 = galos[galo1.id];
            galo2 = galos[galo2.id];

            confirmInput();

            caixaDeDialogo();
            gotoxy(xMenu + 1, yMenu);
            printf("o %s ganhou o %d round", galo1.nome, round);
            confirmInput();

            placar[0]++;

            if (placar[0] == 2)
            {
                return 1;
            }
            round++;
            novoRound(galo1.id, galo2.id, round);
        }
        else if (brigaResult == 2)
        {

            // RESETANDO GALOS
            galo1 = galos[galo1.id];
            galo2 = galos[galo2.id];

            confirmInput();

            // PRINTANDO RESULTADO
            caixaDeDialogo();
            gotoxy(xMenu + 1, yMenu);
            printf("o %s ganhou o %d round", galo2.nome, round);
            confirmInput();
            placar[1]++;

            if (placar[1] == 2)
            {
                return 2;
            }

            round++;
            novoRound(galo1.id, galo2.id, round);
            //Cada mapa tem um som
            loop_song(22 + (fundoDefinido % 5));
        }
    }
}

void novoRound(int galo1Id, int galo2Id, int round)
{

    int roundx = LARGURA / 2 - sprRound.width / 2 - numbers[2].width;
    int roundy = ALTURA / 2 - sprRound.height / 2;

    int numberx = LARGURA / 2 - sprRound.width / 2 - numbers[2].width + sprRound.width + 3;

    clearScreen();

    desenharBatalha(galo1Id, galo2Id);

    drawSpriteBufferColorMaster(roundx, roundy, &sprRound, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);
    drawSpriteBufferColorMaster(numberx, roundy, &numbers[round - 1], 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);

    drawScreen();

    if (round == 1)
    {
        //ROUND ONE, FIGHT
        play_song(ROUND_1);
    }
    else if (round == 2)
    {
        play_song(ROUND_2);
    }
    else if (round == 3)
    {
        play_song(ROUND_3);
    }

    Sleep(1500);
    pause_song();

    clearScreen();

    desenharBatalha(galo1Id, galo2Id);

    drawSpriteBufferColorMaster(4, 2, &sprfight, 1, 1, 0, 0, 1, 1, LARGURA, ALTURA);

    drawScreen();
    play_song(FIGHT);

    Sleep(1500);
    pause_song();
}

// tentando fragmentar a batalha fe em deus que ele é justo
int menuPrincipal(struct galo_status galo)
{

    // OPCOES DO MENU

    char opcoesMenu[4][15];

    strcpy(opcoesMenu[0], "ATACK");
    strcpy(opcoesMenu[1], "SEE STATUS");
    strcpy(opcoesMenu[2], "DRAW");
    strcpy(opcoesMenu[3], "RESIGN");

    int temp;

    do
    {
        temp = 0;
        caixaDeDialogo();
        textbackground(BLACK);
        // preencher_com_espacos(30, 1, LARGURA / 2 - 11 , 2); btea

        preencher_com_espacos(80, 2, 1, 23);
        gotoxy(LARGURA / 2 - 12, 23);
        //Caso seja uma revanche, o placar é mostrado
        if (is_rematch)
            printf("Player 1 [%d] - [%d] Player 2", placar1, placar2);

        //-1 na seleção bidimensional é o esc. Como não pode sair desse primeiro menu, o usuário fica preso até escolher uma opção
        int opcaoMenu = selecionar_opcao_bidimensional(xMenu + 1, yMenu, espLat, espVert, 2, 2, 4, 15, opcoesMenu, corTexto, RED, 0);
        while (opcaoMenu == -1)
        {
            textcolor(WHITE);
            opcaoMenu = selecionar_opcao_bidimensional(xMenu + 1, yMenu, espLat, espVert, 2, 2, 4, 15, opcoesMenu, corTexto, RED, 0);
        }

        switch (opcaoMenu)
        {

        case 0:;
            // isso eh uma semilinha visto que voce nao pode criar uma variavel logo apos dois pontos
            int aux = opcaoAtk(galo);
            //Caso o usuário pressione esc, a condição do "do while" é atendida e o usuário volta do menu de atks para o primeiro menu
            if (aux == -1)
            {
                temp = 1;
            }
            else
            {
                return aux;
            }
            break;
        case 1:;

            //Case 1: Os 2 players ganham vida
            desenhar_quadrado(20, 10, LARGURA / 2 - 5, ALTURA / 2 - 5);
            gotoxy(LARGURA / 2 - 5 + 1, ALTURA / 2 - 5 + 1);
            printf("HP ->\t%d", galo.hp);
            gotoxy(LARGURA / 2 - 5 + 1, ALTURA / 2 - 5 + 2);
            printf("ATK ->\t%d", galo.ataque);
            gotoxy(LARGURA / 2 - 5 + 1, ALTURA / 2 - 5 + 3);
            printf("SPATK ->\t%d", galo.ataque_especial);
            gotoxy(LARGURA / 2 - 5 + 1, ALTURA / 2 - 5 + 4);
            printf("DEF ->\t%d", galo.defesa);
            gotoxy(LARGURA / 2 - 5 + 1, ALTURA / 2 - 5 + 5);
            printf("SPDEF ->\t%d", galo.defesa_especial);
            gotoxy(LARGURA / 2 - 5 + 1, ALTURA / 2 - 5 + 6);
            printf("SPEED ->\t%d", galo.velocidade);

            confirmInput();
            clearScreen();
            clrscr();
            return -2;

            break;
        case 2:;
            return opcaoEmpate();
            break;
        case 3:;

            return -3;
            break;
        }

    } while (temp);
}

int opcaoAtk(struct galo_status galo)
{

    char opcoesAtk[4][20];

    // preenchendo as opcoes com os nomes dos ataques
    for (int i = 0; i < 4; i++)
    {
        strcpy(opcoesAtk[i], galo.atks[i].nome);
    }

    // SELEÇÃO DE ATAQUES
    caixaDeDialogo();

    return selecionar_opcao_bidimensional(xMenu + 1, yMenu, espLat, espVert, 2, 2, 4, 20, opcoesAtk, corTexto, MAGENTA, 0);
}

//  RETORNO -1 Empate -2 Cancelado
int opcaoEmpate()
{
    caixaDeDialogo();
    gotoxy(xMenu + 1, yMenu);
    printf("do you wanna offer a draw?");
    gotoxy(xMenu + 30, yMenu);
    printf("no");
    gotoxy(xMenu + 30, yMenu + 1);
    printf("yes");
    int a = selecionar_opcao(xMenu + 29, yMenu, 2);
    if (a == 2)
    {
        caixaDeDialogo();
        gotoxy(xMenu + 1, yMenu);
        printf("do you wanna accept a draw?");
        gotoxy(xMenu + 30, yMenu);
        printf("no");
        gotoxy(xMenu + 30, yMenu + 1);
        printf("yes");
        int b = selecionar_opcao(xMenu + 29, yMenu, 2);
        if (b == 2)
        {
            caixaDeDialogo();
            gotoxy(xMenu + 1, yMenu);
            printf("DRAW BY GENERAL DECISION");
            return -1;
        }
        else
        {
            printf("not a draw");
            caixaDeDialogo();
            return -2;
        }
    }
    else
    {
        caixaDeDialogo();
        printf("not a draw");
        return -2;
    }
}

// EXECUTA ATAQUES E PROCESSA O RESULTADO DE UM TURNO DA BATALHA
int briga(struct galo_status *galo1, struct galo_status *galo2, int move1, int move2)
{

    // DECIDINDO QUAL ATACA PRIMEIRO
    if (galo1->velocidade > galo2->velocidade)
    {

        // GALO1 ATACA
        //Verifica se acertou o atk
        if (accurate(atks[move1]))
        {
            executarAtaque(move1, 0, galo1, galo2);

            if (galo2->hp <= 0)
            {
                return 1;
            }
        }
        else
        {
            char text[40];
            text[0] = '\0';

            sprintf(&text, " Attack Missed");
            caixaDeDialogoTexto(&text);
            confirmInput();
        }

        // GALO2 ATACA
        if (accurate(atks[move2]))
        {
            executarAtaque(move2, 1, galo1, galo2);

            if (galo1->hp <= 0)
            {
                return 2;
            }
        }
        else
        {
            char text[40];
            text[0] = '\0';

            sprintf(&text, " Attack Missed");
            caixaDeDialogoTexto(&text);
            confirmInput();
        }
    }
    else
    {

        // GALO2 ATACA
        if (accurate(atks[move2]))
        {
            executarAtaque(move2, 1, galo1, galo2);

            if (galo1->hp <= 0)
            {
                return 2;
            }
        }
        else
        {
            char text[40];
            text[0] = '\0';

            sprintf(&text, " Attack Missed");
            caixaDeDialogoTexto(&text);
            confirmInput();
        }

        // GALO1 ATACA

        if (accurate(atks[move1]))
        {
            executarAtaque(move1, 0, galo1, galo2);

            if (galo2->hp <= 0)
            {
                return 1;
            }
        }
        else
        {
            char text[40];
            text[0] = '\0';

            sprintf(&text, " Attack Missed");
            caixaDeDialogoTexto(&text);
            confirmInput();
        }
    }

    return 0;
}
//Recebe o atk q vai ser usado, recebe a ordem dos atks e os galos
void executarAtaque(int atkId, int ordem, struct galo_status *galo1, struct galo_status *galo2)
{

    // DEFININDO ATACANTE E DEFENSOR
    struct galo_status *atacante = galo1;
    struct galo_status *defensor = galo2;

    if (ordem == 1)
    {
        atacante = galo2;
        defensor = galo1;
    }

    // TEXTO SOBRE O ATAQUE
    char text[500];
    text[0] = '\0';

    sprintf(&text, " %s usou %s", atacante->nome, atks[atkId].nome);
    caixaDeDialogoTexto(&text);
    confirmInput();

    //Caso umas dessas condições seja atendida, chama o grandioso vetor de função na posição atkId
    if (atks[atkId].categoria != STATUS || atkId == GINGADO || atkId == CANTAR || atkId == OLHAR_MALIGNO)
    {
        animacoes[atkId](galo1, galo2, ordem);
    }
    else
    {
        //Essa função não está no vetor, pois ela possui uma assinatura diferente
        ataqueStatus(galo1, galo2, ordem, 2);
    }

    // ATUALIZACAO INICIAL DA BARRA DE HP
    barraDeHpGalos(galo1, galo2);

    // GUARDANDO VALORES ATUAIS DE HP PARA ANIMACAO
    int galosHpAntes[2];

    galosHpAntes[0] = galo1->hp;
    galosHpAntes[1] = galo2->hp;

    // ESSA E A PARTE QUE ANIMA A BARRA DE VIDA DESCENDO
    // E EXECUTA O ATAQUE

    int ordem2 = (ordem + 1) % 2;

    if (ordem == 0)
    {
        atacar[atkId](galo1, galo2);
    }
    else
    {
        atacar[atkId](galo2, galo1);
    }

    // DANO RECEBIDO PELO DEFENSOR
    int hpDif = max(defensor->hp, 0) - galosHpAntes[ordem2];
    barraDeHpAnim(defensor, galosHpAntes[ordem2], hpDif, ordem2);

    // DANO RECEBIDO PELO ATACANTE
    // PARA ATAQUES COM RECOIL

    hpDif = max(atacante->hp, 0) - galosHpAntes[ordem];
    barraDeHpAnim(atacante, galosHpAntes[ordem], hpDif, ordem);

    // ATUALIZACAO FINAL DA BARRA DE HP
    barraDeHpGalos(galo1, galo2);

    Sleep(600);
}

// FAZ A ANIMACAO DA BARRA DE VIDA INDO DE UM VALOR PARA OUTRO
void barraDeHpAnim(struct galo_status *galoDanificado, int hpAntes, int hpDif, int ordem)
{
    if (hpDif != 0)
    {
        char text2[500];
        text2[0] = '\0';
        sprintf(&text2, " %s perdeu %d pontos de vida", galoDanificado->nome, -hpDif);
        caixaDeDialogoTexto(&text2);
        confirmInput();
    }

    int difSign = (hpDif > 0) ? 1 : -1;

    int hpMax = galos[galoDanificado->id].hp;

    int sleepTime = 50;

    for (int i = 0; i < hpDif * difSign; i++)
    {
        barraDeHpGalo(hpMax, hpAntes + (i * difSign), ordem);
        Sleep(sleepTime);
    }
}

// DESENHA UMA BARRA DE VIDA DE UM GALO ESPECIFICO
void barraDeHpGalo(int hpMax, int hp, int ordem)
{
    if (ordem == 0)
    {
        barraDeHp(4, 2, hpMax, hp);
    }
    else
    {
        barraDeHp(LARGURA - 22, 2, hpMax, hp);
    }
}

// DESENHA AS DUAS BARRAS DE VIDA
void barraDeHpGalos(struct galo_status *galo1, struct galo_status *galo2)
{
    barraDeHpGalo(galos[galo1->id].hp, galo1->hp, 0);
    barraDeHpGalo(galos[galo2->id].hp, galo2->hp, 1);
}

// DESENHA UMA BARRA DE VIDA
void barraDeHp(int posicaox, int posicaoy, int hpMax, int hp)
{

    int barLenght = 20;
    int lifeBarLenght = (hp * barLenght) / hpMax;
    // apenas uma regra de 3 simples para deixar a barra do mesmo tamanho independente da vida do galo

    // CRIANDO STRINGS PROS NUMEROS
    char hpString[5] = "0000";
    char hpMaxString[5] = "0000";

    // Hp + 1000 PRA A CONVERSAO PRA STRING VIR COM OS ZEROS NA FRENTE
    int hpNum = max(min(1000 + max(min(hp, hpMax), 0), 9999), 0);
    int hpMaxNum = max(min(1000 + hpMax, 9999), 0);

    itoa(hpNum, hpString, 10);
    itoa(hpMaxNum, hpMaxString, 10);

    char hpCharArray[8];
    hpCharArray[0] = hpString[1];
    hpCharArray[1] = hpString[2];
    hpCharArray[2] = hpString[3];
    hpCharArray[3] = '/';
    hpCharArray[4] = hpMaxString[1];
    hpCharArray[5] = hpMaxString[2];
    hpCharArray[6] = hpMaxString[3];
    hpCharArray[7] = '\0';

    for (int i = 0; i < barLenght; i++)
    {
        gotoxy(posicaox + i, posicaoy);

        int color = (i < lifeBarLenght) ? GREEN : RED;

        if (i > 0 && i < 8)
        {
            textcolor(BLACK);
            textbackground(color);
            printf("%c", hpCharArray[i - 1]);
        }
        else
        {
            textcolor(color);
            printf("█");
        }
    }
}

// FUNCOES PARA CALCULAR DANO
int damageCalculator(struct galo_status attacker, struct galo_status defender, int atk_ID)
{
    float Base = atks[atk_ID].dano;
    float atk;
    float def;

    // caso ataque seja  fisico o parametro eh a defesa e o ataque, se for especial o contrario.
    if (atks[atk_ID].categoria == FISICO)
    {
        atk = attacker.ataque;
        def = defender.defesa;
    }
    else
    {
        atk = attacker.ataque_especial;
        def = defender.defesa_especial;
    }

    float Modifier = criticalhit(25) * randfloat(0.9, 1.1);

    int damnum = ((1 * (atk / def) * (Base) + 2) * Modifier);

    return damnum / 2;
}

// RETORNA UMA NUMERO ALEATORIO ENTRE DUAS FLOATS
float randfloat(float a, float b)
{

    int x = a * 100;
    int y = b * 100;
    float c = (rand() % (y - x) + x);
    return c / 100;
}

// DETERMINA SE UM ATAQUE E CRITICO COM BASE EM UMA CHANCE
int criticalhit(int t)
{
    int a = rand() % 256;
    return a < t ? 2 : 1;
}

// DETERMINA SE UM ATAQUE VAI SER EXECUTADO OU NAO COM BASE NA PRECISAO
int accurate(struct ataques atk)
{
    int temp = (rand() % 99) + 1;
    if (temp <= atk.precisao)
    {
        return 1;
    }
    return 0;
}

// PAUSA
void pausar()
{
    gotoxy(1, ALTURA - 1);
    system("pause");
}

// Função que pausa o código até receber a tecla de confirmar
// De certa forma melhor que system("pause")
// Pq n mostra a mensagem pra pressionar qualuqer tecla
// E evita q o cara despause sem querer
char confirmInput()
{
    char input = getch();

    while (input != KEY_ENTER)
    {
        input = getch();
    }
    return input;
}

void desenharBatalha(int galo1, int galo2)
{
    // DESENHAR OS SPRITES DOS GALOS
    int borderColor = configBatalha.borderColor;
    int hasBorder = configBatalha.hasBorder;

    drawSpriteBufferColorMaster(1, 1, &fundos[configBatalha.fundo], 1, 1, hasBorder, borderColor, 1, 1, LARGURA, ALTURA);
    drawSpriteBufferColorMaster(2, ALTURA - 5 - galoSprites[galo1][0].height, &galoSprites[galo1][0], 2, 1, hasBorder, borderColor, 1, 1, LARGURA, ALTURA);
    drawSpriteBufferColorMaster(LARGURA - galoSprites[galo2][1].width * 2, ALTURA - 5 - galoSprites[galo2][0].height, &galoSprites[galo2][1], 2, 1, hasBorder, borderColor, 1, 1, LARGURA, ALTURA);
}

// DESENHA BORDA DA TELA
void desenharBorda()
{
    desenhar_quadrado(80, 24, 1, 1);
}

// DESENHA A CAIXA DE DIALOGO
void caixaDeDialogo()
{
    textbackground(BLACK);
    textcolor(WHITE);
    desenhar_quadrado(80, 6, 1, ALTURA - 5);
    desenhar_quadrado(80, 4, 1, ALTURA - 5);
}

// DESENHA TEXTO DENTRO DA CAIXA DE DIALOGO
void caixaDeDialogoTexto(char *texto)
{
    caixaDeTexto(texto, 1, ALTURA - 5, 80, 4);
}

// FUNCAO QUE ESCREVE TEXTO EM AREA DEFINIVEL
// QUEBRA LINHA QUANDO NECESSARIO E CRIA MULTIPLAS
// PAGINAS QUANDO O TEXTO NAO CABE EM APENAS UMA
void caixaDeTexto(char *texto, int x, int y, int wid, int hei)
{

    int charLimit = 5000;

    int index = 0;

    int textWid = wid - 2;
    int textHei = hei - 2;

    int backColor = BLACK;
    int mainColor = WHITE;

    int yy = 0;

    int stringEnd = 0;

    int charTime = 20;

    textcolor(mainColor);
    textbackground(backColor);

    desenhar_quadrado(wid, hei, x, y);

    if (!(textWid > 0 && textHei > 0))
    {
        return;
    }

    while (*(texto + index) != '\0' && index < charLimit && stringEnd == 0)
    {

        gotoxy(x + 1, y + yy + 1);
        int lastStop = 0;
        for (int i = 0; i < textWid; i++)
        {
            char actChar = *(texto + index + i);
            if (actChar != '\0' && index + i < charLimit)
            {
                if (actChar == ' ')
                {
                    lastStop = i;
                }
            }
            else
            {
                stringEnd = 1;
                lastStop = i;
                i = textWid;
            }
        }

        if (lastStop == 0)
        {
            for (int j = 0; j < textWid; j++)
            {
                char actChar = *(texto + index + j);
                printf("%c", actChar);
                Sleep(charTime);
            }
            index += textWid;
        }
        else
        {
            for (int j = 0; j < lastStop; j++)
            {
                char actChar = *(texto + index + j);
                printf("%c", actChar);
                Sleep(charTime);
            }
            index += lastStop + 1;
        }

        yy++;
        if (yy >= textHei)
        {
            yy = 0;
            confirmInput();
            desenhar_quadrado(wid, hei, x, y);
        }
    }
}

#endif // BATALHADEGALO_H_INCLUDED
