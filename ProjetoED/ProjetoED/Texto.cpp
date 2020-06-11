#include "Texto.h"
#define _CRT_SECURE_NO_WARNINGS

extern void AddHASHING(Hashing* H, LIVRO* X);
extern void AddLista(LISTA* L, void* EL);
extern LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano);
extern LIVRO* CriarLivro_Sessao(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano, int num_req, const char* estado_req);
extern REQUISITANTE* CriarRequisitante(const char* id_requisitante, const char* requisitante, const char* data_nasc, const char* id_freguesia);
extern REQUISITANTE* CriarRequisitante_Sessao(const char* id_requisitante, const char* requisitante, const char* data_nasc, int ja_requisitou, int tem_requisicao, const char* id_freguesia);
extern REQUISICAO* CriarRequisicao(int id_requisitante, int id_livro);
extern FREGUESIA* CriarFreguesia(const char* id_freguesia, const char* freguesia); 
extern CONCELHO* CriarConcelho(const char* id_concelho, const char* concelho);
extern DISTRITO* CriarDistrito(const char* id_distrito, const char* distrito);
extern void GuardarLISTA(LISTA* L, void (*func)(void*, FILE*), FILE* F);
extern void GravarLivro(void* P, FILE* F);
extern void GravarRequisitante(void* P, FILE* F);
extern void GravarDistrito(void* P, FILE* F);
extern void GravarConcelho(void* P, FILE* F);
extern void GravarFreguesia(void* P, FILE* F);
extern void GravarRequisicoes(void* P, FILE* F);
extern void GravarLivro_Sessao(void* P, FILE* F);
extern void GravarRequisitante_Sessao(void* P, FILE* F);
extern void GravarDistrito_Sessao(void* P, FILE* F);
extern void GravarConcelho_Sessao(void* P, FILE* F);
extern void GravarFreguesia_Sessao(void* P, FILE* F);
extern void GravarRequisicoes_Sessao(void* P, FILE* F);
//-------------------------------
char** SepararCampos(char* linha, int n_campos, const char* separadores) 
{
	char** v = (char**)malloc(sizeof(char*) * n_campos);
	if (!v)
		return NULL;
	char* campo;
	int i = 0;
	campo = strtok(linha, separadores);
	while (campo != NULL) {
		if (campo) {
			v[i] = (char*)malloc((strlen(campo) + 1) * sizeof(char));
			if (v[i])
				strcpy(v[i], campo);
		}
		campo = strtok(NULL, separadores);
		i++;
	}
	if (i != n_campos) {
		for (int j = 0; j < i; j++) {
			if (v[j])
				free(v[j]);
		}
		return NULL;
	}
	return v;
}
//-------------------------------
//A ideia seria abrir o ficheiro original, filtrar e guardar o conteudo num ficheiro auxiliar
void OrganizarLivros()
{
	FILE* fich_livros = fopen("Ficheiros/Livro de registo Biblioteca.csv", "r");
	FILE* fich_livros_organizado = fopen("Ficheiros/Livros_Organizados.txt", "w");
	FILE* logs = fopen("Ficheiros/logs_livros.txt", "a+");
	if (!fich_livros) return;
	char linha[400];
	char linha_separar[400];
	char copia[400];
	while (fgets(linha, sizeof(linha), fich_livros) != NULL) {

		strcpy(linha_separar, linha);

		char** v = SepararCampos(linha_separar, 20, ";");

		if (v) {
			//Validar se os campos utilizados existem
			if (strstr(v[1], "---") || strstr(v[10], "---") || strstr(v[11], "---") || strstr(v[2], "---") || strstr(v[0], "---") || strstr(linha, "Dep.")) {
				//Se a área não existir
				if (strstr(v[1], "---")) {
					fputs("\nArea inválida\n", logs);
					fputs(linha, logs);
				}
				//Se o ISBN não existir
				if (strstr(v[10], "---")) {
					fputs("\Código do livro inválido\n", logs);
					fputs(linha, logs);
				}
				//Se o título não existir
				if (strstr(v[11], "---")) {
					fputs("\Título do livro inválido\n", logs);
					fputs(linha, logs);
				}
				//Se o autor não existir
				if (strstr(v[2], "---")) {
					fputs("\Autor do livro inválido\n", logs);
					fputs(linha, logs);
				}
				//Se a data do livro não existir
				if (strstr(v[0], "---")) {
					fputs("\nData do livro inválida\n", logs);
					fputs(linha, logs);
				}
				//Se a linha for a descrição dos campos
				if (strstr(linha, "Dep.")) {
					fputs("\nLinha a ser ignorada\n", logs);
					fputs(linha, logs);
				}
			}
			else {
				strcpy(copia, linha);
				fputs(copia, fich_livros_organizado);
			}
			for (int i = 0; i < 20; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_livros);
	fclose(fich_livros_organizado);
	fclose(logs);
}
//-------------------------------
void CarregarLivros(Hashing* Biblioteca, const char* nome_fich)
{
	FILE* fich_livros = fopen(nome_fich, "r");
	if (!fich_livros)
		return;
	char linha[400];
	while (!feof(fich_livros)) {
		fgets(linha, 400, fich_livros);

		char** v = SepararCampos(linha, 20, ";");

		if (v) {
			AddHASHING(Biblioteca, CriarLivro(v[1], v[10], v[11], v[2], v[0]));
			for (int i = 0; i < 20; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_livros);
}
//-------------------------------
void CarregarFreguesias(LISTA* Freguesias, const char* nome_fich)
{
	FILE* fich_freguesias = fopen(nome_fich, "r");
	if (!fich_freguesias)
		return;
	char linha[400];
	while (!feof(fich_freguesias)) {
		fgets(linha, 400, fich_freguesias);

		char** v = SepararCampos(linha, 2, "\t");

		if (v) {
			AddLista(Freguesias, CriarFreguesia(v[0], v[1]));
			for (int i = 0; i < 2; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_freguesias);
}
//-------------------------------
void CarregarConcelhos(LISTA* Concelhos, const char* nome_fich)
{
	FILE* fich_concelhos = fopen(nome_fich, "r");
	if (!fich_concelhos)
		return;
	char linha[400];
	while (!feof(fich_concelhos)) {
		fgets(linha, 400, fich_concelhos);

		char** v = SepararCampos(linha, 2, "\t");

		if (v) {
			AddLista(Concelhos, CriarConcelho(v[0], v[1]));
			for (int i = 0; i < 2; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_concelhos);
}
//-------------------------------
void CarregarDistritos(LISTA* Distritos, const char* nome_fich)
{
	FILE* fich_distritos = fopen(nome_fich, "r");
	if (!fich_distritos)
		return;
	char linha[400];
	while (!feof(fich_distritos)) {
		fgets(linha, 400, fich_distritos);

		char** v = SepararCampos(linha, 2, "\t");

		if (v) {
			AddLista(Distritos, CriarDistrito(v[0], v[1]));
			for (int i = 0; i < 2; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_distritos);
}
//-------------------------------
void OrganizarRequisitantes() {
	FILE* fich_requisitantes = fopen("Ficheiros/Requisitantes.txt", "r");
	FILE* fich_requisitantes_organizado = fopen("Ficheiros/Requisitantes_Organizados.txt", "w");
	FILE* logs = fopen("Ficheiros/logs.txt", "a+");
	if (!fich_requisitantes) return;
	char linha[400];
	char linha_separar[400];
	char copia[400];
	while (fgets(linha, sizeof(linha), fich_requisitantes) != NULL) {

		strcpy(linha_separar, linha);

		char** v = SepararCampos(linha_separar, 4, "\t");

		int sum_id = atoi(v[0]), resto = 0, sum = 0, dia;

		char* primeiro_arg = strtok(v[2], "-");
		dia = atoi(primeiro_arg);

		//Soma os algarismos do id requisitante
		while (sum_id > 0)
		{
			resto = sum_id % 10;
			sum = sum + resto;
			sum_id = sum_id / 10;
		}
		//Validar id requisitante e data de nascimento
		if (strlen(v[0]) != 9 || sum % 10 || strstr(v[2], "/") || dia > 31 || strlen(v[3]) != 7) {
			//Se id requisitante não tiver 9 algarismos
			if (strlen(v[0]) != 9) {
				fputs("\nID de requisitante inválido\n", logs);
				fputs(linha, logs);
			}
			//Se a soma dos algarismos do id requisitante não for múltiplo de 10
			if (sum % 10) {
				fputs("\nSomátorio dos 9 algarismos não é múltiplo de 10\n", logs);
				fputs(linha, logs);
			}
			//Se data não tiver no formato necessário, dd-mm-yyyy
			if (strstr(v[2], "/") || dia > 31) {
				fputs("\nFormato de data inválido\n", logs);
				fputs(linha, logs);
			}
			//Se id freguesia não tiver 6 caracteres
			if (strlen(v[3]) != 7) {
				fputs("\nID de freguesia inválido\n", logs);
				fputs(linha, logs);
			}
		}
		else {
			strcpy(copia, linha);
			fputs(copia, fich_requisitantes_organizado);
		}

		for (int i = 0; i < 4; i++)
			free(v[i]);
		free(v);
	}
	fclose(fich_requisitantes);
	fclose(fich_requisitantes_organizado);
	fclose(logs);
}
//-------------------------------
void CarregarRequisitantes(LISTA* Requisitantes, const char* nome_fich)
{
	FILE* fich_requisitantes = fopen(nome_fich, "r");
	if (!fich_requisitantes)
		return;
	char linha[400];
	while (!feof(fich_requisitantes)) {
		fgets(linha, 400, fich_requisitantes);

		char** v = SepararCampos(linha, 4, "\t");

		if (v) {
			AddLista(Requisitantes, CriarRequisitante(v[0], v[1], v[2], v[3]));
			for (int i = 0; i < 4; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_requisitantes);
}
//-------------------------------
void GravarXML(Hashing* H, LISTA* R, LISTA* D, LISTA* C, LISTA* F, LISTA* Req, const char* nome_xml)
{
	FILE* fich_xml = fopen(nome_xml, "w");
	if (!fich_xml) return;

	fprintf(fich_xml, "<Biblioteca>\n");
	fprintf(fich_xml, "\t<Areas>\n");

	if (!H) return;
	NO_HAS* P = H->Inicio;
	while (P)
	{
		fprintf(fich_xml, "\t\t<%s>\n", P->CHAVE);
		GuardarLISTA(P->LLivros, GravarLivro, fich_xml);
		fprintf(fich_xml, "\t\t<%s/>\n", P->CHAVE);
		P = P->Prox_Chave;
	}

	fprintf(fich_xml, "\t<Areas/>\n");
	fprintf(fich_xml, "\t<Requisicoes>\n");
	GuardarLISTA(Req, GravarRequisicoes, fich_xml);
	fprintf(fich_xml, "\t<Requisicoes/>\n");
	fprintf(fich_xml, "\t<Requisitantes>\n");
	GuardarLISTA(R, GravarRequisitante, fich_xml);
	fprintf(fich_xml, "\t<Requisitantes/>\n");
	fprintf(fich_xml, "\t<Distritos>\n");
	GuardarLISTA(D, GravarDistrito, fich_xml);
	fprintf(fich_xml, "\t<Distritos/>\n");
	fprintf(fich_xml, "\t<Concelhos>\n");
	GuardarLISTA(C, GravarConcelho, fich_xml);
	fprintf(fich_xml, "\t<Concelhos/>\n");
	fprintf(fich_xml, "\t<Freguesias>\n");
	GuardarLISTA(F, GravarFreguesia, fich_xml);
	fprintf(fich_xml, "\t<Freguesias/>\n");
	fprintf(fich_xml, "<Biblioteca/>\n");

	fclose(fich_xml);
}
//-------------------------------
void GravarSessao(Hashing* H, LISTA* R, LISTA* D, LISTA* C, LISTA* F, LISTA* Req)
{
	FILE* fichH = fopen("Ficheiros/Sessao/livros_manter.txt", "w");
	FILE* fichR = fopen("Ficheiros/Sessao/requisitantes_manter.txt", "w");
	FILE* fichD = fopen("Ficheiros/Sessao/distritos_manter.txt", "w");
	FILE* fichC = fopen("Ficheiros/Sessao/concelhos_manter.txt", "w");
	FILE* fichF = fopen("Ficheiros/Sessao/freguesias_manter.txt", "w");
	FILE* fichReq = fopen("Ficheiros/Sessao/requisicoes_manter.txt", "w");

	if (!fichReq && !fichH && !fichR && !fichD && !fichC && !fichF) return;

	if (!H) return;
	NO_HAS* P = H->Inicio;
	while (P)
	{
		GuardarLISTA(P->LLivros, GravarLivro_Sessao, fichH);
		P = P->Prox_Chave;
	}
	
	GuardarLISTA(R, GravarRequisitante_Sessao, fichR);
	GuardarLISTA(Req, GravarRequisicoes_Sessao, fichReq);
	GuardarLISTA(D, GravarDistrito_Sessao, fichD);
	GuardarLISTA(C, GravarConcelho_Sessao, fichC);
	GuardarLISTA(F, GravarFreguesia_Sessao, fichF);

	fclose(fichH);
	fclose(fichR);
	fclose(fichD);
	fclose(fichC);
	fclose(fichF);
	fclose(fichReq);
}
//-------------------------------
void CarregarSessao(Hashing* Biblioteca, LISTA* Freguesias, LISTA* Concelhos, LISTA* Distritos,LISTA* Requisitantes, LISTA* Requisicoes)
{
	char linha[400];
	//Carregar livros da sessão anterior
	FILE* fich_livros = fopen("Ficheiros/Sessao/livros_manter.txt", "r");
	if (!fich_livros)
		return;
	while (!feof(fich_livros)) {
		fgets(linha, 400, fich_livros);

		char** v = SepararCampos(linha, 7, ";");

		if (v) {
			AddHASHING(Biblioteca, CriarLivro_Sessao(v[1], v[0], v[2], v[3], v[4], atoi(v[5]), v[6]));
			for (int i = 0; i < 7; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_livros);
	//Carregar freguesias da sessão anterior
	FILE* fich_freguesias = fopen("Ficheiros/Sessao/freguesias_manter.txt", "r");
	if (!fich_freguesias)
		return;
	while (!feof(fich_freguesias)) {
		fgets(linha, 400, fich_freguesias);

		char** v = SepararCampos(linha, 3, "\t");

		if (v) {
			AddLista(Freguesias, CriarFreguesia(v[0], v[1]));
			for (int i = 0; i < 3; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_freguesias);
	//Carregar concelhos da sessão anterior
	FILE* fich_concelhos = fopen("Ficheiros/Sessao/concelhos_manter.txt", "r");
	if (!fich_concelhos)
		return;
	while (!feof(fich_concelhos)) {
		fgets(linha, 400, fich_concelhos);

		char** v = SepararCampos(linha, 3, "\t");

		if (v) {
			AddLista(Concelhos, CriarConcelho(v[0], v[1]));
			for (int i = 0; i < 3; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_concelhos);
	//Carregar distritos da sessão anterior
	FILE* fich_distritos = fopen("Ficheiros/Sessao/distritos_manter.txt", "r");
	if (!fich_distritos)
		return;
	while (!feof(fich_distritos)) {
		fgets(linha, 400, fich_distritos);

		char** v = SepararCampos(linha, 2, "\t");

		if (v) {
			AddLista(Distritos, CriarDistrito(v[0], v[1]));
			for (int i = 0; i < 2; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_distritos);
	//Carregar requisitantes da sessão anterior
	FILE* fich_requisitantes = fopen("Ficheiros/Sessao/requisitantes_manter.txt", "r");
	if (!fich_requisitantes)
		return;
	while (!feof(fich_requisitantes)) {
		fgets(linha, 400, fich_requisitantes);

		char** v = SepararCampos(linha, 6, "\t");

		if (v) {
			AddLista(Requisitantes, CriarRequisitante_Sessao(v[0], v[1], v[2], atoi(v[3]), atoi(v[4]), v[5]));
			for (int i = 0; i < 6; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_requisitantes);
	//Carregar requisições da sessão anterior
	FILE* fich_requisicoes = fopen("Ficheiros/Sessao/requisicoes_manter.txt", "r");
	if (!fich_requisicoes)
		return;
	while (!feof(fich_requisicoes)) {
		fgets(linha, 400, fich_requisicoes);

		char** v = SepararCampos(linha, 2, "\t");

		if (v) {
			AddLista(Requisicoes, CriarRequisicao(atoi(v[1]), atoi(v[0])));
			for (int i = 0; i < 2; i++)
				free(v[i]);
			free(v);
		}
	}
	fclose(fich_requisicoes);
}