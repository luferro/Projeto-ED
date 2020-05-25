#include "Requisicao.h"

REQUISICAO* CriarRequisicao(int id_requisicao, int id_requisitante, int id_livro)
{
    REQUISICAO* X = (REQUISICAO*)malloc(sizeof(REQUISICAO));
    if (!X) return NULL;

    X->ID_REQUISICAO = id_requisicao;
    X->ID_REQUISITANTE = id_requisitante;
    X->ID_LIVRO = id_livro;
    
    return X;
}
//---------------------------------
void MostrarRequisicoesID(void* P)
{
    REQUISICAO* X = (REQUISICAO*)P;
    printf("REQUISICAO (%d, %d, %d)\n", X->ID_REQUISICAO, X->ID_LIVRO, X->ID_REQUISITANTE);
}
//---------------------------------
void GravarRequisicoes(void* P, FILE* F)
{
    REQUISICAO* X = (REQUISICAO*)P;
    fprintf(F, "\t\t\tREQUISICAO (%d, %d, %d)\n", X->ID_REQUISICAO, X->ID_LIVRO, X->ID_REQUISITANTE);
}
//---------------------------------
void GravarRequisicoes_Sessao(void* P, FILE* F)
{
    REQUISICAO* X = (REQUISICAO*)P;
    fprintf(F, "%d\t%d\t%d\n", X->ID_REQUISICAO, X->ID_LIVRO, X->ID_REQUISITANTE);
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
        free(X);    //Se encontrar, liberta a requisição referente a esse livro permitindo que este seja novamente requisitado
    }
}
//-------------------------------
void DestruirREQUISICAO(void* P)
{
    REQUISICAO* X = (REQUISICAO*)P;
    free(X);
}