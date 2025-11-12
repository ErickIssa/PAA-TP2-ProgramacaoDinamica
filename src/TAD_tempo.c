#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/TAD_tempo.h"

void inicializarTabela(TabelaDesempenho *tabela) {
    tabela->qtd = 0;
    tabela->capacidade = 10;
    tabela->dados = malloc(tabela->capacidade * sizeof(Medicao));
}

void registrarTempo(TabelaDesempenho *tabela, int tamanhoEntrada, double tempo) {
    if (tabela->qtd >= tabela->capacidade) {
        tabela->capacidade *= 2;
        tabela->dados = realloc(tabela->dados, tabela->capacidade * sizeof(Medicao));
    }
    tabela->dados[tabela->qtd].tamanhoEntrada = tamanhoEntrada;
    tabela->dados[tabela->qtd].tempoExecucao = tempo;
    tabela->qtd++;
}

void salvarCSV(TabelaDesempenho tabela, const char *nomeArquivo) {
    FILE *fp = fopen(nomeArquivo, "w");
    if (!fp) {
        printf("Erro ao salvar arquivo\n");
        return;
    }
    fprintf(fp, "TamanhoEntrada,TempoExecucao\n");
    for (int i = 0; i < tabela.qtd; i++) {
        fprintf(fp, "%d,%.6f\n", tabela.dados[i].tamanhoEntrada, tabela.dados[i].tempoExecucao);
    }
    fclose(fp);
    printf("Arquivo CSV salvo em: %s\n", nomeArquivo);
}

void liberarTabela(TabelaDesempenho *tabela) {
    free(tabela->dados);
    tabela->dados = NULL;
    tabela->qtd = tabela->capacidade = 0;
}

double medirTempo(void (*func)(void *), void *arg) {
    clock_t inicio = clock();
    func(arg);
    clock_t fim = clock();
    return ((double)(fim - inicio)) / CLOCKS_PER_SEC;
}
