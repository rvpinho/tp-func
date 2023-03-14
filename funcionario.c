#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "funcionario.h"

TFunc *funcionario(int cod, char *nome, char *cpf, char *data, double salario){
	TFunc *funcionario = (TFunc *) malloc(sizeof(TFunc));
	if (funcionario) memset(funcionario, 0, sizeof(TFunc));
	funcionario->cod = cod;
	strcpy(funcionario->nome, nome);
	strcpy(funcionario->cpf, cpf);
	strcpy(funcionario->data_nascimento, data);
	funcionario->salario = salario;
	return funcionario;
}

int tamanho_registro() {
  return sizeof(TFunc);
}

void imprime_funcionario(TFunc *funcionario){
	printf("%d, %s, %s, %s, %.2f \n", funcionario->cod, funcionario->nome, funcionario->cpf, funcionario->data_nascimento, funcionario->salario);
}

void salva_funcionario(TFunc *func, FILE *out) {
    fwrite(&func->cod, sizeof(int), 1, out);
    // func→nome ao invés de &func→nome, pois string já é ponteiro
    fwrite(func->nome, sizeof(char),sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char),sizeof(func->cpf), out);
    fwrite(func->data_nascimento, sizeof(char),sizeof(func->data_nascimento), out);
    fwrite(&func->salario, sizeof(double), 1, out);
    fflush(out);
}

TFunc *le_funcionario(FILE *in) {
    TFunc *func = (TFunc *) malloc(sizeof(TFunc));
    int result =fread(&func->cod, sizeof(int), 1, in);
   // printf("result %d func->cod %d \n" , result, func->cod);
    if (0 >= result) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(func->data_nascimento, sizeof(char), sizeof(func->data_nascimento), in);
    fread(&func->salario, sizeof(double), 1, in);

    return func;

}

void cria_base_funcionarios(FILE* arq, FILE* arqIndicePrimario,  FILE* arqIndicePrimarioNaoOrdenado, int nFunc){
    int chaves[nFunc+1];
    // Define a semente para a função rand baseado no tempo atual
    srand(time(NULL));
    char nome[] = "Funcionario";
    int numero_aleatorio;
    for(int i =0; i<nFunc; i++){
        // cria e preenche arquivo de funcionario
        // cria a string formatada
        snprintf(nome,sizeof(nome)+1,"Funcionario%d",i+1);


        // Gera um número aleatório entre 0 e 19
        numero_aleatorio = rand() % 50;
        // Adiciona 1 para obter um número aleatório entre 1 e 50
        numero_aleatorio += 1;

        TFunc *func = funcionario(numero_aleatorio, nome,"000.000.000-00","27/05/1989",5000);
        fseek(arq, (i) * tamanho_registro(), SEEK_SET);
        salva_funcionario(func, arq);
        // cria e preenche arquivo de chaves

        chaves[func->cod]= i;
        fwrite(&func->cod,sizeof(int), 1, arqIndicePrimario);  //escreve a chave
        fwrite(&i, sizeof(int), 1, arqIndicePrimario); //escreve o rrn
        free(func);
    }

    //escrevendo o arquivo de indice primario (chave e rrn) ordenado pela chave
    int aux = nFunc;
    for(int f = 1 ; f <=nFunc; f++){
        fwrite(&f, sizeof(int), 1, arqIndicePrimarioNaoOrdenado);  //escreve a chave
        fwrite(&chaves[aux], sizeof(int), 1, arqIndicePrimarioNaoOrdenado); //escreve o rrn
        aux--;
    }

}

void imprime_base_dados_funcionarios(FILE *arq) {
    rewind(arq);
    int i = 0;
    fseek(arq,  0 * sizeof (TFunc), SEEK_SET);
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

void imprime_indice_primario_funcionarios(FILE *arqIndicePrimario, int nFunc) {
    rewind(arqIndicePrimario);
    for(int i = 1 ; i <= nFunc ; i++){
        int chave, byteoffset;
        fread(&chave, sizeof(int), 1, arqIndicePrimario);
        fread(&byteoffset, sizeof(int), 1, arqIndicePrimario);
        printf("%d: %d\n", chave, byteoffset);
    }
}
