#ifndef DATAS_H_INCLUDED
#define DATAS_H_INCLUDED
typedef struct calend{
    int dia;
    int mes;
    int ano;
} CALEND;

typedef struct horas{
    int hora;
    int minuto;
    int segundo;
} HORAS;

typedef struct datacao{
    CALEND data_cal;
    HORAS data_hor;
} DATACAO;
#endif
