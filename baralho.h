
#ifndef BARALHO_H
#define BARALHO_H


typedef struct baralho Baralho;

struct carta
{
    int naipe; // 0 a 3 representando os naipes
    int valor_naipe; // 1 a 13 representando os valores das cartas    
    int revelada; // 0 para não revelada, 1 para revelada

};

typedef struct carta Carta;


#endif