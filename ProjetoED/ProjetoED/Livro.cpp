#include "Livro.h"

LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano)
{
    LIVRO* X = (LIVRO*)malloc(sizeof(LIVRO));
    strcpy(X->AREA, area);
    strcpy(X->ISBN, isbn);
    strcpy(X->TITULO, titulo);
    strcpy(X->AUTOR, autor);
    strcpy(X->ANO, ano);
    X->N_REQ = 0;
    strcpy(X->ESTADO_REQ, "Disponivel");
    return X;
}
//-------------------------------
void MostrarLivro(void* P)
{
    LIVRO* X = (LIVRO*)P;
    printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
}
//-------------------------------
void MostrarLivroMaisRequisitado(void* P, int parametro)
{
    LIVRO* X = (LIVRO*)P;

    int requisicao_maior = X->N_REQ;

    if (requisicao_maior == parametro)
    {
        printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
        printf("Com um total de %d requisições!\n", requisicao_maior);
    }
}
//-------------------------------
void MostrarLivroMaisRecente(void* P, int parametro)
{
    LIVRO* X = (LIVRO*)P;

    char* str = X->ANO;
    int ano = 0;

    char* last = strrchr(str, '/');
    if (last != NULL) {
        ano = atoi(last + 1);
    }

    if (ano == parametro)
    {
        printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
        printf("No ano 20%d!\n", ano);
    }
}
//-------------------------------
void ProcurarLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    if (strcmp(X->ISBN, parametro) == 0)
    {
        printf("Encontrei\n");
        printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
    }
}
//-------------------------------
int GetLivrosMaisRecentes(void* P)
{
    LIVRO* X = (LIVRO*)P;

    char* str = X->ANO;
    int ano = 0;

    char* last = strrchr(str, '/');
    if (last != NULL) {
        ano = atoi(last + 1);
    }

    return ano;
}
//-------------------------------
int GetRequisicoesLivros(void* P)
{
    LIVRO* X = (LIVRO*)P;

    //int requisicoes = X->N_REQ;
    int requisicoes = X->N_REQ;

    return requisicoes;
}
//-------------------------------
void RequisitarLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    if (strcmp(X->TITULO, parametro) == 0)
    {
        if (strcmp(X->ESTADO_REQ, "Disponivel") == 0) {
            strcpy(X->ESTADO_REQ, "Requisitado");
            X->N_REQ++;

            printf("Livro Requisitado!\n");
            printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
        }
        else printf("Livro %s já se encontra requisitado.\n", X->TITULO);
    }
}
//-------------------------------
void DevolverLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    if (strcmp(X->TITULO, parametro) == 0)
    {
        if (strcmp(X->ESTADO_REQ, "Requisitado") == 0) {
            strcpy(X->ESTADO_REQ, "Disponivel");

            printf("Livro devolvido!\n");
            printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
        }
        else printf("Livro %s já se encontra disponivel para requisição.\n", X->TITULO);
    }
}
//-------------------------------
void MostrarRequisicoes(void* P)
{
    LIVRO* X = (LIVRO*)P;

    if (strcmp(X->ESTADO_REQ, "Requisitado") == 0) {
        printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
    }
}
//-------------------------------
void DestruirLIVRO(void* P)
{
    LIVRO* X = (LIVRO*)P;
    //free(X->ISBN);
    //free(X->TITULO);
    free(X);
}