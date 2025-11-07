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

                if (!celulaValida(mapa.celula[tempo][i][j])){
                    continue;
                }

                int melhorVizinho = testaDirecoes(mapaPD, tempo, i, j);
                if (melhorVizinho == invalido){
                    continue;
                }

                int novaForca = melhorVizinho;
                int valorCelula = mapa.celula[tempo][i][j]; //celula atual

                // descancanso ou inimigo
                if (valorCelula == valordescanso){
                    novaForca += atlas.descanso;

                }else if (valorCelula > 0){
                    novaForca -= valorCelula;
                }

                mapaPD.celula[tempo][i][j] = novaForca;

                // Ancora que copia valor
                if (valorCelula == teletransporte) { //so comeca preencher passado aqui porque enquanto n tem ancora n tem valor em passado
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
    //acha na ultima coluna maior forca do passado ou presente
    for (int tempo = passado; tempo <= presente; tempo++) { //tp entre passado e presente
        for (int i = 0; i < mapa.altura; i++) {
            int f = mapaPD.celula[tempo][i][mapa.largura - 1]; //f = força da ultima coluna
            if (celulaValida(f) && f > melhorForca) {
                melhorForca = f;
                
            }
        }
    }

    int tamanho;
    Posicao *melhorCaminho = encontraMelhorCaminho(atlas, &tamanho);

    if (melhorCaminho != NULL) {
        for (int i = 0; i < tamanho; i++) {
            printf("%d %d tempo: %d\n", melhorCaminho[i].linha, melhorCaminho[i].coluna, melhorCaminho[i].tempo);
        }
        free(melhorCaminho);
    }
        //else{printf("A tripulacao nao possui caminho\n");}

    if (melhorForca <= 0) {
        printf("A calamidade de Nikador e inevitável\n");
    } else if (melhorForca >= atlas.forcaNikador) {
        printf("A ruina de Nikador e iminente\n");
    } else {
        printf("Sera necessário mais planejamento para parar a calamidade\n");
    }
}

Posicao* encontraMelhorCaminho(Atlas atlas, int *tamanho) {
    Mapa mapa = atlas.mapa;
    Mapa mapaPD = atlas.mapaPD;

    int melhorForca = invalido;
    int tempoAtual = presente;
    int linhaAtual = -1;
    int colFinal = mapa.largura - 1;

    // maior forca coluna fim
    for (int tempo = passado; tempo <= presente; tempo++) {
        for (int i = 0; i < mapa.altura; i++) {
            int f = mapaPD.celula[tempo][i][colFinal];
            if (celulaValida(f) && f > melhorForca) {
                melhorForca = f;
                linhaAtual = i;
                tempoAtual = tempo;
            }
        }
    }

    if (melhorForca == invalido || linhaAtual == -1) {
        *tamanho = 0;
        return NULL;
    }

    Posicao *trajeto = malloc(mapa.largura * mapa.altura * sizeof(Posicao));
    int passos = 0;
    //aqui salva outras posicoes sem ser a inicial
    // da direita pra esquerda
    for (int j = colFinal; j >= 0; j--) {
        trajeto[passos].linha = linhaAtual;
        trajeto[passos].coluna = j;
        trajeto[passos].tempo = tempoAtual;
        passos++;

        int cel = mapa.celula[tempoAtual][linhaAtual][j];

        // verificacao ancora
        if (cel == teletransporte) {
            int outroTempo;

            if (tempoAtual == presente) {
                outroTempo = passado;
            } else {
                outroTempo = presente;
            }
            int valorAtual = mapaPD.celula[tempoAtual][linhaAtual][j];
            int valorOutro = mapaPD.celula[outroTempo][linhaAtual][j];
            int celOutro = mapa.celula[outroTempo][linhaAtual][j];

            if (celulaValida(celOutro) && celulaValida(valorOutro) && valorOutro >= valorAtual) {
                tempoAtual = outroTempo;
            }
        }

        if (j == 0) 
            break;

        int proximaCol = j - 1; //sem a 1 col
        if (proximaCol < 0){
            break;
        }
        // logica pra escolher melhor celula
        int melhorI = linhaAtual; //melhor celula anterior
        int melhorValor = invalido;

        for (int direcao = -1; direcao <= 1; direcao++) {//verifica as 3 direcoes e as compara
            int nvLinha = linhaAtual + direcao;
            if (nvLinha < 0 || nvLinha >= mapa.altura) 
                continue;

            int valor = mapaPD.celula[tempoAtual][nvLinha][proximaCol];
            int celulaOriginal = mapa.celula[tempoAtual][nvLinha][proximaCol]; //verificar validade

            if (celulaValida(valor) && celulaValida(celulaOriginal) && valor > melhorValor) { //verific validade, celula original valida e valor PD
                melhorValor = valor;
                melhorI = nvLinha; //atualiza val e linha
            }
        }

        linhaAtual = melhorI;
    }

    // Inverte o caminho
    Posicao *trajetoFinal = malloc(passos * sizeof(Posicao));
    for (int i = 0; i < passos; i++) {
        trajetoFinal[i] = trajeto[passos - i - 1];
    }

    free(trajeto);
    *tamanho = passos;
    return trajetoFinal;
}