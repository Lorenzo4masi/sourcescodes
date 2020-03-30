/*
se l' altro sta per fare punto ed io no
    difendi
altrimenti
    piazza

*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tic_tac_toe.h"
int mat[3][3];
int coord[4];
int end = N;
int first = Y;


int main()
{
    srand(time(NULL));
    while (end == N)
    {
        stampa();
        turno_giocatore();
        turno_computer();
    }
}

int turno_giocatore(void)
{
    int i = 0;
    char input[2];

    for (i = 0;i <= 2;++i)
        input[i] = getchar();
    if (input[1] > '3' || input[1] < '1' || input[0] > 'c' || input[0] < 'A' || input[0] > 'C' && input[0] < 'a' || mat[input[0] - 'a'][input[1] - '1'] != 0 || mat[input[0] - 'A'][input[1] - '1'] != 0)
        turno_giocatore();
    else
    {
        if (input[0] <= 'C')
            input[0] |= 32;
        mat[input[0] - 'a'][input[1] - '1'] = 1;
    }
}

                    /* CONTROLLA LA VITTORIA, LA SCONFITTA, LA POSSIBILITA' DI FARE PUNTO O DI PIAZZARE SIA DEL GIOCATORE CHE DELLA MACCHINA */
int somma(int type,int onetime,int check)
{
    int somma = 0;
    int spazi = 0;
    int space = 0;
    int count = 0;
    int i = 0;
    int a = 0;

    if (check == Y)
    {
        if (type == C)
            somma = -3;
        else
            somma = 3; 
        spazi = 0;
        onetime = Y;
    }
    else
    {
        if (type == C)
            somma = -2;
        else
            somma = 2;
        spazi = 1;
    }

    while (count != 3)
    {
                    /* ALTEZZA */
        for (i = 0;i <= 2;++i)
        {
            for (a = 0;a <= 2;++a)
                if (mat[a][i]==0)
                    ++space;

            if (mat[0][i]+mat[1][i]+mat[2][i]==somma && space == spazi)
            {
                coord[0] = 0;
                coord[1] = i;
                coord[2] = 2;
                coord[3] = i;
                return Y;
            }
            space = 0;
        }
                    /* LARGHEZZA */
        for (i = 0;i <= 2;++i)
        {
            for (a = 0;a <= 2;++a)
                if (mat[i][a]==0)
                    ++space;
            if (mat[i][0]+mat[i][1]+mat[i][2]==somma && space == spazi)
            {
                coord[0] = i;
                coord[1] = 0;
                coord[2] = i;
                coord[3] = 2;
                return Y;
            }
            space = 0;
        }
                    /* DIAGONALE 1 */
            for (i = 0;i <= 2;++i)
                if (mat[i][i]==0)
                    ++space;
            if (mat[0][0]+mat[1][1]+mat[2][2]==somma && space == spazi)
            {
                coord[0] = 0;
                coord[1] = 0;
                coord[2] = 2;
                coord[3] = 2;
                return Y;
            }
            space = 0;
                    /* DIAGONALE 2 */
            for (i = 0,a = 2;i <= 2 && a >= 0;++i,--a)
                if (mat[a][i]==0)
                    ++space;
            if (mat[0][2]+mat[1][1]+mat[2][0]==somma && space == spazi)
            {
                coord[0] = 0;
                coord[1] = 2;
                coord[2] = 2;
                coord[3] = 0;
                return Y;
            }
            space = 0;
                    /* CONSIDERA LE OPZIONI DELLA CHIAMATA PER USCIRE */
            if (type == P || onetime == Y)
                return N;
                    /* RIPETE IL PROCEDIMENTO CON SOMMA = +-1 E SPAZI = 2 ,POI CON SOMMA = 0 E SPAZI = 1 */
            ++count;
            ++somma;
            if ( count == 2)
                spazi = 1;
            else
                ++spazi;  
    }
                    /* IN CASO CHE NON ABBIA TROVATO NULLA */
    return N;
}  
                    /* TURNO DEL COMPUTER*/
int turno_computer(void)
{
    int i = 0;
    int a = 0;
    int space = 0;

                    /* IN CASO SIA LA PRIMA VOLTA */
    if (first == Y)
    {
                    /* SE CENTRO LIBERO */
        if (mat[1][1] == 0)
        { 
            first = N;
            mat[1][1] = -1;
            return 0;
        }
        else
        {           /* OCCUPA UNO DEI 4 ANGOLI */
            first = N;
            corners(); 
            return 0;
        } 
    }
                    /* SE L' AVVERSARIO STA PER FARE PUNTO E COMPUTER NO, DIFENDI, ALTRIMENTI PIAZZA */
    if (somma(C,Y,N)==N && somma(P,N,N)==Y)
        imposta();
    else
    {
        somma(C,N,N); 
        imposta();
    }
                    /* SE LA SOMMA E' 3 IL GIOCATORE HA VINTO */
    if (somma(P,N,Y)==Y)
    {
        stampa();
        printf("Hai vinto!\n");
        end = Y;
        return 0;
    }
                    /* SE LA SOMMA E' -3 IL COMPUTER HA VINTO */
    else if (somma(C,N,Y)==Y)
    {
        stampa();
        printf("Hai perso\n");
        end = Y;
        return 0;
    }
                    /* SE NON CI SONO SPAZI VUOTI PAREGGIO */
    for (a = 0;a <= 2;++a)
        for (i = 0;i <= 2;++i)
            if (mat[a][i] == 0)
                ++space;
    if (space == 0)
    {
        stampa();
        printf("Pareggio");
        end = Y;
        return 0;
    }
}
                    /* STAMPA IL TIC_TAC_TOE */
int stampa(void)
{
    int y = 0;
    int x = 0;
    char copy[3][3];
                    /* CLONA MAT IN COPY E LO STAMPA COME CARATTERE */
    for (y = 0;y <= 2;++y)
    {
        for (x = 0;x <= 2;++x)
        {
            if (mat[y][x] == 1)
                copy[y][x] = 'X';
            else if (mat[y][x] == -1)
                copy[y][x] = 'O';
            else
                copy[y][x] = 0; 
        }
    }
    system("cls");
    printf("        1      2     3\n            |     |\n     A   %c  |  %c  |  %c\n       _____|_____|_____\n            |     |\n     B   %c  |  %c  |  %c\n       _____|_____|_____\n            |     |\n     C   %c  |  %c  |  %c\n            |     |\n",copy[0][0],copy[0][1],copy[0][2],copy[1][0],copy[1][1],copy[1][2],copy[2][0],copy[2][1],copy[2][2]);
}

                    /* IMPOSTA IL CURSORE NEL PRIMO PUNTO VUOTO IN COORD */
int imposta(void)
{
    int i = 0;
    int a = 0;
                    /* CERCA IN TUTTE LE STRISCE ORIZZONTALI */
    if (coord[0] == coord[2])
    {
        for (i = coord[1];i <= coord[3];++i)
            if (mat[coord[0]][i] == 0)
            {
                mat[coord[0]][i] = -1;
                return 0;
            }
    }
                    /* CERCA IN TUTTE LE STRISCE VERTICALI */
    else if (coord[1] == coord[3])
    {
        for (i = coord[0];i <= coord[2];++i)
            if (mat[i][coord[1]] == 0)
            {
                mat[i][coord[1]] = -1;
                return 0;
            }
    }
                    /* CERCA NELLA DIAGONALE 1 */
    else if (coord[0] == 0 && coord[3] == 2)
    {
        for (i = 0;i <= 2;++i)
        if (mat[i][i] == 0)
        {
            mat[i][i] = -1;
            return 0;
        }
    }
                    /* CERCA NELLA DIAGONALE 2 */
    else
    {
        for (i = 0,a = 2;i <= 2 && a >= 0;++i,--a)
        if (mat[a][i] == 0)
        {
            mat[a][i] = -1;
            return 0;
        }
    }
}

                    /* OCCUPA UNO DEI 4 ANGOLI */
int corners(void)
{
    int x = rand() % 100;
    srand(time(NULL));
    int y = rand() % 100;

    if (x >= 50)
        x = 2;
    else
        x = 0;

    if (y >= 50)
        y = 2;
    else 
        y = 0;

    mat[y][x] = -1;
}