#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_mapa.h"

int celulaValida(int n){
    if(n == invalido){
        return 0;
    }else{
        return 1;
    }
}

void inicializarAtlasVazio(Atlas *atlas, int altura, int largura, int forcaTripulacao, int descanso, int forcaNikador) {
    Mapa *mapa = &atlas->mapa;
    Mapa *mapaPD = &atlas->mapaPD;
    int tempos = 2;

    atlas->forcaInicial = forcaTripulacao;
    atlas->descanso = descanso;
    atlas->forcaNikador = forcaNikador;

    // inicializa o mapa normal
    mapa->altura = altura;
    mapa->largura = largura;

    mapa->celula = malloc(tempos * sizeof(int **));
    for (int t = 0; t < tempos; t++) {
        mapa->celula[t] = malloc(altura * sizeof(int *));
        for (int i = 0; i < altura; i++) {
            mapa->celula[t][i] = malloc(largura * sizeof(int));
            for (int j = 0; j < largura; j++) {
                mapa->celula[t][i][j] = invalido;
            }
        }
    }

    // inicializa mapaPD
    mapaPD->altura = altura;
    mapaPD->largura = largura;

    mapaPD->celula = malloc(tempos * sizeof(int **));
    for (int t = 0; t < tempos; t++) {
        mapaPD->celula[t] = malloc(altura * sizeof(int *));
        for (int i = 0; i < altura; i++) {
            mapaPD->celula[t][i] = malloc(largura * sizeof(int));
            for (int j = 0; j < largura; j++) {
                mapaPD->celula[t][i][j] = invalido;
            }
        }
    }
}


void imprimeMapa(Atlas atlas) {
    Mapa mapa = atlas.mapa;
    printf("Forca Inicial: %d | Descanso: %d | Forca Nikador: %d\n",
           atlas.forcaInicial, atlas.descanso, atlas.forcaNikador);

    printf("--Mapa Presente--\n");
    for (int i = 0; i < mapa.altura; i++) {
        for (int j = 0; j < mapa.largura; j++) {
            int valor = mapa.celula[presente][i][j];
            if (valor == invalido)
                printf("*** ");
            else if (valor == teletransporte)
                printf("AAA ");
            else
                printf("%03d ", valor);
        }
        printf("\n");
    }

    printf("--Mapa Passado--\n");
    for (int i = 0; i < mapa.altura; i++) {
        for (int j = 0; j < mapa.largura; j++) {
            int valor = mapa.celula[passado][i][j];
            if (valor == invalido){
                printf("*** ");
            }
            else if (valor == teletransporte){
                printf("AAA ");
            }
            else{printf("%03d ", valor);}
        }
        printf("\n");
    }
}

void imprimeMapaPD(Atlas atlas) {
    Mapa mapa = atlas.mapaPD;
    printf("MAPA PD --- para debug\n ");

    printf("--Mapa Presente--\n");
    for (int i = 0; i < mapa.altura; i++) {
        for (int j = 0; j < mapa.largura; j++) {
            int valor = mapa.celula[presente][i][j];
            if (valor == invalido){
                printf("*** ");
            }
            else if (valor == teletransporte){
                printf("AAA ");
            }
            else{printf("%03d ", valor);}
        }
        printf("\n");
    }

    printf("--Mapa Passado--\n");
    for (int i = 0; i < mapa.altura; i++) {
        for (int j = 0; j < mapa.largura; j++) {
            int valor = mapa.celula[passado][i][j];
            if (valor == invalido){
                printf("*** ");
            }
            else if (valor == teletransporte){
                printf("AAA ");
            }
            else{
                printf("%03d ", valor);
            }
        }
        printf("\n");
    }
}
