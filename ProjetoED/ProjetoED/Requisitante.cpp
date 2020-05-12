#include "Requisitante.h"

REQUISITANTE* CriarRequisitante(const char* id_requisitante, const char* requisitante, const char* data_nasc)
{
    REQUISITANTE* X = (REQUISITANTE*)malloc(sizeof(REQUISITANTE));
    strcpy(X->ID_REQUISITANTE, id_requisitante);
    strcpy(X->REQUISITANTE, requisitante);
    strcpy(X->DATA_NASC, data_nasc);
    return X;
}
//-------------------------------
void MostrarRequisitante(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    printf("REQUISITANTE (%s, %s, %s)\n", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC);
}
//-------------------------------
void ProcurarRequisitante(void* P, const char* parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    if (strstr(X->REQUISITANTE, parametro) != NULL)
    {
        printf("REQUISITANTE (%s, %s, %s)\n", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC);
    }
}
//-------------------------------
int GetIdadeRequisitantes(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    char* dia, *mes, *ano;
    char* data = X->DATA_NASC;
    int idade = 0, ano_nasc;

    dia = strtok(data, "-");
    mes = strtok(data, "-");
    ano = strtok(NULL, "-");

    ano_nasc = atoi(ano);

    //something
    idade = 2020 - ano_nasc;
    
    return idade;
}
//-------------------------------
void DestruirREQUISITANTE(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    free(X);
}