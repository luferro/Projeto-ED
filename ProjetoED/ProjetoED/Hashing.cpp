
#include "Hashing.h"

extern LISTA* CriarLISTA();

extern void AddLista(LISTA* L, void* EL);
extern void MostrarLISTA(LISTA* L, void (*func)(void*));
extern void ProcurarLISTA(LISTA* L, void (*func)(void*, const char*), const char* parametro);
extern void DestruirLISTA(LISTA* L, void (*func)(void*));

extern int GetRequisicoesArea(LISTA* L, int (*func)(void*));
extern int GetRequisicoesLivroMaisRequisitado(LISTA* L, int (*func)(void*));
extern int GetRequisicoesLivros(void* P);

extern void MostrarLivro(void* P);
extern void ProcurarLivro(void* P, const char* parametro);
extern void RequisitarLivro(void* P, const char* parametro);
extern void DevolverLivro(void* P, const char* parametro);
extern void MostrarRequisicoes(void* P);
extern void ProcurarLivroMaisRequisitado(LISTA* L, void (*func)(void*, int), int parametro);
extern void MostrarLivroMaisRequisitado(void* P, int parametro);
extern void DestruirLIVRO(void* P);

//---------------------------------
Hashing* CriarHASHING()
{
    Hashing* H = (Hashing*)malloc(sizeof(Hashing));
    if (!H) return NULL;
    H->Inicio = NULL;
    H->NUM_CHAVES = 0;
    return H;
}
//-------------------------------
NO_HAS* Hashing_Vector_Area(Hashing* H, const char* area)
{
    if (!H) return NULL;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        if (strcmp(P->CHAVE, area) == 0)
            return P;
        P = P->Prox_Chave;
    }
    return NULL;
}
//-------------------------------
NO_HAS* Hashing_Vector(Hashing* H, LIVRO* V)
{
    return Hashing_Vector_Area(H, V->AREA);
}
//-------------------------------
void AddHASHING(Hashing* H, LIVRO* X)
{
    if (!H) return;
    NO_HAS* P = Hashing_Vector(H, X);
    if (P == NULL)
    {
        P = (NO_HAS*)malloc(sizeof(NO_HAS));
        strcpy(P->CHAVE, X->AREA);
        P->LLivros = CriarLISTA();
        P->Prox_Chave = H->Inicio;
        H->Inicio = P;
        H->NUM_CHAVES++;
    }
    AddLista(P->LLivros, X);
}
//-------------------------------
void MostrarHASHING(Hashing* H)
{
    if (!H) return;
    NO_HAS* P = H->Inicio;
    printf("NUMERO-AREAS = %d\n", H->NUM_CHAVES);
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        MostrarLISTA(P->LLivros, MostrarLivro);
        P = P->Prox_Chave;
    }
}
//-------------------------------
void AreaComMaisLivros(Hashing* H)
{
    if (!H) return;
    int tmp = 0, quantidade = 0;
    char* chave = NULL;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        tmp = P->LLivros->NEL;
        if (tmp > quantidade) {
            quantidade = tmp;
            chave = P->CHAVE;
        }
        P = P->Prox_Chave;
    }
    if(quantidade == 0) printf("Área não tem nenhum livro.");
    else printf("Área com mais livros: %s, registando um total de %d livros.", chave, quantidade);
}
//-------------------------------
void PesquisarLivros(Hashing* H, const char* parametro)
{
    if (!H) return;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        ProcurarLISTA(P->LLivros, ProcurarLivro, parametro);
        P = P->Prox_Chave;
    }
}
//-------------------------------
void Requisitar(Hashing* H, const char* parametro)
{
    if (!H) return;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        ProcurarLISTA(P->LLivros, RequisitarLivro, parametro);
        P = P->Prox_Chave;
    }
}
//-------------------------------
void Devolver(Hashing* H, const char* parametro)
{
    if (!H) return;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        ProcurarLISTA(P->LLivros, DevolverLivro, parametro);
        P = P->Prox_Chave;
    }
}
//-------------------------------
void MostrarLivrosRequisitados(Hashing* H)
{
    if (!H) return;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        MostrarLISTA(P->LLivros, MostrarRequisicoes);
        P = P->Prox_Chave;
    }
}
//-------------------------------
void PesquisarLivroMaisRequisitado(Hashing* H)
{
    if (!H) return;
    int tmp, maior_req_todos = 0;
    void* teste = NULL;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        tmp = GetRequisicoesLivroMaisRequisitado(P->LLivros, GetRequisicoesLivros);
        if (tmp > maior_req_todos) {
            maior_req_todos = tmp;
            ProcurarLivroMaisRequisitado(P->LLivros, MostrarLivroMaisRequisitado, maior_req_todos);
        }
        P = P->Prox_Chave;
    }
    if (maior_req_todos == 0) printf("Nenhum livro foi requisitado");
}
//-------------------------------
void PesquisarAreaMaisRequisitada(Hashing* H)
{
    if (!H) return;
    int tmp, maior_req_todos = 0, i = 0;
    char* chave = (char*)malloc(sizeof(char) * 50);
    NO_HAS* P = H->Inicio;
    while (P)
    {
        tmp = GetRequisicoesArea(P->LLivros, GetRequisicoesLivros);
        if (tmp > maior_req_todos) {
            maior_req_todos = tmp;
            chave = P->CHAVE;
        }
        else if (i == 0 && tmp == 0) chave = P->CHAVE;
        i++;
        P = P->Prox_Chave;
    }
    printf("O maior número de requisições vai para a área %s com um total de %d requisições\n", chave, maior_req_todos);
}
//-------------------------------
void PesquisarAreaMenosRequisitada(Hashing* H)  //Não era pedido
{
    if (!H) return;
    int tmp, maior_req_todos, i = 0;
    char* chave = (char*)malloc(sizeof(char) * 50);
    NO_HAS* P = H->Inicio;
    maior_req_todos = GetRequisicoesArea(P->LLivros, GetRequisicoesLivros);
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        tmp = GetRequisicoesArea(P->LLivros, GetRequisicoesLivros);
        if (tmp < maior_req_todos) {
            maior_req_todos = tmp;
            chave = P->CHAVE;
        }
        else if(i == 0 && tmp == 0) chave = P->CHAVE;
        i++;
        P = P->Prox_Chave;
    }
    printf("O menor número de requisições vai para a área %s com um total de %d requisições\n", chave, maior_req_todos);
}
//-------------------------------
void DestruirHASHING(Hashing* H)
{
    if (!H) return;
    NO_HAS* Aux = NULL;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        Aux = P->Prox_Chave;
        DestruirLISTA(P->LLivros, DestruirLIVRO);
        free(P);
        P = Aux;
    }
    free(H);
}