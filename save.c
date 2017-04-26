#include <stdio.h>
#include <stdlib.h>

#include "save.h"
#include "destinos.h"
#include "clientes.h"
#include "cadeias.h"
#include "gestao.h"

#define MAX_CHAR 256

void Salva_Lista_cliente(char* s){
    char string_cliente[MAX_CHAR];
    strcpy(string_cliente, "Clientes.txt");
    FILE *fp;
    fp = fopen(string_cliente,"a");
    if (fp == NULL)
        printf("Erro ao abrir o ficheiro \"%s\".",string_cliente);
    else
        fprintf(fp,"\n%s", s);
    fclose(fp);
}

int Save_Sessao(Lista_clientes lc){
    Lista_save ls = Cria_Lista_Save();
    Percorre_Lista_Clientes(ls, lc);/*Destinos comprados*/
    if (Imprime_Lista_Save(ls) == 1)
        printf("Lista salva com sucesso.\n");
    if (Destroi_Lista_Save(ls) == NULL)
        printf("Lista apagada com sucesso.\n");
    return 1;
}

int Imprime_Lista_Save(Lista_save x)
{
    char string_caminho[MAX_CHAR];

    strcpy(string_caminho, "Sessao.txt");
    FILE *f_X = fopen(string_caminho, "w");

    if (f_X == NULL)
        printf("Erro ao abrir o ficheiro \"%s\".",string_caminho);
    else{
        Lista_save a = x->next;
        /*fprintf(f_X,"%s\n"," -----------------------------------------------");
        fprintf(f_X,"%s\n"," ID Cliente    ID Destino      Data da Aquisicao");
        fprintf(f_X,"%s\n"," -----------------------------------------------");*/
        while(a)
        {
            fprintf(f_X," %12d %s %12d %s %4d%s%2d%s%2d %s%2d%s%2d%s%2d\n",
                a->cli,",",
                a->des,",",
                a->dat->data_cal.ano,",",
                a->dat->data_cal.mes,",",
                a->dat->data_cal.dia,",",
                a->dat->data_hor.hora,",",
                a->dat->data_hor.minuto,",",
                a->dat->data_hor.segundo);
                a = a->next;
        }
        /*fprintf(f_X,"%s\n"," ------------------------------------------------");*/
    }
    fclose(f_X);
    return 1;
}

void Percorre_Lista_Clientes(Lista_save pls, Lista_clientes plc){

    Lista_clientes ant_plc;
    Lista_clientes atu_plc;
    Lista_destinos ant_d;
    Lista_destinos atu_d;

    ant_plc = plc;
    atu_plc = plc->next;
    while(atu_plc != NULL){
        ant_d = atu_plc->info->destinos_comprados;
        atu_d = ant_d->next;
        while(atu_d != NULL){
            Insere_Em_Ordem_Data_Lista_Save_Comp(pls, atu_plc, atu_d);
            ant_d = atu_d;
            atu_d = atu_d->next;
        }
        ant_plc = atu_plc;
        atu_plc = atu_plc->next;
    }

    ant_plc = plc;
    atu_plc = plc->next;
    while(atu_plc != NULL){
        ant_d = atu_plc->info->destinos_espera;
        atu_d = ant_d->next;
        while(atu_d != NULL){
            Insere_Em_Ordem_Data_Lista_Save_Esp(pls, atu_plc, atu_d);
            ant_d = atu_d;
            atu_d = atu_d->next;
        }
        ant_plc = atu_plc;
        atu_plc = atu_plc->next;
    }
}

void Insere_Em_Ordem_Data_Lista_Save_Comp(Lista_save x, Lista_clientes y, Lista_destinos z){
    Lista_save ant_s, atu_s;
    Lista_save no;

    no = (Lista_save) malloc(sizeof(NO_SAVE));

    if(no != NULL){
        no->dat = (DATACAO*) malloc(sizeof(DATACAO));
        if(no->dat != NULL){
            no->cli = y->info->n_cidadao;
            no->des = z->info->id;
            no->dat->data_cal.ano = z->info_pedido_c->data_cal.ano;
            no->dat->data_cal.mes = z->info_pedido_c->data_cal.mes;
            no->dat->data_cal.dia = z->info_pedido_c->data_cal.dia;
            no->dat->data_hor.hora = z->info_pedido_c->data_hor.hora;
            no->dat->data_hor.minuto = z->info_pedido_c->data_hor.minuto;
            no->dat->data_hor.segundo = z->info_pedido_c->data_hor.segundo;
            Procura_Data_Lista_Save(x, fun_s(no), &ant_s, &atu_s);
            no->next = ant_s->next;
            ant_s->next = no;
        }
    }
}

void Insere_Em_Ordem_Data_Lista_Save_Esp(Lista_save x, Lista_clientes y, Lista_destinos z){
    Lista_save ant_s, atu_s;
    Lista_save no;

    no = (Lista_save) malloc(sizeof(NO_SAVE));

    if(no != NULL){
        no->dat = (DATACAO*) malloc(sizeof(DATACAO));
        if(no->dat != NULL){
            no->cli = y->info->n_cidadao;
            no->des = z->info->id;
            no->dat->data_cal.ano = z->info_espera_c->data_cal.ano;
            no->dat->data_cal.mes = z->info_espera_c->data_cal.mes;
            no->dat->data_cal.dia = z->info_espera_c->data_cal.dia;
            no->dat->data_hor.hora = z->info_espera_c->data_hor.hora;
            no->dat->data_hor.minuto = z->info_espera_c->data_hor.minuto;
            no->dat->data_hor.segundo = z->info_espera_c->data_hor.segundo;
            Procura_Data_Lista_Save(x, fun_s(no), &ant_s, &atu_s);
            no->next = ant_s->next;
            ant_s->next = no;
        }
    }
}

void Procura_Data_Lista_Save(Lista_save x, double l, Lista_save* ant_s, Lista_save* atu_s){
    *ant_s = x;
    *atu_s = x->next;

    while((*atu_s) != NULL && fun_s(*atu_s) < l){
        *ant_s = *atu_s;
        *atu_s = (*atu_s)->next;
    }

    if((*atu_s) != NULL && fun_s(*atu_s) != l)
        *atu_s = NULL;
}


double fun_s(Lista_save s){
    double val_s1 = (double) (s->dat->data_cal.ano)*10000000000;
    double val_s2 = (double) (s->dat->data_cal.mes)*100000000;
    double val_s3 = (double) (s->dat->data_cal.dia)*1000000;
    double val_s4 = (double) (s->dat->data_hor.hora)*10000;
    double val_s5 = (double) (s->dat->data_hor.minuto)*100;
    double val_s6 = (double) (s->dat->data_hor.segundo)*1;
    double val_s = (double) (val_s1 + val_s2 + val_s3 + val_s4 +val_s5 + val_s6);
    return val_s;
}


Lista_save Cria_Lista_Save(void)
{
    Lista_save nova;
    nova = (Lista_save) malloc (sizeof(NO_SAVE));
    if(nova != NULL)
    {
        (*nova).cli = NULL;
        nova->des = NULL;
        nova->dat = NULL;
        nova->next = NULL;
    }
    return nova;
}

Lista_save Destroi_Lista_Save(Lista_save x){
    Lista_save p;
    while(Vazio_Lista_Save(x) == 0){
        p = x;
        x = x->next;
        free(p->dat);
        free(p);
    }
    free(x);
    return NULL;
}


int Vazio_Lista_Save(Lista_save a)
{
    return (a->next == NULL ? 1 : 0);
}

int Cheio_Lista_Save(Lista_save a)
{
    return 0;
}
