#ifndef INTERFACE_H
#define INTERFACE_H

int menu_principal(int* escolha, int resume);
int interface_rodada(int tipo_jogador, int aposta, int* jogada);
int define_aposta(int* aposta, int dinheiro_disponivel);
int interface_fim(int resultado, int aposta, int* deseja_continuar);
int game_over(void);
void imprime_cartas(int tipo_jogador);
const char* naipe_to_string(int naipe);
const char* valor_to_string(int valor);

#endif
