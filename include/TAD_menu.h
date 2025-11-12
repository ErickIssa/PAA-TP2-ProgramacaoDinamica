#ifndef MENU_H
#define MENU_H

#include "../include/TAD_mapa.h"
#include "../include/TAD_trajeto.h"
#include "../include/TAD_tempo.h"

void menu();
void leituraArquivo(Atlas *atlas);
void wrapperMelhorCaminho(void *arg);
void testarDesempenho();

#endif