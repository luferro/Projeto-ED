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
void MostrarIdadeMaxima(LISTA* L, int (*func)(void*))
{
    if (!L) return;
    int idade_max = 0, tmp = 0;
    NO* P = L->Inicio;
    while (P)
    {
        tmp = (*func)(P->INFO);
       
        if (tmp > idade_max && tmp < 150) {
            idade_max = tmp;
        }
        P = P->PROX;
    }
    printf("Idade Máxima é de %d anos!\n", idade_max);
}
//-------------------------------
void MostrarIdadeMedia(LISTA* L, int (*func)(void*))
{
    if (!L) return;
    int idade_med = 0, tmp = 0;
    NO* P = L->Inicio;
    while (P)
    {
        tmp += (*func)(P->INFO);
        if (P->PROX == NULL)
            idade_med = tmp / L->NEL;
        P = P->PROX;
    }
    printf("Idade Média é de %d anos!\n", idade_med);
}
//-------------------------------
void MostrarIdadeSuperiorX(LISTA* L, int (*func)(void*), int parametro)
{
    if (!L) return;
    int tmp = 0, contagem = 0;
    NO* P = L->Inicio;
    while (P)
    {
        tmp = (*func)(P->INFO);
        if (tmp > parametro) {
            contagem++;
        }
        P = P->PROX;
    }
    printf("\n%d pessoas tem idade superior a %d\n", contagem, parametro);
}
//-------------------------------
void MostrarIdadeMaisComum(LISTA* L, int (*func)(void*))
{
    if (!L) return;
    int *array = (int*)malloc(L->NEL * sizeof(int)), *array_freq = (int*)malloc(L->NEL * sizeof(int)), contagem = 0, idade_freq = 0, ocorrencias = 0;

    for (int k = 0; k < L->NEL; k++) {
        array[k] = 0;
        array_freq[k] = -1;
    }

    int i = 0;
    NO* P = L->Inicio;

    while (P)
    {
        array[i++] = (*func)(P->INFO);
        P = P->PROX;
    }
    
    for (int k = 0; k < L->NEL; k++) {
        contagem = 1;
        for (int j = k + 1; j < L->NEL; j++) {
            if (array[k] == array[j]) {
                contagem++;
                array_freq[j] = 0;
            }
        }

        if (array_freq[k] != 0) {
            array_freq[k] = contagem;

            if (array_freq[k] > ocorrencias) {
                ocorrencias = array_freq[k];
                idade_freq = array[k];
            }
        }
    }

    printf("%d anos é a idade com mais requisitantes, totalizando %d requisitantes\n", idade_freq, ocorrencias);

    free(array);
    free(array_freq);
}
//-------------------------------
void MostrarSobrenomeMaisComum(LISTA* L, char* (*func)(void*))
{
    if (!L) return;
    NO* P = L->Inicio;
    char** array = (char**)malloc(L->NEL * sizeof(char*)), *sobrenome = (char*)malloc(20 * sizeof(char));
    int* array_freq = (int*)malloc(L->NEL * sizeof(int)), i = 0, contagem = 0, ocorrencias = 0;
    while (P)
    {
        array[i++] = (*func)(P->INFO);
        P = P->PROX;
    }

    for (int k = 0; k < L->NEL; k++) {
        contagem = 1;
        for (int j = k + 1; j < L->NEL; j++) {
            if (strcmp(array[k], array[j]) == 0) {
                contagem++;
                array_freq[j] = 0;
            }
        }

        if (array_freq[k] != 0) {
            array_freq[k] = contagem;

            if (array_freq[k] > ocorrencias) {
                ocorrencias = array_freq[k];
                strcpy(sobrenome, array[k]);
            }
            printf("%s occurs %d times\n", array[k], array_freq[k]);
        }
    }

    printf("%s é o sobrenome com mais requisitantes, totalizando %d requisitantes\n", sobrenome, ocorrencias);

    free(array);
    free(array_freq);
    
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
void ProcurarLivroMaisRequisitadoRecente(LISTA* L, void (*func)(void*, int), int parametro)
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
int GetListaLivrosMaisRecentes(LISTA* L, int (*func)(void*))
{
    if (!L) return 0;
    int mais_recentes = 0, tmp = 0;
    NO* P = L->Inicio;
    while (P)
    {
        tmp = (*func)(P->INFO);
        if (tmp > mais_recentes) {
            mais_recentes = tmp;
        }
        P = P->PROX;
    }
    return mais_recentes;
}
//-------------------------------
int GetRequisicoesLivroMaisRequisitado(LISTA* L, int (*func)(void*))
{
    if (!L) return 0;
    int maior_req = 0, tmp = 0;
    NO* P = L->Inicio;
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

