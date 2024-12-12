#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"


bool existe(FILE *f_stockage,char *long_url) {
    if (f_stockage == NULL) {
        perror("Erreur d'ouverture du fichier - Existe");
    }
    else {
        char ligne[1024];
        char l_url[1024];
        while(fgets(ligne,1024, f_stockage)) {
            strncpy(l_url, strchr(ligne, ' ') + 1, strchr(ligne, '\n') - strchr(ligne, ' ') );
            if(strcmp(l_url, long_url) == 0) {
                return true;
            }
        }
    }
    fclose(f_stockage);
    return false;
}


unsigned long long numero(FILE *f_stockage,char *short_url) {
    unsigned long long num = 0;
    char ligne[200],s_url[200];
    while (fgets(ligne, 100, f_stockage)) {
        strncpy(s_url, strchr(ligne, '-') + 1, strchr(ligne, ' ') - strchr(ligne, '-') );
        if(strcmp(s_url, short_url) == 0) {
            num++;
        }
    }
    fclose(f_stockage);
    return num;
}