#include "Texto.h"
#define _CRT_SECURE_NO_WARNINGS

extern void AddHASHING(Hashing* H, LIVRO* X);
extern void AddLista(LISTA* L, void* EL);
extern LIVRO* CriarLivro(const char* area, const char* isbn, const char* titulo, const char* autor, const char* ano);
extern REQUISITANTE* CriarRequisitante(const char* id_requisitante, const char* requisitante, const char* data_nasc);
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
	FILE* logs = fopen("Ficheiros/logs.txt", "a+");
	if (!fich_livros) return;
	char linha[400];
	char copia[400];
	while (fgets(linha, sizeof(linha), fich_livros) != NULL) {
		if (strstr(linha, "----------") || strstr(linha, ";;;") || strstr(linha, "Dep.")) {
			fputs("\nRegisto de Livro inválido\n", logs);
			fputs(linha, logs);
		}
		else {
			strcpy(copia, linha);
			fputs(copia, fich_livros_organizado);
		}
	}
	fclose(fich_livros);
	fclose(fich_livros_organizado);
	fclose(logs);
}
//-------------------------------
void CarregarLivros(Hashing* Biblioteca) 
{
	FILE* fich_livros = fopen("Ficheiros/Livros_Organizados.txt", "r");
	if (!fich_livros)
		return;
	char linha[400];
	while (!feof(fich_livros)) {
		fgets(linha, 400, fich_livros);

		char** v = SepararCampos(linha, 20, ";");

		if (v) {
			AddHASHING(Biblioteca, CriarLivro(v[1], v[10], v[11], v[2], v[0]));
		}
	}
	fclose(fich_livros);
}
//-------------------------------
void OrganizarRequisitantes() {
	//Validar os campos
}
//-------------------------------
void CarregarRequisitantes(LISTA* Requisitantes)
{
	FILE* fich_requisitantes = fopen("Ficheiros/Requisitantes.txt", "r");
	if (!fich_requisitantes)
		return;
	char linha[400];
	while (!feof(fich_requisitantes)) {
		fgets(linha, 400, fich_requisitantes);

		char** v = SepararCampos(linha, 4, "\t");

		if (v) {
			AddLista(Requisitantes, CriarRequisitante(v[0], v[1], v[2]));
		}
	}
	fclose(fich_requisitantes);
}

