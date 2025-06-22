#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jogador.h"
#include "partida.h"
#include "interface.h"
#include "cJSON/cJSON.h"

int parse_naipe(const char *str);
int parse_valor(const char *str);
const char* naipe_to_string(int naipe);
const char* valor_to_string(int valor);

iniciajogo_cond_ret inicia_jogo(int* resume, int* aposta){
    Espelho_Jogador jogadores[2]; // jogadores[0] = usuário, jogadores[1] = dealer
    
    Carta* cartas[52]; // vetor de ponteiros para representar o baralho

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

        if (inicializa_jogador(jogadores))
            return INICIA_JOGO_INICIA_JOGADOR_FALHA;

        *aposta = 0;
        *resume = 0;

        // Inicializa o baralho vazio
        if (inicializa_baralho(NULL))
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
        
        if (inicializa_jogador(jogadores))
            return INICIA_JOGO_INICIA_JOGADOR_FALHA;

        if (inicializa_baralho(cartas))
            return INICIA_JOGO_INICIA_BARALHO_FALHA;

        // Define a aposta e marca que foi retomado de um jogo salvo
        *aposta = aposta_json->valueint;
        *resume = 1;
        
        // Libera recursos alocados
        cJSON_Delete(root);
        free(json_buffer);
        
        for (int i = 0; i < 11; i++){
            if(jogadores[0].v_mao[i])
                free(jogadores[0].v_mao[i]);

            if(jogadores[1].v_mao[i])
                free(jogadores[1].v_mao[i]);
        }

        for (int i = 0; i < 52; i++){
            if(cartas[i])
                free(cartas[i]);
        }
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

        if (inicializa_jogador(jogadores))
            return CHAMA_MENU_INICIA_JOGADOR_FALHA;

        // Inicializa o baralho vazio
        if (inicializa_baralho(NULL))
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

    if (ler_baralho(baralho)){ // Recebe as cartas restantes no baralho
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

    if (ler_jogador(0, &usuario)){ // Recebe os dados do usuário
        return FECHA_JOGO_LER_JOGADOR_FALHA;
    }

    if (ler_jogador(1, &dealer)){ // Recebe os dados do dealer
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

    for (int i = 0; i < 11; i++){
            if(jogadores[0].v_mao[i])
                free(jogadores[0].v_mao[i]);

            if(jogadores[1].v_mao[i])
                free(jogadores[1].v_mao[i]);
        }

    for (int i = 0; i < 52; i++){
        if(baralho[i])
            free(baralho[i]);
    }

    return FECHA_JOGO_OK;
}

inicia_cond_ret inicia_rodada(int* aposta){
    if (!aposta) // Verifica se o ponteiro é nulo
        return INICIA_PARAM_APOSTA_INVALIDO;

    if (define_aposta(aposta)) // Pergunta ao usuário qual será a aposta da rodada
        return INICIA_DEFINE_APOSTA_FALHA;

    if (altera_dinheiro(-(*aposta))) // Retira o valor da aposta do dinheiro do usuário
        return INICIA_ALTERA_DINHEIRO_FALHA;

    for (int i = 0; i < 2; i++){ // Limpa as mãos dos jogadores
        if (limpa_mao(i))
            return INICIA_LIMPA_MAO_FALHA;
    }

    if (adiciona_carta(2, 0)) // Adiciona e revela as cartas iniciais do usuário
        return INICIA_ADICIONA_CARTA_FALHA;

    if (revela_cartas(0))
        return INICIA_REVELA_CARTAS_FALHA;

    if (adiciona_carta(1, 1)) // Adiciona e revela apenas a primeira carta das iniciais do dealer
        return INICIA_ADICIONA_CARTA_FALHA;

    if (revela_cartas(1))
        return INICIA_REVELA_CARTAS_FALHA;

    if (adiciona_carta(1, 1))
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
        if (calcula_pontuacao(0, &pontuacao))
            return USUARIO_CALCULA_PONTUACAO_FALHA;

        if (pontuacao >= 21)
            break;

        if (interface_rodada(aposta, &jogada, 0)) // Define a escolha de jogada do usuário
            return USUARIO_INTERFACE_RODADA_FALHA;

        if (jogada == 0){ // Stand
            break;
        }
        else if (jogada == 1){ // Hit
            if(adiciona_carta(1, 0))
                return USUARIO_ADICIONA_CARTA_FALHA;
            if (revela_cartas(0))
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

// Funções auxiliares para converter de int/enum para string
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