#include "Concelho.h"

CONCELHO* CriarConcelho(const char* id_concelho, const char* concelho)
{
    CONCELHO* X = (CONCELHO*)malloc(sizeof(CONCELHO));
    if (!X) return NULL;

    X->ID_CONCELHO = (char*)malloc((strlen(id_concelho) + 1) * sizeof(char));
    X->NOME_CONCELHO = (char*)malloc((strlen(concelho) + 1) * sizeof(char));

    strcpy(X->ID_CONCELHO, id_concelho);
    strcpy(X->NOME_CONCELHO, concelho);
    
    int tmp = atoi(id_concelho);
    char zero[3];
    strcpy(zero, "0");
    char* id_distrito = (char*)malloc((strlen(id_concelho) + 1) * sizeof(char));
    //A partir do id_concelho, conseguimos "partir" o id conseguido o id_distrito
    tmp = tmp / 100;
    itoa(tmp, id_distrito, 10);
    //Se o id_distrito for < 10, concateno um 0 ao seu valor
    if(tmp < 10) id_distrito = strcat(zero, id_distrito);

    strcpy(X->ID_DISTRITO, id_distrito);
  
    return X;
}
//-------------------------------
void MostrarConcelho(void* P)
{
    CONCELHO* X = (CONCELHO*)P;
    printf("CONCELHO (%s, %s, %s)\n", X->ID_CONCELHO, X->ID_DISTRITO, X->NOME_CONCELHO);
}
//-------------------------------
void GravarConcelho(void* P, FILE* F)
{
    CONCELHO* X = (CONCELHO*)P;
    fprintf(F, "\t\t\tCONCELHO (%s, %s, %s)\n", X->ID_CONCELHO, X->ID_DISTRITO, X->NOME_CONCELHO);
}
//-------------------------------
void GravarConcelho_Sessao(void* P, FILE* F)
{
    CONCELHO* X = (CONCELHO*)P;
    fprintf(F, "%s\t%s\t%s\n", X->ID_CONCELHO, X->ID_DISTRITO, X->NOME_CONCELHO);
}
//-------------------------------
void DestruirCONCELHO(void* P)
{
    CONCELHO* X = (CONCELHO*)P;
    free(X->ID_CONCELHO);
    free(X->NOME_CONCELHO);
    free(X);
}
