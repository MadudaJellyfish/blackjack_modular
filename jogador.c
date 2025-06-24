#include <stdio.h>
#include <stdlib.h>
#include "baralho.h"
#include "jogador.h"

struct jogador
{
   int tipo; // 0 para usuário, 1 para dealer
   Carta* v_mao[11]; // ponteiro para as cartas na mão do jogador, máximo de 11 cartas
   int dinheiro_total; // Dinheiro do jogador
};


Jogador* v_true_jogadores = NULL; // Vetor de jogadores, deve ser inicializado antes de usar


inicializa_returns inicializa_jogador(Espelho_Jogador* player, Espelho_Jogador* dealer)
{
    if (player == NULL || dealer == NULL)
        return INICIA_JOGADOR_N_INIC;

   v_true_jogadores = malloc(sizeof(Jogador)*2);
    // Inicializa o jogador usuário
    v_true_jogadores[0].tipo = 0; // Usuário
    v_true_jogadores[0].dinheiro_total = player->dinheiro_total; // Dinheiro inicial do usuário

    for (int i = 0; i < 11; i++)
    {
        v_true_jogadores[0].v_mao[i] = player->v_mao[i];

    }
      
    // Inicializa o jogador dealer
    v_true_jogadores[1].tipo = 1; // Dealer
    v_true_jogadores[1].dinheiro_total = dealer->dinheiro_total; // Dealer não começa com dinheiro

    for (int i = 0; i < 11; i++)
    {
        v_true_jogadores[1].v_mao[i] = dealer->v_mao[i]; // Mão do dealer vazia
    }

    return INICIA_JOGADORES_INIC_CORR;
}

calc_returns calcula_pontuacao(int tipo_jogador, int* valor)
{
    if(valor == NULL)
        return CALC_VALOR_INVAL;

    if(tipo_jogador != 0 && tipo_jogador != 1)
        return CALC_JOGADOR_INVAL;
    
    int pontuacao = 0;
    int num_ases = 0;

    Jogador* jogador = NULL; // Aqui você deve obter o jogador correto baseado no tipo_jogador
    jogador = &v_true_jogadores[tipo_jogador];

    for (int i = 0; i < 11; i++)
    {
        if(jogador->v_mao[i] == NULL) break; // Se não houver mais cartas, sai do loop

        Carta* p_carta = jogador->v_mao[i]; // ponteiro para a carta atual

        int naipe = p_carta->naipe;
        int valor_naipe = p_carta->valor_naipe;
        int revelada = p_carta->revelada;

        if (revelada == 1) // Se a carta está revelada
        {
            if (valor_naipe >= 2 && valor_naipe <= 10)
            {
                pontuacao += valor_naipe; // Cartas de 2 a 10 valem seu valor nominal
            }
            else if (valor_naipe == 1) // Ás
            {
                num_ases++;
                pontuacao += 11; // Considera o Ás como 11 inicialmente
            }
            else if (valor_naipe >= 11 && valor_naipe <= 13) // Valete, Dama, Rei
            {
                pontuacao += 10; // Valem 10 pontos
            }
        }
    }

    *valor = pontuacao;

   return PONTUACAO_CORR ;
    
}

ler_returns ler_jogador(int tipo_jogador, Espelho_Jogador* jogador)
{
    if (jogador == NULL)
        return LER_JOGADOR_INIC_INCORR;

    if (tipo_jogador < 0 || tipo_jogador > 1)
        return LER_TIPO_INVAL;

    jogador->dinheiro_total = v_true_jogadores[tipo_jogador].dinheiro_total;
    for (int i = 0; i < 11; i++)
    {
        jogador->v_mao[i] = v_true_jogadores[tipo_jogador].v_mao[i];
    }
   
    return LER_JOGADOR_CORR;
}

adic_returns adiciona_carta(int qtd_cartas, int tipo_jogador)
{
    if (qtd_cartas < 1 || qtd_cartas > 2)
        return ADIC_QTD_CARTAS_INV;

    if (tipo_jogador < 0 || tipo_jogador > 1)
        return ADIC_JOGADOR_INIC_INCORR;

    Jogador* jogador = NULL; // Aqui você deve obter o jogador correto baseado no tipo_jogador
    jogador = &v_true_jogadores[tipo_jogador];

    Carta* v_aux_cartas[11];

    int ret = retira_cartas(v_aux_cartas, qtd_cartas); //função a ser definida no módulo Baralho
    if(ret != 0)
        return ADIC_RETIRA_CARTAS_INCORR;

    for (int i = 0; i < qtd_cartas; i++) {

       if(jogador->v_mao[i] == NULL)
       {
          jogador->v_mao[i] = v_aux_cartas[i];
       }
        
    }

    return ADIC_CARTA_ADIC_CORR;
}

limpa_returns limpa_mao(int tipo_jogador)
{
    if (tipo_jogador < 0 || tipo_jogador > 1)
        return LIMPA_TIPO_JOGADOR_INVAL;

    Jogador* jogador = NULL; 
    jogador = &v_true_jogadores[tipo_jogador];

    for (int i = 0; i < 11; i++)
    {
        if (jogador->v_mao[i] != NULL)
        {
            free(jogador->v_mao[i]); // Libera a memória da carta
            jogador->v_mao[i] = NULL; // Define como NULL
        }
    }

    return LIMPA_CARTA_REMOV_CORR;
}

revela_returns revela_cartas(int tipo_jogador)
{
    if (tipo_jogador < 0 || tipo_jogador > 1)
        return REVELA_JOGADOR_INVAL;

    Jogador* jogador = NULL; 
    jogador = &v_true_jogadores[tipo_jogador];

    for (int i = 0; i < 11; i++)
    {
        if (jogador->v_mao[i] == NULL) break; // Se não houver mais cartas, sai do loop
     
        jogador->v_mao[i]->revelada = 1; // Marca a carta como revelada
        
    }

    return CARTAS_REVEL_CORR;
}

altera_returns altera_dinheiro(int valor)
{
    if (v_true_jogadores == NULL)
        return ALTERA_JOGADOR_INVAL;

    if (valor > 99999)
        return ALTERA_VALOR_INVAL;

    v_true_jogadores[0].dinheiro_total += valor; // Altera o dinheiro do usuário

    if (v_true_jogadores[0].dinheiro_total < 0)
        v_true_jogadores[0].dinheiro_total = 0; // Evita que o dinheiro fique negativo

    return ALTERA_DINHEIRO_ALT_CORR;
}

void free_jogadores()
{
    if (v_true_jogadores == NULL)
        return; // Se já estiver liberado, não faz nada

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 11; j++) {
            if (v_true_jogadores[i].v_mao[j] != NULL) {
                free(v_true_jogadores[i].v_mao[j]); // Libera cada carta na mão
            }
        }
    }
   free(v_true_jogadores);
}
