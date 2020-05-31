#include "Lista.h"

//-------------------------------
LISTA* CriarLISTA()
{
    LISTA* L = (LISTA*)malloc(sizeof(LISTA));
    if (!L) return NULL;

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
void GuardarLISTA(LISTA* L, void (*func)(void*, FILE*), FILE* F)
{
    if (!L) return;
    NO* P = L->Inicio;
    while (P)
    {
        (*func)(P->INFO, F);
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
        tmp = (*func)(P->INFO); //tmp recebe a idade
        //Compara tmp com idade_max, previamente inicializada a 0, e verifica também se a idade guardada em tmp é menor que um valor credível (no caso, 150) 
        if (tmp > idade_max && tmp < 150) {
            idade_max = tmp;    //se for maior e for um valor credivel, guarda esse valor na idade_max
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
        tmp += (*func)(P->INFO);    //tmp recebe a idade e vai somando esses valores
        //Verifica se o próximo elemento é null
        if (P->PROX == NULL)       
            idade_med = tmp / L->NEL;   //Se não existir, significa que estamos no último elemento pelo que pegamos no valor do somatório resultante do tmp e dividimos pelo número de elementos
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
        tmp = (*func)(P->INFO); //tmp recebe a idade
        //Compara tmp com o parametro de entrada dado pelo utilizador
        if (tmp > parametro) {
            contagem++; //Se for superior, incrementa a variável contagem
        }
        P = P->PROX;
    }
    printf("\n%d pessoas tem idade superior a %d\n", contagem, parametro);
}
//-------------------------------
void MostrarIdadeMaisComum(LISTA* L, int (*func)(void*))
{
    if (!L) return;
    //Criação de dois arrays. Um vai conter a informação pertinente (neste caso, idades) e outro será auxiliar para permitir contar a frequência com que x idade aparece
    int *array = (int*)malloc(L->NEL * sizeof(int)), *array_freq = (int*)malloc(L->NEL * sizeof(int)), contagem = 0, idade_freq = 0, ocorrencias = 0;

    //Inicialização dos arrays. Os elementos do array_freq são inicializados a -1, uma vez que o 0 será uma flag utilizada mais para a frente
    for (int k = 0; k < L->NEL; k++) {
        array[k] = 0;
        array_freq[k] = -1;
    }

    int i = 0;
    NO* P = L->Inicio;

    while (P)
    {
        array[i++] = (*func)(P->INFO);  //Enche o array com as idades dos requisitantes
        P = P->PROX;
    }
    
    //Ciclo for que percorre os elementos todos dos requisitantes
    for (int k = 0; k < L->NEL; k++) {
        contagem = 1;
        //Ciclo for que percorre os elementos todos dos requisitantes, estando uma casa na frente em relação ao ciclo anterior
        for (int j = k + 1; j < L->NEL; j++) {
            //Se forem iguais
            if (array[k] == array[j]) {
                contagem++; //Incrementa a contagem
                array_freq[j] = 0;  //e é acionada a flag como foi encontrado. No caso, é metido a 0
            }
        }

        if (array_freq[k] != 0) {
            array_freq[k] = contagem;   //array_freq[k] fica com valor presente na contagem
            //Compara o valor do array_freq[k] com o número de ocorrencias previamente inicializado a 0
            if (array_freq[k] > ocorrencias) {
                ocorrencias = array_freq[k];    //Se o valor do array_freq[k] for superior, a variavel ocorrencias fica com esse valor
                idade_freq = array[k];  //e idade_freq, previamente inicializada a 0, fica com o valor do array[k]
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
    //Criação de dois arrays. Um vai conter a informação pertinente (neste caso, apelidos) e outro será auxiliar para permitir contar a frequência com que x apelido aparece
    char** array = (char**)malloc(L->NEL * sizeof(char*)), *sobrenome = (char*)malloc(20 * sizeof(char));
    int* array_freq = (int*)malloc(L->NEL * sizeof(int)), i = 0, contagem = 0, ocorrencias = 0;

    //Inicialização do array
    for (int k = 0; k < L->NEL; k++) {
        array_freq[k] = -1;
    }

    while (P)
    {
        array[i++] = (*func)(P->INFO); //Enche o array com os apelidos dos requisitantes
        P = P->PROX;
    }

    //Ciclo for que percorre os elementos todos dos requisitantes
    for (int k = 0; k < L->NEL; k++) {
        contagem = 1;
        //Ciclo for que percorre os elementos todos dos requisitantes, estando uma casa na frente em relação ao ciclo anterior
        for (int j = k + 1; j < L->NEL; j++) {
            //Se forem iguais
            if (strcmp(array[k], array[j]) == 0) {
                contagem++; //Incrementa a contagem
                array_freq[j] = 0;  //e é acionada a flag como foi encontrado. No caso, é metido a 0
            }
        }

        if (array_freq[k] != 0) {
            array_freq[k] = contagem;   //array_freq[k] fica com valor presente na contagem
            //Compara o valor do array_freq[k] com o número de ocorrencias previamente inicializado a 0
            if (array_freq[k] > ocorrencias) {
                ocorrencias = array_freq[k];    //Se o valor do array_freq[k] for superior, a variavel ocorrencias fica com esse valor
                strcpy(sobrenome, array[k]);    // e sobrenome fica com o valor do array[k]
            }
        }
    }

    printf("%s é o sobrenome com mais requisitantes, totalizando %d requisitantes\n", sobrenome, ocorrencias);

    free(array);
    free(array_freq);
    free(sobrenome);
    
}
//-------------------------------
int ProcurarDistrito(LISTA* L, int (*func)(void*, const char*), const char* parametro)
{
    if (!L) return 0;
    NO* P = L->Inicio;
    int id_distrito;
    while (P)
    {
        id_distrito = (*func)(P->INFO, parametro); 

        if(id_distrito != 0)
            return id_distrito;
        P = P->PROX;
    }
    return 0;
}
//-------------------------------
int ProcurarPessoasDistrito(LISTA* L, int (*func)(void*, const char*, int), const char* parametro1, int parametro2)
{
    if (!L) return 0;
    NO* P = L->Inicio;
    int num_pessoas = 0;
    while (P)
    {
        num_pessoas += (*func)(P->INFO, parametro1, parametro2);
        P = P->PROX;
    }
    return num_pessoas;
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
int ProcurarRequisitar(LISTA* L, int (*func)(void*, const char*), const char* parametro)
{
    if (!L) return 0;
    NO* P = L->Inicio;
    int jaRequisitado = 0;
    while (P)
    {
        jaRequisitado = (*func)(P->INFO, parametro);
        if (jaRequisitado != 0) return jaRequisitado;
        P = P->PROX;
    }
    return 0;
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
int GetID(LISTA* L, int (*func)(void*, const char*), const char* parametro)
{
    if (!L) return 0;
    int id = 0;
    NO* P = L->Inicio;
    while (P)
    {
        id = (*func)(P->INFO, parametro);
        if (id != 0) return id;
        P = P->PROX;
    }
    return 0;
}
//-------------------------------
int GetIDRequisitantesComIDLivro(LISTA* L, int (*func)(void*, int), int parametro)
{
    if (!L) return 0;
    int id = 0;
    NO* P = L->Inicio;
    while (P)
    {
        id = (*func)(P->INFO, parametro);
        if (id != 0) return id;
        P = P->PROX;
    }
    return 0;
}
//-------------------------------
void SortLISTA(LISTA* L, char* (*func1)(void*), void (*func2)(void*, const char*))
{
    if (!L) return;

    char** array = (char**)malloc(L->NEL * sizeof(char*)), * tmp;
    int i = 0, j = 0, k = 0, l = 0, size = L->NEL;

    NO* P = L->Inicio;

    while (P)
    {
        array[i++] = (*func1)(P->INFO); //O array recebe a informação pela qual desejo organizar a lista como apelido, nome e id_freguesia
        P = P->PROX;
    }

    //Ordena o array
    for (j = 0; j < size - 1; ++j)
    {
        for (k = j + 1; k < size; ++k)
        {
            if (strcmp(array[j], array[k]) > 0)
            {
                //Procede a fazer a troca dos elementos
                tmp = array[j];
                array[j] = array[k];
                array[k] = tmp;
            }
        }
    }
    //Remove elementos duplicados do array
    for (j = 0; j < size; j++)
    {
        for (k = j + 1; k < size; k++)
        {
            //Verifica se são iguais
            if (strcmp(array[j], array[k]) == 0)
            {
                for (l = k; l < size; l++)
                {
                    //Atribui o valor de l+1 a l
                    array[l] = array[l + 1];
                }
                size--; //Decrementa o tamanho, uma vez que foi removido um duplicado 
                k--;
            }
        }
        //Procura na lista os elementos do array já organizado e sem duplicados
        ProcurarLISTA(L, (*func2), array[j]);
    }

    free(array);
}
//-------------------------------
int MemoriaLista(LISTA* L) 
{
    if (!L) return 0;

    int Mem = 0;
    Mem += sizeof(*L);

    NO* P = L->Inicio;
    while (P)
    {
        Mem += sizeof(*P);
        Mem += sizeof(P->INFO);
        P = P->PROX;
    }
    return Mem;
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
//-------------------------------
