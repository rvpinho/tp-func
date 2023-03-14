#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

#define TAM_NOME 200

/*estrutura do registro funcion�rio com campos de tamanho fixo*/
typedef struct Funcionario {
    int cod;
    char nome[TAM_NOME];
    char cpf[15];
    char data_nascimento[11];
    double salario;
}TFunc;

/* cria um funcion�rio inicializando-o com os valores passados por par�metro*/
TFunc *funcionario(int cod, char *nome, char *cpf, char *data, double salario);

/* o tamanho do registro, retornado pela fun��o tamanho_registro() � dado em bytes (aula 03 arquivos)*/
int tamanho_registro();

/* imprime na tela as informa��es do funcion�rio */
void imprime_funcionario(TFunc *funcionario);

/* Salva no arquivo out o funci�n�rio na posi��o atual do cursor*/
void salva_funcionario(TFunc *func, FILE *out);

/* L� um funcion�rio do arquivo in na posi��o atual do cursor, retorna um ponteiro para funcion�rio lido do arquivo*/
TFunc *le_funcionario(FILE *in);

/* cria .dat com 50 funcionarios*/
void cria_base_funcionarios(FILE* arq, FILE* arqIndicePrimario,  FILE* arqIndicePrimarioNaoOrdenado, int nFunc);

/*imprime uma base de dados de funcion�rios lidos de um arquivo */
void imprime_base_dados_funcionarios(FILE *arq);

/*imprime uma arquivo de indice primario de funcion�rios*/
void imprime_indice_primario_funcionarios(FILE *arqIndicePrimario, int nFunc);

#endif // FUNCIONARIO_H_INCLUDED
