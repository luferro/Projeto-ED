#include "Requisicao.h"

REQUISICAO* CriarRequisicao(int id_requisitante, int id_livro)
{
    REQUISICAO* X = (REQUISICAO*)malloc(sizeof(REQUISICAO));
    if (!X) return NULL;

    X->ID_REQUISITANTE = id_requisitante;
    X->ID_LIVRO = id_livro;
    
    return X;
}
//---------------------------------
void MostrarRequisicoesID(void* P)
{
    REQUISICAO* X = (REQUISICAO*)P;
    printf("REQUISICAO: %d\t%d\n", X->ID_LIVRO, X->ID_REQUISITANTE);
}
//---------------------------------
void GravarRequisicoes(void* P, FILE* F)
{
    REQUISICAO* X = (REQUISICAO*)P;
    if(X->ID_LIVRO != 0 && X->ID_REQUISITANTE != 0)
        fprintf(F, "\t\tREQUISICAO: %d\t%d\n", X->ID_LIVRO, X->ID_REQUISITANTE);
}
//---------------------------------
void GravarRequisicoes_Sessao(void* P, FILE* F)
{
    REQUISICAO* X = (REQUISICAO*)P;
    if (X->ID_LIVRO != 0 && X->ID_REQUISITANTE != 0)
        fprintf(F, "%d\t%d\n", X->ID_LIVRO, X->ID_REQUISITANTE);
}
//---------------------------------
int GetIDRequisitante(void* P, int parametro)
{
    REQUISICAO* X = (REQUISICAO*)P;

    int id_requisitante = X->ID_REQUISITANTE;

    //Compara o id_livro com o parametro de entrada
    if (X->ID_LIVRO == parametro) {
        return id_requisitante; //Devolve o id_requisitante
    }
    return 0;
}
//---------------------------------
int GetIDRequisitanteEmRequisicoes(void* P, int parametro)
{
    REQUISICAO* X = (REQUISICAO*)P;

    int id_livro = X->ID_LIVRO;

    if (X->ID_REQUISITANTE == parametro) {
        return id_livro; //Devolve o id_livro
    }
    return 0;
}
//---------------------------------
void RemoverRequisicao(void* P, int parametro)
{
    REQUISICAO* X = (REQUISICAO*)P;
    
    //Compara o id_livro com o parametro de entrada
    if (X->ID_LIVRO == parametro) { 
        X->ID_LIVRO = 0; X->ID_REQUISITANTE = 0;    //Se encontrar, liberta a requisição referente a esse livro permitindo que este seja novamente requisitado
    }
}
//-------------------------------
void DestruirREQUISICAO(void* P)
{
    REQUISICAO* X = (REQUISICAO*)P;
    free(X);
}