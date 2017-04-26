#ifndef LISTA_CLIENTE_H_INCLUDED
#define LISTA_CLIENTE_H_INCLUDED

#include "clientes.h"

typedef struct lista_cliente* ptr_lista_cliente;

typedef struct lista_cliente{
    CLIENTE *info;
    ptr_lista_cliente next;
} LISTA_CLIENTE;

#endif // LISTA_CLIENTE_H_INCLUDED
