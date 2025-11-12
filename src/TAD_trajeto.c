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
    // Verificação de segurança
    if (!atlas.mapa.celula || !atlas.mapaPD.celula) {
        printf("Erro: atlas inválido.\n");
        return;
    }

    Mapa mapa = atlas.mapa;
    Mapa mapaPD = atlas.mapaPD;

    // Primeira coluna (inicialização)
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

    // Calcula PD coluna por coluna e tempo
    for (int j = 1; j < mapa.largura; j++) {
        for (int i = 0; i < mapa.altura; i++) {
            for (int tempo = passado; tempo <= presente; tempo++) {
                if (!celulaValida(mapa.celula[tempo][i][j]))
                    continue;

                int melhorVizinho = testaDirecoes(mapaPD, tempo, i, j);
                if (melhorVizinho == invalido)
                    continue;

                int novaForca = melhorVizinho;
                int valorCelula = mapa.celula[tempo][i][j];

                // Atualiza força conforme tipo de célula
                if (valorCelula == valordescanso)
                    novaForca += atlas.descanso;
                else if (valorCelula > 0)
                    novaForca -= valorCelula;

                mapaPD.celula[tempo][i][j] = novaForca;

                // Tratamento de portais (teletransportes)
                if (valorCelula == teletransporteA) {
                    if (tempo == presente) {
                        int *dest = &mapaPD.celula[passado][atlas.mapaPD.portalApassado.linha][atlas.mapaPD.portalApassado.coluna];
                        if (novaForca > *dest)
                            *dest = novaForca;
                    } else {
                        int *dest = &mapaPD.celula[presente][atlas.mapaPD.portalApresente.linha][atlas.mapaPD.portalApresente.coluna];
                        if (novaForca > *dest)
                            *dest = novaForca;
                    }
                }

                if (valorCelula == teletransporteB) {
                    if (tempo == presente) {
                        int *dest = &mapaPD.celula[passado][atlas.mapaPD.portalBpassado.linha][atlas.mapaPD.portalBpassado.coluna];
                        if (novaForca > *dest)
                            *dest = novaForca;
                    } else {
                        int *dest = &mapaPD.celula[presente][atlas.mapaPD.portalBpresente.linha][atlas.mapaPD.portalBpresente.coluna];
                        if (novaForca > *dest)
                            *dest = novaForca;
                    }
                }
            }
        }
    }

    // Analisa última coluna — maior força
    int melhorForca = invalido;
    for (int tempo = passado; tempo <= presente; tempo++) {
        for (int i = 0; i < mapa.altura; i++) {
            int f = mapaPD.celula[tempo][i][mapa.largura - 1];
            if (celulaValida(f) && f > melhorForca)
                melhorForca = f;
        }
    }

    // Reconstrução do caminho ótimo
    int tamanho;
    Posicao *melhorCaminho = encontraMelhorCaminho(atlas, &tamanho);

    if (melhorCaminho != NULL) {
        // Cria matrizes locais para imprimir o caminho
        char caminhoPresente[mapa.altura][mapa.largura];
        char caminhoPassado[mapa.altura][mapa.largura];

        // Inicializa ambas
        for (int i = 0; i < mapa.altura; i++) {
            for (int j = 0; j < mapa.largura; j++) {
                caminhoPresente[i][j] = 'X';
                caminhoPassado[i][j] = 'X';
            }
        }

        // Marca as posições do caminho
        for (int i = 0; i < tamanho; i++) {
            if (melhorCaminho[i].tempo == presente)
                caminhoPresente[melhorCaminho[i].linha][melhorCaminho[i].coluna] = '0' + i + 1;
            else
                caminhoPassado[melhorCaminho[i].linha][melhorCaminho[i].coluna] = '0' + i + 1;
        }

        // Imprime o resultado visual
        printf("PRESENTE:\n");
        for (int i = 0; i < mapa.altura; i++) {
            for (int j = 0; j < mapa.largura; j++) {
                if (caminhoPresente[i][j] == 'X')
                    printf("\x1b[31m" "[%c]" "\x1b[0m", caminhoPresente[i][j]);
                else
                    printf("\x1b[34m" "[%c]" "\x1b[0m", caminhoPresente[i][j]);
            }
            printf("\n");
        }

        printf("PASSADO:\n");
        for (int i = 0; i < mapa.altura; i++) {
            for (int j = 0; j < mapa.largura; j++) {
                if (caminhoPassado[i][j] == 'X')
                    printf("\x1b[31m" "[%c]" "\x1b[0m", caminhoPassado[i][j]);
                else
                    printf("\x1b[34m" "[%c]" "\x1b[0m", caminhoPassado[i][j]);
            }
            printf("\n");
        }

        free(melhorCaminho);
    }

    // Resultado textual da força final
    if (melhorForca <= 0) {
        printf("A calamidade de Nikador e inevitável\n");
    } else if (melhorForca >= atlas.forcaNikador) {
        printf("A ruina de Nikador e iminente\n");
    } else {
        printf("Sera necessario mais planejamento para parar a calamidade\n");
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
    int colunaAtual = colFinal;
    while(colunaAtual >= 0) {
        trajeto[passos].linha = linhaAtual;
        trajeto[passos].coluna = colunaAtual;
        trajeto[passos].tempo = tempoAtual;
        
        
        passos++;

        int cel = mapa.celula[tempoAtual][linhaAtual][colunaAtual];

        // verificacao ancora
        if (cel == teletransporteA){
            if(tempoAtual == presente){

                if (testaDirecoes(mapaPD,tempoAtual,linhaAtual,colunaAtual) <= testaDirecoes(mapaPD,passado,mapaPD.portalApassado.linha,mapaPD.portalApassado.coluna)) {
                tempoAtual = passado;
                linhaAtual = mapaPD.portalApassado.linha;
                colunaAtual = mapaPD.portalApassado.coluna;
                }

            }else{

                if (testaDirecoes(mapaPD,tempoAtual,linhaAtual,colunaAtual) <= testaDirecoes(mapaPD,presente,mapaPD.portalApresente.linha,mapaPD.portalApresente.coluna)) {
                tempoAtual = presente;
                linhaAtual = mapaPD.portalApresente.linha;
                colunaAtual = mapaPD.portalApresente.coluna;
                }
            }
        }
        else if (cel == teletransporteB){
            if(tempoAtual == presente){
                if (testaDirecoes(mapaPD,tempoAtual,linhaAtual,colunaAtual) <= testaDirecoes(mapaPD,passado,mapaPD.portalBpassado.linha,mapaPD.portalBpassado.coluna)) {
                tempoAtual = passado;
                linhaAtual = mapaPD.portalBpassado.linha;
                colunaAtual = mapaPD.portalBpassado.coluna;
                }

            }else{
                if (testaDirecoes(mapaPD,tempoAtual,linhaAtual,colunaAtual) <= testaDirecoes(mapaPD,presente,mapaPD.portalBpresente.linha,mapaPD.portalBpresente.coluna)) {
                tempoAtual = presente;
                linhaAtual = mapaPD.portalBpresente.linha;
                colunaAtual = mapaPD.portalBpresente.coluna;
                }
            }
        }

        if (colunaAtual == 0) 
            break;

        int proximaCol = colunaAtual - 1; //sem a 1 col
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
        colunaAtual--;
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