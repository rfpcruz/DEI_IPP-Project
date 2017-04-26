#include <stdio.h>
#include <stdlib.h>

#include "cadeias.h"
#include "clientes.h"
#include "datas.h"
#include "destinos.h"
#include "gestao.h"
#include "save.h"
#include "time.h"

#define MAX_CHAR 256

/*http://www.catho.com.br/profissoes/cargo/*/

void clrscr(){
    system("@cls||clear");
}

int main()
{
    char leitura[MAX_CHAR];
    char venda[MAX_CHAR];
    char string_cliente[MAX_CHAR];
    char string_destino[MAX_CHAR];
    char string_compras[MAX_CHAR];
    char str[MAX_CHAR];
    char string_opcao[128];

    int opcao,i,c,d;
    int hora, minuto, segundo, ano, mes, dia;

    struct tm *dataVenda;
    time_t seg;

    Lista_clientes lis_cliente_Nome = Cria_Lista_Cliente();
    Lista_destinos lis_destino_Nome = Cria_Lista_Destino();

    puts("\nCarrega Lista de Clientes ...");
    /*
    Leitura by console
    while (1)
    {
        gets(leitura);
        if(leitura[0] == '\0')
            break;
        else
            Insere_Em_Ordem_Nome_Lista_Cliente(lis_cliente_Nome, leitura);
    };*/

    /*
    Leitura by file
    */
    strcpy(string_cliente, "Clientes.txt");
    FILE *f_clientes = fopen(string_cliente,"r");
    if (f_clientes == NULL)
        printf("Erro ao abrir o ficheiro \"%s\". Verifique o seu nome.",string_cliente);
    else{
        rewind(f_clientes);
        while (fgets(leitura, MAX_CHAR,f_clientes) != NULL)
            Insere_Em_Ordem_Nome_Lista_Cliente(lis_cliente_Nome, leitura);
    }
    fclose(f_clientes);


    puts("\nCarrega Lista de Destinos ...");
    /*
    Leitura by console
    while (1)
    {
        gets(leitura);
        if(leitura[0] == '\0')
            break;
        else
            Insere_Em_Ordem_Nome_Lista_Destino(lis_destino_Nome, leitura);
    };
    */
     /*
    Leitura by file
    */
    strcpy(string_destino, "Destinos.txt");
    FILE *f_destinos = fopen(string_destino, "r");
    if (f_destinos == NULL)
        printf("Erro ao abrir o ficheiro \"%s\". Verifique o seu nome.",string_destino);
    else {
        rewind(f_destinos);
        while (fgets(leitura, MAX_CHAR,f_destinos) != NULL)
            Insere_Em_Ordem_Nome_Lista_Destino(lis_destino_Nome, leitura);
    }
    fclose(f_destinos);

    puts("\nCarrega vendas ...");

    /*Leitura by console
    while (1)
    {
        gets(leitura);
        if(leitura[0] == '\0')
            break;
        else
            atribui_uma_venda(lis_cliente_Nome, lis_destino_Nome, leitura);
    };
    */
    /*
    Leitura by file
    */
    strcpy(string_compras, "Compras.txt");
    FILE *f_compras = fopen(string_compras, "r");

    if (f_compras == NULL)
        printf("Erro ao abrir o ficheiro \"%s\". Verifique o seu nome.",string_compras);
    else {
        rewind(f_compras);
        while (fgets(leitura, MAX_CHAR,f_compras) != NULL){
            atribui_uma_venda(lis_cliente_Nome, lis_destino_Nome, leitura);
        }
    }

    fclose(f_compras);

    while(1){
        printf("\nEscolher um metodo:\n\
           1 - Vender uma viagem;\n\
           2 - Cancelar uma viagem;\n\
           3 - Cancelar uma reserva;\n\
           4 - Listar clientes;\n\
           5 - Listar destinos;\n\
           6 - Listar destinos de um cliente;\n\
           7 - Listar clientes de um destino;\n\
           8 - Listar voos de um destino;\n\
           9 - Salvar sessao;\n\
          10 - Exit;\a\n");
        i = scanf("%d",&opcao);
        if (i == 0 || opcao <= 0 || opcao > 10) {
            gets(string_opcao);
            clrscr();
            printf("Escolha uma das opcoes disponiveis.\n");
            continue;
        }
        switch(opcao){
            case 1: c = Registar_Cliente(lis_cliente_Nome);
                    d = Registar_Destino(lis_destino_Nome);

                    sprintf(venda,"%d",c);
                    concatString_PRO(venda,",");

                    sprintf(str, "%d", d);
                    concatString_PRO(venda,str);
                    concatString_PRO(venda,",");

                    time(&seg);/*devolve hora em segundos*/
                    dataVenda = localtime(&seg);/*converte a hora em segundos*/

                    sprintf(str, "%d", dataVenda->tm_year + 1900);
                    concatString_PRO(venda,str);
                    concatString_PRO(venda,",");

                    sprintf(str, "%d", dataVenda->tm_mon + 1);
                    concatString_PRO(venda,str);
                    concatString_PRO(venda,",");

                    sprintf(str, "%d", dataVenda->tm_mday);
                    concatString_PRO(venda,str);
                    concatString_PRO(venda,",");

                    sprintf(str, "%d", dataVenda->tm_hour);
                    concatString_PRO(venda,str);
                    concatString_PRO(venda,",");

                    sprintf(str, "%d", dataVenda->tm_min);
                    concatString_PRO(venda,str);
                    concatString_PRO(venda,",");

                    sprintf(str, "%d", dataVenda->tm_sec);
                    concatString_PRO(venda,str);

                    atribui_uma_venda(lis_cliente_Nome, lis_destino_Nome, venda);
                    if(Save_Sessao(lis_cliente_Nome) == 1)
                        printf("Registo Cliente e Atribuicao Destino salvo com sucesso.\n");
                    break;
            case 2: cancelar_viagem(lis_cliente_Nome,lis_destino_Nome);
                    if(Save_Sessao(lis_cliente_Nome) == 1)
                        printf("Cancelamento da viagem salvo com sucesso.\n");
                    break;
            case 3: cancelar_reserva(lis_cliente_Nome,lis_destino_Nome);
                    if(Save_Sessao(lis_cliente_Nome) == 1)
                        printf("Cancelamento da reserva salvo com sucesso.\n");
                    break;
            case 4: puts("\nLista de clientes:\n");
                    Imprime_Nome_Lista_Cliente(lis_cliente_Nome);
                    break;
            case 5: puts("\nLista de destinos:\n");
                    Imprime_Nome_Lista_Destino(lis_destino_Nome);
                    break;
            case 6: Imprime_Destinos_de_cliente(lis_cliente_Nome);
                    break;
            case 7: Imprime_Clientes_de_destino(lis_destino_Nome);
                    break;
            case 8: Imprime_Voos_Destino(lis_destino_Nome);
                    break;
            case 9: Save_Sessao(lis_cliente_Nome);
                    break;
            case 10: return 0;
        }
    }
}
