#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "jogador.h"

void imprime_cartas(int tipo_jogador);
void imprime_status(int tipo_jogador, int dinheiro);
void imprime_msg(const char* msg);

void imprime_cartas(int tipo_jogador) {
    Espelho_Jogador* jogador;
    if (ler_jogador(tipo_jogador, &jogador) != LER_JOGADOR_CORR) return;

    printf("%s: ", tipo_jogador == 0 ? "Usuário" : "Dealer");
    for (int i = 0; i < 11 && jogador->v_mao[i] != NULL; i++) {
        if (jogador->v_mao[i]->revelada) {
            printf("[%d de %d] ", jogador->v_mao[i]->valor_naipe, jogador->v_mao[i]->naipe);
        } else {
            printf("[?] ");
        }
    }
    printf("\n");
}

void imprime_status(int tipo_jogador, int dinheiro) {
    if (tipo_jogador == 0)
        printf("Dinheiro disponível: R$ %d\n", dinheiro);
}

void imprime_msg(const char* msg) {
    printf("=== %s ===\n", msg);
}

int menu_principal(int* escolha, int resume) {
    do {
        printf("\n=== BLACKJACK ===\n");
        printf("0 - Novo Jogo\n");
        if (resume) printf("1 - Continuar Jogo\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", escolha) != 1) {
            printf("Entrada inválida. Digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        if (*escolha < 0 || *escolha > 2 || (!resume && *escolha == 1)) {
            printf("Opção inválida. Tente novamente.\n");
        }
    } while (*escolha < 0 || *escolha > 2 || (!resume && *escolha == 1));
    return 0;
}

int interface_rodada(int tipo_jogador, int aposta, int* jogada) {
    if (tipo_jogador == 0) {
        do {
            imprime_cartas(0);
            printf("Aposta atual: R$ %d\n", aposta);
            printf("0 - Manter (stand)\n1 - Comprar carta (hit)\n2 - Voltar ao menu\n");
            printf("Escolha: ");
            if (scanf("%d", jogada) != 1) {
                printf("Entrada inválida. Digite um número.\n");
                while (getchar() != '\n');
                continue;
            }
            if (*jogada < 0 || *jogada > 2) {
                printf("Opção inválida. Tente novamente.\n");
            }
        } while (*jogada < 0 || *jogada > 2);
        return 0;
    } else {
        imprime_msg("Turno do dealer...");
        imprime_cartas(1);
        return 0;
    }
}

int define_aposta(int* aposta, int dinheiro_disponivel) {
    int valor;
    do {
        printf("Digite sua aposta (até R$ %d): ", dinheiro_disponivel);
        if (scanf("%d", &valor) != 1) {
            printf("Entrada inválida. Digite um número.\n");
            while (getchar() != '\n');
            continue;
        }
        if (valor <= 0 || valor > dinheiro_disponivel) {
            printf("Valor inválido. Tente novamente.\n");
        }
    } while (valor <= 0 || valor > dinheiro_disponivel);
    *aposta = valor;
    return 0;
}

int interface_fim(int resultado, int aposta, int* deseja_continuar) {
    switch (resultado) {
        case 2: printf("Você venceu R$%d!\n", aposta); break;
        case 3: printf("Blackjack! Você ganhou R$%d!\n", aposta * 1.5); break;
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
            printf("Opção inválida. Digite 0 ou 1.\n");
        }
    } while (continuar != 0 && continuar != 1);
    *deseja_continuar = continuar;
    return 0;
}

void game_over() {
    printf("\n=== GAME OVER ===\n");
}
