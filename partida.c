#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "partida.h"
#include "interface.h"
#include "baralho.h"
#include "cJSON/cJSON.h"

int verifica_vencedor(void);
int parse_naipe(const char *str);
int parse_valor(const char *str);

iniciajogo_cond_ret inicia_jogo(int* resume, int* aposta){
    Espelho_Jogador jogadores[2]; // jogadores[0] = usuário, jogadores[1] = dealer
    
    Carta* cartas[52]; // vetor de ponteiros para representar o baralho
    int qtd_cartas = 0;

    // Abre o arquivo JSON
    FILE* file = fopen("db.json", "r");
    if (!file){
        return INICIA_JOGO_SEM_ARQUIVO;
    }

    // Verifica se os ponteiros fornecidos são válidos
    if (!resume){
        return INICIA_JOGO_PARAM_RESUME_INVALIDO;
    }

    if (!aposta){
        return INICIA_JOGO_PARAM_APOSTA_INVALIDO;
    }

    // Move o cursor até o final do arquivo para medir o tamanho
    fseek(file, 0, SEEK_END);
    int size = ftell(file);

    // Caso o arquivo esteja vazio, inicializa uma partida padrão (novo jogo)
    if (size == 0) {
        jogadores[0].dinheiro_total = 2500;
        jogadores[1].dinheiro_total = 0;

        // Inicializa mãos dos jogadores como vazias
        for (int i = 0; i < 11; i++) {
            jogadores[0].v_mao[i] = NULL;
            jogadores[1].v_mao[i] = NULL;
        }

        if (inicializa_jogador(&jogadores[0], &jogadores[1]) != INICIA_JOGADORES_INIC_CORR)
            return INICIA_JOGO_INICIA_JOGADOR_FALHA;

        *aposta = 0;
        *resume = 0;

        // Inicializa o baralho vazio
        if (inicializa_baralho(NULL, 0))
            return INICIA_JOGO_INICIA_BARALHO_FALHA;
    }
    else {
        // Lê o conteúdo do arquivo para um buffer de string
        fseek(file, 0, SEEK_SET);
        char *json_buffer = malloc(size + 1);
        fread(json_buffer, 1, size, file);
        json_buffer[size] = '\0';

        // Faz o parsing do JSON para um objeto cJSON
        cJSON *root = cJSON_Parse(json_buffer);
        if (!root) {
            free(json_buffer);
            return INICIA_JOGO_ARQUIVO_INVALIDO;
        }

        // Recupera o valor da aposta do JSON
        cJSON *aposta_json = cJSON_GetObjectItemCaseSensitive(root, "aposta");

        // Recupera o vetor de cartas do baralho
        cJSON *baralho = cJSON_GetObjectItemCaseSensitive(root, "baralho");
        for (int i = 0; i < cJSON_GetArraySize(baralho) && i < 52; i++) {
            cJSON *carta_json = cJSON_GetArrayItem(baralho, i);
            if (!cJSON_IsNull(carta_json)) {
                cartas[i] = malloc(sizeof(Carta));
                cartas[i]->naipe = parse_naipe(cJSON_GetObjectItem(carta_json, "naipe")->valuestring);
                cartas[i]->valor_naipe = parse_valor(cJSON_GetObjectItem(carta_json, "valor")->valuestring);
                cartas[i]->revelada = cJSON_GetObjectItem(carta_json, "revelado")->valueint;
                qtd_cartas++;
            } else {
                cartas[i] = NULL;
            }
        }

        // Carrega os dados dos dois jogadores: usuário (0) e dealer (1)
        for (int j = 0; j < 2; j++) {
            const char* chave = (j == 0) ? "usuario" : "dealer";
            cJSON *jogador_json = cJSON_GetObjectItemCaseSensitive(root, chave);

            // Dinheiro total
            jogadores[j].dinheiro_total = cJSON_GetObjectItem(jogador_json, "dinheiro_total")->valueint;

            // Cartas na mão do jogador
            cJSON *cartas_json = cJSON_GetObjectItem(jogador_json, "cartas");
            for (int i = 0; i < cJSON_GetArraySize(cartas_json) && i < 11; i++) {
                cJSON *carta_json = cJSON_GetArrayItem(cartas_json, i);
                if (!cJSON_IsNull(carta_json)) {
                    jogadores[j].v_mao[i] = malloc(sizeof(Carta));
                    jogadores[j].v_mao[i]->naipe = parse_naipe(cJSON_GetObjectItem(carta_json, "naipe")->valuestring);
                    jogadores[j].v_mao[i]->valor_naipe = parse_valor(cJSON_GetObjectItem(carta_json, "valor")->valuestring);
                    jogadores[j].v_mao[i]->revelada = cJSON_GetObjectItem(carta_json, "revelado")->valueint;
                } else {
                    jogadores[j].v_mao[i] = NULL;
                }
            }
        }
        
        if (inicializa_jogador(&jogadores[0], &jogadores[1]) != INICIA_JOGADORES_INIC_CORR)
            return INICIA_JOGO_INICIA_JOGADOR_FALHA;

        if (inicializa_baralho(cartas, qtd_cartas))
            return INICIA_JOGO_INICIA_BARALHO_FALHA;

        // Define a aposta e marca que foi retomado de um jogo salvo
        *aposta = aposta_json->valueint;
        *resume = 1;
        
        // Libera recursos alocados
        cJSON_Delete(root);
        free(json_buffer);
    }

    fclose(file);

    return INICIA_JOGO_OK;
}

menu_cond_ret chama_menu(int* escolha, int resume){
    Espelho_Jogador jogadores[2]; // jogadores[0] = usuário, jogadores[1] = dealer

    // Verifica se os ponteiros fornecidos são válidos
    if (!escolha)
        return CHAMA_MENU_PARAM_ESCOLHA_INVALIDO;

    if (resume < 0 || resume > 1)
        return CHAMA_MENU_PARAM_RESUME_INVALIDO;

    // Recebe a escolha do usuário
    if (menu_principal(escolha, resume))
        return CHAMA_MENU_MENU_PRINCIPAL_FALHA;

    if (*escolha == 0){ // Iniciar Novo Jogo
        jogadores[0].dinheiro_total = 2500;
        jogadores[1].dinheiro_total = 0;

        // Inicializa mãos dos jogadores como vazias
        for (int i = 0; i < 11; i++) {
            jogadores[0].v_mao[i] = NULL;
            jogadores[1].v_mao[i] = NULL;
        }

        if (inicializa_jogador(&jogadores[0], &jogadores[1]) != INICIA_JOGADORES_INIC_CORR)
            return CHAMA_MENU_INICIA_JOGADOR_FALHA;

        // Inicializa o baralho vazio
        if (inicializa_baralho(NULL, 0))
            return CHAMA_MENU_INICIA_BARALHO_FALHA;

        if (embaralha_cartas())
            return CHAMA_MENU_EMBARALHA_CARTAS_FALHA;
    }
    else if (*escolha == 1 && resume == 0) // Continuar jogo mas não existe jogo anterior
        return CHAMA_MENU_DADOS_ANTERIORES_FALTANTES;

    return CHAMA_MENU_OK;
}

fecha_cond_ret fecha_jogo(int aposta, int resume){
    Espelho_Jogador jogadores[2]; // jogadores[0] = usuário, jogadores[1] = dealer
    Carta* baralho[52];
    Espelho_Jogador usuario, dealer;

    if (aposta < 0 || aposta > 999999) { // A aposta não pode ser negativa nem acima de 999999
        return FECHA_JOGO_PARAM_APOSTA_INVALIDO;
    }
    if (resume != 0 && resume != 1) { // Resume deve ser 0 ou 1
        return FECHA_JOGO_PARAM_RESUME_INVALIDO;
    }

    if (resume == 0){ // Escreve arquivo em branco caso não hajam dados a salvar
        FILE* file = fopen("db.json", "w");
        fclose(file);
        return FECHA_JOGO_OK;
    }

    cJSON *root = cJSON_CreateObject();
    if (!root) {
        return FECHA_JOGO_DADOS_NAO_SALVOS; // Falha ao criar o objeto JSON raiz
    }
    
    // Adiciona a aposta
    cJSON_AddNumberToObject(root, "aposta", aposta);

    // Adiciona o baralho
    cJSON *baralho_json = cJSON_CreateArray();
    if (!baralho_json) {
        cJSON_Delete(root);
        return FECHA_JOGO_DADOS_NAO_SALVOS; // Falha ao criar o array do baralho
    }
    cJSON_AddItemToObject(root, "baralho", baralho_json);

    int qtd_cartas;
    if (obter_cartas_restantes(baralho, &qtd_cartas)){ // Recebe as cartas restantes no baralho
        return FECHA_JOGO_LER_BARALHO_FALHA;
    }

    // Itera sobre o baralho e adiciona as cartas
    for (int i = 0; i < 52; i++) {
        if (baralho[i] != NULL) {
            cJSON *carta_json = cJSON_CreateObject();
            if (!carta_json) {
                cJSON_Delete(root);
                return FECHA_JOGO_DADOS_NAO_SALVOS;
            }
            cJSON_AddStringToObject(carta_json, "naipe", naipe_to_string(baralho[i]->naipe));
            cJSON_AddStringToObject(carta_json, "valor", valor_to_string(baralho[i]->valor_naipe));
            cJSON_AddNumberToObject(carta_json, "revelado", baralho[i]->revelada);
            cJSON_AddItemToArray(baralho_json, carta_json);
        } else {
            cJSON_AddItemToArray(baralho_json, cJSON_CreateNull()); // Adiciona null para cartas não existentes
        }
    }

    if (ler_jogador(0, &usuario) != LER_JOGADOR_CORR){ // Recebe os dados do usuário
        return FECHA_JOGO_LER_JOGADOR_FALHA;
    }

    if (ler_jogador(1, &dealer) != LER_JOGADOR_CORR){ // Recebe os dados do dealer
        return FECHA_JOGO_LER_JOGADOR_FALHA;
    }

    jogadores[0] = usuario;
    jogadores[1] = dealer;

    // Adiciona os dados dos jogadores (usuário e dealer)
    for (int j = 0; j < 2; j++) {
        const char* chave = (j == 0) ? "usuario" : "dealer";
        cJSON *jogador_json = cJSON_CreateObject();
        if (!jogador_json) {
            cJSON_Delete(root);
            return FECHA_JOGO_DADOS_NAO_SALVOS;
        }
        cJSON_AddItemToObject(root, chave, jogador_json);

        cJSON_AddNumberToObject(jogador_json, "dinheiro_total", jogadores[j].dinheiro_total); // Adiciona dinheiro do jogador ao JSON

        cJSON *cartas_mao_json = cJSON_CreateArray();
        if (!cartas_mao_json) {
            cJSON_Delete(root);
            return FECHA_JOGO_DADOS_NAO_SALVOS;
        }
        cJSON_AddItemToObject(jogador_json, "cartas", cartas_mao_json);

        for (int i = 0; i < 11; i++) { // Máximo de 11 cartas na mão
            if (jogadores[j].v_mao[i] != NULL) {
                cJSON *carta_mao_json = cJSON_CreateObject();
                if (!carta_mao_json) {
                    cJSON_Delete(root);
                    return FECHA_JOGO_DADOS_NAO_SALVOS;
                }
                cJSON_AddStringToObject(carta_mao_json, "naipe", naipe_to_string(jogadores[j].v_mao[i]->naipe)); // Adiciona a mão do jogador ao JSON
                cJSON_AddStringToObject(carta_mao_json, "valor", valor_to_string(jogadores[j].v_mao[i]->valor_naipe));
                cJSON_AddNumberToObject(carta_mao_json, "revelado", jogadores[j].v_mao[i]->revelada);
                cJSON_AddItemToArray(cartas_mao_json, carta_mao_json);
            } else {
                cJSON_AddItemToArray(cartas_mao_json, cJSON_CreateNull()); // Adiciona null para slots vazios
            }
        }
    }

    // Escreve o JSON formatado para o arquivo
    char *json_string = cJSON_Print(root);
    if (!json_string) {
        cJSON_Delete(root);
        return FECHA_JOGO_DADOS_NAO_SALVOS; // Falha ao imprimir o JSON
    }

    FILE* file = fopen("db.json", "w");
    if (!file) {
        free(json_string);
        cJSON_Delete(root);
        return FECHA_JOGO_DADOS_NAO_SALVOS; // Falha ao abrir o arquivo para escrita
    }

    fprintf(file, "%s", json_string);
    fclose(file);

    free(json_string);
    cJSON_Delete(root);

    return FECHA_JOGO_OK;
}

inicia_cond_ret inicia_rodada(int* aposta){
    Espelho_Jogador jogador;

    if (!aposta) // Verifica se o ponteiro é nulo
        return INICIA_PARAM_APOSTA_INVALIDO;

    ler_jogador(0, &jogador);

    if (define_aposta(aposta, jogador.dinheiro_total)) // Pergunta ao usuário qual será a aposta da rodada
        return INICIA_DEFINE_APOSTA_FALHA;

    if (altera_dinheiro(-(*aposta)) != ALTERA_DINHEIRO_ALT_CORR) // Retira o valor da aposta do dinheiro do usuário
        return INICIA_ALTERA_DINHEIRO_FALHA;

    for (int i = 0; i < 2; i++){ // Limpa as mãos dos jogadores
        if (limpa_mao(i) != LIMPA_CARTA_REMOV_CORR)
            return INICIA_LIMPA_MAO_FALHA;
    }

    if (adiciona_carta(2, 0) != ADIC_CARTA_ADIC_CORR) // Adiciona e revela as cartas iniciais do usuário
        return INICIA_ADICIONA_CARTA_FALHA;

    if (revela_cartas(0) != CARTAS_REVEL_CORR)
        return INICIA_REVELA_CARTAS_FALHA;

    if (adiciona_carta(1, 1) != ADIC_CARTA_ADIC_CORR) // Adiciona e revela apenas a primeira carta das iniciais do dealer
        return INICIA_ADICIONA_CARTA_FALHA;

    if (revela_cartas(1) != CARTAS_REVEL_CORR)
        return INICIA_REVELA_CARTAS_FALHA;

    if (adiciona_carta(1, 1) != ADIC_CARTA_ADIC_CORR)
        return INICIA_ADICIONA_CARTA_FALHA;

    return INICIA_OK;    
}

usuario_cond_ret turno_usuario(int aposta, int* voltar_menu){
    int pontuacao, jogada;

    if (aposta < 0 || aposta > 999999) { // A aposta não pode ser negativa nem acima de 999999
        return USUARIO_PARAM_APOSTA_INVALIDO;
    }

    if (!voltar_menu){
        return USUARIO_PARAM_VOLTAR_MENU_INVALIDO;
    }

    *voltar_menu = 0; // Para evitar que passe como 1 sem o usuário ter escolhido
    while (1){
        if (calcula_pontuacao(0, &pontuacao) != PONTUACAO_CORR)
            return USUARIO_CALCULA_PONTUACAO_FALHA;

        if (pontuacao >= 21)
            break;

        if (interface_rodada(0, aposta, &jogada)) // Define a escolha de jogada do usuário
            return USUARIO_INTERFACE_RODADA_FALHA;

        if (jogada == 0){ // Stand
            break;
        }
        else if (jogada == 1){ // Hit
            if(adiciona_carta(1, 0) != ADIC_CARTA_ADIC_CORR)
                return USUARIO_ADICIONA_CARTA_FALHA;
            if (revela_cartas(0) != CARTAS_REVEL_CORR)
                return USUARIO_REVELA_CARTAS_FALHA;
            continue;
        }
        else if (jogada == 2){ // Voltar ao menu
            *voltar_menu = 1;
            break;
        }
    }

    return USUARIO_OK;
}

dealer_cond_ret turno_dealer(int aposta){
    int pontuacao, jogada;

    if (aposta < 0 || aposta > 999999) { // A aposta não pode ser negativa nem acima de 999999
        return DEALER_PARAM_APOSTA_INVALIDO;
    }

    if (revela_cartas(1) != CARTAS_REVEL_CORR) // Revela a segunda carta, virada para baixo
            return DEALER_REVELA_CARTAS_FALHA;

    while (1){
        if (calcula_pontuacao(1, &pontuacao) != PONTUACAO_CORR)
            return DEALER_CALCULA_PONTUACAO_FALHA;

        if (pontuacao >= 17) // Por regra, o dealer escolhe stand ao chegar em 17
            break;

        if (interface_rodada(1, aposta, &jogada)) // Demonstra a jogada do dealer
            return DEALER_INTERFACE_RODADA_FALHA;

        if(adiciona_carta(1, 1) != ADIC_CARTA_ADIC_CORR)
            return DEALER_ADICIONA_CARTA_FALHA;
        if (revela_cartas(1) != CARTAS_REVEL_CORR)
            return DEALER_REVELA_CARTAS_FALHA;
    }

    return DEALER_OK;
}

fim_cond_ret fim_de_rodada(int aposta, int* deseja_continuar, int* resume){
    int resultado, alt;
    Espelho_Jogador jogadores[2];

    if (aposta < 0 || aposta > 999999) // A aposta não pode ser negativa nem acima de 999999
        return FIM_PARAM_APOSTA_INVALIDO;

    if (!deseja_continuar)
        return FIM_PARAM_CONTINUAR_INVALIDO;

    if (!resume)
        return FIM_PARAM_RESUME_INVALIDO;

    resultado  = verifica_vencedor();
    if (resultado == 4)
        return FIM_VERIFICA_VENCEDOR_FALHA;
    
    switch (resultado){
        case 1: // Caso o dealer ganhe
            alt = 0;
            break;
        case 2: // Caso o usuário ganhe
            alt = aposta * 2;
            break;
        case 3: // Caso o usuário ganhe um 21 pontos
            alt = aposta * 2.5;    
    }

    if (altera_dinheiro(alt) != ALTERA_DINHEIRO_ALT_CORR) // Soma o dinheiro da rodada ao total do usuário
        return FIM_ALTERA_DINHEIRO_FALHA;

    if (ler_jogador(0, &jogadores[0]) != LER_JOGADOR_CORR)
        return FIM_LER_JOGADOR_FALHA;

    if (jogadores[0].dinheiro_total == 0){ // Game Over caso o dinheiro do usuário acabe
        if (game_over())
            return FIM_GAME_OVER_FALHA;

        *deseja_continuar = 0;
        *resume = 0;

        jogadores[0].dinheiro_total = 2500;
        jogadores[1].dinheiro_total = 0;

        // Inicializa mãos dos jogadores como vazias
        for (int i = 0; i < 11; i++) {
            jogadores[0].v_mao[i] = NULL;
            jogadores[1].v_mao[i] = NULL;
        }

        if (inicializa_jogador(&jogadores[0], &jogadores[1]) != INICIA_JOGADORES_INIC_CORR)
            return FIM_INICIALIZA_JOGADOR_FALHA;

        // Inicializa o baralho vazio
        if (inicializa_baralho(NULL, 0))
            return FIM_INICIALIZA_BARALHO_FALHA;

        if (embaralha_cartas())
            return FIM_EMBARALHA_CARTAS_FALHA;

        return FIM_OK;
    }

    if (baralho_vazio()){ // Caso hajam 20 ou menos cartas no baralho
        if (inicializa_baralho(NULL, 0))
            return FIM_INICIALIZA_BARALHO_FALHA;

        if (embaralha_cartas())
            return FIM_EMBARALHA_CARTAS_FALHA;
    }

    if (interface_fim(resultado, aposta, deseja_continuar)) // Pergunta se o usuário deseja continuar jogando ou ir para o menu principal
        return FIM_INTERFACE_FIM_FALHA;

    return FIM_OK;
}

int verifica_vencedor(void){
    int pontuacao_dealer, pontuacao_usuario;

    if (calcula_pontuacao(0, &pontuacao_usuario) != PONTUACAO_CORR)
        return 4;

    if (calcula_pontuacao(1, &pontuacao_dealer) != PONTUACAO_CORR)
        return 4;

    if ((pontuacao_dealer == pontuacao_usuario) || ((pontuacao_dealer > 21) && (pontuacao_usuario > 21))) // Empate caso a pontuação seja igual ou os 2 estourem
        return 0;

    if (pontuacao_usuario == 21) // Blackjack caso o usuário faça 21
        return 3;

    if (pontuacao_usuario > 21) // Dealer ganha se usuário passa de 21
        return 1;

    if (pontuacao_dealer > 21) // Usuário ganha se dealer passa de 21
        return 2;

    if (pontuacao_dealer > pontuacao_usuario) // Dealer ganha se a pontuação for maior que a do usuário
        return 1;

    if (pontuacao_usuario > pontuacao_dealer) // Usuário ganha se a pontuação for maior que a do dealer
        return 2;    

    return 4;
}

// Função auxiliar que converte uma string do JSON para um código de naipe (0 a 3)
int parse_naipe(const char *str) {
    if (strcmp(str, "espadas") == 0) return 0;
    if (strcmp(str, "copas") == 0) return 1;
    if (strcmp(str, "ouros") == 0) return 2;
    if (strcmp(str, "paus") == 0) return 3;
    return -1; // valor inválido
}

// Função auxiliar que converte uma string de valor de carta (ex: "A", "10") para valor numérico
int parse_valor(const char *str) {
    if (strcmp(str, "A") == 0) return 1;
    if (strcmp(str, "J") == 0) return 11;
    if (strcmp(str, "Q") == 0) return 12;
    if (strcmp(str, "K") == 0) return 13;
    return atoi(str); // valores numéricos de 2 a 10
}

void libera_jogadores()
{
    free_jogadores();
}
