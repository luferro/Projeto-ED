#ifndef CONCELHO_H_INCLUDED
#define CONCELHO_H_INCLUDED

#include "Lista.h"
#include "Distrito.h"

typedef struct
{
    char* ID_CONCELHO;
    char* NOME_CONCELHO;
    char ID_DISTRITO[3];
}CONCELHO;

#endif // CONCELHO_H_INCLUDED
