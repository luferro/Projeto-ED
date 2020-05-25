#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include "Lista.h"
#include "Hashing.h"

typedef struct
{
    char* ISBN;
    char* TITULO;
    char* AUTOR;
    char* AREA;
    char* ANO;
    char ESTADO_REQ[15];
    int N_REQ;
}LIVRO;

#endif // LIVRO_H_INCLUDED


