#ifndef TAD_TEMPO_H
#define TAD_TEMPO_H

#include <time.h>

typedef struct {
    int tamanhoEntrada;  
    double tempoExecucao; 
} Medicao;

typedef struct {
    Medicao *dados;
    int qtd;
    int capacidade;
} TabelaDesempenho;

void inicializarTabela(TabelaDesempenho *tabela);
void registrarTempo(TabelaDesempenho *tabela, int tamanhoEntrada, double tempo);
void salvarCSV(TabelaDesempenho tabela, const char *nomeArquivo);
void liberarTabela(TabelaDesempenho *tabela);
double medirTempo(void (*func)(void *), void *arg);

#endif
