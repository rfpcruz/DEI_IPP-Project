#include <stdio.h>
#include <stdlib.h>

#define MAX_CHAR 256
#define MAX_STRING 100
#define MAX_INT 50

char *apagaCaratString(char *s, char x){
    int i, j;
    for (i = j = 0; s[i] != '\0'; i++)
        if(s[i] != x)
            s[j++] = s[i];
    s[j] = '\0';
    return s;
}

int compriString(char *s){
    int i;
    for(i=0; s[i] !='\0';i++)
        ;
    return i;
}

char *concatString_PRO(char *d, char *o){
    int i = 0, l = compriString(d);
    while (d[l++] = o[i++])
        ;
    return d;
}

int conta_digitos(char *s){
    int i = 0, j = 0, res = 0;
    while(s[i] != '\0'){
        if(isdigit(s[i]))
            j++;
        i++;
    }
    return j;
}

int atoi_melhorado_sem_sinal(char *s){
    int i = 0, res = 0;
    while(s[i] != '\0'){
        if(isdigit(s[i]))
            res = res*10 + s[i] - '0';
        i++;
    }
    return res;
}

char* string_trim(char *r){
    int i, j;
    for(i = 0, j = 0; r[i] != '\0'; i++)
        if(r[i] != 32)
        {
            for( ; r[i] != '\0'; i++)
                r[j++] = r[i];
            break;
        }
    r[j] = '\0';
    return r;
}

char** tokenizer_string(char* s, char x){
    int i, j, k;
    int fica = 1;
    char** v;
    v = (char**) malloc(MAX_STRING*sizeof(char*));
    for(i = 0; i < MAX_STRING; i++)
        {
            v[i] = (char*) malloc(MAX_CHAR*sizeof(char)); /*strtok()*/
            v[i][0] = '\0';
        }
    i = j = k = 0;
    while (fica){
        if(s[i] == '\0')
            {
                v[j][k] = '\0';
                string_trim(v[j]);
                fica = 0;
            }
        if(s[i] != x){
            v[j][k] = s[i];
            k++;
        }else{
            v[j][k] = '\0';
            string_trim(v[j]);
            j++;
            k = 0;
        }
        i++;
    }
    return v;
}
