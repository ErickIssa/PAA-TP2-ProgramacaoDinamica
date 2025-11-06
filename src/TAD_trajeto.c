#include <stdio.h>
#include <stdlib.h>

#include "../include/TAD_mapa.h"
#include "../include/TAD_trajeto.h"

//mapa.celula[tempo][linha][coluna]

void melhorCaminho(Atlas atlas){
    Mapa mapa = atlas.mapa;
    Mapa mapaPD = atlas.mapaPD;

    for(int i = 0; i < mapa.largura; i++){
        for(int j = 0; j < mapa.altura;j++){
            if(celulaValida(mapa.celula[presente][i][j]) == 1){
                if(testaDirecoes(mapa,presente,i,j) == -999){
                    continue;
                }
                else{mapa.celula[presente][i][j] = mapa.celula[presente][i][j] + testaDirecoes(mapa,presente,i,j);}
                printf("%d\n", testaDirecoes(mapa,presente,i,j));
            }
        }
    }
}

int testaDirecoes(Mapa mapa, int tempo, int i, int j) {
    int melhorValor = -999; // começa como "nenhum valor válido encontrado"
    int valor;

    // Direção 1: diagonal superior esquerda
    if (i - 1 >= 0 && j - 1 >= 0) {
        valor = mapa.celula[tempo][i - 1][j - 1];
        if (valor > 0 && (melhorValor == -1 || valor > melhorValor)) {
            melhorValor = valor;
        }
    }

    // Direção 2: esquerda
    if (j - 1 >= 0) {
        valor = mapa.celula[tempo][i][j - 1];
        if (valor > 0 && (melhorValor == -1 || valor > melhorValor)) {
            melhorValor = valor;
        }
    }

    // Direção 3: diagonal inferior esquerda
    if (i + 1 < mapa.altura && j - 1 >= 0) {
        valor = mapa.celula[tempo][i + 1][j - 1];
        if (valor > 0 && (melhorValor == -1 || valor > melhorValor)) {
            melhorValor = valor;
        }
    }

    return melhorValor;
}

