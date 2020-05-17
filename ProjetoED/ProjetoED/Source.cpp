#include <stdio.h>
#include <locale.h>
#include "Hashing.h"
#include "Lista.h"
#include "Requisitante.h"

extern Hashing* CriarHASHING();
extern void AddHASHING(Hashing* H, LIVRO* X);
extern void MostrarHASHING(Hashing* H);
extern void DestruirHASHING(Hashing* H);

extern LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano);
extern void CarregarLivros(Hashing* Biblioteca);
extern void OrganizarLivros();
extern void PesquisarLivros(Hashing* H, const char* parametro);
extern void PesquisarLivroMaisRequisitado(Hashing* H);
extern void PesquisarAreaMaisRequisitada(Hashing* H);
extern void PesquisarAreaMenosRequisitada(Hashing* H);
extern void AreaComMaisLivros(Hashing* H);
extern void Requisitar(Hashing* H, const char* parametro);
extern void Devolver(Hashing* H, const char* parametro);
extern void MostrarLivrosRequisitados(Hashing* H);

extern LISTA* CriarLISTA();
extern void MostrarLISTA(LISTA* L, void (*func)(void*));
extern void ProcurarLISTA(LISTA* L, void (*func)(void*, const char*), const char* parametro);

extern REQUISITANTE* CriarRequisitante(const char* id_requisitante, const char* requisitante, const char* data_nasc);
extern void CarregarRequisitantes(LISTA* Requisitantes);
extern void MostrarRequisitante(void* P);
extern void ProcurarRequisitante(void* P, const char* parametro);

extern void MostrarLivrosMaisRecentes(Hashing* H);

//---------------------------------
int menuGestao()
{
    int x;
    printf("\n\n# MENU PRINCIPAL ------------------------------------------------------------#");
    printf("\n| (1) Gestão de Livros                                                       |");
    printf("\n| (2) Gestão de Requisitantes                                                |");
    printf("\n| (3) Gestão de Requisições                                                  |");
    printf("\n| (4) Determinar Memória Total                                               |");
    printf("\n| (5) Gravar Tudo em XML                                                     |");
    printf("\n| ---------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                   |");
    printf("\n#----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 5);
    return x;
}
//---------------------------------
int GestaoLivros()
{
    int x;
    printf("\n\n# GESTÃO DE LIVROS------------------------------------------------------------#");
    printf("\n| (1) Adicionar Livro                                                         |");
    printf("\n| (2) Listar Todos os Livros                                                  |");
    printf("\n| (3) Determinar Área com mais Livros                                         |");
    printf("\n| (4) Verificar se Livro existe                                               |");
    printf("\n| (5) Determinar Livros mais recentes                                         |");
    printf("\n| (6) Determinar Livro mais requisitado                                       |");
    printf("\n| (7) Determinar Área mais requisitada                                        |");
    printf("\n| (8) Determinar Área menos requisitada                                       |");
    printf("\n| ----------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                    |");
    printf("\n#-----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 8);
    return x;
}
//---------------------------------
int GestaoRequisitantes()
{
    int x;
    printf("\n\n# GESTÃO DE REQUISITANTES-----------------------------------------------------#");
    printf("\n| (1) Adicionar Requisitante                                                  |");
    printf("\n| (2) Verificar se Requisitante existe                                        |");
    printf("\n| (3) Listar Requisitantes                                                    |");
    printf("\n| (4) Determinar idade máxima                                                 |");
    printf("\n| (5) Determinar idade média                                                  |");
    printf("\n| (6) Determinar número de pessoas com idade superior a x                     |");
    printf("\n| (7) Determinar idade com mais Requisitantes                                 |");
    printf("\n| (8) Listar Requisições de um dado Requisitante                              |");
    printf("\n| (9) Listar Requisitantes que nunca requisitaram                             |");
    printf("\n| (10) Listar Requisitantes que têm livros requisitados                       |");
    printf("\n| (11) Determinar sobrenome mais utilizado                                    |");
    printf("\n| (12) Determinar número de pessoas de um dado Distrito que têm um dado nome  |");
    printf("\n| ----------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                    |");
    printf("\n#-----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 12);
    return x;
}
//---------------------------------
int GestaoRequisicoes()
{
    int x;
    printf("\n\n# GESTÃO DE REQUISIÇÕES-------------------------------------------------------#");
    printf("\n| (1) Requisitar Livro                                                        |");
    printf("\n| (2) Devolver Livro                                                          |");
    printf("\n| (3) Listar Todos os Livros atualmente requisitados                          |");
    printf("\n| ----------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                    |");
    printf("\n#-----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 3);
    return x;
}
//---------------------------------
int main()
{
	setlocale(LC_ALL, "Portuguese");
    char o[50] = "adads"; //só para testar o adicionar livro e requisitante
	Hashing* Biblioteca = CriarHASHING();
    LISTA* Requisitantes = CriarLISTA();
	OrganizarLivros();
	CarregarLivros(Biblioteca);
    CarregarRequisitantes(Requisitantes);
    bool MenuP = true, MenuL = true, MenuRequisitantes = true, MenuRequisicoes = true;
    while (MenuP)
    {
        int opP = menuGestao();
        switch (opP)
        {
        case 1:
            MenuL = true;
            while (MenuL)
            {
                int opL = GestaoLivros();
                switch (opL)
                {
                case 1: 
                    char area[50];
                    printf("Em que área se insere o livro a adicionar? ");  //falta os outros dados, mas a ideia é esta
                    scanf("%s", area);
                    AddHASHING(Biblioteca, CriarLivro(area, o, o, o, o));
                    break;
                case 2: 
                    MostrarHASHING(Biblioteca); 
                    break;
                case 3: 
                    AreaComMaisLivros(Biblioteca);
                    break;
                case 4: 
                    char isbn[50];
                    printf("Introduza o código do livro: ");
                    scanf("%s", isbn);
                    PesquisarLivros(Biblioteca, isbn);
                    break;
                case 5: 
                    //Falta pesquisar livros mais recentes
                    MostrarLivrosMaisRecentes(Biblioteca);
                    break;
                case 6: 
                    PesquisarLivroMaisRequisitado(Biblioteca);
                    break;
                case 7: 
                    PesquisarAreaMaisRequisitada(Biblioteca);
                    break;
                case 8:
                    PesquisarAreaMenosRequisitada(Biblioteca);
                    break;
                case 0: 
                    MenuL = false;
                    break;
                }
            }
            break;
        case 2:
            MenuRequisitantes = true;
            while (MenuRequisitantes)
            {
                int opRequisitantes = GestaoRequisitantes();
                switch (opRequisitantes)
                {
                case 1:
                    char nome[50];
                    printf("Nome do utilizador a adicionar? ");  //falta os outros dados, mas a ideia é esta
                    scanf(" %[^\n]", nome);
                    CriarRequisitante(o, nome, o);
                    break;
                case 2: 
                    char nome_req[100];
                    printf("Introduza o nome do requisitante: ");
                    scanf(" %[^\n]", nome_req);
                    ProcurarLISTA(Requisitantes, ProcurarRequisitante, nome_req);
                    break;
                case 3: 
                    MostrarLISTA(Requisitantes, MostrarRequisitante);
                    break;
                case 4: break;
                case 5: break;
                case 6: break;
                case 7: break;
                case 8: break;
                case 9: break;
                case 10: break;
                case 11: break;
                case 12: break;
                case 0:
                    MenuRequisitantes = false;
                    break;
                }
            }
            break;
        case 3:
            MenuRequisicoes = true;
            while (MenuRequisicoes)
            {
                int opRequisicoes = GestaoRequisicoes();
                switch (opRequisicoes)
                {
                case 1: 
                    char livro_a_requisitar[100];
                    printf("Introduza o nome do livro que deseja requisitar: ");
                    scanf(" %[^\n]", livro_a_requisitar);
                    Requisitar(Biblioteca, livro_a_requisitar);
                    break;
                case 2: 
                    char livro_a_devolver[100];
                    printf("Introduza o nome do livro que deseja devolver: ");
                    scanf(" %[^\n]", livro_a_devolver);
                    Devolver(Biblioteca, livro_a_devolver);
                    break;
                case 3: 
                    MostrarLivrosRequisitados(Biblioteca);
                    break;
                case 0:
                    MenuRequisicoes = false;
                    break;
                }
            }
            break;
        case 4: break;
        case 5: break;
        case 0: MenuP = false;
        }
    }
	DestruirHASHING(Biblioteca);

	return 0;
}