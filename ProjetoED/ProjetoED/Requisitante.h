#ifndef REQUISITANTE_H_INCLUDED
#define REQUISITANTE_H_INCLUDED

#include <time.h>
#include "Lista.h"
#include "Freguesia.h"

typedef struct
{
    char* ID_REQUISITANTE;
    char* REQUISITANTE;
    char* DATA_NASC;
    char ID_FREGUESIA[7];
    int JA_REQUISITOU;
    int TEM_REQUISICAO;
}REQUISITANTE;

#endif // REQUISITANTE_H_INCLUDED
