#include "Livro.h"

LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano, const char* n_req)
{
    LIVRO* X = (LIVRO*)malloc(sizeof(LIVRO));
    strcpy(X->AREA, area);
    strcpy(X->ISBN, isbn);
    strcpy(X->TITULO, titulo);
    strcpy(X->AUTOR, autor);
    strcpy(X->ANO, ano);
    strcpy(X->N_REQ, n_req);
    //X->N_REQ, n_req;
    return X;
}
//-------------------------------
void MostrarLivro(void* P)
{
    LIVRO* X = (LIVRO*)P;
    printf("LIVRO (%s, %s, %s, %s, %s, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ);
}
//-------------------------------
void MostrarLivroMaisRequisitado(void* P, int parametro)
{
    LIVRO* X = (LIVRO*)P;

    //int requisicao_maior = X->N_REQ;
    int requisicao_maior = atoi(X->N_REQ);

    if (requisicao_maior == parametro)
    {
        printf("LIVRO (%s, %s, %s, %s, %s, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ);
        printf("Com um total de %d requisições!\n", requisicao_maior);
    }
}
//-------------------------------
void ProcurarLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    if (strcmp(X->ISBN, parametro) == 0)
    {
        printf("Encontrei\n");
        printf("LIVRO (%s, %s, %s, %s, %s, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ);
    }
}
//-------------------------------
int GetRequisicoesLivros(void* P)
{
    LIVRO* X = (LIVRO*)P;

    //int requisicoes = X->N_REQ;
    int requisicoes = atoi(X->N_REQ);

    return requisicoes;
}
//-------------------------------
void DestruirLIVRO(void* P)
{
    LIVRO* X = (LIVRO*)P;
    //free(X->ISBN);
    //free(X->TITULO);
    free(X);
}