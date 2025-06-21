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


inicializa_returns inicializa_jogador(Jogador* v_jogadores)
{
    if (v_jogadores == NULL)
        return JOGADOR_N_INIC;

    // Inicializa o jogador usuário
    v_jogadores[0].tipo = 0; // Usuário
    v_jogadores[0].dinheiro_total = 2500; // Dinheiro inicial do usuário

    for (int i = 0; i < 11; i++)
        v_jogadores[0].v_mao[i] = NULL; // Mão do usuário vazia

    // Inicializa o jogador dealer
    v_jogadores[1].tipo = 1; // Dealer
    v_jogadores[1].dinheiro_total = 0; // Dealer não começa com dinheiro
    for (int i = 0; i < 11; i++)
        v_jogadores[1].v_mao[i] = NULL; // Mão do dealer vazia

    v_true_jogadores = v_jogadores; // Esse aqui é o vetor de jogadores que pertence ao módulo Jogador. Os clientes só acessam os espelho dele

    return JOGADORES_INIC_CORR;
}

calc_returns calcula_pontuacao(int tipo_jogador, int* valor)
{
    if(valor == NULL)
        return VALOR_INVAL;

    if(tipo_jogador != 0 || tipo_jogador != 1)
        return TIPO_INVAL;
    
    int pontuacao = 0;
    int num_ases = 0;

    Jogador* jogador = NULL; // Aqui você deve obter o jogador correto baseado no tipo_jogador
    ler_jogador(tipo_jogador, jogador);

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
    
}

ler_returns ler_jogador(int tipo_jogador, Jogador* jogador)
{
    if (jogador == NULL)
        return JOGADOR_INIC_INCORR;

    if (tipo_jogador < 0 || tipo_jogador > 1)
        return TIPO_INVAL;

    jogador = &v_true_jogadores[tipo_jogador];

    // Preencher os dados do jogador
    jogador->tipo = tipo_jogador;
   
    return JOGADOR_CORR;
}

adic_returns adiciona_carta(int qtd_cartas, int tipo_jogador)
{
    if (qtd_cartas < 1 || qtd_cartas > 2)
        return QTD_CARTAS_INV;

    if (tipo_jogador < 0 || tipo_jogador > 1)
        return JOGADOR_INIC_INCORR;

    Jogador* jogador = NULL; // Aqui você deve obter o jogador correto baseado no tipo_jogador
    ler_jogador(tipo_jogador, jogador);

    int ret = retirar_cartas(jogador->v_mao, 1); //função a ser definida no módulo Baralho
    if(ret != 0)
        return RETIRA_CARTAS_INCORR;

    return CARTA_ADIC_CORR;
}

limpa_returns limpa_mao(int tipo_jogador)
{
    if (tipo_jogador < 0 || tipo_jogador > 1)
        return TIPO_JOGADOR_INVAL;

    Jogador* jogador = NULL; 
    ler_jogador(tipo_jogador, jogador);

    for (int i = 0; i < 11; i++)
    {
        if (jogador->v_mao[i] != NULL)
        {
            free(jogador->v_mao[i]); // Libera a memória da carta
            jogador->v_mao[i] = NULL; // Define como NULL
        }
    }

    return CARTA_REMOV_CORR;
}

revela_returns revela_cartas(int tipo_jogador)
{
    if (tipo_jogador < 0 || tipo_jogador > 1)
        return JOGADOR_INVAL;

    Jogador* jogador = NULL; 
    ler_jogador(tipo_jogador, jogador);

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
        return JOGADOR_INVAL;

    if (valor > 999999)
        return VALOR_INVAL;

    v_true_jogadores[0].dinheiro_total += valor; // Altera o dinheiro do usuário

    if (v_true_jogadores[0].dinheiro_total < 0)
        v_true_jogadores[0].dinheiro_total = 0; // Evita que o dinheiro fique negativo

    return DINHEIRO_ALT_CORR;
}