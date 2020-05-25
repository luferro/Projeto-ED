#include "Freguesia.h"

FREGUESIA* CriarFreguesia(const char* id_freguesia, const char* freguesia)
{
    FREGUESIA* X = (FREGUESIA*)malloc(sizeof(FREGUESIA));
    if (!X) return NULL;

    X->ID_FREGUESIA = (char*)malloc((strlen(id_freguesia) + 1) * sizeof(char));
    X->NOME_FREGUESIA = (char*)malloc((strlen(freguesia) + 1) * sizeof(char));
    
    strcpy(X->ID_FREGUESIA, id_freguesia);
    strcpy(X->NOME_FREGUESIA, freguesia);

    int tmp = atoi(id_freguesia);
    char zero[3];
    strcpy(zero, "0");
    char* id_concelho = (char*)malloc((strlen(id_freguesia) + 1) * sizeof(char));
    //A partir do id_freguesia, conseguimos "partir" o id conseguido o id_concelho
    tmp = tmp / 100;
    itoa(tmp, id_concelho, 10);
    //Se o id_concelho for < 10, concateno um 0 ao seu valor
    if (tmp < 10) id_concelho = strcat(zero, id_concelho);

    strcpy(X->ID_CONCELHO, id_concelho);

    return X;
}
//-------------------------------
void MostrarFreguesia(void* P)
{
    FREGUESIA* X = (FREGUESIA*)P;
    printf("FREGUESIA (%s, %s, %s)\n", X->ID_FREGUESIA, X->ID_CONCELHO, X->NOME_FREGUESIA);
}
//-------------------------------
void GravarFreguesia(void* P, FILE* F)
{
    FREGUESIA* X = (FREGUESIA*)P;
    fprintf(F, "\t\t\tFREGUESIA (%s, %s, %s)\n", X->ID_FREGUESIA, X->ID_CONCELHO, X->NOME_FREGUESIA);
}
//-------------------------------
void GravarFreguesia_Sessao(void* P, FILE* F)
{
    FREGUESIA* X = (FREGUESIA*)P;
    fprintf(F, "%s\t%s\t%s\n", X->ID_FREGUESIA, X->ID_CONCELHO, X->NOME_FREGUESIA);
}
//-------------------------------
void DestruirFREGUESIA(void* P)
{
    FREGUESIA* X = (FREGUESIA*)P;
    free(X->ID_FREGUESIA);
    free(X->NOME_FREGUESIA);
    free(X);
}