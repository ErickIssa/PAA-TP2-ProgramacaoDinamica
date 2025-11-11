#ifndef MAPA_H
#define MAPA_H


#define presente 1
#define passado 0
#define invalido -3
#define teletransporteA -1
#define teletransporteB -2
#define valordescanso 000

typedef struct {
    int linha;
    int coluna;
    int tempo;
} Posicao;

typedef struct Mapa
{
    Posicao portalApresente;
    Posicao portalApassado;
    Posicao portalBpresente;
    Posicao portalBpassado;

    int altura;
    int largura;
    int ***celula; // assusta nao isso é 2 ponteiros para linha e coluna, 1 ponteiro para passado e futuro, 1 ponteiro para String
} Mapa;

typedef struct Setor{

    int forcaInicial;
    int descanso;
    int forcaNikador;
    Mapa mapa;
    Mapa mapaPD;
} Atlas;




void imprimeMapa(Atlas Atlas);
void imprimeMapaPD(Atlas atlas);
void inicializarAtlasVazio(Atlas *atlas, int altura, int largura,  int forcaTripulacao, int descanso, int forcaNikador);
int celulaValida(int n);

#endif