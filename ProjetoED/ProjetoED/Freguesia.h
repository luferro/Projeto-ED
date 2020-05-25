#ifndef FREGUESIA_H_INCLUDED
#define FREGUESIA_H_INCLUDED

#include "Lista.h"
#include "Concelho.h"

typedef struct
{
    char* ID_FREGUESIA;
    char* NOME_FREGUESIA;
    char ID_CONCELHO[5];
}FREGUESIA;

#endif // FREGUESIA_H_INCLUDED
