#ifndef ORDENACAO_BUSCA_H_INCLUDED
#define ORDENACAO_BUSCA_H_INCLUDED

#include <stdio.h>
#include "funcionario.h"

TFunc* busca_binaria(int cod, FILE *arq, int tam);

void insertion_sort_disco(FILE *arq, int tam);

#endif // ORDENACAO_BUSCA_H_INCLUDED
