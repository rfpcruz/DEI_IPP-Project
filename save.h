#ifndef SAVE_H_INCLUDED
#define SAVE_H_INCLUDED

#include "destinos.h"
#include "clientes.h"
#include "datas.h"

typedef struct no_save* Lista_save;

typedef struct no_save{
    int cli;
    int des;
    DATACAO* dat;
    Lista_save next;
}NO_SAVE;

void Salva_Lista_Cliente(char*);
Lista_save Destroi_Lista_Save(Lista_save);
int Imprime_Lista_Save(Lista_save);
void Percorre_Lista_Clientes(Lista_save, Lista_clientes);
void Insere_Em_Ordem_Data_Lista_Save_Comp(Lista_save, Lista_clientes, Lista_destinos);
void Insere_Em_Ordem_Data_Lista_Save_Esp(Lista_save, Lista_clientes, Lista_destinos);
void Procura_Data_Lista_Save(Lista_save, double, Lista_save*, Lista_save*);
double fun_s(Lista_save);
int Save_Sessao(Lista_clientes);
Lista_save Cria_Lista_Save(void);
int Vazio_Lista_Save(Lista_save);
int Cheio_Lista_Save(Lista_save);
#endif
