#ifndef LIVRO_H_INCLUDED
#define LIVRO_H_INCLUDED

#include "Lista.h"
#include "Hashing.h"

typedef struct
{
    char ISBN[50];
    char TITULO[50];
    char AUTOR[50];
    char AREA[50];
    char ANO[50];
    char N_REQ[50];
    //int N_REQ;
}LIVRO;

#endif // LIVRO_H_INCLUDED


