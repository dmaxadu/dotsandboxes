#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CHECA_NUMERO(a, b) ((a != '+' && (a < '0' || a > '9')) || (a == '+' && (b == '\0' || b < '0' || b > '9')))

/* Checa se o sistema operacional e um Windows ou um Linux e em seguida determina algumas macros */
#ifdef _WIN32
#define LIMPA_TELA "cls"
#define MUDA_COR_LETRA "COLOR "
#define MUDA_COR_FUNDO "COLOR "
#define PRETO "0"
#define VERMELHO "4"
#define AMARELO "6"
#define RESETA_COR "COLOR 0f"

#elif __linux__
#define LIMPA_TELA "tput clear"
#define MUDA_COR_LETRA "tput setaf "
#define MUDA_COR_FUNDO "tput setab "
#define PRETO "0"
#define VERMELHO "1"
#define AMARELO "3"
#define RESETA_COR "tput setaf 9"

#endif

void Cooldown()
{
    unsigned long int i;
    for (i = 0; i < 1000000000; i++)
    {
    }
}

typedef struct _CAIXA
{
    int r1, r2, r3, r4;
} CAIXA;

typedef struct _VERTICAL
{
    char c1, c2, c3, c4;
} VERTICAL;

int *usado;
CAIXA caixa[9];
VERTICAL vertical[12];
char vetorHorizontal[12][13];
int *jaPontuado;
int p1 = 0, p2 = 0;
int vez = 0;
char numero[11];

void Checa(int *usado, int escolhido);

void DefineCaixasEVertical()
{
    int i;
    for (i = 0; i < 12; i++)
    {
        vertical[i].c1 = ' ';
        vertical[i].c2 = ' ';
        vertical[i].c3 = ' ';
        vertical[i].c4 = ' ';
    }

    caixa[0].r1 = 1;
    caixa[0].r2 = 4;
    caixa[0].r3 = 13;
    caixa[0].r4 = 14;

    caixa[1].r1 = 2;
    caixa[1].r2 = 5;
    caixa[1].r3 = 14;
    caixa[1].r4 = 15;

    caixa[2].r1 = 3;
    caixa[2].r2 = 6;
    caixa[2].r3 = 15;
    caixa[2].r4 = 16;

    caixa[3].r1 = 4;
    caixa[3].r2 = 7;
    caixa[3].r3 = 17;
    caixa[3].r4 = 18;

    caixa[4].r1 = 5;
    caixa[4].r2 = 8;
    caixa[4].r3 = 18;
    caixa[4].r4 = 19;

    caixa[5].r1 = 6;
    caixa[5].r2 = 9;
    caixa[5].r3 = 19;
    caixa[5].r4 = 20;

    caixa[6].r1 = 7;
    caixa[6].r2 = 10;
    caixa[6].r3 = 21;
    caixa[6].r4 = 22;

    caixa[7].r1 = 8;
    caixa[7].r2 = 11;
    caixa[7].r3 = 22;
    caixa[7].r4 = 23;

    caixa[8].r1 = 9;
    caixa[8].r2 = 12;
    caixa[8].r3 = 23;
    caixa[8].r4 = 24;
}

void Desenha()
{
    system(LIMPA_TELA);
    printf("\nPontos do jogador 1: %d                               Pontos do jogador 2: %d\n", p1, p2);
    printf("%c%s %c%s %c%s %c\n", 254, vetorHorizontal[0], 254, vetorHorizontal[1], 254, vetorHorizontal[2], 254);
    printf("%c            %c            %c            %c\n", vertical[0].c1, vertical[1].c1, vertical[2].c1, vertical[3].c1);
    printf("%c            %c            %c            %c\n", vertical[0].c2, vertical[1].c2, vertical[2].c2, vertical[3].c2);
    printf("13          14            15           16\n");
    printf("%c            %c            %c            %c\n", vertical[0].c3, vertical[1].c3, vertical[2].c3, vertical[3].c3);
    printf("%c            %c            %c            %c\n", vertical[0].c4, vertical[1].c4, vertical[2].c4, vertical[3].c4);
    printf("%c%s %c%s %c%s %c\n", 254, vetorHorizontal[3], 254, vetorHorizontal[4], 254, vetorHorizontal[5], 254);
    printf("%c            %c            %c            %c\n", vertical[4].c1, vertical[5].c1, vertical[6].c1, vertical[7].c1);
    printf("%c            %c            %c            %c\n", vertical[4].c2, vertical[5].c2, vertical[6].c2, vertical[7].c2);
    printf("17          18            19           20\n");
    printf("%c            %c            %c            %c\n", vertical[4].c3, vertical[5].c3, vertical[6].c3, vertical[7].c3);
    printf("%c            %c            %c            %c\n", vertical[4].c4, vertical[5].c4, vertical[6].c4, vertical[7].c4);
    printf("%c%s %c%s %c%s %c\n", 254, vetorHorizontal[6], 254, vetorHorizontal[7], 254, vetorHorizontal[8], 254);
    printf("%c            %c            %c            %c\n", vertical[8].c1, vertical[9].c1, vertical[10].c1, vertical[11].c1);
    printf("%c            %c            %c            %c\n", vertical[8].c2, vertical[9].c2, vertical[10].c2, vertical[11].c2);
    printf("21          22            23           24\n");
    printf("%c            %c            %c            %c\n", vertical[8].c3, vertical[9].c3, vertical[10].c3, vertical[11].c3);
    printf("%c            %c            %c            %c\n", vertical[8].c4, vertical[9].c4, vertical[10].c4, vertical[11].c4);
    printf("%c%s%c%s%c%s%c\n", 254, vetorHorizontal[9], 254, vetorHorizontal[10], 254, vetorHorizontal[11], 254);
}

int main(void)
{
    usado = (int *)calloc(25, sizeof(int));
    jaPontuado = (int *)calloc(9, sizeof(int));
    int start = 0, i;

    system(LIMPA_TELA);

    DefineCaixasEVertical();
    printf("\t\t\tBem vindo ao\n");
    system(MUDA_COR_LETRA VERMELHO);
    Cooldown();

    while (start != 1)
    {
        system(LIMPA_TELA);
        printf("______      _                         _  ______                    \n");
        printf("|  _  \\    | |                       | | | ___ \\                   \n");
        printf("| | | |___ | |_ ___    __ _ _ __   __| | | |_/ / _____  _____  ___ \n");
        printf("| | | / _ \\| __/ __|  / _` | '_ \\ / _` | | ___ \\/ _ \\ \\/ / _ \\/ __|\n");
        printf("| |/ / (_) | |_\\__ \\ | (_| | | | | (_| | | |_/ / (_) >  <  __/\\__ \\ \n");
        printf("|___/ \\___/ \\__|___/  \\__,_|_| |_|\\__,_| \\____/ \\___/_/\\_\\___||___/ \n");
        printf("\n\nDigite 1 para iniciar: ");
        scanf("%s", numero);
        if (atoi(numero) == 1)
            start = 1;
        else
        {
            printf("Valor invalido!");
            Cooldown();
        }
    }
    do
    {
    } while (getchar() != '\n');

    system(RESETA_COR);
    int escolhido = 0;

    for (i = 0; i < 12; i++)
    {
        sprintf(vetorHorizontal[i], "     %d     ", i + 1);
    }
    for (i = 0; i < 24; i++)
    {
        if (start == 1)
        {
            for (i = 0; i < 24; i++)
            {
                Desenha();
                printf("\nJogador %d, escolha uma reta: ", vez % 2 + 1);
                scanf("%s", numero);

                if (CHECA_NUMERO(numero[0], numero[1]) || atoi(numero) <= 0 || atoi(numero) >= 25)
                {
                    printf("Coordenada invalida! Por favor, digite novamente!\n");
                    Cooldown();
                    i--;
                }
                else if (usado[escolhido = atoi(numero)] == 0)
                {
                    usado[escolhido] = 1;
                    if (vez % 2 == 0)
                    {
                        if (escolhido < 13)
                            sprintf(vetorHorizontal[escolhido - 1], "ooooo%dooooo", escolhido);
                        else
                        {
                            vertical[escolhido - 12 - 1].c1 = 'o';
                            vertical[escolhido - 12 - 1].c2 = 'o';
                            vertical[escolhido - 12 - 1].c3 = 'o';
                            vertical[escolhido - 12 - 1].c4 = 'o';
                        }
                    }
                    else
                    {
                        if (escolhido < 13)
                            sprintf(vetorHorizontal[escolhido - 1], "xxxxx%dxxxxx", escolhido);
                        else
                        {
                            vertical[escolhido - 12 - 1].c1 = 'x';
                            vertical[escolhido - 12 - 1].c2 = 'x';
                            vertical[escolhido - 12 - 1].c3 = 'x';
                            vertical[escolhido - 12 - 1].c4 = 'x';
                        }
                    }
                    Checa(usado, escolhido);
                    vez++;
                }
                else
                {
                    puts("já escolhido!\n");
                    Cooldown();
                    i--;
                }
            }
        }
    }
    Desenha();
    printf("O ganhador e:\n");
    printf("              .-=========-.\n");
    printf("              \\'-=======-'/\n");
    printf("              _|   .=.   |_\n");
    printf("             ((|  {{1}}  |))\n");
    printf("              \\|   /|\\   |/\n");
    printf("               \\__ '`' __/\n");
    printf("                 _`) (`_\n");

    /* imprime a base do troféu de acordo com o jogador vencedor */
    if (p1 > p2)
    {
        printf("               _/!!!1!!!\\_\n");
        printf("              /___________\\\n");
        printf("            Parabens jogador 1!!\n");
    }
    else
    {
        printf("               _/!!!2!!!\\_\n");
        printf("              /___________\\\n");
        printf("            Parabens jogador 2!!\n");
    }

#ifdef _WIN32
    system("COLOR 06");
    system("COLOR 60");
    system("COLOR 06");
    system("COLOR 60");
    system("COLOR 06");
    system("COLOR 60");
    system("COLOR 06");
    system("COLOR 60");
    system("COLOR 06");
#elif __linux__
    system(MUDA_COR_LETRA AMARELO);
    system(MUDA_COR_FUNDO PRETO);
    system(MUDA_COR_LETRA PRETO);
    system(MUDA_COR_FUNDO AMARELO);
    system(MUDA_COR_LETRA AMARELO);
    system(MUDA_COR_FUNDO PRETO);

    system(MUDA_COR_LETRA PRETO);
    system(MUDA_COR_FUNDO AMARELO);
    system(MUDA_COR_LETRA AMARELO);
    system(MUDA_COR_FUNDO PRETO);

    system(MUDA_COR_LETRA PRETO);
    system(MUDA_COR_FUNDO AMARELO);
    system(MUDA_COR_LETRA AMARELO);
    system(MUDA_COR_FUNDO PRETO);

    system(MUDA_COR_LETRA PRETO);
    system(MUDA_COR_FUNDO AMARELO);
    system(MUDA_COR_LETRA AMARELO);
    system(MUDA_COR_FUNDO PRETO);
#endif

    return 0;
}

void Checa(int *usado, int escolhido)
{
    int controlador = 0;
    int vezInicial = vez;
    int ponto = 0;
    /* caixa 0 */
    if (!jaPontuado[0])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[0].r1] && usado[caixa[0].r2] && usado[caixa[0].r3] && usado[caixa[0].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[0].r1 || escolhido == caixa[0].r2 || escolhido == caixa[0].r3 || escolhido == caixa[0].r4)
            {
                ponto++;
                jaPontuado[0] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[1])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[1].r1] && usado[caixa[1].r2] && usado[caixa[1].r3] && usado[caixa[1].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[1].r1 || escolhido == caixa[1].r2 || escolhido == caixa[1].r3 || escolhido == caixa[1].r4)
            {
                ponto++;
                jaPontuado[1] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[2])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[2].r1] && usado[caixa[2].r2] && usado[caixa[2].r3] && usado[caixa[2].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[2].r1 || escolhido == caixa[2].r2 || escolhido == caixa[2].r3 || escolhido == caixa[2].r4)
            {
                /*if (vezInicial % 2 == 0)
                    p2++;
                else
                    p1++;*/
                ponto++;
                jaPontuado[2] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[3])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[3].r1] && usado[caixa[3].r2] && usado[caixa[3].r3] && usado[caixa[3].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[3].r1 || escolhido == caixa[3].r2 || escolhido == caixa[3].r3 || escolhido == caixa[3].r4)
            {
                ponto++;
                jaPontuado[3] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[4])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[4].r1] && usado[caixa[4].r2] && usado[caixa[4].r3] && usado[caixa[4].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[4].r1 || escolhido == caixa[4].r2 || escolhido == caixa[4].r3 || escolhido == caixa[4].r4)
            {
                ponto++;
                jaPontuado[4] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[5])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[5].r1] && usado[caixa[5].r2] && usado[caixa[5].r3] && usado[caixa[5].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[5].r1 || escolhido == caixa[5].r2 || escolhido == caixa[5].r3 || escolhido == caixa[5].r4)
            {
                ponto++;
                jaPontuado[5] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[6])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[6].r1] && usado[caixa[6].r2] && usado[caixa[6].r3] && usado[caixa[6].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[6].r1 || escolhido == caixa[6].r2 || escolhido == caixa[6].r3 || escolhido == caixa[6].r4)
            {
                ponto++;
                jaPontuado[6] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[7])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[7].r1] && usado[caixa[7].r2] && usado[caixa[7].r3] && usado[caixa[7].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[7].r1 || escolhido == caixa[7].r2 || escolhido == caixa[7].r3 || escolhido == caixa[7].r4)
            {
                ponto++;
                jaPontuado[7] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }

    if (!jaPontuado[8])
    {
        /* checa se todas as retas ja foram escolhidas na caixa x */
        if (usado[caixa[8].r1] && usado[caixa[8].r2] && usado[caixa[8].r3] && usado[caixa[8].r4])
        {
            /* checa se escolhido é uma das retas*/
            if (escolhido == caixa[8].r1 || escolhido == caixa[8].r2 || escolhido == caixa[8].r3 || escolhido == caixa[8].r4)
            {
                ponto++;
                jaPontuado[8] = 1;
                /* checa se vez ja foi decrementada */
                if (controlador != 1)
                {
                    controlador++;
                    if (vez >= 0)
                        vez--;
                }
            }
        }
    }
    if (vezInicial % 2 == 0)
        p1 += ponto;
    else
        p2 += ponto;
}