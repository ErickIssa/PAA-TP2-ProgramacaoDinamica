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

