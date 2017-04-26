#include <stdio.h>
#include <stdlib.h>

#include "destinos.h"

#define MAX_CHAR 256

int Registar_Destino(Lista_destinos x){
    char string_lixo[128];
    char reg_destino[MAX_CHAR], leitura[MAX_CHAR];
    int ID_Destino,i;
    Lista_destinos ant_d, atu_d;

    do{
        puts("Indique ID do destino:\n");
        i = scanf("%d",&ID_Destino);
        gets(string_lixo);
        if(i != 0){
            Procura_ID_Lista_Destino(x, ID_Destino, &ant_d, &atu_d);
            if(atu_d == NULL)
                printf(" A agencia nao disponibiliza este  destino.\n Escolha outro de entre os 345 disponiveis.\n");
        }
    }while(atu_d == NULL || i == 0);
    return ID_Destino;
}

void Imprime_Voos_Destino(Lista_destinos x){
    Lista_destinos a = x->next, b;
    Lista_destinos lis_destino_voos = Cria_Lista_Destino();
    Lista_destinos ant_d,atu_d,no_voo, ant_voo, atu_voo;
    int ID_Destino;
    int i;
    char string_lixo[128];

    do {
        puts("Indique ID do destino:\n");
        i = scanf("%d", &ID_Destino);
        gets(string_lixo);
        if(i != 0){
            Procura_ID_Lista_Destino(x, ID_Destino, &ant_d, &atu_d);
            if(atu_d == NULL)
                printf(" A agencia nao disponibiliza este  destino.\n Escolha outro de entre os 345 disponiveis.\n");
        }
    }while(atu_d == NULL || i == 0);

    while(a){
        if(!strcmp(a->info->nome,atu_d->info->nome)){
            Lista_destinos no_voo = (Lista_destinos) malloc(sizeof(NO_DESTINO));
            no_voo->info = a->info;
            Procura_DataVoo_Lista_Destinos(lis_destino_voos, fun_data(a->info->partida), &ant_voo, &atu_voo);
            no_voo->next = ant_voo->next;
            ant_voo->next = no_voo;
        }
        a = a->next;
    }

    b = lis_destino_voos->next;
    printf(" ------------------------------------------------------------------------------------------------\n");
    printf(" ID    Destino                                   Maximo  Vendidos  Em Fila        Data de Partida\n");
    printf(" ------------------------------------------------------------------------------------------------\n");
    while(b){
        printf(" %4d  %-40s  %6d  %8d  %7d    %4d/%02d/%02d %02d:%02d:%02d\n",
               (b->info)->id,
               (b->info)->nome,
               (b->info)->limite_clientes,
               (b->info)->vendidos,
               (b->info)->em_fila,
               ((b->info)->partida)->data_cal.ano,
               ((b->info)->partida)->data_cal.mes,
               ((b->info)->partida)->data_cal.dia,
               ((b->info)->partida)->data_hor.hora,
               ((b->info)->partida)->data_hor.minuto,
               ((b->info)->partida)->data_hor.segundo
               );
        b = b->next;
    }
    printf(" ------------------------------------------------------------------------------------------------\n");
}

Procura_DataVoo_Lista_Destinos(Lista_destinos x, double l, Lista_destinos* ant_voo, Lista_destinos* atu_voo)
{
    *ant_voo = x;
    *atu_voo = x->next;
    while((*atu_voo) != NULL && fun_voo(atu_voo) > l)
    {
        *ant_voo = *atu_voo;
        *atu_voo = (*atu_voo)->next;

    }
    if((*atu_voo) != NULL && fun_voo(atu_voo) != l)
        *atu_voo = NULL;
}

void Imprime_Destinos_de_cliente(Lista_clientes x)
{
    Lista_clientes ant_c, atu_c;
    int ID_Cliente;
    int i;
    char string_lixo[128];

    do{
        puts("Indique ID do cliente:\n");
        i = scanf("%d",&ID_Cliente);
        gets(string_lixo);
        if( i != 0){
            Procura_ID_Lista_Cliente(x, ID_Cliente, &ant_c, &atu_c);
            if(atu_c == NULL)
                printf(" Cliente nao registado.\n");
        }
    }while(atu_c == NULL || i == 0);

    Imprime_Nome_Lista_Destino_Cliente(atu_c->info->destinos_comprados,atu_c);
    Imprime_Nome_Lista_Destino_Cliente_Espera(atu_c->info->destinos_espera,atu_c);
}
void Imprime_Nome_Lista_Destino(Lista_destinos x)
{
    Lista_destinos a = x->next;
    printf(" ------------------------------------------------------------------------------------------------\n");
    printf(" ID    Destino                                   Maximo  Vendidos  Em Fila        Data de Partida\n");
    printf(" ------------------------------------------------------------------------------------------------\n");
    while(a)
    {
        printf(" %4d  %-40s  %6d  %8d  %7d    %4d/%02d/%02d %02d:%02d:%02d\n",
               (a->info)->id,
               (a->info)->nome,
               (a->info)->limite_clientes,
               (a->info)->vendidos,
               (a->info)->em_fila,
               ((a->info)->partida)->data_cal.ano,
               ((a->info)->partida)->data_cal.mes,
               ((a->info)->partida)->data_cal.dia,
               ((a->info)->partida)->data_hor.hora,
               ((a->info)->partida)->data_hor.minuto,
               ((a->info)->partida)->data_hor.segundo
               );
        a = a->next;
    }
    printf(" ------------------------------------------------------------------------------------------------\n");
}


void Imprime_Nome_Lista_Destino_Cliente_Espera(Lista_destinos x, Lista_clientes c)
{
    Lista_destinos a = x->next;
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("Destinos em espera adquiridos pelo cliente: %72s\n", (c->info)->nome);
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("   ID                                 Destino Disponiveis Vendidas Em Fila         Data Partida         Data Reserva\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    while(a)
    {
        printf("%5d%40s%12d%9d%8d  %4d/%02d/%02d %02d:%02d:%02d  %4d/%02d/%02d %02d:%02d:%02d\n",
               (a->info)->id,
               (a->info)->nome,
               (a->info)->limite_clientes,
               (a->info)->vendidos,
               (a->info)->em_fila,
               ((a->info)->partida)->data_cal.ano,
               ((a->info)->partida)->data_cal.mes,
               ((a->info)->partida)->data_cal.dia,
               ((a->info)->partida)->data_hor.hora,
               ((a->info)->partida)->data_hor.minuto,
               ((a->info)->partida)->data_hor.segundo,
               ((a->info_espera_c)->data_cal).ano,
               ((a->info_espera_c)->data_cal).mes,
               ((a->info_espera_c)->data_cal).dia,
               ((a->info_espera_c)->data_hor).hora,
               ((a->info_espera_c)->data_hor).minuto,
               ((a->info_espera_c)->data_hor).segundo
               );
        a = a->next;
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}
void Imprime_Nome_Lista_Destino_Cliente(Lista_destinos x, Lista_clientes c)
{
    Lista_destinos a = x->next;
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("Destinos adquiridos pelo cliente: %82s\n", (c->info)->nome);
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    printf("   ID                                 Destino Disponiveis Vendidas Em Fila         Data Partida       Data Aquisicao\n");
    printf("--------------------------------------------------------------------------------------------------------------------\n");
    while(a)
    {
        printf("%5d%40s%12d%9d%8d  %4d/%02d/%02d %02d:%02d:%02d  %4d/%02d/%02d %02d:%02d:%02d\n",
               (a->info)->id,
               (a->info)->nome,
               (a->info)->limite_clientes,
               (a->info)->vendidos,
               (a->info)->em_fila,
               ((a->info)->partida)->data_cal.ano,
               ((a->info)->partida)->data_cal.mes,
               ((a->info)->partida)->data_cal.dia,
               ((a->info)->partida)->data_hor.hora,
               ((a->info)->partida)->data_hor.minuto,
               ((a->info)->partida)->data_hor.segundo,
               ((a->info_pedido_c)->data_cal).ano,
               ((a->info_pedido_c)->data_cal).mes,
               ((a->info_pedido_c)->data_cal).dia,
               ((a->info_pedido_c)->data_hor).hora,
               ((a->info_pedido_c)->data_hor).minuto,
               ((a->info_pedido_c)->data_hor).segundo
               );
        a = a->next;
    }
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}

void Insere_Em_Ordem_Nome_Lista_Destino(Lista_destinos x, char s[])
{
    char** v;
    Lista_destinos ant, atu;
    Lista_destinos no = (Lista_destinos) malloc(sizeof(NO_DESTINO));
    v = tokenizer_string(s,',');
    if(no !=NULL)
    {
        no->info = (DESTINO*) malloc(sizeof(DESTINO));
       (no->info)->id = atoi_melhorado_sem_sinal(v[0]);
       (no->info)->nome = strdup(v[1]); /* malloc + strcpy */
       (no->info)->limite_clientes = atoi_melhorado_sem_sinal(v[2]);
       (no->info)->vendidos = atoi_melhorado_sem_sinal(v[3]);
       (no->info)->em_fila = atoi_melhorado_sem_sinal(v[4]);

       (no->info)->partida = (DATACAO*) malloc(sizeof(DATACAO));
       ((no->info)->partida)->data_cal.ano = atoi_melhorado_sem_sinal(v[5]);
       ((no->info)->partida)->data_cal.mes =atoi_melhorado_sem_sinal(v[6]);
       ((no->info)->partida)->data_cal.dia = atoi_melhorado_sem_sinal(v[7]);

       ((no->info)->partida)->data_hor.hora = atoi_melhorado_sem_sinal(v[8]);
       ((no->info)->partida)->data_hor.minuto = atoi_melhorado_sem_sinal(v[9]);
       ((no->info)->partida)->data_hor.segundo = atoi_melhorado_sem_sinal(v[10]);

       (no->info)->clientes_compraram = Cria_Lista_Cliente();
       (no->info)->clientes_espera = Cria_Lista_Cliente();

        Procura_Nome_Lista_Destino(x, v[1], &ant, &atu);
        no->next = ant->next;
        ant->next = no;
    }
}

void Procura_Ultimo_Lista_Destino(Lista_destinos x, Lista_destinos* ant_d, Lista_destinos* atu_d)
{
    *ant_d = x;
    *atu_d = x->next;
    while((*atu_d) != NULL)
    {
        *ant_d = *atu_d;
        *atu_d = (*atu_d)->next;
    }
}


void Procura_DataAquisi_Lista_Destinos(Lista_destinos x, double l, Lista_destinos* ant_d, Lista_destinos* atu_d)
{
    *ant_d = x;
    *atu_d = x->next;

    while((*atu_d) != NULL && fun_d(atu_d) < l)/*Ordem crescente*/
    {
        *ant_d = *atu_d;
        *atu_d = (*atu_d)->next;
    }
    if((*atu_d) != NULL && fun_d(atu_d) != l)
        *atu_d = NULL;
}


double fun_d(Lista_destinos *g){
    double val_g1 = (double) (((*g)->info_pedido_c)->data_cal.ano)*10000000000;
    double val_g2 = (double) (((*g)->info_pedido_c)->data_cal.mes)*100000000;
    double val_g3 = (double) (((*g)->info_pedido_c)->data_cal.dia)*1000000;
    double val_g4 = (double) (((*g)->info_pedido_c)->data_hor.hora)*10000;
    double val_g5 = (double) (((*g)->info_pedido_c)->data_hor.minuto)*100;
    double val_g6 = (double) (((*g)->info_pedido_c)->data_hor.segundo)*1;
    double val_g = (double) (val_g1 + val_g2 + val_g3 + val_g4 +val_g5 + val_g6);
    return val_g;
}
double fun_voo(Lista_destinos *g){
    double val_g1 = (double) (((*g)->info)->partida->data_cal.ano)*10000000000;
    double val_g2 = (double) (((*g)->info)->partida->data_cal.mes)*100000000;
    double val_g3 = (double) (((*g)->info)->partida->data_cal.dia)*1000000;
    double val_g4 = (double) (((*g)->info)->partida->data_hor.hora)*10000;
    double val_g5 = (double) (((*g)->info)->partida->data_hor.minuto)*100;
    double val_g6 = (double) (((*g)->info)->partida->data_hor.segundo)*1;
    double val_g = (double) (val_g1 + val_g2 + val_g3 + val_g4 +val_g5 + val_g6);
    return val_g;
}

void Procura_ID_Lista_Destino(Lista_destinos x, int y, Lista_destinos* ant_d, Lista_destinos* atu_d)
{
    *ant_d = x;
    *atu_d = x->next;
    while((*atu_d) != NULL && (((*atu_d)->info)->id) != y)
    {
        *ant_d = *atu_d;
        *atu_d = (*atu_d)->next;
    }
    if((*atu_d) != NULL && (((*atu_d)->info)->id) != y)
        *atu_d = NULL;/*nao existe!*/
}

void Procura_Nome_Lista_Destino(Lista_destinos x, char s[], Lista_destinos* ant, Lista_destinos* atu)
{
    *ant = x;
    *atu = x->next;
    while((*atu) != NULL && strcmp((*atu)->info->nome,s) < 0)
    {
        *ant = *atu;
        *atu = (*atu)->next;
    }
    if((*atu) != NULL && strcmp((*atu)->info->nome,s) != 0)
        *atu = NULL;
}

Lista_destinos Cria_Lista_Destino(void)
{
    Lista_destinos nova;
    nova = (Lista_destinos) malloc (sizeof(NO_DESTINO));
    if(nova != NULL)
    {
        (*nova).info = NULL;
        nova->info_pedido_c = NULL;
        nova->info_espera_c = NULL;
        nova->next = NULL;
    }
    return nova;
}

int Vazio_Lista_Destino(Lista_destinos a)
{
    return (a->next == NULL ? 1 : 0);
}

int Cheio_Lista_Destino(Lista_destinos a)
{
    return 0;
}
