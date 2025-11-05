#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_mapa.h"

void inicializarMapaVazio(Atlas *atlas, int altura, int largura) {
    Mapa *mapa = &atlas->mapa;
    int tempos = 2;

    mapa->altura = altura;
    mapa->largura = largura;

    mapa->celula = malloc(tempos * sizeof(int **)); //isso aponta para um vetor de planos(passado e futuro)
    for (int t = 0; t < tempos; t++) {
        mapa->celula[t] = malloc(altura * sizeof(int *)); //dentro de cada tempo tem um vetor de ponteiro para as linhas
        for (int i = 0; i < altura; i++) {
            mapa->celula[t][i] = malloc(largura * sizeof(int));
            for (int j = 0; j < largura; j++) { // a linha em si
                mapa->celula[t][i][j] = 999;
            }
        }
    }
}

void imprimeMapa(Atlas atlas){
    Mapa mapa = atlas.mapa;
    printf("--Mapa Presente--\n");
    for(int i = 0;i<mapa.largura;i++){
        for(int j = 0;j<mapa.altura;j++){
            printf("%d ",mapa.celula[presente][i][j]);
        }
        printf("\n");
    }
    printf("--Mapa Passado--\n");
    for(int i = 0;i<mapa.largura;i++){
        for(int j = 0;j<mapa.altura;j++){
            printf("%d ",mapa.celula[passado][i][j]);
        }
        printf("\n");
    }
}

