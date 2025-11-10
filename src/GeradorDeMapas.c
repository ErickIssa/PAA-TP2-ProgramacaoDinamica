#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int gerarNmrAleatorio(int min, int max){
    if(min == max) return min;
    return (rand() % (max - min + 1)) + min;
}

void preencheMapa(FILE * fp, int altura, int largura, int portal1_x, int portal1_y, int portal2_x, int portal2_y){
    for (int i=1; i<=altura;i++){
        for (int j=1; j<=largura; j++){
            if(i == portal1_y && j == portal1_x){
                fprintf(fp,"AAA");
            }
            if(i == portal2_y && j == portal2_x){
                fprintf(fp,"BBB");
            }
            else{
                int oraculo = gerarNmrAleatorio(1,5);
                if (oraculo == 1 || oraculo == 2){
                    fprintf(fp,"***");
                }
                else if (oraculo == 3){
                    fprintf(fp, "000");
                }
                else if(oraculo == 4 || oraculo ==5){
                    fprintf(fp,"%03d",gerarNmrAleatorio(1,10));
                }
            }
            if (j == largura){
                fprintf(fp,"\n");
            }
            else{
                fprintf(fp," ");
            }
        }
    }

    fprintf(fp, "///\n");

    for (int i=1; i<=altura;i++){
        for (int j=1; j<=largura; j++){
            if( (i == portal1_y && j == portal1_x) || (i == portal2_y && j == portal2_x)){
                fprintf(fp,"AAA");
            }
            else{
                int oraculo = gerarNmrAleatorio(1,5);
                if (oraculo == 1 || oraculo == 2){
                    fprintf(fp,"***");
                }
                else if (oraculo == 3){
                    fprintf(fp, "000");
                }
                else if(oraculo == 4 || oraculo ==5){
                    fprintf(fp,"%03d",gerarNmrAleatorio(1,10));
                }
            }
            if (j == largura){
                fprintf(fp,"\n");
            }
            else{
                fprintf(fp," ");
            }
        }
    }

}

void gerarMapa(FILE * fp){
    
    int altura = gerarNmrAleatorio(2,6);
    int largura = gerarNmrAleatorio(2,6);
    int forcaTripulacao = gerarNmrAleatorio(10,100);
    int forcaNikador = gerarNmrAleatorio(1,60);
    int descanso = gerarNmrAleatorio(1,20);
    fprintf(fp,"%d %d %d %d %d\n", altura, largura, forcaTripulacao, descanso, forcaNikador);

    int portal1_x = gerarNmrAleatorio(1,largura);
    int portal1_y = gerarNmrAleatorio(1,altura);
    int portal2_x = gerarNmrAleatorio(1,largura);
    int portal2_y = gerarNmrAleatorio(1,altura);

    while(portal1_x == portal2_x){
        portal2_x = gerarNmrAleatorio(1,largura);
    }

    while(portal1_y == portal2_y){
        portal2_y = gerarNmrAleatorio(1,altura);
    }

    preencheMapa(fp,altura, largura, portal1_x, portal1_y, portal2_x, portal2_y);

    return;
}

void geradorDeMapas(){
    srand(time(NULL));

    FILE *fp;
    char *caminho = "../input/entrada_criada.txt";
    fp = fopen(caminho, "w");
    if (fp == NULL)
    {
        printf("Erro ao criar arquivo\n");
        return;
    }
    gerarMapa(fp);
    return;

}