#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no
{
    void* INFO;
    struct no* PROX;
}NO;
typedef struct
{
    NO* Inicio;
    int NEL;
}LISTA;

#endif // LISTA_H_INCLUDED
