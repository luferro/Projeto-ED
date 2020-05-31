#include "Requisitante.h"

REQUISITANTE* CriarRequisitante(const char* id_requisitante, const char* requisitante, const char* data_nasc, const char* id_freguesia)
{
    REQUISITANTE* X = (REQUISITANTE*)malloc(sizeof(REQUISITANTE));
    if (!X) return NULL;

    X->ID_REQUISITANTE = (char*)malloc((strlen(id_requisitante) + 1) * sizeof(char));
    X->REQUISITANTE = (char*)malloc((strlen(requisitante) + 1) * sizeof(char));
    X->DATA_NASC = (char*)malloc((strlen(data_nasc) + 1) * sizeof(char));

    strcpy(X->ID_REQUISITANTE, id_requisitante);
    strcpy(X->REQUISITANTE, requisitante);
    strcpy(X->DATA_NASC, data_nasc);
    strcpy(X->ID_FREGUESIA, id_freguesia);
    X->JA_REQUISITOU = 0;
    X->TEM_REQUISICAO = 0;

    return X;
}
//-------------------------------
REQUISITANTE* CriarRequisitante_Sessao(const char* id_requisitante, const char* requisitante, const char* data_nasc, int ja_requisitou, int tem_requisicao, const char* id_freguesia)
{
    REQUISITANTE* X = (REQUISITANTE*)malloc(sizeof(REQUISITANTE));
    if (!X) return NULL;

    X->ID_REQUISITANTE = (char*)malloc((strlen(id_requisitante) + 1) * sizeof(char));
    X->REQUISITANTE = (char*)malloc((strlen(requisitante) + 1) * sizeof(char));
    X->DATA_NASC = (char*)malloc((strlen(data_nasc) + 1) * sizeof(char));

    strcpy(X->ID_REQUISITANTE, id_requisitante);
    strcpy(X->REQUISITANTE, requisitante);
    strcpy(X->DATA_NASC, data_nasc);
    strcpy(X->ID_FREGUESIA, id_freguesia);
    X->JA_REQUISITOU = ja_requisitou;
    X->TEM_REQUISICAO = tem_requisicao;

    return X;
}
//-------------------------------
void MostrarRequisitante(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    printf("REQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
}
//-------------------------------
void MostrarRequisitanteOrdernadoFreg(void* P, const char* parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    if (strstr(X->ID_FREGUESIA, parametro) != NULL) 
    {
        printf("REQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
    }
}
//-------------------------------
void MostrarRequisitanteOrdernadoApelido(void* P, const char* parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    char* str = X->REQUISITANTE;
    char* sobrenome = NULL;

    //Conseguir a última token do nome do requisitante, neste caso o apelido
    char* last = strrchr(str, ' ');
    if (last != NULL) {
        sobrenome = last + 1;
    }
     
    if (strstr(sobrenome, parametro) != NULL)
    {
        printf("REQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
    }
}
//-------------------------------
void GravarRequisitante(void* P, FILE* F)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    fprintf(F, "\t\t\tREQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
}
//-------------------------------
void GravarRequisitante_Sessao(void* P, FILE* F)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    fprintf(F, "%s\t%s\t%s\t%d\t%d\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->JA_REQUISITOU, X->TEM_REQUISICAO, X->ID_FREGUESIA);
}
//-------------------------------
void ProcurarRequisitante(void* P, const char* parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    //Compara o nome do requisitante com o parametro de entrada, verificando se o nome do requisitante contém o nome presente no parametro de entrada
    if (strstr(X->REQUISITANTE, parametro) != NULL)
    {
        printf("REQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
    }
}
//-------------------------------
void AlterarEstadoRequisitar(void* P, const char* parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    //Compara o nome do requisitante com o parametro de entrada, verificando se o nome do requisitante contém o nome presente no parametro de entrada
    if (strcmp(X->REQUISITANTE, parametro) == 0)
    {
        X->JA_REQUISITOU = 1;
        X->TEM_REQUISICAO++;
    }
}
//-------------------------------
void AlterarEstadoDevolver(void* P, int parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    int id_requisitante = atoi(X->ID_REQUISITANTE);

    //Compara o nome do requisitante com o parametro de entrada, verificando se o nome do requisitante contém o nome presente no parametro de entrada
    if (id_requisitante == parametro)
    {
        X->TEM_REQUISICAO--;
    }
}
//-------------------------------
void GetTemRequisicoes(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    //Compara o nome do requisitante com o parametro de entrada, verificando se o nome do requisitante contém o nome presente no parametro de entrada
    if (X->TEM_REQUISICAO > 0)
    {
        printf("REQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
    }
}
//-------------------------------
int GetIdadeRequisitantes(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    
    char* str = X->DATA_NASC;
    int ano = 0, idade = 0;

    //Conseguir a última token da data de nascimento, neste caso o ano
    char* last = strrchr(str, '-');
    if (last != NULL) {
        ano = atoi(last + 1);
    }  

    //Calcular a idade do requisitante conforme o seu ano de nascimento previamente conseguido
    idade = 2020 - ano;

    return idade;
}
//-------------------------------
char* GetNomeRequisitantes(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    char* nome = X->REQUISITANTE;

    return nome;
}
//-------------------------------
char* GetSobrenomeRequisitantes(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    char* str = X->REQUISITANTE;
    char* sobrenome = NULL;

    //Conseguir a última token do nome do requisitante, neste caso o apelido
    char* last = strrchr(str, ' ');
    if (last != NULL) {
        sobrenome = last + 1;
    }

    return sobrenome;
}
int GetNumPessoasFreguesiaApelido(void* P, const char* parametro1, int parametro2)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    char* str = X->REQUISITANTE;
    char* sobrenome = NULL;

    //Conseguir a última token do nome do requisitante, neste caso o apelido
    char* last = strrchr(str, ' ');
    if (last != NULL) {
        sobrenome = last + 1;
    }

    //Verifica o distrito a que o requisitante pertence, através do id_freguesia conseguindo os dois primeiros digitos
    int id_distrito = atoi(X->ID_FREGUESIA);
    id_distrito = id_distrito / 10000;

    //Compara o apelido previamente conseguido com o parametro de entrada 1
    if (strcmp(sobrenome, parametro1) == 0) {
        if (id_distrito == parametro2) //Compara o id_distrito previamente conseguido com o parametro de entrada 2
        {
            return 1;   //Se o requisitante com o apelido parametro1 existir no distrito parametro2, retorna 1 que será usado para calcular o número de pessoas
        }
        else return 0;
    }
    else return 0;
}
//-------------------------------
int GetIDRequisitante(void* P, const char* parametro)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    int id_requisitante = atoi(X->ID_REQUISITANTE);

    //Compara o nome completo do requisitante com o parametro de entrada
    if (strcmp(X->REQUISITANTE, parametro) == 0) {
        return id_requisitante; //Se encontrar, devolve o seu ID
    }
    return 0;
}
//-------------------------------
char* GetIDFreguesia(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    char* id_freguesia = X->ID_FREGUESIA;

    return id_freguesia;
}
//-------------------------------
void GetNuncaRequisitou(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;

    //Verifica o estado de requisição do requisitante
    if (X->JA_REQUISITOU == 0) {
        printf("REQUISITANTE: %s\t%s\t%s\t%d livros\t%s", X->ID_REQUISITANTE, X->REQUISITANTE, X->DATA_NASC, X->TEM_REQUISICAO, X->ID_FREGUESIA);
    }
}
//-------------------------------
void DestruirREQUISITANTE(void* P)
{
    REQUISITANTE* X = (REQUISITANTE*)P;
    free(X->ID_REQUISITANTE);
    free(X->REQUISITANTE);
    free(X->DATA_NASC);
    free(X);
}