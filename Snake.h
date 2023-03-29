#include <stdio.h>
#include <stdlib.h>
// Para poder pegar input do teclado sem a necessidade de input do usuário
#include <conio.h>
#include <time.h>

#define STOP 0
#define ESQD 1
#define DIRT 2
#define CIMA 3
#define BAIX 4
#define MURO 178
#define COBR 219
#define FRUT 149


int fimDoJogo = 0;
const int largura = 20;
const int altura = 20;
int x, y, frutaX, frutaY, pontos, direcao;

void inicializa()
{
    time_t t;
    fimDoJogo = 0;
    direcao = STOP;
    x = largura / 2;
    y = altura / 2;
    pontos = 0;
    srand(time(&t));
    frutaX = rand() % largura + 1;
    frutaY = rand() % largura + 1;
}

void desenha()
{
    int i, j;
    system("cls");

    // Imprime primeira linha
    for (i = 0; i <= largura + 2; i++)
    {
        printf("%c", char(MURO));
    }

    // Imprime outras linhas
    for (j = 1; j <= altura + 1; j++)
    {
        printf("\n");
        for (i = 0; i <= largura + 2; i++)
        {
            if (i == 0 || i == largura + 2) {
                printf("%c", char(MURO));
            }
            else
            {
                if (i == x && j == y)
                {
                    printf("%c", char(COBR));
                }
                else if (i == frutaX && j == frutaY)
                {
                    printf("%c", char(FRUT));
                }
                else printf(" ");
            }
        }
    }

    printf("\n");
    // Imprime última linha
    for (i = 0; i <= largura + 2; i++)
    {
        printf("%c", char(MURO));
    }

    printf("\npontos = %d", pontos);
}

void entrada()
{
    if (_kbhit()) {
        switch (_getch())
        {
        case 'w':
            direcao = CIMA;
            break;
        case 'W':
            direcao = CIMA;
            break;
        case 'a':
            direcao = ESQD;
            break;
        case 'A':
            direcao = ESQD;
            break;
        case 'd':
            direcao = DIRT;
            break;
        case 'D':
            direcao = DIRT;
            break;
        case 's':
            direcao = BAIX;
            break;
        case 'S':
            direcao = BAIX;
            break;
        case 'x':
            fimDoJogo = 1;
            break;
        case 'X':
            fimDoJogo = 1;
            break;
        case 224:
            if (_kbhit())
            {
                switch (_getch()) {
                case 72:
                    direcao = CIMA;
                    break;
                case 75:
                    direcao = ESQD;
                    break;
                case 77:
                    direcao = DIRT;
                    break;
                case 80:
                    direcao = BAIX;
                    break;
                }
            }
        }
    }
}

void logica()
{
    switch (direcao)
    {
    case CIMA:
        y--;
        break;
    case ESQD:
        x--;
        break;
    case DIRT:
        x++;
        break;
    case BAIX:
        y++;
        break;
    case STOP:
        direcao = rand() % 4 + 1;
        break;
    }

    if (x == 0 || x == largura + 2 || y == 0 || y == altura + 2) {
        fimDoJogo = 1;
    }
    if (x == frutaX && y == frutaY) {
        pontos = pontos + 10;
        frutaX = rand() % largura + 1;
        frutaY = rand() % altura + 1;
    }
}

void finaliza()
{
    system("cls");
    printf("\n\n\n*** FIM DE JOGO ***\n\n\nSua pontuação foi: %d", pontos);
}