#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

#include "gestao.h"
#include "datas.h"
#include "cadeias.h"
#include "destinos.h"

typedef struct no_destino* Lista_destinos;
typedef struct no_cliente* Lista_clientes;

typedef struct cliente{
    char* nome;
    char* prof;
    char* morada;
    int n_cidadao;
    CALEND nasci;
    Lista_destinos destinos_comprados;
    Lista_destinos destinos_espera;
} CLIENTE;

typedef struct no_cliente{
    CLIENTE* info;
    DATACAO* info_pedido_d;
    DATACAO* info_espera_d;
    Lista_clientes next;
} NO_CLIENTE;

int Registar_Cliente(Lista_clientes);
void Procura_Ultimo_Lista_Cliente(Lista_clientes, Lista_clientes*, Lista_clientes*);
void Imprime_Nome_Lista_Cliente_Destino_Espera(Lista_clientes,Lista_destinos);
double fun(Lista_clientes*);
void Procura_DataAquisi_Lista_Cliente(Lista_clientes, double , Lista_clientes*, Lista_clientes*);
void Imprime_Nome_Lista_Cliente_Destino(Lista_clientes, Lista_destinos);
void Imprime_Clientes_de_destino(Lista_destinos);
void Procura_ID_Lista_Cliente(Lista_clientes, int, Lista_clientes*, Lista_clientes*);
void Insere_Em_Ordem_Nome_Lista_Cliente(Lista_clientes, char[]);
void Procura_Nome_Lista_Cliente(Lista_clientes, char[], Lista_clientes*, Lista_clientes*);
Lista_clientes Cria_Lista_Cliente(void);
int Vazio_Lista_Cliente(Lista_clientes);
int Cheio_Lista_Cliente(Lista_clientes);
#endif
