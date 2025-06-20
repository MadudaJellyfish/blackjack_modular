#include <stdio.h>
#include <stdlib.h>
#include "baralho.h"
#include "jogador.h"

struct jogador
{
   int tipo; // 0 para usuário, 1 para dealer
   Baralho* v_mao[11]; // ponteiro para as cartas na mão do jogador, máximo de 11 cartas
   int dinheiro_total; // Dinheiro do jogador
};


