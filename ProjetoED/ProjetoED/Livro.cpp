#include "Livro.h"

LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano)
{
    LIVRO* X = (LIVRO*)malloc(sizeof(LIVRO));
    if (!X) return NULL;

    X->AREA = (char*)malloc((strlen(area) + 1) * sizeof(char));
    X->ISBN = (char*)malloc((strlen(isbn) + 1) * sizeof(char));
    X->TITULO = (char*)malloc((strlen(titulo) + 1) * sizeof(char));
    X->AUTOR = (char*)malloc((strlen(autor) + 1) * sizeof(char));
    X->ANO = (char*)malloc((strlen(ano) + 1) * sizeof(char));

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
LIVRO* CriarLivro_Sessao(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano, int num_req, const char* estado_req)
{
    LIVRO* X = (LIVRO*)malloc(sizeof(LIVRO));
    if (!X) return NULL;

    X->AREA = (char*)malloc((strlen(area) + 1) * sizeof(char));
    X->ISBN = (char*)malloc((strlen(isbn) + 1) * sizeof(char));
    X->TITULO = (char*)malloc((strlen(titulo) + 1) * sizeof(char));
    X->AUTOR = (char*)malloc((strlen(autor) + 1) * sizeof(char));
    X->ANO = (char*)malloc((strlen(ano) + 1) * sizeof(char));

    strcpy(X->AREA, area);
    strcpy(X->ISBN, isbn);
    strcpy(X->TITULO, titulo);
    strcpy(X->AUTOR, autor);
    strcpy(X->ANO, ano);
    X->N_REQ = num_req;
    strcpy(X->ESTADO_REQ, estado_req);
    return X;
}
//-------------------------------
void MostrarLivro(void* P)
{
    LIVRO* X = (LIVRO*)P;
    printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
}
//-------------------------------
void MostrarLivrosRequisitadosPorRequisitante(void* P, int parametro)
{
    LIVRO* X = (LIVRO*)P;

    int id_livro = atoi(X->ISBN);

    if (id_livro == parametro)
        printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
}
//-------------------------------
void GravarLivro(void* P, FILE* F)
{
    LIVRO* X = (LIVRO*)P;
    fprintf(F, "\t\t\tLIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
}
//-------------------------------
void GravarLivro_Sessao(void* P, FILE* F)
{
    LIVRO* X = (LIVRO*)P;
    fprintf(F, "%s;%s;%s;%s;%s;%d;%s\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
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
    //Conseguir a última token da data, neste caso o ano
    char* last = strrchr(str, '/');
    if (last != NULL) {
        ano = atoi(last + 1);
    }
    //Comparar o ano conseguido no passo anterior e comparar com o parametro de entrada 
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

    //Comparar o cod. do livro com o parametro de entrada 
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

    //Conseguir a última token da data, neste caso o ano
    char* last = strrchr(str, '/');
    if (last != NULL) {
        ano = atoi(last + 1);
    }
    //e devolver essa mesma token
    return ano;
}
//-------------------------------
int GetRequisicoesLivros(void* P)
{
    LIVRO* X = (LIVRO*)P;

    int requisicoes = X->N_REQ;

    return requisicoes;
}
//-------------------------------
int GetIDLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    int id_livro = atoi(X->ISBN);

    //Compara o titulo completo do livro com o parametro de entrada, devolvendo depois o seu ID
    if (strcmp(X->TITULO, parametro) == 0) {
        return id_livro;
    }
    return 0;
}
//-------------------------------
int RequisitarLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    //Compara o titulo completo do livro com o parametro de entrada
    if (strcmp(X->TITULO, parametro) == 0)
    {
        //Posteriormente, verifica o estado de requisição do livro em questão
        if (strstr(X->ESTADO_REQ, "Disponivel") != NULL) {
            strcpy(X->ESTADO_REQ, "Requisitado");   //Se estiver disponivel, o estado de requisição é atualizado para REQUISITADO
            X->N_REQ++; //e incrementa o número de requisições desse mesmo livro

            printf("Livro Requisitado!\n");
            printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
            return 0;   
        }
        else {
            printf("Livro %s já se encontra requisitado.\n", X->TITULO);
            return 1;   //Serve para verificar mais tarde se o livro se encontra requisitado. Especialmente útil para adicionar requisições na lista requisicao
        }
    }
    return 0;
}
//-------------------------------
void DevolverLivro(void* P, const char* parametro)
{
    LIVRO* X = (LIVRO*)P;

    //Compara o titulo completo do livro com o parametro de entrada
    if (strcmp(X->TITULO, parametro) == 0)
    {
        //Posteriormente, verifica o estado de requisição do livro em questão
        if (strcmp(X->ESTADO_REQ, "Requisitado") == 0) {
            strcpy(X->ESTADO_REQ, "Disponivel"); //Se estiver requisitado, o estado de requisição é atualizado para DISPONIVEL

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

    //Mostra livros com estado de requisição REQUISITADO
    if (strstr(X->ESTADO_REQ, "Requisitado") != NULL) {
        printf("LIVRO (%s, %s, %s, %s, %s, %d, %s)\n", X->ISBN, X->AREA, X->TITULO, X->AUTOR, X->ANO, X->N_REQ, X->ESTADO_REQ);
    }
}
//-------------------------------
void DestruirLIVRO(void* P)
{
    LIVRO* X = (LIVRO*)P;
    free(X->AREA);
    free(X->ISBN);
    free(X->TITULO);
    free(X->AUTOR);
    free(X->ANO);
    free(X);
}