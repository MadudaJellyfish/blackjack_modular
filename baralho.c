#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "baralho.h"

struct baralho {
    Carta* v_cartas[52];
    int qtd_cartas;
};

typedef struct baralho Baralho;

static Baralho baralho = {.qtd_cartas = -1};
//Qtd cartas = -1 para ter como padrao o teste do baralho nao ser incializado

int inicializa_baralho(Carta* cartas_salvas[], int qtd_cartas) {
    //Carta de outro jogo
    if (cartas_salvas != NULL) {
        // Erro de parametro
        if (qtd_cartas >52 || qtd_cartas <0) return 2;

        //Copiando as cartas salvas para as cartas do baralho
        baralho.qtd_cartas = qtd_cartas;
        for (int i = 0; i < qtd_cartas; i++) {
            baralho.v_cartas[i] = cartas_salvas[i];
        }
    }
    //Nao tem cartas salvas de outro jogo
    else {
        //Criando o baralho do 0
        baralho.qtd_cartas = 52;
        int index =  0;
        for (int naipe = 0; naipe < 4; naipe++) {
            for (int valor_naipe = 1; valor_naipe < 14; valor_naipe++) {
                baralho.v_cartas[index] = (Carta*)malloc(sizeof(Carta));
                baralho.v_cartas[index]->naipe = naipe;
                baralho.v_cartas[index]->valor_naipe = valor_naipe;
                baralho.v_cartas[index]->revelada = 0;
                index++;
            }
        }

    }
    //Nao inicializou
    if (baralho.qtd_cartas == -1) return 1;
    return 0;
}

int obter_cartas_restantes(Carta* v_cartas_saida[], int* qtd_saida) {
    //Erros de parametro e incializacao
    if (v_cartas_saida == NULL || qtd_saida == NULL) return 1;
    if (baralho.qtd_cartas == -1) return 2;
    //Copia baralho para vetor e numero de cartas
    *qtd_saida = baralho.qtd_cartas;
    for (int i = 0; i<baralho.qtd_cartas;i++) {
        v_cartas_saida[i] = baralho.v_cartas[i];
    }
    return 0;
}

int embaralha_cartas(void) {
    if (baralho.qtd_cartas <= 0) {
        return 2; //vazio ou nao inciou
    }

    int n = baralho.qtd_cartas;

    // loop de tras para frente
    for (int i = n - 1; i > 0; i--) {
        // Eecolher um indice aleatorio
        int j = rand() % (i + 1);

        //trocar a carta da posicao i e j
        Carta* temp = baralho.v_cartas[i];
        baralho.v_cartas[i] = baralho.v_cartas[j];
        baralho.v_cartas[j] = temp;
    }

    return 0;
}

int retira_cartas(Carta* v_cartas[], int qtd_ditr) {
    if (qtd_ditr > baralho.qtd_cartas) return 1; //Nao retirou
    if (baralho.qtd_cartas == -1) return 2; // Nao inciou
    if (qtd_ditr<0 || qtd_ditr>52) return 3; // qtd_ditr invalido
    if (baralho.qtd_cartas == 0) return 4; // baralho vazio
    if (v_cartas == NULL) return 5;// ponteiro invalido
    //retira carta
    for (int i = 0; i < qtd_ditr; i++) {
        baralho.qtd_cartas--;
        v_cartas[i] = (Carta*)malloc(sizeof(Carta));
        v_cartas[i]->naipe = baralho.v_cartas[baralho.qtd_cartas]->naipe;
        v_cartas[i]->valor_naipe = baralho.v_cartas[baralho.qtd_cartas]->valor_naipe;
        v_cartas[i]->revelada = baralho.v_cartas[baralho.qtd_cartas]->revelada;
        
        free(baralho.v_cartas[baralho.qtd_cartas]);
        baralho.v_cartas[baralho.qtd_cartas] = NULL;
    }
    return 0;

}


int baralho_vazio(void) {
    if (baralho.qtd_cartas == -1) return 2;
    if (baralho.qtd_cartas<=20) {
        return 1;
    } else {
        return 0;
    }
}

void libera_baralho(void) {
    //Resetando toda a estrutura
    memset(&baralho, 0, sizeof(Baralho));

    // Redefine o estado para "nao inicializado"
    baralho.qtd_cartas = -1;
}
