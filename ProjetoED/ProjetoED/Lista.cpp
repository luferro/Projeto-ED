#include "Lista.h"

//-------------------------------
LISTA* CriarLISTA()
{
    LISTA* L = (LISTA*)malloc(sizeof(LISTA));
    L->Inicio = NULL;
    L->NEL = 0;
    return L;
}
//-------------------------------
void AddLista(LISTA* L, void* EL)
{
    if (!L) return;
    NO* aux = (NO*)malloc(sizeof(NO));
    aux->INFO = EL;
    aux->PROX = L->Inicio;
    L->Inicio = aux;
    L->NEL++;
}
//-------------------------------
void MostrarLISTA(LISTA* L, void (*func)(void*))
{
    if (!L) return;
    NO* P = L->Inicio;
    while (P)
    {
        (*func)(P->INFO);
        P = P->PROX;
    }
}
//-------------------------------
void ProcurarLISTA(LISTA* L, void (*func)(void*, const char*), const char* parametro)
{
    if (!L) return;
    NO* P = L->Inicio;
    while (P)
    {
        (*func)(P->INFO, parametro);
        P = P->PROX;
    }
}
//-------------------------------
void ProcurarLivroMaisRequisitado(LISTA* L, void (*func)(void*, int), int parametro)
{
    if (!L) return;
    NO* P = L->Inicio;
    while (P)
    {
        (*func)(P->INFO, parametro);
        P = P->PROX;
    }
}
//-------------------------------
int GetRequisicoesArea(LISTA* L, int (*func)(void*))
{
    if (!L) return 0;
    int maior_req = 0, tmp = 0;
    NO* P = L->Inicio;
    while (P)
    {
        tmp += (*func)(P->INFO);
        if (tmp > maior_req) maior_req = tmp;
        P = P->PROX;
    }
    return maior_req;
}
//-------------------------------
int GetRequisicoesLivroMaisRequisitado(LISTA* L, int (*func)(void*))
{
    if (!L) return 0;
    int maior_req = 0, tmp = 0;
    NO* P = L->Inicio;
    void* teste = NULL;
    while (P)
    {
        tmp = (*func)(P->INFO);
        if (tmp > maior_req) {
            maior_req = tmp;
        }
        P = P->PROX;
    }
    return maior_req;
}
//-------------------------------
void DestruirLISTA(LISTA* L, void (*func)(void*))
{
    if (!L) return;
    NO* Aux = NULL;
    NO* P = L->Inicio;
    while (P)
    {
        Aux = P->PROX;
        (*func)(P->INFO);
        free(P);
        P = Aux;
    }
    free(L);
}

