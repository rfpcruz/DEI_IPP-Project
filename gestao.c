#include <stdlib.h>
#include <string.h>

#include "gestao.h"
#include "clientes.h"
#include "destinos.h"

void atribui_uma_venda(Lista_clientes lis_cliente_Nome, Lista_destinos lis_destino_Nome, char s[])
{
    Lista_clientes ant_c, atu_c;
    Lista_destinos ant_d, atu_d;

    char** str_venda;

    str_venda = tokenizer_string(s,',');
    /*printf("[0] = %d e [1] = %d %d\n", atoi(str_venda[0]),atoi(str_venda[1]),atoi(str_venda[0])+atoi(str_venda[1]));*/
    Procura_ID_Lista_Cliente(lis_cliente_Nome, atoi_melhorado_sem_sinal(str_venda[0]), &ant_c, &atu_c);/*Esta funcao da o ponteiro para ID (atu_c)*/
    Procura_ID_Lista_Destino(lis_destino_Nome, atoi_melhorado_sem_sinal(str_venda[1]), &ant_d, &atu_d);/*Esta funcao da o ponteiro para ID (atu_d)*/
    /*printf("O endereco Cliente is: %d\n",atu_c);
    printf("O endereco Destino is: %d\n",atu_d);*/

    Insere_Destinos_Comprados(str_venda, atu_c, atu_d);/*Par cliente destino*/

}

void Insere_Destinos_Comprados(char** x_str, Lista_clientes x_c, Lista_destinos x_d){

    Lista_clientes no_c, ant_c, atu_c, no_ce, ant_ce, atu_ce;
    Lista_destinos no_d, ant_d, atu_d, no_de, ant_de, atu_de;

    Lista_destinos sub_lis_compra_d = x_c->info->destinos_comprados;
    Lista_destinos sub_lis_compra_de = x_c->info->destinos_espera;

    Lista_clientes sub_lis_compra_c = x_d->info->clientes_compraram;
    Lista_clientes sub_lis_compra_ce = x_d->info->clientes_espera;

    /*Atualiza contador vendidos*/
    x_d->info->vendidos = x_d->info->vendidos + 1;
    /*Atribui venda em espera ou satisfeita*/
    if((x_d->info->limite_clientes - x_d->info->vendidos) < 0){

        x_d->info->em_fila = x_d->info->em_fila + 1;

        no_de = (Lista_destinos) malloc(sizeof(NO_DESTINO));
        no_de->info_pedido_c = (DATACAO*) malloc(sizeof(DATACAO));
        no_de->info_espera_c = (DATACAO*) malloc(sizeof(DATACAO));
        no_de->info = x_d->info;

        Procura_DataAquisi_Lista_Destinos(sub_lis_compra_de, fun_double(x_str), &ant_de, &atu_de);
        no_de->info_espera_c->data_cal.ano = atoi_melhorado_sem_sinal(x_str[2]);
        no_de->info_espera_c->data_cal.mes = atoi_melhorado_sem_sinal(x_str[3]);
        no_de->info_espera_c->data_cal.dia = atoi_melhorado_sem_sinal(x_str[4]);
        no_de->info_espera_c->data_hor.hora = atoi_melhorado_sem_sinal(x_str[5]);
        no_de->info_espera_c->data_hor.minuto = atoi_melhorado_sem_sinal(x_str[6]);
        no_de->info_espera_c->data_hor.segundo = atoi_melhorado_sem_sinal(x_str[7]);
        no_de->next = ant_de->next;
        ant_de->next = no_de;

        no_ce = (Lista_clientes) malloc(sizeof(NO_CLIENTE));
        no_ce->info_pedido_d = (DATACAO*) malloc(sizeof(DATACAO));
        no_ce->info_espera_d = (DATACAO*) malloc(sizeof(DATACAO));
        no_ce->info = x_c->info;
        Procura_DataAquisi_Lista_Cliente(sub_lis_compra_ce, fun_double(x_str), &ant_ce, &atu_ce);
        no_ce->info_espera_d->data_cal.ano = atoi_melhorado_sem_sinal(x_str[2]);
        no_ce->info_espera_d->data_cal.mes = atoi_melhorado_sem_sinal(x_str[3]);
        no_ce->info_espera_d->data_cal.dia = atoi_melhorado_sem_sinal(x_str[4]);
        no_ce->info_espera_d->data_hor.hora = atoi_melhorado_sem_sinal(x_str[5]);
        no_ce->info_espera_d->data_hor.minuto = atoi_melhorado_sem_sinal(x_str[6]);
        no_ce->info_espera_d->data_hor.segundo = atoi_melhorado_sem_sinal(x_str[7]);
        no_ce->next = ant_ce->next;
        ant_ce->next = no_ce;

    }else{

        no_d = (Lista_destinos) malloc(sizeof(NO_DESTINO));
        no_d->info_pedido_c = (DATACAO*) malloc(sizeof(DATACAO));
        no_d->info_espera_c = (DATACAO*) malloc(sizeof(DATACAO));
        no_d->info = x_d->info;
        Procura_DataAquisi_Lista_Destinos(sub_lis_compra_d, fun_double(x_str), &ant_d, &atu_d);
        no_d->info_pedido_c->data_cal.ano = atoi_melhorado_sem_sinal(x_str[2]);
        no_d->info_pedido_c->data_cal.mes = atoi_melhorado_sem_sinal(x_str[3]);
        no_d->info_pedido_c->data_cal.dia = atoi_melhorado_sem_sinal(x_str[4]);
        no_d->info_pedido_c->data_hor.hora = atoi_melhorado_sem_sinal(x_str[5]);
        no_d->info_pedido_c->data_hor.minuto = atoi_melhorado_sem_sinal(x_str[6]);
        no_d->info_pedido_c->data_hor.segundo = atoi_melhorado_sem_sinal(x_str[7]);
        no_d->next = ant_d->next;
        ant_d->next = no_d;

        no_c = (Lista_clientes) malloc(sizeof(NO_CLIENTE));
        no_c->info_pedido_d = (DATACAO*) malloc(sizeof(DATACAO));
        no_c->info_espera_d = (DATACAO*) malloc(sizeof(DATACAO));
        no_c->info = x_c->info;
        Procura_DataAquisi_Lista_Cliente(sub_lis_compra_c, fun_double(x_str), &ant_c, &atu_c);
        no_c->info_pedido_d->data_cal.ano = atoi_melhorado_sem_sinal(x_str[2]);
        no_c->info_pedido_d->data_cal.mes = atoi_melhorado_sem_sinal(x_str[3]);
        no_c->info_pedido_d->data_cal.dia = atoi_melhorado_sem_sinal(x_str[4]);
        no_c->info_pedido_d->data_hor.hora = atoi_melhorado_sem_sinal(x_str[5]);
        no_c->info_pedido_d->data_hor.minuto = atoi_melhorado_sem_sinal(x_str[6]);
        no_c->info_pedido_d->data_hor.segundo = atoi_melhorado_sem_sinal(x_str[7]);
        no_c->next = ant_c->next;
        ant_c->next = no_c;
    }
}

void cancelar_viagem(Lista_clientes x_c, Lista_destinos x_d)
{
    Lista_destinos ant_d, atu_d, ant1, atu1;
    Lista_clientes ant_c, atu_c, ant2, atu2, ant3, atu3;
    int ID_Cliente;
    int ID_Destino;
    int i;
    char string_lixo[128];

    do{
        puts("Indique ID do cliente:\n");
        i = scanf("%d",&ID_Cliente);
        gets(string_lixo);
        if(i != 0){
            Procura_ID_Lista_Cliente(x_c, ID_Cliente, &ant_c, &atu_c);
            if(atu_c == NULL)
                printf(" Cliente nao registado.\n");
        }
    }while (atu_c == NULL || i == 0);

    do{
        puts("Indique ID da viagem que o cliente quer cancelar:\n");
        i = scanf("%d",&ID_Destino);
        gets(string_lixo);
        if(i != 0){
            Procura_ID_Lista_Destino(x_d, ID_Destino, &ant_d, &atu_d);
            if(atu_d == NULL)
                printf(" A agencia nao disponibiliza este  destino.\n");
        }
    }while(atu_d == NULL || i == 0);

    /*Na sublista destinos_comprados do cliente apagar os ponteiros associados a este destino*/
    Procura_ID_Lista_Destino(atu_c->info->destinos_comprados, ID_Destino, &ant1, &atu1);

    if(atu1 == NULL){
        printf("Este destino nao pertence a este cliente.\n");
    }else{
        if(atu1 != NULL){
            free(atu1->info);
            free(atu1->info_espera_c);
            free(atu1->info_pedido_c);
            ant1->next = atu1->next;
            free(atu1);
        }
        /*Na sublista clientes_compraram do destino apagar os ponteiros associados a este cliente*/
        Procura_ID_Lista_Cliente(atu_d->info->clientes_compraram, ID_Cliente, &ant2, &atu2);
        if(atu2 != NULL){
            free(atu2->info);
            free(atu2->info_espera_d);
            free(atu2->info_pedido_d);
            ant2->next = atu2->next;
            free(atu2);
        }
        /*Verificar se a sublista clientes_espera deste destino é vazia*/
        if(!Vazio_Lista_Cliente(atu_d->info->clientes_espera)){
            printf("Ha clientes em espera para este destino.\n");
            Procura_Ultimo_Lista_Cliente(atu_d->info->clientes_espera, &ant3, &atu3);
            printf("O cliente a promover is: %d\n",atu3->info->n_cidadao);
            Insere_Destino_Atualiza(atu3, atu1);
            atu_d->info->em_fila = atu_d->info->em_fila - 1;
            atu_d->info->vendidos = atu_d->info->vendidos -1;
            free(atu3->info);
            free(atu3->info_espera_d);
            free(atu3->info_pedido_d);
            ant3->next = atu3->next;
            free(atu3);
        }else{
            printf("Nao ha clientes em espera para este destino.\n");
            atu_d->info->vendidos = atu_d->info->vendidos -1;
        }
    }
}

void Insere_Destino_Atualiza(Lista_clientes y_c, Lista_destinos y_d){
        Lista_destinos no_d, anty_d, atuy_d;
        Lista_clientes no_c, anty_c, atuy_c;

        no_d = (Lista_destinos) malloc(sizeof(NO_DESTINO));
        no_d->info_pedido_c = (DATACAO*) malloc(sizeof(DATACAO));
        no_d->info_espera_c = (DATACAO*) malloc(sizeof(DATACAO));
        no_d->info = y_d->info;
        Procura_DataAquisi_Lista_Destinos(y_c->info->destinos_comprados, fun_double_c(y_c), &anty_d, &atuy_d);
        no_d->info_pedido_c->data_cal.ano = y_c->info_espera_d->data_cal.ano;
        no_d->info_pedido_c->data_cal.mes = y_c->info_espera_d->data_cal.mes;
        no_d->info_pedido_c->data_cal.dia = y_c->info_espera_d->data_cal.dia;
        no_d->info_pedido_c->data_hor.hora = y_c->info_espera_d->data_hor.hora;
        no_d->info_pedido_c->data_hor.minuto = y_c->info_espera_d->data_hor.minuto;
        no_d->info_pedido_c->data_hor.segundo = y_c->info_espera_d->data_hor.segundo;
        no_d->next = anty_d->next;
        anty_d->next = no_d;

        no_c = (Lista_clientes) malloc(sizeof(NO_CLIENTE));
        no_c->info_pedido_d = (DATACAO*) malloc(sizeof(DATACAO));
        no_c->info_espera_d = (DATACAO*) malloc(sizeof(DATACAO));
        no_c->info = y_c->info;
        Procura_DataAquisi_Lista_Cliente(y_d->info->clientes_compraram, fun_double_d(y_d), &anty_c, &atuy_c);
        no_c->info_pedido_d->data_cal.ano = y_c->info_espera_d->data_cal.ano;
        no_c->info_pedido_d->data_cal.mes = y_c->info_espera_d->data_cal.mes;
        no_c->info_pedido_d->data_cal.dia = y_c->info_espera_d->data_cal.dia;
        no_c->info_pedido_d->data_hor.hora = y_c->info_espera_d->data_hor.hora;
        no_c->info_pedido_d->data_hor.minuto = y_c->info_espera_d->data_hor.minuto;
        no_c->info_pedido_d->data_hor.segundo = y_c->info_espera_d->data_hor.segundo;
        no_c->next = anty_c->next;
        anty_c->next = no_c;
}

void cancelar_reserva(Lista_clientes x_c, Lista_destinos x_d)
{
    Lista_destinos ant_d, atu_d, ant1, atu1;
    Lista_clientes ant_c, atu_c, ant2, atu2;
    int ID_Cliente;
    int ID_Destino;
    int i;
    char string_lixo[128];

    do{
        puts("Indique ID do cliente:\n");
        i = scanf("%d",&ID_Cliente);
        gets(string_lixo);
        if(i != 0){
            Procura_ID_Lista_Cliente(x_c, ID_Cliente, &ant_c, &atu_c);
            if(atu_c == NULL)
                printf(" Cliente nao registado.\n");
        }
    }while (atu_c == NULL || i == 0);

    do{
        puts("Indique ID da reserva que o cliente quer cancelar:\n");
        i = scanf("%d",&ID_Destino);
        gets(string_lixo);
        if(i != 0){
            Procura_ID_Lista_Destino(x_d, ID_Destino, &ant_d, &atu_d);
            if(atu_d == NULL)
                printf(" A agencia nao disponibiliza este  destino.\n");
        }
    }while(atu_d == NULL || i == 0);

    Procura_ID_Lista_Destino(atu_c->info->destinos_espera, ID_Destino, &ant1, &atu1);
    if(atu1 == NULL)
        printf("Este cliente nao reservou este destino pelo que nao \nse encontra na sublista de \"Destinos_Espera\" do cliente.\n");
    if(atu1 != NULL){
        free(atu1->info);
        free(atu1->info_espera_c);
        free(atu1->info_pedido_c);
        ant1->next = atu1->next;
        free(atu1);
    }

    Procura_ID_Lista_Cliente(atu_d->info->clientes_espera, ID_Cliente, &ant2, &atu2);
    if(atu1 == NULL)
        printf("Este destino nao foi reservado por este cliente pelo \nque nao se encontra na sublista de \"Clientes_Espera\" do destino.\n");
    if(atu2 != NULL){
        free(atu2->info);
        free(atu2->info_espera_d);
        free(atu2->info_pedido_d);
        ant2->next = atu2->next;
        free(atu2);
    }
    if(atu1 != NULL && atu2 != NULL){
        atu_d->info->em_fila = atu_d->info->em_fila - 1;
        atu_d->info->vendidos = atu_d->info->vendidos - 1;
    }
}

double fun_double_c(Lista_clientes c){
    double a, m, d, h, mi, s;
    a = (double) c->info_espera_d->data_cal.ano;
    m = (double) c->info_espera_d->data_cal.mes;
    d = (double) c->info_espera_d->data_cal.dia;
    h = (double) c->info_espera_d->data_hor.hora;
   mi = (double) c->info_espera_d->data_hor.minuto;
    s = (double) c->info_espera_d->data_hor.segundo;
    return  a*10000000000+
            m*100000000+
            d*1000000+
            h*10000+
           mi*100+
            s*1;
}


double fun_double_d(Lista_destinos d){
    double a, m, di, h, mi, s;
    a = (double) d->info_espera_c->data_cal.ano;
    m = (double) d->info_espera_c->data_cal.mes;
   di = (double) d->info_espera_c->data_cal.dia;
    h = (double) d->info_espera_c->data_hor.hora;
   mi = (double) d->info_espera_c->data_hor.minuto;
    s = (double) d->info_espera_c->data_hor.segundo;
    return  a*10000000000+
            m*100000000+
           di*1000000+
            h*10000+
           mi*100+
            s*1;
}


double fun_double(char** x_str){
    return (double) atof(x_str[2])*10000000000+
        (double) atof(x_str[3])*100000000+
        (double) atof(x_str[4])*1000000+
        (double) atof(x_str[5])*10000+
        (double) atof(x_str[6])*100+
        (double) atof(x_str[7])*1;
}

double fun_data(DATACAO* z){
    return (double) z->data_cal.ano*10000000000+
        (double) z->data_cal.mes*100000000+
        (double) z->data_cal.dia*1000000+
        (double) z->data_hor.hora*10000+
        (double) z->data_hor.minuto*100+
        (double) z->data_hor.segundo*1;
}


