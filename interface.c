#include <stdio.h>
#include <stdlib.h>
#include "interface.h"
#include "jogador.h"


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

int menu_principal(int resume) {
    int opcao;
    printf("\n=== BLACKJACK ===\n");
    printf("0 - Novo Jogo\n");
    if (resume) printf("1 - Continuar Jogo\n");
    printf("2 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    return opcao;
}

int interface_rodada(int tipo_jogador, int aposta) {
    if (tipo_jogador == 0) {
        int escolha;
        imprime_cartas(0);
        printf("Aposta atual: R$ %d\n", aposta);
        printf("0 - Manter (stand)\n1 - Comprar carta (hit)\n2 - Voltar ao menu\n");
        printf("Escolha: ");
        scanf("%d", &escolha);
        return escolha;
    } else {
        imprime_msg("Turno do dealer...");
        imprime_cartas(1);
        return 0;
    }
}

int define_aposta(int* aposta, int dinheiro_disponivel) {
    int valor;
    printf("Digite sua aposta (até R$ %d): ", dinheiro_disponivel);
    scanf("%d", &valor);
    if (valor <= 0 || valor > dinheiro_disponivel) {
        printf("Valor inválido. Tente novamente.\n");
        return 1;
    }
    *aposta = valor;
    return 0;
}

int interface_fim(int resultado, int aposta) {
    switch (resultado) {
        case 1: printf("Você venceu R$%d!\n", aposta); break;
        case 2: printf("Blackjack! Você ganhou R$%d!\n", aposta * 1.5); break;
        case 0: printf("Você perdeu R$%d!\n", aposta); break;
        case 3: printf("Empate!\n"); break;
    }
    int continuar;
    printf("Deseja continuar? (1 - Sim / 0 - Não): ");
    scanf("%d", &continuar);
    return continuar;
}

void game_over() {
    printf("\n=== GAME OVER ===\n");
}
