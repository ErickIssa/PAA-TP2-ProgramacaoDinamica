#include <stdio.h>
#include <stdlib.h>
#include "../include/TAD_mapa.h"
#include "../include/TAD_trajeto.h"

int testaDirecoes(Mapa mapaPD, int tempo, int i, int j) {
    int melhorValor = invalido;
    int valor;

    // diagonal superior esquerda
    if (i - 1 >= 0 && j - 1 >= 0) {
        valor = mapaPD.celula[tempo][i - 1][j - 1];
        if (celulaValida(valor) && valor > melhorValor)
            melhorValor = valor;
    }

    // esquerda
    if (j - 1 >= 0) {
        valor = mapaPD.celula[tempo][i][j - 1];
        if (celulaValida(valor) && valor > melhorValor)
            melhorValor = valor;
    }

    // diagonal inferior esquerda
    if (i + 1 < mapaPD.altura && j - 1 >= 0) {
        valor = mapaPD.celula[tempo][i + 1][j - 1];
        if (celulaValida(valor) && valor > melhorValor)
            melhorValor = valor;
    }

    return melhorValor;
}


// Função principal da PD
void melhorCaminho(Atlas atlas) {
    Mapa mapa = atlas.mapa;
    Mapa mapaPD = atlas.mapaPD;

    // Primeira coluna, nao pode ser AAA
    for (int i = 0; i < mapa.altura; i++) {
        if (celulaValida(mapa.celula[presente][i][0])) {
            int valorCelula = mapa.celula[presente][i][0];
            int f = atlas.forcaInicial;

            if (valorCelula == valordescanso)
                f += atlas.descanso;
            else if (valorCelula > 0)
                f -= valorCelula;

            mapaPD.celula[presente][i][0] = f;
        }
    }

    // calculo PD coluna por coluna e tempo
    for (int j = 1; j < mapa.largura; j++) {
        for (int i = 0; i < mapa.altura; i++) {
            // percorre presente e passado
            for (int tempo = passado; tempo <= presente; tempo++) { //tp entre passado e presente

                if (!celulaValida(mapa.celula[tempo][i][j]))
                    continue;

                int melhorVizinho = testaDirecoes(mapaPD, tempo, i, j);
                if (melhorVizinho == invalido)
                    continue;

                int novaForca = melhorVizinho;
                int valorCelula = mapa.celula[tempo][i][j]; //celula atual

                // descancanso ou inimigo
                if (valorCelula == valordescanso)
                    novaForca += atlas.descanso;
                else if (valorCelula > 0)
                    novaForca -= valorCelula;

                mapaPD.celula[tempo][i][j] = novaForca;

                // Ancora que copia valor
                if (valorCelula == teletransporte) {
                    int outroTempo;
                    if (tempo == presente) {
                        outroTempo = passado;
                    } else {
                    outroTempo = presente;
                    }
                    if (novaForca > mapaPD.celula[outroTempo][i][j]) {
                    mapaPD.celula[outroTempo][i][j] = novaForca; //maior vai
                    }
                }
            }
        }
    }

    // analise ultima linha, ve qual maior forla e qual tempo é o melhor
    int melhorForca = invalido;
    int tempoFinal = presente;

    for (int tempo = passado; tempo <= presente; tempo++) { //tp entre passado e presente
        for (int i = 0; i < mapa.altura; i++) {
            int f = mapaPD.celula[tempo][i][mapa.largura - 1]; //f = força da ultima coluna
            if (celulaValida(f) && f > melhorForca) {
                melhorForca = f;
                tempoFinal = tempo;
            }
        }
    }

    if (melhorForca <= 0) {
        printf("A calamidade de Nikador e inevitável\n");
    } else if (melhorForca >= atlas.forcaNikador) {
        printf("A ruina de Nikador e iminente\n");
    } else {
        printf("Sera necessário mais planejamento para parar a calamidade\n");
    }
}
