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
    
    char* str = X->DATA_NASC;
    int ano = 0, idade = 0;

    char* last = strrchr(str, '-');
    if (last != NULL) {
        ano = atoi(last + 1);
    }  

    idade = 2020 - ano;

    return idade;
}
//-------------------------------
char* GetSobrenomeRequisitantes(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    char* str = X->REQUISITANTE;
    char* sobrenome = NULL;

    char* last = strrchr(str, ' ');
    if (last != NULL) {
        sobrenome = last + 1;
    }

    return sobrenome;
}
//-------------------------------
void DestruirREQUISITANTE(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    free(X);
}