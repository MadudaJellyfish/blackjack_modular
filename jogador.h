#pragma once

typedef struct jogador Jogador;

//todas a funções presentes aqui são funções de acesso para os clientes

enum calc_return_types 
{
    PONTUACAO_CORR = 1,
    PONTUACAO_INCORR,
    JOGADOR_INIC_INCORR,
    VALOR_INVAL,
    JOGADOR_INVAL,


} calc_returns;

int calcula_pontuacao(int tipo_jogador, int* valor);

enum ler_return_types 
{
    JOGADOR_CORR = 1,
    JOGADOR_INCORR,
    JOGADOR_INIC_INCORR,
    TIPO_INVAL,
    JOGADOR_INVAL,


} ler_returns;

int ler_jogador(int tipo_jogador, Jogador jogador);

enum adic_return_types 
{
    CARTA_ADIC_CORR = 1,
    RETIRA_CARTAS_INCORR,
    QTD_CARTAS_INV,
    JOGADOR_INIC_INCORR,
    JOGADOR_INVAL,


} adic_returns;

int adiciona_carta(int qtd_cartas, int* valor);

enum limpa_return_types 
{
    CARTA_REMOV_CORR = 1,
    CARTA_REMOV_INCORR,
    TIPO_JOGADOR_INVAL,


} limpa_returns;

int limpa_mao(int tipo_jogador);

enum revela_return_types 
{
    CARTAS_REVEL_CORR = 1,
    CARTAS_REVEL_INCORR,
    JOGADOR_INVAL,

} revela_returns;

int revela_cartas(int tipo_jogador);

enum altera_return_types 
{
    DINHEIRO_ALT_CORR = 1,
    DINHEIRO_ALT_INCORR,
    VALOR_INVAL,

} altera_returns;

int altera_dinheiro(int valor);

enum inicializa_return_types 
{
    JOGADORES_INIC_CORR = 1,
    JOGADORES_INIC_INCORR,
    JOGADOR_N_INIC,

} inicializa_returns;

int inicializa_jogador(Jogador* v_jogadores);



