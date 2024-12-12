#include <stdio.h>
#include <string.h>
#include "main.h"
#define MOD 218340105584896ULL //62 à la puissance 8
#define MULTIPLIER 31ULL

unsigned long long f_hashage(char *input) {
    unsigned long long hash = 0;
    int i = 0;
    while (input[i] != '\0') {
        hash = (hash * MULTIPLIER + input[i])%MOD ;
        i++;
    }
    return hash;
}

void To_Base62(unsigned long long hash, char *output) {
    const char alphabets[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    strcpy(output, "00000000");  // Initialisation de output
    int i = -1;
    do {
        i++;
        output[i] = alphabets[hash % 62];
        hash /= 62;
    }
    while (hash > 0);
    output[i+1] = '\0';  // Assure la terminaison de la chaîne
}

void encode(char *input, char *output) {
    unsigned long long hash = f_hashage(input);
    char output_inter[9];
    To_Base62(hash, output_inter);
    unsigned long long num=numero(output_inter);
    sprintf(output, "%llu-%s", num, output_inter);
}

