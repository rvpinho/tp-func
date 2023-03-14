#ifndef INSERTION_SORT_H_INCLUDED
#define INSERTION_SORT_H_INCLUDED

#include <stdio.h>
#include "funcionarios.h"

TFunc* busca_binaria(int cod, FILE *arq, int tam);

void insertion_sort_disco(FILE *arq, int tam);


#endif // INSERTION_SORT_H_INCLUDED
