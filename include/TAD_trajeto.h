#ifndef TRAJETO_H
#define TRAJETO_H

#include "../include/TAD_mapa.h"


void melhorCaminho(Atlas atlas);
int testaDirecoes(Mapa mapa, int tempo, int i, int j);
Posicao* encontraMelhorCaminho(Atlas atlas, int *tamanhoCaminho);


#endif