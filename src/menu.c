#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/TAD_menu.h"

void menu(){
    printf("QUE COMECE A BATALHA CONTRA NIKADOR!\n");

    Atlas atlas;

    while(1){
        int opcao;

        printf("--------------------MENU--------------------\n");
        printf("1- Ler arquivo de entrada\n");
        printf("2- Iniciar jornada\n");
        printf("3- Desativar modo de analise\n");
        printf("4 - Gerar um novo mapa\n");
        printf("0- Sair\n");

        printf("Escolha uma opcao acima:\n");
        scanf("%d", &opcao);
        switch (opcao)
        {

        case 1:
            leituraArquivo(&atlas);
            break;
        case 2:
            break;
        case 3:
            break;  
        case 4:
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
    
    inicializarMapaVazio(atlas,altura,largura);
    
    Mapa *mapa = &atlas->mapa;
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            char buffer[4];
            fscanf(file, "%s", buffer);

            int valor;

            if (strcmp(buffer, "***") == 0) {
                valor = -1;
            } else if (strcmp(buffer, "AAA") == 0) {
                valor = -2;
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
    long pos = ftell(file);
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
                valor = -1;
            } else if (strcmp(buffer, "AAA") == 0) {
                valor = -2;
            } else {
            valor = atoi(buffer);
            }

            mapa->celula[passado][i][j] = valor;
    }

}
        imprimeMapa(*atlas);
        fgetc(file);
}

