#include <stdio.h>
#include <string.h>
#include <locale.h>
#include "Hashing.h"
#include "Lista.h"
#include "Requisitante.h"
#include "Requisicao.h"

extern Hashing* CriarHASHING();
extern void AddHASHING(Hashing* H, LIVRO* X);
extern void MostrarHASHING(Hashing* H);
extern LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano);
extern void CarregarLivros(Hashing* Biblioteca, const char* nome_fich);
extern void OrganizarLivros();
extern void OrganizarRequisitantes();
extern void PesquisarLivros(Hashing* H, const char* parametro);
extern void PesquisarLivroMaisRequisitado(Hashing* H);
extern void PesquisarAreaMaisRequisitada(Hashing* H);
extern void PesquisarAreaMenosRequisitada(Hashing* H);
extern void AreaComMaisLivros(Hashing* H);
extern int Requisitar(Hashing* H, const char* parametro);
extern int RequisitarIDLivro(Hashing* H, const char* parametro);
extern void Devolver(Hashing* H, const char* parametro);
extern void MostrarLivrosRequisitados(Hashing* H);
extern void MostrarHASHINGLivrosRequisitadosPorRequisitante(Hashing* H, LISTA* L, int parametro);
extern int MemoriaHASHING(Hashing* H);
extern void DestruirHASHING(Hashing* H);

extern LISTA* CriarLISTA();
extern void AddLista(LISTA* L, void* EL);
extern void MostrarLISTA(LISTA* L, void (*func)(void*));
extern void SortLISTA(LISTA* L, char* (*func1)(void*), void (*func2)(void*, const char*));
extern void ProcurarLISTA(LISTA* L, void (*func)(void*, const char*), const char* parametro);
extern void ProcurarLivroMaisRequisitadoRecente(LISTA* L, void (*func)(void*, int), int parametro);
extern int GetIDRequisitantesComIDLivro(LISTA* L, int (*func)(void*, int), int parametro);
extern int GetID(LISTA* L, int (*func)(void*, const char*), const char* parametro);
extern int MemoriaLista(LISTA* L);
extern void DestruirLISTA(LISTA* L, void (*func)(void*));

extern REQUISITANTE* CriarRequisitante(const char* id_requisitante, const char* requisitante, const char* data_nasc, const char* id_freguesia);
extern void CarregarRequisitantes(LISTA* Requisitantes, const char* nome_fich);
extern void MostrarRequisitante(void* P);
extern void MostrarRequisitanteOrdernadoFreg(void* P, const char* parametro);
extern void MostrarRequisitanteOrdernadoApelido(void* P, const char* parametro);
extern void ProcurarRequisitante(void* P, const char* parametro);
extern void MostrarIdadeMaxima(LISTA* L, int (*func)(void*));
extern int GetIdadeRequisitantes(void* P);
extern void MostrarIdadeMedia(LISTA* L, int (*func)(void*));
extern void MostrarIdadeSuperiorX(LISTA* L, int (*func)(void*), int parametro);
extern void MostrarIdadeMaisComum(LISTA* L, int (*func)(void*));
extern void MostrarLivrosMaisRecentes(Hashing* H);
extern void MostrarSobrenomeMaisComum(LISTA* L, char* (*func)(void*));
extern char* GetNomeRequisitantes(void* P);
extern char* GetSobrenomeRequisitantes(void* P);
extern int GetIDRequisitante(void* P, const char* parametro);
extern char* GetIDFreguesia(void* P);
extern void AlterarEstadoRequisitar(void* P, const char* parametro);
extern void AlterarEstadoDevolver(void* P, int parametro);
extern void GetTemRequisicoes(void* P);
extern void GetNuncaRequisitou(void* P);
extern void DestruirREQUISITANTE(void* P);

extern REQUISICAO* CriarRequisicao(int id_requisicao, int id_requisitante, int id_livro);
extern void MostrarRequisicoesID(void* P);
extern void RemoverRequisicao(void* P, int parametro);
extern int GetIDRequisitante(void* P, int parametro);

extern void DestruirREQUISICAO(void* P);

extern void CarregarFreguesias(LISTA* Freguesias, const char* nome_fich);
extern void MostrarFreguesia(void* P);
extern void DestruirFREGUESIA(void* P);

extern void CarregarConcelhos(LISTA* Concelhos, const char* nome_fich);
extern void MostrarConcelho(void* P);
extern void DestruirCONCELHO(void* P);

extern void CarregarDistritos(LISTA* Distritos, const char* nome_fich);
extern void MostrarDistrito(void* P);
extern int ProcurarDistrito(LISTA* L, int (*func)(void*, const char*), const char* parametro);
extern int ProcurarPessoasDistrito(LISTA* L, int (*func)(void*, const char*, int), const char* parametro1, int parametro2);
extern int GetNumPessoasFreguesiaApelido(void* P, const char* parametro1, int parametro2);
extern int GetDistritos(void* P, const char* parametro);
extern void DestruirDISTRITO(void* P);

extern void GravarXML(Hashing* H, LISTA* R, LISTA* D, LISTA* C, LISTA* F, LISTA* Req, const char* nome_xml);
extern void GravarSessao(Hashing* H, LISTA* R, LISTA* D, LISTA* C, LISTA* F, LISTA* Req);
extern void CarregarSessao(Hashing* Biblioteca, LISTA* Freguesias, LISTA* Concelhos, LISTA* Distritos, LISTA* Requisitantes, LISTA* Requisicoes);
//---------------------------------
int GestaoSessao()
{
    int x;
    printf("\n\n# GESTÃO DE SESSÃO------------------------------------------------------------#");
    printf("\n| (1) Continuar Sessão anterior                                               |");
    printf("\n| (2) Nova Sessão                                                             |");
    printf("\n| ----------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                    |");
    printf("\n#-----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 2);
    return x;
}
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
    printf("\n| (6) Gravar Alterações da Sessão                                            |");
    printf("\n| ---------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                   |");
    printf("\n#----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 6);
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
    printf("\n| (3) Listar Requisitantes ordernados por ID Freguesia                        |");
    printf("\n| (4) Listar Requisitantes ordernados por Nome                                |");
    printf("\n| (5) Listar Requisitantes ordernados por Apelido                             |");
    printf("\n| (6) Determinar idade máxima                                                 |");
    printf("\n| (7) Determinar idade média                                                  |");
    printf("\n| (8) Determinar número de pessoas com idade superior a x                     |");
    printf("\n| (9) Determinar idade com mais Requisitantes                                 |");
    printf("\n| (10) Listar Requisições de um dado Requisitante                             |");
    printf("\n| (11) Listar Requisitantes que nunca requisitaram                            |");
    printf("\n| (12) Listar Requisitantes que têm livros requisitados                       |");
    printf("\n| (13) Determinar sobrenome mais utilizado                                    |");
    printf("\n| (14) Determinar número de pessoas de um dado Distrito que têm um dado nome  |");
    printf("\n| ----------------------------------------------------------------------------|");
    printf("\n| (0) SAIR                                                                    |");
    printf("\n#-----------------------------------------------------------------------------#\n");
    fflush(stdin);
    do {
        printf("\n  Qual é a sua opção? ");
        fflush(stdin);
        scanf("%d", &x);
    } while (x < 0 || x > 15);
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
    //while (1) {
    setlocale(LC_ALL, "Portuguese");

    Hashing* Biblioteca = CriarHASHING();
    LISTA* Requisitantes = CriarLISTA();
    LISTA* Requisicoes = CriarLISTA();
    LISTA* Freguesias = CriarLISTA();
    LISTA* Concelhos = CriarLISTA();
    LISTA* Distritos = CriarLISTA();
       
    //Diretório e extensão para guardar em XML
    char dir[] = "Ficheiros/XML/", extensao[] = ".xml";

    bool MenuP = true, MenuL = true, MenuRequisitantes = true, MenuRequisicoes = true, MenuS = true;

    //Gerir sessões
    while (MenuS)
    {
        int opS = GestaoSessao();
        switch (opS)
        {
        case 1:
            //Carregar informação previamente guardada noutra sessão
            CarregarSessao(Biblioteca, Freguesias, Concelhos, Distritos, Requisitantes, Requisicoes);
            MenuS = false;
            break;
        case 2:
            //Carregar Informação como se fosse a primeira vez
            OrganizarLivros();
            OrganizarRequisitantes();
            CarregarLivros(Biblioteca, "Ficheiros/Livros_Organizados.txt");
            CarregarDistritos(Distritos, "Ficheiros/Distritos.txt");
            CarregarConcelhos(Concelhos, "Ficheiros/Concelhos.txt");
            CarregarFreguesias(Freguesias, "Ficheiros/Freguesias.txt");
            CarregarRequisitantes(Requisitantes, "Ficheiros/Requisitantes_Organizados.txt");
            MenuS = false;
            break;
        case 0:
            //Sai do programa
            return 0;
        }
    }

    //Gerir livros, requisitantes, etc
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
                    char area[4], titulo[20], isbn_livro[9], autor[50], data[12];

                    printf("Em que área se insere o livro a adicionar?\n");
                    scanf("%s", area);
                    printf("Qual o ISBN do livro a adicionar?\n");
                    scanf("%s", isbn_livro);
                    printf("Qual o título do livro a adicionar?\n");
                    scanf(" %[^\n]", titulo);
                    printf("Qual o autor do livro a adicionar?\n");
                    scanf(" %[^\n]", autor);
                    printf("Qual a data de lançamento do livro a adicionar? dd/mm(ex. mai)/yy\n");
                    scanf("%s", data);

                    AddHASHING(Biblioteca, CriarLivro(area, isbn_livro, titulo, autor, data));  //Adiciona um novo livro
                    break;
                case 2:
                    MostrarHASHING(Biblioteca); //Lista todos os livros
                    break;
                case 3:
                    AreaComMaisLivros(Biblioteca);  //Mostra a área com mais livros, bem como a sua quantidade
                    break;
                case 4:
                    char isbn[10];

                    printf("Introduza o código do livro: ");
                    scanf("%s", isbn);

                    PesquisarLivros(Biblioteca, isbn);  //Procura um determinado livro através do seu código
                    break;
                case 5:
                    MostrarLivrosMaisRecentes(Biblioteca);  //Mostra os Livros com o ano mais recente
                    break;
                case 6:
                    PesquisarLivroMaisRequisitado(Biblioteca);  //Mostra Livro com mais requisições
                    break;
                case 7:
                    PesquisarAreaMaisRequisitada(Biblioteca);   //Mostra Area mais requisitante
                    break;
                case 8:
                    PesquisarAreaMenosRequisitada(Biblioteca);  //Mostra Area menos requisitante
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
                    char id_utilizador[12], nome[50], data_nasc[12], id_freguesia[7];

                    printf("ID do utilizador a adicionar?\n");
                    scanf("%s", id_utilizador);
                    printf("ID da freguesia do utilizador a adicionar?\n");
                    scanf("%s", id_freguesia);
                    do {
                        printf("Nome completo do utilizador a adicionar?\n");
                        scanf(" %[^\n]", nome);
                    } while (strstr(nome, " ") == NULL);    //Verificar que o nome é composto
                    printf("Data de nascimento do utilizador a adicionar? dd-mm-yyyy\n");
                    scanf("%s", data_nasc);

                    AddLista(Requisitantes, CriarRequisitante(id_utilizador, nome, data_nasc, id_freguesia));   //Adiciona um novo requisitante
                    break;
                case 2:
                    char nome_req[50];

                    printf("Introduza o nome do requisitante: ");
                    scanf(" %[^\n]", nome_req);

                    ProcurarLISTA(Requisitantes, ProcurarRequisitante, nome_req);   //Verifica se um determinado requisitante existe
                    break;
                case 3:
                    SortLISTA(Requisitantes, GetIDFreguesia, MostrarRequisitanteOrdernadoFreg); //Ordena a lista de requisitantes por ordem do id_freguesia
                    break;
                case 4:
                    SortLISTA(Requisitantes, GetNomeRequisitantes, ProcurarRequisitante); //Ordena a lista de requisitantes por ordem do nome
                    break;
                case 5:
                    SortLISTA(Requisitantes, GetSobrenomeRequisitantes, MostrarRequisitanteOrdernadoApelido);   //Ordena a lista de requisitantes por ordem do apelido
                    break;
                case 6:
                    MostrarIdadeMaxima(Requisitantes, GetIdadeRequisitantes);   //Mostra a idade mais alta entre os requisitantes
                    break;
                case 7:
                    MostrarIdadeMedia(Requisitantes, GetIdadeRequisitantes);    //Calcula e mostra a idade média dos requisitantes
                    break;
                case 8:
                    int idade_x;

                    printf("Introduza a idade que deseja: ");
                    scanf(" %d", &idade_x);

                    MostrarIdadeSuperiorX(Requisitantes, GetIdadeRequisitantes, idade_x);   //Mostra quantos requisitantes têm idade superior a idade_x
                    break;
                case 9:
                    MostrarIdadeMaisComum(Requisitantes, GetIdadeRequisitantes);    //Mostra a idade com mais ocorrencias entre os requisitantes
                    break;
                case 10:
                    char nome_req_com_requisicoes[50];
                    int id_requisitante_com_requisicoes;

                    printf("Introduza o nome completo do requisitante: ");
                    scanf(" %[^\n]", nome_req_com_requisicoes);

                    id_requisitante_com_requisicoes = GetID(Requisitantes, GetIDRequisitante, nome_req_com_requisicoes);    //Recebe o ID do requisitante que corresponde ao seu nome completo

                    MostrarHASHINGLivrosRequisitadosPorRequisitante(Biblioteca, Requisicoes, id_requisitante_com_requisicoes);   //Mostra todas as requisições de um dado requisitante
                    break;
                case 11:
                    MostrarLISTA(Requisitantes, GetNuncaRequisitou);    //Mostra todos os requisitantes que nunca requisitaram
                    break;
                case 12:
                    MostrarLISTA(Requisitantes, GetTemRequisicoes);     //Mostra os requisitantes que têm requisições ativas
                    break;
                case 13:
                    MostrarSobrenomeMaisComum(Requisitantes, GetSobrenomeRequisitantes);    //Mostra o sobrenome com mais ocorrencias entre os requisitantes
                    break;
                case 14:
                    char nome_distrito[50], apelido[50];
                    int id_distrito, num_pessoas;

                    printf("Introduza o apelido (primeira letra maiuscula): ");
                    scanf("%s", apelido);
                    printf("Introduza o distrito (tudo maiusculo): ");
                    scanf("%s", nome_distrito);

                    id_distrito = ProcurarDistrito(Distritos, GetDistritos, nome_distrito); //id_distrito recebe o id do nome do distrito introduzido pelo utilizador 
                    num_pessoas = ProcurarPessoasDistrito(Requisitantes, GetNumPessoasFreguesiaApelido, apelido, id_distrito);  //id_distrito é passado para a função ProcurarPessoasDistrito que por sua vez irá devolver a contagem de pessoas com o apelido introduzido pelo utilizador, no distrito também introduzido pelo utilizador

                    printf("No distrito %s, o apelido %s ocorre %d vezes.\n", nome_distrito, apelido, num_pessoas);
                    break;
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
                    char livro_a_requisitar[50], nome_requisitante[50];
                    int id_livro, id_requisitante, jaRequisitado;

                    printf("Introduza o nome completo do requisitante a efetuar a requisição: ");
                    scanf(" %[^\n]", nome_requisitante);
                    printf("Introduza o nome completo do livro que deseja requisitar: ");
                    scanf(" %[^\n]", livro_a_requisitar);

                    id_requisitante = GetID(Requisitantes, GetIDRequisitante, nome_requisitante);   //Retorna o ID associado ao nome_requisitante
                    id_livro = RequisitarIDLivro(Biblioteca, livro_a_requisitar);   //Retorna o ID associado ao livro_a_requisitar

                    //Validações simples
                    if (id_requisitante == 0 && id_livro == 0) { printf("Nem o livro %s, nem o requisitante %s existem!\n", livro_a_requisitar, nome_requisitante); break; }
                    if (id_requisitante == 0) { printf("Requisitante %s não existe!\n", nome_requisitante); break; }
                    if (id_livro == 0) { printf("Livro %s não existe!\n", livro_a_requisitar); break; }

                    jaRequisitado = Requisitar(Biblioteca, livro_a_requisitar); //Alterar estado do livro e quantidade de requisições feitas
                    if (jaRequisitado == 1) break;  //Se o livro já tiver com estado REQUISITADO, sai

                    ProcurarLISTA(Requisitantes, AlterarEstadoRequisitar, nome_requisitante); //Alterar estado de requisitante para JÁ REQUISITOU e incrementa número de livros que tem requisitados

                    AddLista(Requisicoes, CriarRequisicao(1, id_requisitante, id_livro));   //Adiciono na lista requisições
                    break;
                case 2:
                    char livro_a_devolver[50];
                    int id_livro_a_devolver, id_requisitante_devolver;

                    printf("Introduza o nome do livro que deseja devolver: ");
                    scanf(" %[^\n]", livro_a_devolver);

                    id_livro_a_devolver = RequisitarIDLivro(Biblioteca, livro_a_requisitar); //Retorna o ID associado ao livro_a_devolver
                    id_requisitante_devolver = GetIDRequisitantesComIDLivro(Requisicoes, GetIDRequisitante, id_livro_a_devolver); //Retorna o ID requisitante associado à requisição referente ao id_livro a devolver

                    //Validação simples
                    if (id_livro_a_devolver == 0) { printf("Livro %s não existe!\n", livro_a_devolver); break; }

                    Devolver(Biblioteca, livro_a_devolver); //Alterar estado do livro

                    ProcurarLivroMaisRequisitadoRecente(Requisitantes, AlterarEstadoDevolver, id_requisitante_devolver);  //Decrementa número de livros que um requisitante tem requisitados
                    ProcurarLivroMaisRequisitadoRecente(Requisicoes, RemoverRequisicao, id_livro_a_devolver);   //Remover o livro previamente requisitado da lista requisições
                    break;
                case 3:
                    MostrarLivrosRequisitados(Biblioteca);  //Mostra todos os livros com estado REQUISITADO
                    break;
                case 0:
                    MenuRequisicoes = false;
                    break;
                }
            }
            break;
        case 4:
            printf("Memória utilizada pela estrutura de dados corresponde a %d bytes\n", MemoriaHASHING(Biblioteca) + MemoriaLista(Requisitantes) + MemoriaLista(Requisicoes) + MemoriaLista(Freguesias) + MemoriaLista(Concelhos) + MemoriaLista(Distritos));
            break;
        case 5:
            char nome_xml[20], diretorio[15];
            
            strcpy(diretorio, dir);

            printf("Indique o nome para o ficheiro xml: \n");
            scanf("%s", nome_xml);

            strcat(diretorio, nome_xml);  //Concatena o diretório com o nome do ficheiro
            strcat(diretorio, extensao);  //Concatena o diretório + nome ficheiro com extensão do ficheiro, no caso XML 

            GravarXML(Biblioteca, Requisitantes, Distritos, Concelhos, Freguesias, Requisicoes, diretorio);
            printf("Ficheiro gravado! Pode encontrar o seu ficheiro em %s\n", diretorio);
            break;
        case 6:
            printf("A gravar alterações...\t");
            GravarSessao(Biblioteca, Requisitantes, Distritos, Concelhos, Freguesias, Requisicoes);
            printf("Alterações gravadas.\n");
            break;
        case 0: MenuP = false;
        }
    }
    //Gravar informação ao sair
    printf("A gravar sessão...\t");
    GravarSessao(Biblioteca, Requisitantes, Distritos, Concelhos, Freguesias, Requisicoes);
    printf("Sessão gravada.\n");

    //Libertar estruturas
    printf("A limpar memória...\t");
    DestruirLISTA(Distritos, DestruirDISTRITO);
    DestruirLISTA(Concelhos, DestruirCONCELHO);
    DestruirLISTA(Freguesias, DestruirFREGUESIA);
    DestruirLISTA(Requisicoes, DestruirREQUISICAO);
    DestruirLISTA(Requisitantes, DestruirREQUISITANTE);
    DestruirHASHING(Biblioteca);
    printf("Memória limpa.\n");
    //}
    return 0;
}