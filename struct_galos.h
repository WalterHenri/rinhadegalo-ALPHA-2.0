#ifndef GALOS__H
#define GALOS__H
#include <string.h>
#include "desenhos.h"

typedef enum ataques_id
{

    BATER_ASAS,
    POEIRA,
    BICADA,
    CANTAR,
    ARRANHAR,
    VOAR,
    ATIRAR,
    BICO_DE_ACO,
    FURIA,
    OLHAR_MALIGNO,
    JOGAR_OVO,
    ATAQUE_DE_ASA,
    BICO_BROCA,
    SKY_ATACK,
    AERO_EGG,
    GINGADO,
    AU_DA_CAPOEIRA,
    ESPORA_GIRATORIA,
    CORTAR,
    PICAR,
    ESGUICHO,
    CLOACA_DE_FERRO,
    PISOTEAR,
    CHICOTE_DE_CINTO,
    PENA_DE_MORTE,
    VINGARDE_LEVE_OVO,
    ALMA_PENADA,
    SURFAR,
    ENXADA_DE_FERRO,
    CANCELAR,
    ERVA_DANINHA,
    LADRAO

} ataques_id;

typedef enum Categoria
{

    FISICO,
    ESPECIAL,
    STATUS

} Categoria;

typedef enum Tipos
{

    CAIPIRA,
    CAPOEIRA,
    GRANJA,
    LUTADOR,
    ATIRADOR,
    NORMAL,
    TERRA,
    FEMEA,
    PATO,
    ANGOLANO,
    FANTASMA,
    TOXICO,
    GOTICO

} Tipos;

typedef enum galos_ID
{

    GALO_DE_TENIS = 0,
    GALO_DE_CALCA = 1,
    GALO_TOPETE = 2,
    GALO_AQUATICO = 3,
    GALO_TWITTER = 4,
    GALO_EMO = 5,
    GALO_MILITAR = 6,
    GALO_ANTONIO = 7,
    GALO_SLIME = 8,
    GALO_MANDRAKE = 9,
    GALO_BRUXO = 10,
    GALO_SNIPER = 11,
    GALO_PIRATA = 12,
    GALINHA_PINTADINHA = 13,
    GALO_BROCADOR = 14,
    GALO_RETANGULO = 15,
    GALO_FAQUEIRO = 16,
    PICA_PAU = 17,
    PIU_PIU = 18,
    LOURO_JOSE = 19,
    JOAO_FRANGO = 20,
    GALO_WHATSAPP = 21,
    URUBU_DO_PIX = 22,
    GALO_FENOMENO = 23,
    GALO_SADIA = 24,
    GALO_CARECA = 25,
    GALO_CARIJO = 26,
    GALO_DA_PESTE = 27

} galos_ID;

typedef struct ataques
{

    int id;
    char nome[20];
    int precisao;
    Tipos tipo;
    Categoria categoria;
    int dano;
    char descricao[200];

} ataques;

typedef struct galo_status
{

    char nome[20];
    int id;
    int hp;
    int ataque;
    int defesa;
    int ataque_especial;
    int defesa_especial;
    int velocidade;
    int tipo;
    struct ataques atks[4];
    int altura;  // medida em cm
    float peso;  // medido em kg
    float idade; // medido em anos

} galo_status;

struct ataques atks[35];
struct galo_status galos[28];

void iniciar_status()
{

    for (int i = 0; i < 27; i++)
    {
        strcpy(galos[i].nome, "GALO GENERICO");
        galos[i].id = i;
        galos[i].idade = 2;
        galos[i].altura = 56;
        galos[i].peso = 1.7;
        galos[i].hp = 80;
        galos[i].ataque = 20;
        galos[i].defesa = 20;
        galos[i].ataque_especial = 20;
        galos[i].defesa_especial = 20;
        galos[i].velocidade = 40;
        galos[i].tipo = PATO;
        galos[i].atks[0] = atks[ESGUICHO];
        galos[i].atks[1] = atks[PISOTEAR];
        galos[i].atks[2] = atks[VOAR];
        galos[i].atks[3] = atks[BATER_ASAS];
    }

    int i = GALO_AQUATICO;

    strcpy(galos[i].nome, "GALO AQU�TICO");
    galos[i].id = i;
    galos[i].idade = 2;
    galos[i].altura = 56;
    galos[i].peso = 1.7;
    galos[i].hp = 80;
    galos[i].ataque = 20;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 20;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 30;
    galos[i].tipo = PATO;
    galos[i].atks[0] = atks[ESGUICHO];
    galos[i].atks[1] = atks[SURFAR];
    galos[i].atks[2] = atks[VOAR];
    galos[i].atks[3] = atks[BATER_ASAS];

    i = GALO_SNIPER;

    strcpy(galos[i].nome, "GALO SNIPER");
    galos[i].id = i;
    galos[i].idade = 9;
    galos[i].altura = 51;
    galos[i].peso = 10;
    galos[i].hp = 55;
    galos[i].ataque = 10;
    galos[i].defesa = 30;
    galos[i].ataque_especial = 60;
    galos[i].defesa_especial = 30;
    galos[i].velocidade = 60;
    galos[i].tipo = ATIRADOR;
    galos[i].atks[0] = atks[ATIRAR];
    galos[i].atks[1] = atks[AERO_EGG];
    galos[i].atks[2] = atks[CHICOTE_DE_CINTO];
    galos[i].atks[3] = atks[ERVA_DANINHA];

    i = GALO_DE_TENIS;

    strcpy(galos[i].nome, "GALO DE TENIS");
    galos[i].id = i;
    galos[i].idade = 1;
    galos[i].altura = 60;
    galos[i].peso = 3.1;
    galos[i].hp = 40;
    galos[i].ataque = 35;
    galos[i].defesa = 35;
    galos[i].ataque_especial = 10;
    galos[i].defesa_especial = 30;
    galos[i].velocidade = 25;
    galos[i].tipo = TERRA;
    galos[i].atks[0] = atks[OLHAR_MALIGNO];
    galos[i].atks[1] = atks[PISOTEAR];
    galos[i].atks[2] = atks[VOAR];
    galos[i].atks[3] = atks[ERVA_DANINHA];

    i = GALO_ANTONIO;

    strcpy(galos[i].nome, "GALO ANTONIO");
    galos[i].id = i;
    galos[i].idade = 9;
    galos[i].altura = 61;
    galos[i].peso = 1.9;
    galos[i].hp = 65;
    galos[i].ataque = 35;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 10;
    galos[i].defesa_especial = 15;
    galos[i].velocidade = 30;
    galos[i].tipo = CAIPIRA;
    galos[i].atks[0] = atks[ENXADA_DE_FERRO];
    galos[i].atks[1] = atks[ARRANHAR];
    galos[i].atks[2] = atks[BICADA];
    galos[i].atks[3] = atks[BICO_DE_ACO];

    i = GALO_EMO;

    strcpy(galos[i].nome, "GALO EMO");
    galos[i].id = i;
    galos[i].idade = 2;
    galos[i].altura = 54;
    galos[i].peso = 2.8;
    galos[i].hp = 40;
    galos[i].ataque = 20;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 30;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 25;
    galos[i].tipo = GOTICO;
    galos[i].atks[0] = atks[OLHAR_MALIGNO];
    galos[i].atks[1] = atks[ALMA_PENADA];
    galos[i].atks[2] = atks[FURIA];
    galos[i].atks[3] = atks[ARRANHAR];

    i = GALO_CARECA;

    strcpy(galos[i].nome, "GALO CARECA");
    galos[i].id = i;
    galos[i].idade = 5;
    galos[i].altura = 53;
    galos[i].peso = 2.5;
    galos[i].hp = 55;
    galos[i].ataque = 31;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 11;
    galos[i].defesa_especial = 12;
    galos[i].velocidade = 34;
    galos[i].tipo = NORMAL;
    galos[i].atks[0] = atks[BATER_ASAS];
    galos[i].atks[1] = atks[ESPORA_GIRATORIA];
    galos[i].atks[2] = atks[ARRANHAR];
    galos[i].atks[3] = atks[BICADA];

    i = GALO_DE_CALCA;

    strcpy(galos[i].nome, "GALO DE KALSA");
    galos[i].id = i;
    galos[i].idade = 4;
    galos[i].altura = 50;
    galos[i].peso = 2.9;
    galos[i].hp = 60;
    galos[i].ataque = 40;
    galos[i].defesa = 30;
    galos[i].ataque_especial = 10;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 40;
    galos[i].tipo = CAPOEIRA;
    galos[i].atks[0] = atks[AU_DA_CAPOEIRA];
    galos[i].atks[1] = atks[GINGADO];
    galos[i].atks[2] = atks[POEIRA];
    galos[i].atks[3] = atks[CHICOTE_DE_CINTO];

    i = GALO_MILITAR;

    strcpy(galos[i].nome, "GALO MILITAR");
    galos[i].id = i;
    galos[i].idade = 18;
    galos[i].altura = 54;
    galos[i].peso = 3.2;
    galos[i].hp = 50;
    galos[i].ataque = 30;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 35;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 30;
    galos[i].tipo = ATIRADOR;
    galos[i].atks[0] = atks[ATIRAR];
    galos[i].atks[1] = atks[PENA_DE_MORTE];
    galos[i].atks[2] = atks[OLHAR_MALIGNO];
    galos[i].atks[3] = atks[FURIA];

    i = GALO_TWITTER;

    strcpy(galos[i].nome, "GALO TWITTER");
    galos[i].id = i;
    galos[i].idade = 16;
    galos[i].altura = 30;
    galos[i].peso = 0.43;
    galos[i].hp = 25;
    galos[i].ataque = 20;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 40;
    galos[i].defesa_especial = 30;
    galos[i].velocidade = 35;
    galos[i].tipo = TOXICO;
    galos[i].atks[0] = atks[CANCELAR];
    galos[i].atks[1] = atks[ARRANHAR];
    galos[i].atks[2] = atks[OLHAR_MALIGNO];
    galos[i].atks[3] = atks[JOGAR_OVO];

    i = GALINHA_PINTADINHA;

    strcpy(galos[i].nome, "GALINHA PINTADINHA");
    galos[i].id = i;
    galos[i].idade = 17;
    galos[i].altura = 40;
    galos[i].peso = 4.5;
    galos[i].hp = 70;
    galos[i].ataque = 20;
    galos[i].defesa = 40;
    galos[i].ataque_especial = 20;
    galos[i].defesa_especial = 40;
    galos[i].velocidade = 20;
    galos[i].tipo = FEMEA;
    galos[i].atks[0] = atks[CANTAR];
    galos[i].atks[1] = atks[GINGADO];
    galos[i].atks[2] = atks[CLOACA_DE_FERRO];
    galos[i].atks[3] = atks[JOGAR_OVO];

    i = GALO_CARIJO;

    strcpy(galos[i].nome, "GALO CARIJO");
    galos[i].id = i;
    galos[i].idade = 17;
    galos[i].altura = 62;
    galos[i].peso = 3.8;
    galos[i].hp = 55;
    galos[i].ataque = 30;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 20;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 30;
    galos[i].tipo = GRANJA;
    galos[i].atks[0] = atks[ERVA_DANINHA];
    galos[i].atks[1] = atks[POEIRA];
    galos[i].atks[2] = atks[ATAQUE_DE_ASA];
    galos[i].atks[3] = atks[BICADA];

    i = GALO_FAQUEIRO;

    strcpy(galos[i].nome, "GALO FAQUEIRO");
    galos[i].id = i;
    galos[i].idade = 3;
    galos[i].altura = 51;
    galos[i].peso = 2.4;
    galos[i].hp = 50;
    galos[i].ataque = 50;
    galos[i].defesa = 15;
    galos[i].ataque_especial = 10;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 35;
    galos[i].tipo = LUTADOR;
    galos[i].atks[0] = atks[CORTAR];
    galos[i].atks[1] = atks[BICO_DE_ACO];
    galos[i].atks[2] = atks[ARRANHAR];
    galos[i].atks[3] = atks[BICADA];

    i = LOURO_JOSE;

    strcpy(galos[i].nome, "LOURO JOSE");
    galos[i].id = i;
    galos[i].idade = 47;
    galos[i].altura = 55;
    galos[i].peso = 2.8;
    galos[i].hp = 53;
    galos[i].ataque = 10;
    galos[i].defesa = 25;
    galos[i].ataque_especial = 40;
    galos[i].defesa_especial = 30;
    galos[i].velocidade = 31;
    galos[i].tipo = FANTASMA;
    galos[i].atks[0] = atks[ALMA_PENADA];
    galos[i].atks[1] = atks[PENA_DE_MORTE];
    galos[i].atks[2] = atks[LADRAO];
    galos[i].atks[3] = atks[BICADA];

    i = JOAO_FRANGO;

    strcpy(galos[i].nome, "JOAO FRANGO");
    galos[i].id = i;
    galos[i].idade = 2.5;
    galos[i].altura = 54;
    galos[i].peso = 2.2;
    galos[i].hp = 70;
    galos[i].ataque = 30;
    galos[i].defesa = 30;
    galos[i].ataque_especial = 35;
    galos[i].defesa_especial = 30;
    galos[i].velocidade = 50;
    galos[i].tipo = ANGOLANO;
    galos[i].atks[0] = atks[SURFAR];
    galos[i].atks[1] = atks[BICADA];
    galos[i].atks[2] = atks[PICAR];
    galos[i].atks[3] = atks[ERVA_DANINHA];

    i = PIU_PIU;

    strcpy(galos[i].nome, "PIU PIU");
    galos[i].id = i;
    galos[i].idade = 3;
    galos[i].altura = 20;
    galos[i].peso = 0.8;
    galos[i].hp = 30;
    galos[i].ataque = 30;
    galos[i].defesa = 32;
    galos[i].ataque_especial = 10;
    galos[i].defesa_especial = 13;
    galos[i].velocidade = 30;
    galos[i].tipo = NORMAL;
    galos[i].atks[0] = atks[PICAR];
    galos[i].atks[1] = atks[BICADA];
    galos[i].atks[2] = atks[OLHAR_MALIGNO];
    galos[i].atks[3] = atks[CANTAR];

    i = PICA_PAU;

    strcpy(galos[i].nome, "PICA PAU");
    galos[i].id = i;
    galos[i].idade = 81;
    galos[i].altura = 33;
    galos[i].peso = 1.7;
    galos[i].hp = 42;
    galos[i].ataque = 34;
    galos[i].defesa = 22;
    galos[i].ataque_especial = 21;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 40;
    galos[i].tipo = TOXICO;
    galos[i].atks[0] = atks[CANTAR];
    galos[i].atks[1] = atks[PICAR];
    galos[i].atks[2] = atks[ERVA_DANINHA];
    galos[i].atks[3] = atks[VOAR];

    i = GALO_BROCADOR;

    strcpy(galos[i].nome, "GALO BROCADOR");
    galos[i].id = i;
    galos[i].idade = 11;
    galos[i].altura = 54;
    galos[i].peso = 2.8;
    galos[i].hp = 40;
    galos[i].ataque = 38;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 20;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 32;
    galos[i].tipo = TERRA;
    galos[i].atks[0] = atks[BICO_BROCA];
    galos[i].atks[1] = atks[LADRAO];
    galos[i].atks[2] = atks[ATAQUE_DE_ASA];
    galos[i].atks[3] = atks[ESPORA_GIRATORIA];

    i = GALO_MANDRAKE;

    strcpy(galos[i].nome, "GALO MANDRAKE");
    galos[i].id = i;
    galos[i].idade = 2;
    galos[i].altura = 49;
    galos[i].peso = 1.9;
    galos[i].hp = 38;
    galos[i].ataque = 32;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 35;
    galos[i].defesa_especial = 34;
    galos[i].velocidade = 49;
    galos[i].tipo = ANGOLANO;
    galos[i].atks[0] = atks[ERVA_DANINHA];
    galos[i].atks[1] = atks[ATIRAR];
    galos[i].atks[2] = atks[LADRAO];
    galos[i].atks[3] = atks[BICADA];

    i = GALO_FENOMENO;

    strcpy(galos[i].nome, "GALO FENOMENO");
    galos[i].id = i;
    galos[i].idade = 9;
    galos[i].altura = 52;
    galos[i].peso = 2.8;
    galos[i].hp = 50;
    galos[i].ataque = 40;
    galos[i].defesa = 22;
    galos[i].ataque_especial = 18;
    galos[i].defesa_especial = 20;
    galos[i].velocidade = 50;
    galos[i].tipo = CAPOEIRA;
    galos[i].atks[0] = atks[BATER_ASAS];
    galos[i].atks[1] = atks[GINGADO];
    galos[i].atks[2] = atks[BICADA];
    galos[i].atks[3] = atks[AU_DA_CAPOEIRA];

    i = GALO_BRUXO;

    strcpy(galos[i].nome, "GALO BRUXO");
    galos[i].id = i;
    galos[i].idade = 1000;
    galos[i].altura = 48;
    galos[i].peso = 2.8;
    galos[i].hp = 75;
    galos[i].ataque = 10;
    galos[i].defesa = 25;
    galos[i].ataque_especial = 70;
    galos[i].defesa_especial = 50;
    galos[i].velocidade = 40;
    galos[i].tipo = GOTICO;
    galos[i].atks[0] = atks[VINGARDE_LEVE_OVO];
    galos[i].atks[1] = atks[LADRAO];
    galos[i].atks[2] = atks[ALMA_PENADA];
    galos[i].atks[3] = atks[PENA_DE_MORTE];

    i = GALO_SLIME;

    strcpy(galos[i].nome, "GALO SLIME");
    galos[i].id = i;
    galos[i].idade = 1000;
    galos[i].altura = 48;
    galos[i].peso = 2.8;
    galos[i].hp = 75;
    galos[i].ataque = 10;
    galos[i].defesa = 40;
    galos[i].ataque_especial = 70;
    galos[i].defesa_especial = 40;
    galos[i].velocidade = 50;
    galos[i].tipo = GOTICO;
    galos[i].atks[0] = atks[VINGARDE_LEVE_OVO];
    galos[i].atks[1] = atks[LADRAO];
    galos[i].atks[2] = atks[JOGAR_OVO];
    galos[i].atks[3] = atks[PISOTEAR];

    i = GALO_PIRATA;

    strcpy(galos[i].nome, "GALO PIRATA");
    galos[i].id = i;
    galos[i].idade = 1000;
    galos[i].altura = 48;
    galos[i].peso = 2.8;
    galos[i].hp = 75;
    galos[i].ataque = 25;
    galos[i].defesa = 30;
    galos[i].ataque_especial = 55;
    galos[i].defesa_especial = 30;
    galos[i].velocidade = 50;
    galos[i].tipo = GOTICO;
    galos[i].atks[0] = atks[CORTAR];
    galos[i].atks[1] = atks[LADRAO];
    galos[i].atks[2] = atks[ATIRAR];
    galos[i].atks[3] = atks[PENA_DE_MORTE];

    i = URUBU_DO_PIX;

    strcpy(galos[i].nome, "URUBU DO PIX");
    galos[i].id = i;
    galos[i].idade = 1.5;
    galos[i].altura = 60;
    galos[i].peso = 1.7;
    galos[i].hp = 90;
    galos[i].ataque = 25;
    galos[i].defesa = 25;
    galos[i].ataque_especial = 55;
    galos[i].defesa_especial = 25;
    galos[i].velocidade = 50;
    galos[i].tipo = CAPOEIRA;
    galos[i].atks[0] = atks[VOAR];
    galos[i].atks[1] = atks[LADRAO];
    galos[i].atks[2] = atks[AU_DA_CAPOEIRA];
    galos[i].atks[3] = atks[GINGADO];

    i = GALO_WHATSAPP;

    strcpy(galos[i].nome, "GALO WHATSAPP");
    galos[i].id = i;
    galos[i].idade = 11;
    galos[i].altura = 54;
    galos[i].peso = 2.4;
    galos[i].hp = 71;
    galos[i].ataque = 40;
    galos[i].defesa = 30;
    galos[i].ataque_especial = 20;
    galos[i].defesa_especial = 35;
    galos[i].velocidade = 50;
    galos[i].tipo = TOXICO;
    galos[i].atks[0] = atks[CANCELAR];
    galos[i].atks[1] = atks[BICADA];
    galos[i].atks[2] = atks[FURIA];
    galos[i].atks[3] = atks[ERVA_DANINHA];

    i = GALO_SADIA;

    strcpy(galos[i].nome, "GALO SADIA");
    galos[i].id = i;
    galos[i].idade = 78;
    galos[i].altura = 40;
    galos[i].peso = 1;
    galos[i].hp = 65;
    galos[i].ataque = 35;
    galos[i].defesa = 50;
    galos[i].ataque_especial = 20;
    galos[i].defesa_especial = 40;
    galos[i].velocidade = 50;
    galos[i].tipo = GRANJA;
    galos[i].atks[0] = atks[AERO_EGG];
    galos[i].atks[1] = atks[ESPORA_GIRATORIA];
    galos[i].atks[2] = atks[OLHAR_MALIGNO];
    galos[i].atks[3] = atks[ARRANHAR];

    i = GALO_TOPETE;

    strcpy(galos[i].nome, "GALO TOPETE");
    galos[i].id = i;
    galos[i].idade = 5;
    galos[i].altura = 34;
    galos[i].peso = 1.8;
    galos[i].hp = 50;
    galos[i].ataque = 25;
    galos[i].defesa = 20;
    galos[i].ataque_especial = 35;
    galos[i].defesa_especial = 15;
    galos[i].velocidade = 35;
    galos[i].tipo = LUTADOR;
    galos[i].atks[0] = atks[BICO_DE_ACO];
    galos[i].atks[1] = atks[BICADA];
    galos[i].atks[2] = atks[PICAR];
    galos[i].atks[3] = atks[BICO_BROCA];

    i = GALO_RETANGULO;

    strcpy(galos[i].nome, "GALO MINECRAFT");
    galos[i].id = i;
    galos[i].idade = 2;
    galos[i].altura = 53;
    galos[i].peso = 3.5;
    galos[i].hp = 70;
    galos[i].ataque = 18;
    galos[i].defesa = 60;
    galos[i].ataque_especial = 25;
    galos[i].defesa_especial = 45;
    galos[i].velocidade = 18;
    galos[i].tipo = NORMAL;
    galos[i].atks[0] = atks[CANCELAR];
    galos[i].atks[1] = atks[PISOTEAR];
    galos[i].atks[2] = atks[ATIRAR];
    galos[i].atks[3] = atks[CANTAR];

    i = GALO_DA_PESTE;

    strcpy(galos[i].nome, "THE PLAGUE");
    galos[i].id = i;
    galos[i].idade = 669;
    galos[i].altura = 80;
    galos[i].peso = 3.5;
    galos[i].hp = 70;
    galos[i].ataque = 18;
    galos[i].defesa = 40;
    galos[i].ataque_especial = 60;
    galos[i].defesa_especial = 45;
    galos[i].velocidade = 60;
    galos[i].tipo = NORMAL;
    galos[i].atks[0] = atks[CANCELAR];
    galos[i].atks[1] = atks[PENA_DE_MORTE];
    galos[i].atks[2] = atks[ALMA_PENADA];
    galos[i].atks[3] = atks[JOGAR_OVO];
}

void iniciar_ataques()
{

    int i = BATER_ASAS;

    atks[i].id = i;
    strcpy(atks[i].nome, "Bater asas");
    atks[i].precisao = 90;
    atks[i].tipo = NORMAL;
    atks[i].categoria = FISICO;
    atks[i].dano = 30;
    strcpy(atks[i].descricao, "Usuario bate as asas com forca causando\ndano\n\nPrecisao: 90%\nCategoria: Fisico\nDano: 30");

    i = POEIRA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Levantar Poeira");
    atks[i].precisao = 100;
    atks[i].tipo = STATUS;
    atks[i].categoria = TERRA;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Invoca a ivete Sangalo, que tras consigo\n uma ventania ao som de levantar poeira,\nque diminui a precisao do inimigo\n\nPrecisao: 100%\nCategoria: Status");

    i = BICADA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Bicada");
    atks[i].precisao = 95;
    atks[i].tipo = NORMAL;
    atks[i].categoria = FISICO;
    atks[i].dano = 25;
    strcpy(atks[i].descricao, "Usuario concentra toda sua forca no \nbico para furar seu inimigo\n\nPrecisao: 95%\nCategoria: Fisico\nDano: 25");

    i = CANTAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Cantar");
    atks[i].precisao = 99;
    atks[i].tipo = FEMEA;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 28;
    strcpy(atks[i].descricao, "Usuario concentra toda sua energia\nnas cordas vocais e canta para destruir\na audicao do inimigo\n\nPrecisao: 99%\nCategoria: Especial\nDano: 28");

    i = ARRANHAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Arranhar");
    atks[i].precisao = 90;
    atks[i].tipo = LUTADOR;
    atks[i].categoria = FISICO;
    atks[i].dano = 24;
    strcpy(atks[i].descricao, "Usuario usa toda a forca de suas unhas\nafiadas para arranhar o inimigo\n\nPrecisao: 90%\nCategoria: Fisico\nDano: 24");

    i = VOAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Voar");
    atks[i].precisao = 85;
    atks[i].tipo = PATO;
    atks[i].categoria = FISICO;
    atks[i].dano = 32;
    strcpy(atks[i].descricao, "Usuario tenta voar e acertar seu inimigo\nem alta velocidade\n\nPrecicao: 85%\nCategoria: Fisico\nDano: 32");

    i = ATIRAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Atirar");
    atks[i].precisao = 90;
    atks[i].tipo = ATIRADOR;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 24;
    strcpy(atks[i].descricao, "Usuario usa uma arma de alto calibre\npara abater seu inimigo\n\nPrecisao: 90%\nCategoria: Especial\nDano: 24");

    i = BICO_DE_ACO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Bico de A�o");
    atks[i].precisao = 95;
    atks[i].tipo = ESPECIAL;
    atks[i].categoria = LUTADOR;
    atks[i].dano = 29;
    strcpy(atks[i].descricao, "Usuario ataca usando seu bico de aco,\ncausando muito dano\n\nPrecisao: 95%\nCategoria: Especial\nDano: 29");

    i = FURIA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Furia");
    atks[i].precisao = 100;
    atks[i].tipo = NORMAL;
    atks[i].categoria = STATUS;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Usuario mostra toda sua raiva para\nintimidar seu inimigo\n\nPrecisao: 100%\nCategoria: Status");

    i = OLHAR_MALIGNO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Olhar Maligno");
    atks[i].precisao = 95;
    atks[i].tipo = GOTICO;
    atks[i].categoria = STATUS;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Usuario olha maliciosamente para seu \ninimigopara intimida-lo\n\nPrecisao: 100%\nCategoria: Status");

    i = JOGAR_OVO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Jogar ovo");
    atks[i].precisao = 100;
    atks[i].tipo = FEMEA;
    atks[i].categoria = FISICO;
    atks[i].dano = 15;
    strcpy(atks[i].descricao, "Usuario joga um ovo no inimigo\n\nPrecisao: 100%\nCategoria: Fisico\nDano: 15");

    i = ATAQUE_DE_ASA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Ataque de Asa");
    atks[i].precisao = 90;
    atks[i].tipo = CAPOEIRA;
    atks[i].categoria = FISICO;
    atks[i].dano = 25;
    strcpy(atks[i].descricao, "Usuario ataca seu inimigo com furia\nusando suas asas\n\nPrecisao: 90%\nCategoria: Fisico\nDano: 25");

    i = BICO_BROCA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Bico Broca");
    atks[i].precisao = 85;
    atks[i].tipo = ESPECIAL;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 30;
    strcpy(atks[i].descricao, "Usuario usa uma broca para destruir\no seu inimigo\n\nPrecisao: 85%\nCategoria: Especial\nDano: 30");

    i = SKY_ATACK;

    atks[i].id = i;
    strcpy(atks[i].nome, "Sky Atack");
    atks[i].precisao = 85;
    atks[i].tipo = PATO;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 30;
    strcpy(atks[i].descricao, "Usuario tenta atacar o inimigo\npelos ceus\n\nPrecisao: 85%\nCategoria: Especial\nDano: 30");

    i = AERO_EGG;

    atks[i].id = i;
    strcpy(atks[i].nome, "Aero egg");
    atks[i].precisao = 95;
    atks[i].tipo = FEMEA;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 35;
    strcpy(atks[i].descricao, "Usuario joga um ovo explosivo\nno inimigo\n\nPrecisao: 95%\nCategoria: Especial\nDano: 35");

    i = GINGADO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Gingado");
    atks[i].precisao = 100;
    atks[i].tipo = CAPOEIRA;
    atks[i].categoria = STATUS;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Usuario usa toda sua malemolencia\npara aumentar sua velocidade e seu ataque\n\nPrecisao: 100%\nCategoria: Status\n");

    i = AU_DA_CAPOEIRA;

    atks[i].id = i;
    strcpy(atks[i].nome, "AU da capoeira");
    atks[i].precisao = 95;
    atks[i].tipo = CAPOEIRA;
    atks[i].categoria = FISICO;
    atks[i].dano = 30;
    strcpy(atks[i].descricao, "O usuario utiliza de todo seu gingado e\nhabilidades capoeiristicas para arrebentar\nseu oponente\n\nPrecisao: 95%\nCategoria: Fisico\nDano: 30");

    i = ESPORA_GIRATORIA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Espora giratoria");
    atks[i].precisao = 95;
    atks[i].tipo = NORMAL;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 20;
    // Alguem com criatividade fa�a esse
    strcpy(atks[i].descricao, "Usuario come�a a girar violentamente\nenquanto se prepara para acertar um\ngolpe com a pata durante o giro\n\nPrecisao: 95%\nCategoria: Especial\nDano: 20");

    i = CORTAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Cortar");
    atks[i].precisao = 90;
    atks[i].tipo = LUTADOR;
    atks[i].categoria = FISICO;
    atks[i].dano = 30;
    strcpy(atks[i].descricao, "Usuario usa uma faca amolada para\ncortar seu inimigo\n\nPrecisao: 90%\nCategoria: Fisico\nDano: 30");

    i = PICAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Picar");
    atks[i].precisao = 95;
    atks[i].tipo = TOXICO;
    atks[i].categoria = FISICO;
    atks[i].dano = 21;
    strcpy(atks[i].descricao, "Usuario usa toda sua velocidade para picar\nseu inimigo rapidamente\n\nPrecisao: 95%\nCategoria: Fisico\nDano: 21");

    i = ESGUICHO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Esguicho");
    atks[i].precisao = 95;
    atks[i].tipo = PATO;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 20;
    // Oq eh um esguicho?
    strcpy(atks[i].descricao, "Uusario esguicha ovo podre para\nfazer o inimigo escorregar\n\nPrecisao: 95%\nCategoria: Especial\nDano: 20");

    i = CLOACA_DE_FERRO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Cloaca de ferro");
    atks[i].precisao = 100;
    atks[i].tipo = FEMEA;
    atks[i].categoria = STATUS;
    atks[i].dano = 20;
    strcpy(atks[i].descricao, "O usuario endurece sua cloaca para aumentar\ntoda a sua defesa\n\nPrecisao: 100%\nCategoria: Status");

    i = PISOTEAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Pisotear");
    atks[i].precisao = 80;
    atks[i].tipo = CAIPIRA;
    atks[i].categoria = FISICO;
    atks[i].dano = 35;
    strcpy(atks[i].descricao, "Usuario usa os pes para destruir os ossos\ndo inimigo\n\nPrecisao: 80%\nCategoria: Fisico\nDano: 35");

    i = CHICOTE_DE_CINTO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Chicote de cinto");
    atks[i].precisao = 90;
    atks[i].tipo = CAPOEIRA;
    atks[i].categoria = FISICO;
    atks[i].dano = 25;
    strcpy(atks[i].descricao, "Usuario usa seu cinto para bater no inimigo\n\nPrecisao: 90%\nCategoria: Fisico\nDano: 25");

    i = PENA_DE_MORTE;

    atks[i].id = i;
    strcpy(atks[i].nome, "Pena de morte");
    atks[i].precisao = 75;
    atks[i].tipo = FANTASMA;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 40;
    strcpy(atks[i].descricao, "O inimigo e mandado para gilhotina\nimediatamente\n\nPrecisao: 75%\nCategoria: Especial\nDano: 40");

    i = VINGARDE_LEVE_OVO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Vingarde leve ovo");
    atks[i].precisao = 95;
    atks[i].tipo = GOTICO;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 21;
    strcpy(atks[i].descricao, "Com seus poderes magicos, levita um ovo\n de encontro com a face de seu oponente\n causando dano\n\nPrecisao: 95%\nCategoria: Especial\nDano: 21");

    i = ALMA_PENADA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Alma penada");
    atks[i].precisao = 85;
    atks[i].tipo = FANTASMA;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 35;
    // Alguem fa�a esse
    strcpy(atks[i].descricao, "Usuario encaixa uma casca de ovo\npela parte traseira do oponente\n\nPrecisao: 85%\nCategoria: Especial\nDano: 35");

    i = SURFAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Surfar");
    atks[i].precisao = 95;
    atks[i].tipo = ANGOLANO;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 27;
    strcpy(atks[i].descricao, "Usuario tira uma onda, causando muito dano\n\nPrecisao: 95%\nCategoria: Especial\nDano: 27");

    i = ENXADA_DE_FERRO;

    atks[i].id = i;
    strcpy(atks[i].nome, "Enxada de ferro");
    atks[i].precisao = 90;
    atks[i].tipo = CAIPIRA;
    atks[i].categoria = FISICO;
    atks[i].dano = 30;
    strcpy(atks[i].descricao, "Usuario usa toda sua experiencia\ndo campo para dar uma enxadada\nno oponente\n\nPrecisao: 90%\nCategoria: Fisico\nDano: 30");

    i = CANCELAR;

    atks[i].id = i;
    strcpy(atks[i].nome, "Cancelar");
    atks[i].precisao = 90;
    atks[i].tipo = TOXICO;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Expoe seu inimigo na internet e bane \nde todas as redes sociais retirando metade \nde seu hp\n\nPrecisao: 90%\nCategoria: Especial");

    i = ERVA_DANINHA;

    atks[i].id = i;
    strcpy(atks[i].nome, "Erva daninha");
    atks[i].precisao = 100;
    atks[i].tipo = ANGOLANO;
    atks[i].categoria = STATUS;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Fuma uma erva um tanto suspeita e debocha\nlegal para aumentar seu ataque absurdamente\nentretanto diminui sua velocidade\ne precisao\n\nPrecisao: 100%\nCategoria: Status");

    i = LADRAO;

    atks[i].id = i;
    strcpy(atks[i].nome, "ladrao");
    atks[i].precisao = 100;
    atks[i].tipo = GOTICO;
    atks[i].categoria = ESPECIAL;
    atks[i].dano = 0;
    strcpy(atks[i].descricao, "Com maestria o usuario copia as habilidades\nde luta do oponente roubando um de seus atks\n\nPrecisao: 100%\nCategoria: Especial");
}

void __baterAsas(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->hp -= damageCalculator(*atacante, *alvo, BATER_ASAS);
}

void __poeira(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->velocidade *= 0.80;
    for (int i = 0; i < 4; i++)
    {
        alvo->atks[i].precisao *= 0.90;
    }

    // TEXTO SOBRE O ATAQUE
    char text[500];
    text[0] = '\0';

    sprintf(&text, " A precisao dos ataques do inimigo diminuiu");
    caixaDeDialogoTexto(&text);
    confirmInput();
}

void __cantar(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->defesa *= 0.75;
    alvo->defesa_especial *= 0.75;

    // TEXTO SOBRE O ATAQUE
    char text[500];
    text[0] = '\0';

    sprintf(&text, " A Defesa do inimigo foi reduzida");
    caixaDeDialogoTexto(&text);
    confirmInput();

    // TEXTO SOBRE O ATAQUE
    char text2[500];
    text2[0] = '\0';

    sprintf(&text2, " A Defesa Especial do inimigo foi reduzida");
    caixaDeDialogoTexto(&text2);
    confirmInput();
}

void __furia(struct galo_status *atacante, struct galo_status *alvo)
{

    atacante->ataque *= 1.10;
    atacante->ataque_especial *= 1.10;
    for (int i = 0; i < 4; i++)
    {
        atacante->atks[i].precisao *= 0.90;
    }

    char text[500];
    text[0] = '\0';

    sprintf(&text, " O Ataque de %s subiu levemente", atacante->nome);
    caixaDeDialogoTexto(&text);
    confirmInput();

    text[0] = '\0';

    sprintf(&text, " O Ataque Especial de %s subiu levemente", atacante->nome);
    caixaDeDialogoTexto(&text);
    confirmInput();

    // TEXTO SOBRE O ATAQUE

    text[0] = '\0';

    sprintf(&text, " A precisao dos ataques de %s diminuiu levemente", atacante->nome);
    caixaDeDialogoTexto(&text);
    confirmInput();
}

void __bicada(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->hp -= damageCalculator(*atacante, *alvo, BICADA);
}

void __arranhar(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ARRANHAR);
}

void __voar(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, VOAR);
}

void __atirar(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ATIRAR);
}

void __bicoDeAco(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, BICO_DE_ACO);
}

void __olharMaligno(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->defesa *= 0.60;
    alvo->defesa_especial *= 0.60;

    // TEXTO SOBRE O ATAQUE
    char text[500];
    text[0] = '\0';

    sprintf(&text, " A Defesa do inimigo foi reduzida drasticamente");
    caixaDeDialogoTexto(&text);
    confirmInput();

    // TEXTO SOBRE O ATAQUE
    char text2[500];
    text2[0] = '\0';

    sprintf(&text2, " A Defesa Especial do inimigo foi reduzida drasticamente");
    caixaDeDialogoTexto(&text2);
    confirmInput();
}

void __jogarOvo(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, JOGAR_OVO);
}

void __ataque_de_asa(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ATAQUE_DE_ASA);
}

void __bicoBroca(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, BICO_BROCA);
}

void __sky_atack(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, SKY_ATACK);
}

void __aeroEgg(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, AERO_EGG);
}

void __gingado(struct galo_status *atacante, struct galo_status *alvo)
{

    atacante->ataque *= 1.5;
    atacante->velocidade *= 1.5;
}

void __au_da_capoeira(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->hp -= damageCalculator(*atacante, *alvo, AU_DA_CAPOEIRA);
}

void __espora_giratoria(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ESPORA_GIRATORIA);
}

void __cortar(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, CORTAR);
}

void __picar(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, PICAR);
}

void __esguicho(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ESGUICHO);
}

void __cloaca_de_ferro(struct galo_status *atacante, struct galo_status *alvo)
{
    atacante->defesa *= 2;
    atacante->defesa_especial *= 2;
}

void __pisotear(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, PISOTEAR);
}

void __chicote_de_cinto(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, CHICOTE_DE_CINTO);
}

void __pena_de_morte(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, PENA_DE_MORTE);
}

void __vingarde_leve_ovo(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, VINGARDE_LEVE_OVO);
}

void __alma_penada(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ALMA_PENADA);
}

void __surfar(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, SURFAR);
}

void __enxada_de_ferro(struct galo_status *atacante, struct galo_status *alvo)
{
    alvo->hp -= damageCalculator(*atacante, *alvo, ENXADA_DE_FERRO);
}

void __cancelar(struct galo_status *atacante, struct galo_status *alvo)
{

    alvo->hp *= 0.5;
}

void __erva_daninha(struct galo_status *atacante, struct galo_status *alvo)
{

    atacante->velocidade *= 0.8;
    atacante->ataque *= 3.0;
    atacante->ataque_especial *= 3.0;
    for (int i = 0; i < 4; i++)
    {
        atacante->atks[i].precisao *= 0.50;
    }
}

void __ladrao(struct galo_status *atacante, struct galo_status *alvo)
{

    int i;

    for (i = 0; i < 4; i++)
    {
        if (atacante->atks[i].id == LADRAO)
        {
            atacante->atks[i] = alvo->atks[rand() % 3];
            break;
        }
    }
}

// Uma função fica guardada na memória, e memória e ponteiros é tipo batman e robin.
// Aqui é criado um ponteiro para função
// O ponteiro vai apontar para todas essas funções de maneira sequencial, tipo um array, que ao serem chamadas de acordo com o indice, vai realizar uma X tarefa
void (*atacar[])(struct galo_status *atacante, struct galo_status *alvo) = {
    __baterAsas, __poeira, __bicada, __cantar, __arranhar, __voar, __atirar, __bicoDeAco, __furia,
    __olharMaligno, __jogarOvo, __ataque_de_asa, __bicoBroca, __sky_atack, __aeroEgg, __gingado,
    __au_da_capoeira, __espora_giratoria, __cortar, __picar, __esguicho, __cloaca_de_ferro, __pisotear,
    __chicote_de_cinto, __pena_de_morte, __vingarde_leve_ovo, __alma_penada, __surfar, __enxada_de_ferro,
    __cancelar, __erva_daninha, __ladrao

};

const int info_x = 35;
const int info_y = 5;

// Essa função printa uma string pulando linhas com o gotoxy
void __print_string(char *str, int x, int y, int n_de_char_em_cada_linha)
{
    gotoxy(x, y);

    for (int i = 0; i < strlen(str); i++)
    {

        if (str[i] == '\n')
        {
            gotoxy(x, ++y);
            continue;
        }
        printf("%c", str[i]);
    }
}

// Informações dos galos
void informacoes_do_galo(struct galo_status galo)
{
    int x = info_x;
    int y = info_y - 2;

    desenhar_quadrado(40, 18, x - 1, y - 1);
    textbackground(BLACK);
    preencher_com_espacos(38, 16, x, y);
    desenhar_quadrado(30, 3, x + 4, y);

    gotoxy((30 + (25 - (strlen(galo.nome)) / 2) - 1), y + 1);
    y += 4;
    x += 4;

    textcolor(GREEN);
    printf("%s", galo.nome);
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(x, y++);
    printf("Age: %.0f %s", galo.idade, galo.idade > 1 ? "years" : "year");
    gotoxy(x, y++);
    printf("Height: %d cm", galo.altura);
    gotoxy(x, y++);
    printf("Weight: %.2f kg", galo.peso);

    y++;
    gotoxy(x, y++);
    textcolor(GREEN);
    printf("HP: %d", galo.hp);
    gotoxy(x, y++);
    textcolor(RED);
    printf("Atk: %d", galo.ataque);
    gotoxy(x, y++);
    printf("Atk Especial: %d", galo.ataque_especial);
    gotoxy(x, y++);
    textcolor(BLUE);
    printf("Def: %d", galo.defesa);
    gotoxy(x, y++);
    printf("Def Especial: %d", galo.defesa_especial);
    textcolor(BLACK);
    textbackground(DARKGRAY);
}

int mudar_cor(int opcao, struct galo_status galo)
{
    // Atualização tem tempo real da tela de ataques

    int x = 40;
    int y = 4;

    for (int i = 0; i < 4; i++)
    {
        textcolor(WHITE);
        gotoxy(x, y++);
        if (opcao == i)
        {
            textcolor(BLACK);
        }
        printf("%s", galo.atks[i].nome);
    }

    while (1)
    {
        char ch = getch();

        if (ch == KEY_UP || ch == 'w' || ch == 'W')
        {
            if (opcao > 0)
            {
                return opcao - 1;
            }
            else
            {
                return 0;
            }
        }
        if (ch == KEY_DOWN || ch == 's' || ch == 'S')
        {
            if (opcao < 3)
            {
                return opcao + 1;
            }
            else
            {
                return 3;
            }
        }

        if (ch == KEY_ESC)
        {
            return -1;
        }
    }
}

void info_atks(galos_ID id)
{

    textcolor(WHITE);
    desenhar_quadrado(51, 24, 30, 1);
    gotoxy(32, 23);
    printf("ESC - Back");

    gotoxy(47, 23);
    printf("W - Move Up");

    gotoxy(60, 23);
    printf("S - Move Down");
    int x = 40;
    int y = 4;

    textcolor(WHITE);

    desenhar_quadrado(25, 6, x - 1, y - 1);

    for (int i = 0; i < 4; i++)
    {
        gotoxy(x, y++);
        printf("%s", galos[id].atks[i].nome);
    }

    textbackground(BLACK);
    desenhar_quadrado(45, 11, x - 7, y + 2);
    __print_string(galos[id].atks[0].descricao, x - 6, y + 3, 43);
    textbackground(DARKGRAY);

    int opcao = mudar_cor(0, galos[id]);

    while (opcao != -1)
    {
        textcolor(WHITE);

        textbackground(BLACK);
        desenhar_quadrado(45, 11, x - 7, y + 2);

        __print_string(galos[id].atks[opcao].descricao, x - 6, y + 3, 43);
        textbackground(DARKGRAY);
        x = 40;
        y = 4;

        for (int i = 0; i < 4; i++)
        {
            gotoxy(x, y++);
            printf("%s", galos[id].atks[i].nome);
        }
        gotoxy(32, 23);
        printf("ESC - Back");

        gotoxy(47, 23);
        printf("W - Move Up");

        gotoxy(60, 23);
        printf("S - Move Down");
        opcao = mudar_cor(opcao, galos[id]);
    }
}

void opcoes()
{
    gotoxy(32, 21);
    printf("[ENTER] Select");
    gotoxy(55, 21);
    printf("[ESPACO] Show Moves");
    gotoxy(32, 22);
    printf("[A] Next");
    gotoxy(55, 22);
    printf("[D] Previous");
    gotoxy(32, 23);
    printf("[R] Random");
}

// Abre o mais lindo menu de seleção da história e retorna um galo
struct galo_status escolher_galo()
{

    textbackground(DARKGRAY);
    clrscr();

    int posx = 3;
    int posy = 2;
    int espacamento_x = 10;
    int espacamento_y = 5;

    galos_ID galo_atual = GALO_DE_TENIS;

    do
    {
        char op;

        do
        {
            clrscr();
            textcolor(WHITE);
            quadrado_sem_espacos(30, 24, 1, 1);

            int backgroundColor = (galo_atual % 15) + 1;

            textbackground(backgroundColor);
            preencher_com_espacos(28, 22, 2, 2);

            drawSpriteColorScl(7, 3, &galoSprites[galo_atual][0], 1, 1);
            textcolor(WHITE);

            textbackground(DARKGRAY);

            desenhar_quadrado(51, 24, 30, 1);
            informacoes_do_galo(galos[galo_atual]);
            opcoes();

            op = getch();

            if (op == KEY_ENTER)
            {
                return galos[galo_atual];
            }
            if (op == ' ')
            {
                info_atks(galo_atual);
                break;
            }
            if (op == 'D' || op == 'd' || op == KEY_RIGHT)
            {
                if (galo_atual == 27)
                {
                    galo_atual = 0;
                }
                else
                {
                    galo_atual++;
                    break;
                }
            }
            if (op == 'A' || op == 'a' || op == KEY_LEFT)
            {
                if (galo_atual == 0)
                {
                    galo_atual = 27;
                }
                else
                {
                    galo_atual--;
                }
                break;
            }
            if (op == 'R' || op == 'r')
            {
                return galos[rand() % 28];
            }

        } while (1);

    } while (1);
}

#endif // GALOS__H
