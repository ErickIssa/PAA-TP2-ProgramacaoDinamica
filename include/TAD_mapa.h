#ifndef MAPA_H
#define MAPA_H


#define presente 1
#define passado 0

typedef struct Mapa
{
    int altura;
    int largura;
    int ***celula; // assusta nao isso é 2 ponteiros para linha e coluna, 1 ponteiro para passado e futuro, 1 ponteiro para String
} Mapa;

typedef struct Setor{

    int forcaInicial;
    int descanso;
    int forcaNikador;
    Mapa mapa;
} Atlas;

void imprimeMapa(Atlas Atlas);
void inicializarMapaVazio(Atlas *atlas, int altura, int largura);

#endif