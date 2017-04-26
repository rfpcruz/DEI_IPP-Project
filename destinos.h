#ifndef DESTINOS_H_INCLUDED
#define DESTINOS_H_INCLUDED

#include "gestao.h"
#include "datas.h"
#include "clientes.h"
#include "cadeias.h"

typedef struct no_destino* Lista_destinos;
typedef struct no_cliente* Lista_clientes;

typedef struct destino{
    int id;
    char* nome;
    int limite_clientes;
    int vendidos;
    int em_fila;
    DATACAO* partida;
    Lista_clientes clientes_compraram;
    Lista_clientes clientes_espera;
} DESTINO;

typedef struct no_destino{
    DESTINO* info;
    DATACAO* info_pedido_c;
    DATACAO* info_espera_c;
    Lista_destinos next;
} NO_DESTINO;

int Registar_Destino(Lista_destinos);
void Procura_Ultimo_Lista_Destino(Lista_destinos, Lista_destinos*, Lista_destinos*);
void Procura_DataVoo_Lista_Destinos(Lista_destinos, double, Lista_destinos*, Lista_destinos*);
void Imprime_Voos_Destino(Lista_destinos);
void Imprime_Nome_Lista_Destino_Cliente_Espera(Lista_destinos, Lista_clientes);
double fun_data(DATACAO*);
double fun_d(Lista_destinos*);
double fun_voo(Lista_destinos*);
void Procura_DataAquisi_Lista_Destinos(Lista_destinos, double , Lista_destinos*, Lista_destinos*);
void Imprime_Destinos_de_cliente(Lista_clientes);
void Imprime_Nome_Lista_Destino_Cliente(Lista_destinos, Lista_clientes);
void Procura_ID_Lista_Destino(Lista_destinos, int, Lista_destinos*, Lista_destinos*);
void Insere_Em_Ordem_Nome_Lista_Destino(Lista_destinos, char[]);
void Procura_Nome_Lista_Destino(Lista_destinos, char[], Lista_destinos*, Lista_destinos*);
Lista_destinos Cria_Lista_Destino(void);
int Vazio_Lista_Destino(Lista_destinos);
int Cheio_Lista_Destino(Lista_destinos);
#endif
