#include <stdio.h>
#include <stdlib.h>

#include "funcionario.c"
#include "busca_sequencial.h"

int menu()
{
    int op;

    printf("\n\n**************MENU************** \n\nBASE DE DADOS\n");

    printf("\n\n-----Quest�o 1----- \n");
    printf("\nDigite 1 para criar a base de dados de teste.");
    printf("\nDigite 2 se desejar imprimir a base de dados funcionario.");
    printf("\nDigite 3 se desejar imprimir o �ndice prim�rio da base de funcionarios.");

    printf("\n\n-----Quest�o 2----- \n");
    printf("\nDigite 4 se desejar consultar funcionarios.");
    printf("\nDigite 5 se desejar imprimir o log de consultas de funcionarios.");

    printf("\n\n-----Quest�o 3----- \n");
    printf("\nDigite 6 se desejar ordenar os funcionarios.(INSERTION SORT)");


    printf("\n\n-----Quest�o 5----- \n");
    printf("\nDigite 7 se desejar ordenar e buscar os funcionarios.(BUSCA BIN�RIA)");

    printf("\nDigite -1 para sair: \n");
    scanf("%d", &op);

    return op;

}

int main()
{
    bool arqPreenchido = true; int numFuncionarios = 5;

    /*criando um arquivo l�gico para abir para leitura e escrita o arquivo bin�rio*/
    FILE* arq = fopen("base_funcionarios.dat", "wb+");
    if(arq == NULL)
    {
        printf("arquivo base_funcionarios.dat n�o encontrado.\n");
        return 1;
    }

    /*criando um arquivo l�gico para abir para leitura e escrita do arquivo de indice primario ordenado*/
    FILE* arqIndicePrimario = fopen("IndicePrimarioFunc.dat", "wb+");
    if(arqIndicePrimario == NULL) {
        printf("Arquivo IndicePrimarioFunc.dat n�o encontrado.\n");
        return 1;
    }

    /*criando um arquivo l�gico para abir para leitura e escrita do arquivo de indice primario n�o ordenado*/
    FILE* arqIndicePrimarioNaoOrdenado = fopen("IndicePrimarioFuncNaoOrdenado.dat", "wb+");
    if(arqIndicePrimarioNaoOrdenado == NULL) {
        printf("Arquivo IndicePrimarioFuncNaoOrdenado.dat n�o encontrado.\n");
        return 1;
    }

    int op = menu();

    while(op!=-1)
    {
        switch (op)
        {
        case(1):
            cria_base_funcionarios(arq, arqIndicePrimario, arqIndicePrimarioNaoOrdenado, 5);
            arqPreenchido = true;
            printf("arquivo base_funcionarios.dat preenchido.\n");
            break;

        case(2):
                //imprime a base de dados dos funcion�rios
                if(arqPreenchido)
                    imprime_base_dados_funcionarios(arq);
                else  printf("Base de dados n�o foi criada e preenchida, crie utilizando a o numero 1 do menu!!!\n");
            break;
        case (3):
            //imprime o arquivo de �ndices prim�rios
            if(arqPreenchido==1){
                printf("\nArquivo ordenado\n ch:rrn\n");
                imprime_indice_primario_funcionarios(arqIndicePrimario, numFuncionarios);
                printf("\nArquivo n�o ordenado\n ch:rrn\n");
                imprime_indice_primario_funcionarios(arqIndicePrimarioNaoOrdenado, numFuncionarios);
            }else {
                printf("Indice primario inexistente para consulta e impress�o, ser� criado ap�s a defini��o da base de dados utilizando a op��o 1 do menu!!!\n");
            }
            break;


        // Quest�o 2
        case(4):
            // realiza busca sequencial na base de dados
            if(arqPreenchido==1){
                //imprime_base_dados_funcionarios(arq, numFuncionarios);
                //procurando por um funcion�rio na base de dados usando o m�todo de busca bin�ria
                int cod_busca;
                printf("\n\nDigite o codigo do funcion�rio procurado (digite -1 caso n�o queira procurar um funcion�rio): ");
                scanf("%d", &cod_busca);
                if(cod_busca!= -1){
                    TFunc func = busca_sequencial_funcionario(arq, cod_busca);
                    imprime_funcionario(&func);
                    free(&func);
                }
            }else printf("Base de dados inexistente para ser ordenada, crie utilizando a op��o 1 do menu!!!\n");
            break;

        case(5):
            break;

        // Quest�o 3
        case(6):
            if(arqPreenchido){
                insertion_sort_disco(arq, numFuncionarios);
                printf("\nBase de dados ordenada no disco\n");
                imprime_base_dados_funcionarios(arq);
            }else printf("Base de dados inexistente para ser ordenada, crie utilizando a op��o 1 do menu!!!\n");
            break;
        // Quest�o 5
        case (7):
                 //ordenando a base de dados utilizando ordena��o direta no arquivo com o m�todo inseriton sort
            if(arqPreenchido){
                insertion_sort_disco(arq, numFuncionarios);
                imprime_base_dados_funcionarios(arq);
                //procurando por um funcion�rio na base de dados usando o m�todo de busca bin�ria
                int cod_busca;
                printf("\n\nDigite o codigo do funcion�rio procurado (digite -1 caso n�o queira procurar um funcion�rio): ");
                scanf("%d", &cod_busca);
                if(cod_busca!= -1){
                    TFunc* func = busca_binaria(cod_busca, arq, numFuncionarios);
                    imprime_funcionario(func);
                    free(func);
                }
            }else printf("Base de dados inexistente para ser ordenada, crie utilizando a op��o 1 do menu!!!\n");
            break;
        }
        op = menu();
    }

}
