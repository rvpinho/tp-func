#ifndef BUSCA_SEQUENCIAL_H_INCLUDED
#define BUSCA_SEQUENCIAL_H_INCLUDED

#define TAM_NOME 200

#include <stdio.h>

typedef struct LogFuncionario {
    int cod;
    char nome[TAM_NOME];
    int numBuscas;
    double tempo;
}LogFunc;

LogFunc *busca_sequencial(int cod, char *nome, int num, double tempo);

TFunc busca_sequencial_funcionario(FILE *arq, int cod_funcionario);

void salva_busca_sequencial(LogFunc *log, FILE *log_txt);

void imprime_log_funcionarios(FILE *arq);

#endif // BUSCA_SEQUENCIAL_H_INCLUDED
