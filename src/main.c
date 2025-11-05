#include <stdio.h>

#include "../include/TAD_mapa.h"
#include "../include/TAD_menu.h"

int main(){

    Atlas atlas;
    inicializarMapaVazio(&atlas, 5,5);
    printf("oaasa");
    imprimeMapa(atlas);
    printf("oaasa");

    menu();

    return 0;
}