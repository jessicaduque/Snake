#include <stdio.h>
#include <stdlib.h>
// Para poder pegar input do teclado sem a necessidade de input do usuário
#include <conio.h>
#include <time.h>
#include <string.h>

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
int rCobraX[100], rCobraY[100];
int tamRCobra;

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
    tamRCobra = 0;
}

void desenha()
{
    int i, j, k;
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
                else 
                {
                    int flag = 0;
                    for (k = 0; k < tamRCobra; k++) 
                    {
                        if (rCobraX[k] == i && rCobraY[k] == j) {
                            printf("%c", char(COBR));
                            flag = 1;
                        }
                    }
                    if (!flag) {
                        printf(" ");
                    }
                }
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
    int rCAntX = rCobraX[0];
    int rCAntY = rCobraY[0];
    int auxX, auxY;

    rCobraX[0] = x;
    rCobraY[0] = y;
    for (int i = 1; i < tamRCobra; i++) {
        auxX = rCobraX[i];
        auxY = rCobraY[i];
        rCobraX[i] = rCAntX;
        rCobraY[i] = rCAntY;
        rCAntX = auxX;
        rCAntY = auxY;
    }

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

    if (x == 0 || x == largura + 2 || y == 0 || y == altura + 2) 
    {
        fimDoJogo = 1;
    }
    for (int i = 0; i < tamRCobra; i++) {
        if (rCobraX[i] == x && rCobraY[i] == y) {
            fimDoJogo = 1;
        }
    }
    if (x == frutaX && y == frutaY) {
        pontos = pontos + 10;
        frutaX = rand() % largura + 1;
        frutaY = rand() % altura + 1;
        tamRCobra++;
    }
}

void finaliza()
{
    FILE* arquivo;
    errno_t erro;
    int leuok = 0;
    char nome[20];

    struct tprecords {
        char nome[20];
        int pontos;
    };

    tprecords scores[5];
    
    printf("\nEntre com seu Apelido: ");
    scanf_s("%19s", nome, 20);

    erro = fopen_s(&arquivo, "recordes.txt", "r");
    if (erro){
        printf("Erro ao tentar abrir o arquivo de records!");
    }
    else {
        for (int i = 0; i < 5; i++) {
            leuok = fscanf_s(arquivo, "%19s", &scores[i].nome, 20);
            if (!leuok) {
                printf("Erro ao tentar ler o arquivo de records na iteração %d", i);
                break;
            }
            else {
                leuok = fscanf_s(arquivo, "%d", &scores[i].pontos);
                if (!leuok) {
                    printf("Erro ao tentar ler o arquivo de records na iteração %d", i);
                    break;
                }
            }
        }
        fclose(arquivo);
        if (leuok) {
            for (int i = 0; i < 5; i++) {
                if (pontos > scores[i].pontos) {
                    for (int j = 4; j > i; j--) {
                        scores[j].pontos = scores[j - 1].pontos;
                        strcpy_s(scores[j].nome, scores[j - 1].nome);
                    }
                    scores[i].pontos = pontos;
                    strcpy_s(scores[i].nome, nome);
                    break;
                }
            }
            erro = fopen_s(&arquivo, "recordes.txt", "w");
            if (erro) {
                printf("Erro ao tentar abrir o arquivo de records!");
            }
            else {
                for (int i = 0; i < 5; i++) {
                    fprintf_s(arquivo, "%s %d\n", scores[i].nome, scores[i].pontos);
                }
            }
            fclose(arquivo);
        }
    }
    printf("\n\n\n*** FIM DE JOGO ***\n\n\nSua pontuação foi: %d", pontos);
}