#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TAD_menu.h"

void menu(){
    printf("QUE COMECE A BATALHA CONTRA NIKADOR!\n");

    Atlas atlas;
    atlas.mapa.celula = NULL;
    atlas.mapaPD.celula = NULL;

    while(1){
        int opcao;

        printf("--------------------MENU--------------------\n");
        printf("1- Ler arquivo de entrada\n");
        printf("2- Imprimir mapa\n");
        printf("3- Montar PD\n");
        printf("4- Imprime Mapa PD\n");
        printf("5- Testar desempenho (gera CSV)\n");
        printf("0- Sair\n");

        printf("Escolha uma opcao acima:\n");
        scanf("%d", &opcao);
        switch (opcao)
        {

        case 1:
            leituraArquivo(&atlas);
        break;
        case 2:
            if (atlas.mapa.celula == NULL) {
                printf("Mapa ainda nao foi carregado!\n");
            }else {
            imprimeMapa(atlas);
            }
        break;
        case 3:
            if (atlas.mapa.celula == NULL) {
                printf("Mapa ainda nao foi carregado!\n");
            }else {
                melhorCaminho(atlas);
            }
            break;  
        case 4:
            if (atlas.mapaPD.celula == NULL) {
                printf("Mapa ainda nao foi carregado!\n");
            }else {
                imprimeMapaPD(atlas);
            }
            break;
        case 5:
            testarDesempenho();
            break;
        case 0:
            printf("Fechando programa...\n");
            return;
        
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
}

void leituraArquivo(Atlas *atlas){

    int largura = 0;
    int altura = 0;
    int forcaNikador = 0;
    int descanso = 0;
    int forcaTripulacao = 0;

    FILE * file;

    while(1){
        char nome[256];

        printf("Digite o caminho para o arquivo (0 para sair):\n");
        scanf("%s", nome);
        
        if(strcmp(nome,"0")==0){
            printf("Saindo...\n");
            return;
        }
        
        file = fopen(nome, "r");

        if(file == NULL){
            printf("Arquivo invalido, tente novamente...\n");
            continue;
        }else{
            break;
        }

    }

    fscanf(file,"%d %d %d %d %d", &altura, &largura, &forcaTripulacao, &descanso, &forcaNikador); fgetc(file);
    
    inicializarAtlasVazio(atlas,altura,largura,forcaTripulacao,descanso,forcaNikador);
    
    Mapa *mapa = &atlas->mapa;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            char buffer[4];
            fscanf(file, "%s", buffer);

            int valor;

            if (strcmp(buffer, "***") == 0) {
                valor = invalido;
            } else if (strcmp(buffer, "AAA") == 0) {
                valor = teletransporteA;
                Posicao posAPresente;
                posAPresente.coluna = j;
                posAPresente.linha = i;
                posAPresente.tempo = presente;
                mapa->portalApresente = posAPresente;
                atlas->mapaPD.portalApresente = posAPresente;
            } else if (strcmp(buffer, "BBB") == 0) {
                valor = teletransporteB;
                Posicao posBPresente;
                posBPresente.coluna = j;
                posBPresente.linha = i;
                posBPresente.tempo = presente;
                mapa->portalBpresente = posBPresente;
                atlas->mapaPD.portalBpresente = posBPresente;
            } else {
            valor = atoi(buffer);
            }

            mapa->celula[presente][i][j] = valor;
    }
}
    // --- Tenta ler a linha seguinte (espera "///")
    int c;
    while ((c = fgetc(file)) == '\n' && !feof(file)); // descarta quebras de linha extras
    if (c != EOF) ungetc(c, file); // devolve caractere não-'\n'

    char linha[16];
    if (fgets(linha, sizeof(linha), file)) {
        if (strncmp(linha, "///", 3) != 0) {
            printf("Arquivo em formato errado\n");
            return; // volta para antes da leitura errada
        }
    }

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            char buffer[4];
            fscanf(file, "%s", buffer);

            int valor;

            if (strcmp(buffer, "***") == 0) {
                valor = invalido;
            } else if (strcmp(buffer, "AAA") == 0) {
                valor = teletransporteA;
                Posicao posAPassado;
                posAPassado.coluna = j;
                posAPassado.linha = i;
                posAPassado.tempo = presente;
                mapa->portalApassado = posAPassado;
                atlas->mapaPD.portalApassado = posAPassado;
            } else if (strcmp(buffer, "BBB") == 0) {
                valor = teletransporteB;
                Posicao posBPassado;
                posBPassado.coluna = j;
                posBPassado.linha = i;
                posBPassado.tempo = presente;
                mapa->portalBpassado = posBPassado;
                atlas->mapaPD.portalBpassado = posBPassado;
            } else {
            valor = atoi(buffer);
            }

            mapa->celula[passado][i][j] = valor;
    }

}
        fgetc(file);
}

void wrapperMelhorCaminho(void *arg) {
    Atlas *atlas = (Atlas *)arg;
    melhorCaminho(*atlas);
}

void testarDesempenho() {
    TabelaDesempenho tabela;
    inicializarTabela(&tabela);

    srand(time(NULL));

    // testa mapas de 3x3 até 1x12 (pode mudar eventualmente)
    for (int n = 2; n <= 3000; n++) {
        char nomeArq[64];
        printf("Gerando e testando mapa %dx%d...\n", n, n);
        sprintf(nomeArq, "input/mapa_%dx%d.txt", n, n);

        FILE *fp = fopen(nomeArq, "w");
        if (!fp) {
            printf("Erro ao criar arquivo %s\n", nomeArq);
            continue;
        }

        // gera mapa aleatório de tamanho n x n
        int altura = n;
        int largura = n;
        int portal1_x = rand() % largura + 1;
        int portal1_y = rand() % altura + 1;
        int portal2_x = rand() % largura + 1;
        int portal2_y = rand() % altura + 1;
        fprintf(fp,"%d %d %d %d %d\n", altura, largura,
                rand() % 90 + 10, rand() % 20 + 1, rand() % 60 + 1);
        preencheMapa(fp, altura, largura, portal1_x, portal1_y, portal2_x, portal2_y);
        fclose(fp);

        Atlas atlas = {0};
        leituraArquivoDireta(&atlas, nomeArq);
        double tempo = medirTempo(wrapperMelhorCaminho, &atlas);
        registrarTempo(&tabela, n * n, tempo);
        liberarAtlas(&atlas);

        //printf("Mapa %dx%d -> Tempo: %.6fs\n", n, n, tempo);
    }

    salvarCSV(tabela, "resultados.csv");
    liberarTabela(&tabela);
    printf("Teste feito. Dados salvos em resultados.csv\n");
}

void leituraArquivoDireta(Atlas *atlas, const char *nome) {
    FILE *file = fopen(nome, "r");
    if (!file) {
        printf("Erro ao abrir %s\n", nome);
        return;
    }

    int altura, largura, forcaTrip, descanso, forcaNikador;
    if (fscanf(file, "%d %d %d %d %d", &altura, &largura, &forcaTrip, &descanso, &forcaNikador) != 5) {
        printf("Erro ao ler cabecalho de %s\n", nome);
        fclose(file);
        return;
    }
    fgetc(file);

    inicializarAtlasVazio(atlas, altura, largura, forcaTrip, descanso, forcaNikador);

    Mapa *mapa = &atlas->mapa;

    for (int tempo = 0; tempo < 2; tempo++) {
        for (int i = 0; i < altura; i++) {
            for (int j = 0; j < largura; j++) {
                char buffer[4];
                if (fscanf(file, "%s", buffer) != 1) {
                    printf("Erro de leitura no mapa (%s)\n", nome);
                    fclose(file);
                    return;
                }

                int valor;
                if (strcmp(buffer, "***") == 0)
                    valor = invalido;
                else if (strcmp(buffer, "AAA") == 0)
                    valor = teletransporteA;
                else
                    valor = atoi(buffer);

                mapa->celula[tempo][i][j] = valor;
            }
        }
        if (tempo == 0) {
            // Pula o separador "///"
            char separador[8];
            fscanf(file, "%s", separador);
        }
    }

    fclose(file);
}



