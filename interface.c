#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "jogador.h"

void imprime_status(int tipo_jogador, int dinheiro);
void imprime_msg(const char* msg);


void imprime_cartas(int tipo_jogador) {
    Espelho_Jogador jogador;
    if (ler_jogador(tipo_jogador, &jogador) != LER_JOGADOR_CORR) return;

    printf("%s: ", tipo_jogador == 0 ? "Player" : "Dealer");
    for (int i = 0; i < 11 && jogador.v_mao[i] != NULL; i++) {
        if (jogador.v_mao[i]->revelada) {
            printf("[%s de %s] ", valor_to_string(jogador.v_mao[i]->valor_naipe), naipe_to_string(jogador.v_mao[i]->naipe));
        } else {
            printf("[?] ");
        }
    }
    printf("\n");
}

void imprime_status(int tipo_jogador, int dinheiro) {
    if (tipo_jogador == 0)
        printf("Dinheiro disponivel: R$ %d\n", dinheiro);
}

void imprime_msg(const char* msg) {
    printf("=== %s ===\n", msg);
}

int menu_principal(int* escolha, int resume) {
    if (escolha == NULL || (resume != 0 && resume != 1)) return -1;

    do {
        printf("\n=== BLACKJACK ===\n");
        printf("0 - Novo Jogo\n");
        if (resume) printf("1 - Continuar Jogo\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", escolha) != 1) {
            printf("Entrada invalida. Digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        if (*escolha < 0 || *escolha > 2 || (!resume && *escolha == 1)) {
            printf("Opção invalida. Tente novamente.\n");
        }
    } while (*escolha < 0 || *escolha > 2 || (!resume && *escolha == 1));
    return 0;
}


int interface_rodada(int tipo_jogador, int aposta, int* jogada) {
    int pontuacao;
    if (tipo_jogador == 0) {
        do {
            calcula_pontuacao(0, &pontuacao);
            printf("\nPontuação: %d\n", pontuacao);
            imprime_cartas(0);
            calcula_pontuacao(1, &pontuacao);
            printf("\nPontuação: %d\n", pontuacao);
            imprime_cartas(1);
            printf("Aposta atual: R$ %d\n", aposta);
            printf("0 - Manter (stand)\n1 - Comprar carta (hit)\n2 - Voltar ao menu\n");
            printf("Escolha: ");
            if (scanf("%d", jogada) != 1) {
                printf("Entrada invalida. Digite um número.\n");
                while (getchar() != '\n');
                continue;
            }
            if (*jogada < 0 || *jogada > 2) {
                printf("Opção invalida. Tente novamente.\n");
            }
        } while (*jogada < 0 || *jogada > 2);
        return 0;
    } else {
        imprime_msg("Turno do dealer...");
        calcula_pontuacao(0, &pontuacao);
        printf("\nPontuação: %d\n", pontuacao);
        imprime_cartas(0);
        calcula_pontuacao(1, &pontuacao);
        printf("\nPontuação: %d\n", pontuacao);
        imprime_cartas(1);
        return 0;
    }
    printf("\n");
}

int define_aposta(int* aposta, int dinheiro_disponivel) {
    int valor;
    do {
        printf("Digite sua aposta (ate R$ %d): ", dinheiro_disponivel);
        if (scanf("%d", &valor) != 1) {
            printf("Entrada invalida. Digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        if (valor <= 0 || valor > dinheiro_disponivel) {
            printf("Valor invalido. Tente novamente.\n");
        }
    } while (valor <= 0 || valor > dinheiro_disponivel);
    *aposta = valor;
    return 0;
}

int interface_fim(int resultado, int aposta, int* deseja_continuar) {
    switch (resultado) {
        case 2: printf("Voce venceu R$%d!\n", aposta); break;
        case 3: printf("Blackjack! Você ganhou R$%.0f!\n", aposta * 1.5); break;
        case 1: printf("Você perdeu R$%d!\n", aposta); break;
        case 0: printf("Empate!\n"); break;
    }
    int continuar;
    do {
        printf("Deseja continuar? (1 - Sim / 0 - Não): ");
        if (scanf("%d", &continuar) != 1) {
            printf("Entrada inválida. Digite 0 ou 1.\n");
            while (getchar() != '\n');
            continue;
        }
        if (continuar != 0 && continuar != 1) {
            printf("Opção invalida. Digite 0 ou 1.\n");
        }
    } while (continuar != 0 && continuar != 1);
    *deseja_continuar = continuar;
    return 0;
}

int game_over(void) {
    printf("\n=== GAME OVER ===\n");
    return 0;
}

const char* naipe_to_string(int naipe) {
    switch (naipe) {
        case 0: return "espadas";
        case 1: return "copas";
        case 2: return "ouros";
        case 3: return "paus";
        default: return "desconhecido";
    }
}

const char* valor_to_string(int valor) {
    switch (valor) {
        case 1: return "A";
        case 11: return "J";
        case 12: return "Q";
        case 13: return "K";
        default: {
            // Para valores numéricos, converter para string
            static char buffer[3]; // Suficiente para "10" e '\0'
            sprintf(buffer, "%d", valor);
            return buffer;
        }
    }
}
