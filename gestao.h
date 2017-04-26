#ifndef GESTAO_H_INCLUDED
#define GESTAO_H_INCLUDED

#include "cadeias.h"
#include "destinos.h"
#include "clientes.h"
#include "datas.h"

void cancelar_reserva(Lista_clientes,Lista_destinos);
void cancelar_viagem(Lista_clientes, Lista_destinos);
void atribui_uma_venda(Lista_clientes, Lista_destinos, char[]);
void vender(Lista_clientes, Lista_destinos, int, int*,int);
void Insere_Destinos_Comprados(char**, Lista_clientes, Lista_destinos);
void Procura_Morada_Lista_Destino(Lista_destinos, char[], Lista_destinos*, Lista_destinos*);
double fun_double_c(Lista_clientes);
double fun_double_d(Lista_destinos);
double fun_double(char**);

#endif
