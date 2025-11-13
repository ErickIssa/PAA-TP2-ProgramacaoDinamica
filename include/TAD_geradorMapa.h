#ifndef GERADOR_MAPAS_H
#define GERADOR_MAPAS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gerarNmrAleatorio(int min, int max);
void preencheMapaBasico(FILE * fp, int altura, int largura, int portal1_x, int portal1_y, int portal2_x, int portal2_y);
void gerarMapaBasico(FILE * fp);
void geradorDeMapasBasico();
void preencheMapaAvancado(FILE * fp, int altura, int largura, int portal1_AAA_x, int portal1_AAA_y, int portal1_BBB_x, int portal1_BBB_y, int portal2_AAA_x, int portal2_AAA_y, int portal2_BBB_x, int portal2_BBB_y);
void gerarMapaAvancado(FILE * fp);
void geradorDeMapasAvancado();
int geradorDeMapas();

#endif