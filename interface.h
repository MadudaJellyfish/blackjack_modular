#ifndef INTERFACE_H
#define INTERFACE_H


int menu_principal(int resume);
int interface_rodada(int tipo_jogador, int aposta);
int interface_fim(int resultado, int aposta);
int define_aposta(int* aposta, int dinheiro_disponivel);
void game_over();
void imprime_cartas(int tipo_jogador);
void imprime_status(int tipo_jogador, int dinheiro);
void imprime_msg(const char* msg);

#endif
