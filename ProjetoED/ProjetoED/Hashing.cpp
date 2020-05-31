
#include "Hashing.h"

extern LISTA* CriarLISTA();

extern void AddLista(LISTA* L, void* EL);
extern void MostrarLISTA(LISTA* L, void (*func)(void*));
extern void ProcurarLISTA(LISTA* L, void (*func)(void*, const char*), const char* parametro);
extern void DestruirLISTA(LISTA* L, void (*func)(void*));

extern int GetRequisicoesArea(LISTA* L, int (*func)(void*));
extern int GetRequisicoesLivroMaisRequisitado(LISTA* L, int (*func)(void*));
extern int GetRequisicoesLivros(void* P);
extern int GetLivrosMaisRecentes(void* P);
extern int GetListaLivrosMaisRecentes(LISTA* L, int (*func)(void*));
extern int GetIDLivro(void* P, const char* parametro);
extern int GetID(LISTA* L, int (*func)(void*, const char*), const char* parametro);
extern int GetIDRequisitanteEmRequisicoes(void* P, int parametro);
extern int ProcurarRequisitar(LISTA* L, int (*func)(void*, const char*), const char* parametro);;

extern void MostrarLivrosRequisitadosPorRequisitante(void* P, int parametro);
extern void MostrarLivro(void* P);
extern void ProcurarLivro(void* P, const char* parametro);
extern int RequisitarLivro(void* P, const char* parametro);
extern void DevolverLivro(void* P, const char* parametro);
extern void MostrarRequisicoes(void* P);
extern void ProcurarLivroMaisRequisitadoRecente(LISTA* L, void (*func)(void*, int), int parametro);
extern void MostrarLivroMaisRecente(void* P, int parametro);
extern void MostrarLivroMaisRequisitado(void* P, int parametro);
extern void MostrarLivrosRequisitadosPorRequisitante(void* P, int parametro);
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
    printf("Número de Areas = %d\n", H->NUM_CHAVES);
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        MostrarLISTA(P->LLivros, MostrarLivro);
        P = P->Prox_Chave;
    }
}
//-------------------------------
void MostrarHASHINGLivrosRequisitadosPorRequisitante(Hashing* H, LISTA* L, int parametro)
{
    if (!H && !L) return;

    NO* N = L->Inicio;
    NO_HAS* P = H->Inicio;

    int* array = (int*)malloc(L->NEL * sizeof(int)), i = 0, k = 0;
    //Inicialização do array
    for (int k = 0; k < L->NEL; k++) {
        array[k] = 0;
    }

    while (N)   //Percorrer lista de requisições
    {
        array[i++] = GetIDRequisitanteEmRequisicoes(N->INFO, parametro);    //Encher array com IDs dos livros relativos a um dado requisitante
        N = N->PROX;
    }

    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        for (int k = 0; k < L->NEL; k++) {
            ProcurarLivroMaisRequisitadoRecente(P->LLivros, MostrarLivrosRequisitadosPorRequisitante, array[k]);    //Mostra livros requisitados por um dado requisitante
        }
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
        tmp = P->LLivros->NEL;  //Vai buscar o número de elementos da estrutura de hashing e guarda numa variável tmp
        //Compara o valor da variável tmp com a quantidade previamente inicializada a 0
        if (tmp > quantidade) { 
            quantidade = tmp;   //Se tmp for superior, a variável quantidade recebe o valor de tmp
            chave = P->CHAVE;   //e guardo a chave/area correspondente a esse valor
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
int Requisitar(Hashing* H, const char* parametro)
{
    if (!H) return 0;
    NO_HAS* P = H->Inicio;
    int jaRequisitado = 0;
    while (P)
    {
        jaRequisitado = ProcurarRequisitar(P->LLivros, RequisitarLivro, parametro);     //jaRequisitado recebe o valor retornado pela função ProcurarRequisitar, 0 ou 1
        if (jaRequisitado != 0) return jaRequisitado; //Se não for 0, sabemos que o livro já está requisitado
        P = P->Prox_Chave;
    }
    return 0;
}
//-------------------------------
int RequisitarIDLivro(Hashing* H, const char* parametro)
{
    if (!H) return 0;
    NO_HAS* P = H->Inicio;
    int id_livro;
    while (P)
    {
        id_livro = GetID(P->LLivros, GetIDLivro, parametro);    //id_livro recebe o id do livro devolvido pela função GetID
        if (id_livro != 0) return id_livro;     //Se o id_livro for diferente de 0, significa que existe pelo que é retornado
        P = P->Prox_Chave;
    }
    return 0;
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
void MostrarLivrosMaisRecentes(Hashing* H)
{
    if (!H) return;
    int tmp = 0, mais_recente = 0;
    NO_HAS* P = H->Inicio;
    NO_HAS* AUX = H->Inicio;
    while (P)
    {
        tmp = GetListaLivrosMaisRecentes(P->LLivros, GetLivrosMaisRecentes);    //tmp recebe o ano encontrado pela função GetListaLivrosMaisRecentes
        //Compara tmp com mais_recente, previamente inicializado a 0
        if (tmp > mais_recente) {   
            mais_recente = tmp; //Se tmp for superior, mais_recente recebe o valor de tmp
        }
        P = P->Prox_Chave;
    }
    printf("%d\n", mais_recente);
    while (AUX)
    {
        ProcurarLivroMaisRequisitadoRecente(AUX->LLivros, MostrarLivroMaisRecente, mais_recente);   //Procura livros com o ano mais recente
        AUX = AUX->Prox_Chave;
    }
    
}
//-------------------------------
void PesquisarLivroMaisRequisitado(Hashing* H)
{
    if (!H) return;
    int tmp, maior_req_todos = 0;
    NO_HAS* P = H->Inicio;
    while (P)
    {
        printf("[%s]\n", P->CHAVE);
        tmp = GetRequisicoesLivroMaisRequisitado(P->LLivros, GetRequisicoesLivros); //tmp recebe o número de requisições encontrado pela função GetRequisicoesLivroMaisRequisitado
        //Compara tmp com maior_req_todos, previamente inicializado a 0
        if (tmp > maior_req_todos) {
            maior_req_todos = tmp;  //Se tmp for superior, mais_recente recebe o valor de tmp
            ProcurarLivroMaisRequisitadoRecente(P->LLivros, MostrarLivroMaisRequisitado, maior_req_todos);  //Procura livro com maior número de requisições
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
    char* chave = (char*)malloc(sizeof(char) * 4);
    NO_HAS* P = H->Inicio;
    while (P)
    {
        tmp = GetRequisicoesArea(P->LLivros, GetRequisicoesLivros); //tmp recebe o número de requisições de uma area encontrado pela função GetRequisicoesArea
        //Compara tmp com maior_req_todos, previamente inicializado a 0
        if (tmp > maior_req_todos) {
            maior_req_todos = tmp;  //Se tmp for superior, maior_req_todos recebe o valor de tmp
            chave = P->CHAVE;   //e guardo a chave relativa a esse número de requisições
        }
        else if (i == 0 && tmp == 0) chave = P->CHAVE;  //Caso não exista nenhuma requisição efetuada
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
    char* chave = (char*)malloc(sizeof(char) * 4);
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
int MemoriaHASHING(Hashing* H)
{
    if (!H) return 0;

    int Mem = 0;
    Mem += sizeof(*H);

    NO_HAS* P = H->Inicio;
    while (P)
    {
        Mem += sizeof(*P);
        Mem += sizeof(*(P->CHAVE));
        Mem += sizeof(*(P->LLivros));
        P = P->Prox_Chave;
    }
    return Mem;
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