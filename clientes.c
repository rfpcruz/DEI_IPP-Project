#include <stdlib.h>
#include <stdio.h>
#include "clientes.h"
#include "gestao.h"

#define MAX_CHAR 256

int Registar_Cliente(Lista_clientes x){
    char reg_cliente[MAX_CHAR] = "";
    char leitura[MAX_CHAR] = "";
    int cd;
    Lista_clientes ant,atu;

    printf("Introduza os dados do cliente a registar:\n");
    getchar();

    do{
        printf("\nN. Cartao Cidadao:\n");
        gets(leitura);
    }while(conta_digitos(leitura) != 9);

    cd = atoi_melhorado_sem_sinal(leitura);

    Procura_ID_Lista_Cliente(x, cd, &ant, &atu);

    if(atu == NULL){
        concatString_PRO(reg_cliente,leitura);
        concatString_PRO(reg_cliente,",");

        printf("\nNome:\n");
        gets(leitura);
        apagaCaratString(leitura,',');
        concatString_PRO(reg_cliente,leitura);
        concatString_PRO(reg_cliente,",");

        printf("\nProfissao:\n");
        gets(leitura);
        apagaCaratString(leitura,',');
        concatString_PRO(reg_cliente,leitura);
        concatString_PRO(reg_cliente,",");

        printf("\nMorada:\n");
        gets(leitura);
        apagaCaratString(leitura,',');
        concatString_PRO(reg_cliente,leitura);
        concatString_PRO(reg_cliente,",");

        do{
            printf("\nAno Nascimento:\n");
            gets(leitura);
        }while(conta_digitos(leitura) != 4);
        concatString_PRO(reg_cliente,leitura);
        concatString_PRO(reg_cliente,",");

        do{
            printf("\nMes Nascimento:\n");
            gets(leitura);
        }while(conta_digitos(leitura) > 2);
        concatString_PRO(reg_cliente,leitura);
        concatString_PRO(reg_cliente,",");

        do{
            printf("\nDia Nascimento:\n");
            scanf("%s",leitura);
        }while(conta_digitos(leitura) > 2);
        concatString_PRO(reg_cliente,leitura);

        if(reg_cliente[0] == '\0')
            printf("String vazia!\n");
        else
            printf("\nCliente Novo: %s\n",reg_cliente);

        Insere_Em_Ordem_Nome_Lista_Cliente(x, reg_cliente);

        Salva_Lista_cliente(reg_cliente);
    }else{
        printf("Cliente com ficha de registo\n");
    }
    return cd;
}

void Imprime_Clientes_de_destino(Lista_destinos x){
    Lista_destinos ant_d, atu_d;
    int ID_Destino;
    int i;
    char string_lixo[128];

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

    Imprime_Nome_Lista_Cliente_Destino(atu_d->info->clientes_compraram,atu_d);
    Imprime_Nome_Lista_Cliente_Destino_Espera(atu_d->info->clientes_espera,atu_d);
}

void Imprime_Nome_Lista_Cliente(Lista_clientes x){
    Lista_clientes a = x->next;

    printf(" -----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf(" N. Cidadao   Nome\t\t\t\t\t\t Profissao\t\t\t\t\t  Morada                                      Data de Nascimento\n");
    printf(" -----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(a)
    {

        printf("%12d  %-50s %-40s %-50s  %4d/%02d/%02d\n",
               (a->info)->n_cidadao,
               (a->info)->nome,
               (a->info)->prof,
               (a->info)->morada,
               ((a->info)->nasci).ano,
               ((a->info)->nasci).mes,
               ((a->info)->nasci).dia
               );
        a = a->next;
    }
    printf(" -----------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void Imprime_Nome_Lista_Cliente_Destino_Espera(Lista_clientes x,Lista_destinos d){
    Lista_clientes a = x->next;
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Clientes em espera que adquiriram o destino: %149s\n",(d->info)->nome);
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("       ID                                                    Nome                                Profissao                                             Morada  Data Nascimento        Data Reserva\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(a)
    {
        printf("%9d %55s %40s %50s %10d/%02d/%02d %4d/%02d/%02d %02d:%02d:%02d\n",
               (a->info)->n_cidadao,
               (a->info)->nome,
               (a->info)->prof,
               (a->info)->morada,
                a->info->nasci.ano,
                a->info->nasci.mes,
                a->info->nasci.dia,
               ((a->info_espera_d)->data_cal).ano,
               ((a->info_espera_d)->data_cal).mes,
               ((a->info_espera_d)->data_cal).dia,
               ((a->info_espera_d)->data_hor).hora,
               ((a->info_espera_d)->data_hor).minuto,
               ((a->info_espera_d)->data_hor).segundo
               );
        a = a->next;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void Imprime_Nome_Lista_Cliente_Destino(Lista_clientes x,Lista_destinos d){
    Lista_clientes a = x->next;
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Clientes que adquiriram o destino: %159s\n",(d->info)->nome);
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("       ID                                                    Nome                                Profissao                                             Morada  Data Nascimento      Data Aquisicao\n");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    while(a)
    {
        printf("%9d %55s %40s %50s %10d/%02d/%02d %4d/%02d/%02d %02d:%02d:%02d\n",
               (a->info)->n_cidadao,
               (a->info)->nome,
               (a->info)->prof,
               (a->info)->morada,
                a->info->nasci.ano,
                a->info->nasci.mes,
                a->info->nasci.dia,
               ((a->info_pedido_d)->data_cal).ano,
               ((a->info_pedido_d)->data_cal).mes,
               ((a->info_pedido_d)->data_cal).dia,
               ((a->info_pedido_d)->data_hor).hora,
               ((a->info_pedido_d)->data_hor).minuto,
               ((a->info_pedido_d)->data_hor).segundo
               );
        a = a->next;
    }
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}


void Insere_Em_Ordem_Nome_Lista_Cliente(Lista_clientes x, char s[]){
    char** v;
    Lista_clientes ant, atu;
    Lista_clientes no;

    v = tokenizer_string(s,',');
    no = (Lista_clientes) malloc(sizeof(NO_CLIENTE));

    if(no !=NULL)
    {
        no->info = (CLIENTE*) malloc(sizeof(CLIENTE));
        if(no->info != NULL){
            (no->info)->n_cidadao = atoi_melhorado_sem_sinal(v[0]);
            (no->info)->nome = strdup(v[1]);/*strdup(v[1]) o mesmo que: malloc + strcpy */
            (no->info)->prof = strdup(v[2]);
            (no->info)->morada = strdup(v[3]);
            ((no->info)->nasci).ano = atoi_melhorado_sem_sinal(v[4]);
            ((no->info)->nasci).mes = atoi_melhorado_sem_sinal(v[5]);
            ((no->info)->nasci).dia = atoi_melhorado_sem_sinal(v[6]);
            (no->info)->destinos_comprados = Cria_Lista_Destino();
            (no->info)->destinos_espera = Cria_Lista_Destino();

            Procura_Nome_Lista_Cliente(x, v[1], &ant, &atu);

            no->next = ant->next;
            ant->next = no;
        }
    }
}

void Procura_Ultimo_Lista_Cliente(Lista_clientes x, Lista_clientes* ant_c, Lista_clientes* atu_c){
    *ant_c = x;
    *atu_c = x->next;
    while((*atu_c)->next != NULL){
        *ant_c = *atu_c;
        *atu_c = (*atu_c)->next;
    }
}


void Procura_DataAquisi_Lista_Cliente(Lista_clientes x, double l, Lista_clientes* ant_c, Lista_clientes* atu_c){
    *ant_c = x;
    *atu_c = x->next;
    while((*atu_c) != NULL && fun(atu_c) > l)/*ordem decrescente*/
    {
        *ant_c = *atu_c;
        *atu_c = (*atu_c)->next;

    }
    if((*atu_c) != NULL && fun(atu_c) != l)
        *atu_c = NULL;
}

double fun(Lista_clientes *g){
    double val_g1 = (double) (((*g)->info_pedido_d)->data_cal.ano)*10000000000;
    double val_g2 = (double) (((*g)->info_pedido_d)->data_cal.mes)*100000000;
    double val_g3 = (double) (((*g)->info_pedido_d)->data_cal.dia)*1000000;
    double val_g4 = (double) (((*g)->info_pedido_d)->data_hor.hora)*10000;
    double val_g5 = (double) (((*g)->info_pedido_d)->data_hor.minuto)*100;
    double val_g6 = (double) (((*g)->info_pedido_d)->data_hor.segundo)*1;
    double val_g = (double) (val_g1 + val_g2 + val_g3 + val_g4 +val_g5 + val_g6);
    return val_g;
}

void Procura_ID_Lista_Cliente(Lista_clientes x, int y, Lista_clientes *ant_c, Lista_clientes *atu_c){
    *ant_c = x;
    *atu_c = x->next;

    while((*atu_c) != NULL && (((*atu_c)->info)->n_cidadao) != y)
    {
        *ant_c = *atu_c;
        *atu_c = (*atu_c)->next;
    }
    if((*atu_c) != NULL && (((*atu_c)->info)->n_cidadao) != y)
        *atu_c = NULL;/*nao existe!*/
}

void Procura_Nome_Lista_Cliente(Lista_clientes x, char s[], Lista_clientes* ant, Lista_clientes* atu){
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

Lista_clientes Cria_Lista_Cliente(void){
    Lista_clientes nova;
    nova = (Lista_clientes) malloc (sizeof(NO_CLIENTE));
    if(nova != NULL)
    {
        (*nova).info = NULL;
        nova->info_espera_d = NULL;
        nova->info_pedido_d = NULL;
        nova->next = NULL;
    }
    return nova;
}

int Vazio_Lista_Cliente(Lista_clientes a){
    return (a->next == NULL ? 1 : 0);
}

int Cheio_Lista_Cliente(Lista_clientes a){
    return 0;
}
