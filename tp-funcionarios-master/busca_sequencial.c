#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <time.h>
#include "funcionario.h"
#include "busca_sequencial.h"

LogFunc *busca_sequencial(int cod, char *nome, int num, double tempo){
	LogFunc *busca = (LogFunc *) malloc(sizeof(LogFunc));
	if (busca) memset(busca, 0, sizeof(LogFunc));
	busca->cod = cod;
	strcpy(busca->nome, nome);
	busca->numBuscas = num;
	busca->tempo = tempo;
	return busca;
}


TFunc busca_sequencial_funcionario(FILE *arq, int cod_funcionario){
    // Cria(se não existir)/Carrega log_funcionario.txt
    FILE* log_funcionario = fopen("log_funcionario.txt", "w");
    if (log_funcionario == NULL) {
        printf("Erro ao criar o log_funcionario.\n");
        return ;
    }
    printf("O log_funcionario carregado com sucesso.\n");

    // Abre o temporizador da busca
    LogFunc *busca = (LogFunc*) malloc(sizeof(LogFunc));
    busca->cod = cod_funcionario;
    int buscas = 0;

    // Abre o temporizador da busca
    clock_t t = clock();

    // Buscar um funcionario
    rewind(arq);
    int i = 0;
    fseek(arq,  0 * sizeof (TFunc), SEEK_SET);
    if(arq != NULL) {

        int aux = 1;
        do{
            fseek(arq, (i) * tamanho_registro(), SEEK_SET);
            TFunc *func = le_funcionario(arq);
            if(func){
                if (func->cod == cod_funcionario) {
                    printf("Registro encontrado: %d - %s\n", func->cod, func->nome);
                    strcpy(busca->nome, func->nome);
                    busca->numBuscas=buscas;
                    busca->tempo = ((double) (clock() - t)) / CLOCKS_PER_SEC;
                    salva_busca_sequencial(busca, log_funcionario);
                    break;
                } else {
                    buscas++;
                }
                i++;
                free(func);
            }else aux = 0;
        }while(aux);
    }
    else printf("Erro ao abrir arquivo\n");


    if (feof(arq)) {
      printf("Registro não encontrado.\n");
    }
    //

    fclose(log_funcionario);
}


void salva_busca_sequencial(LogFunc *log, FILE *log_txt){
    fwrite(&log->cod, sizeof(int), 1, log_txt);
    fwrite(log->nome, sizeof(char),sizeof(log->nome), log_txt);
    fwrite(log->numBuscas, sizeof(int),sizeof(log->numBuscas), log_txt);
    fwrite(&log->tempo, sizeof(double), 1, log_txt);
    fflush(log_txt);
}

void imprime_log_funcionarios(FILE *arq){
    rewind(arq);
    int i = 0;
    fseek(arq,  0 * sizeof (LogFunc), SEEK_SET);
    if(arq != NULL) {

        int aux = 1;
        do{
            fseek(arq, (i) * tamanho_registro(), SEEK_SET);
            TFunc *func = le_funcionario(arq);
            if(func){
                //printf("%d, %s, %s, %s, %lf \n", func->cod, func->nome, func->cpf, func->data_nascimento, func->salario);
                imprime_funcionario(func);
                i++;
                free(func);
            }else aux = 0;
        }while(aux);
    }
    else printf("Erro ao abrir arquivo\n");
}
