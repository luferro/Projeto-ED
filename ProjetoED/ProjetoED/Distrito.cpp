#include "Distrito.h"

DISTRITO* CriarDistrito(const char* id_distrito, const char* distrito)
{
    DISTRITO* X = (DISTRITO*)malloc(sizeof(DISTRITO));
    if (!X) return NULL;

    X->ID_DISTRITO = (char*)malloc((strlen(id_distrito) + 1) * sizeof(char));
    X->NOME_DISTRITO = (char*)malloc((strlen(distrito) + 1) * sizeof(char));

    strcpy(X->ID_DISTRITO, id_distrito);
    strcpy(X->NOME_DISTRITO, distrito);

    return X;
}
//-------------------------------
void MostrarDistrito(void* P)
{
    DISTRITO* X = (DISTRITO*)P;
    printf("DISTRITO: %s\t%s\n", X->ID_DISTRITO, X->NOME_DISTRITO);
}
//-------------------------------
void GravarDistrito(void* P, FILE* F)
{
    DISTRITO* X = (DISTRITO*)P;
    fprintf(F, "\t\t\tDISTRITO: %s\t%s\n", X->ID_DISTRITO, X->NOME_DISTRITO);
}
//-------------------------------
void GravarDistrito_Sessao(void* P, FILE* F)
{
    DISTRITO* X = (DISTRITO*)P;
    fprintf(F, "%s\t%s\n", X->ID_DISTRITO, X->NOME_DISTRITO);
}
//-------------------------------
int GetDistritos(void* P, const char* parametro)
{
    DISTRITO* X = (DISTRITO*)P;

    //Compara o nome do distrito com o parametro de entrada, verificando se o nome do distrito contém o nome presente no parametro de entrada
    if (strstr(X->NOME_DISTRITO, parametro) != NULL)
    {
        int id_distrito = atoi(X->ID_DISTRITO);
        return id_distrito; //Se existir, devolve o seu ID
    }
    
}
//-------------------------------
void DestruirDISTRITO(void* P)
{
    DISTRITO* X = (DISTRITO*)P;
    free(X->ID_DISTRITO);
    free(X->NOME_DISTRITO);
    free(X);
}
