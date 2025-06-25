#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "partida.h"
#include "jogador.h"
#include "baralho.h"
#include "interface.h"
#include "teste_partida.h"
#include <string.h>

void print_resultado(const char* nome_teste, int sucesso);

int main(void) {

  printf("[INICIANDO TESTE DA APLICACAO]\n");
  printf("====================================\n");
  printf("Testando funcoes de partida...\n");
  teste_inicia_jogo();
  teste_chama_menu();
  teste_fecha_jogo();
  teste_inicia_rodada();
  teste_turno_usuario();
  teste_turno_dealer();
  teste_fim_de_rodada();
  teste_libera_jogador();
  teste_free_baralho();
  printf("Testes de partida concluidos com sucesso!\n");

  printf("Testando funcoes de baralho...\n");
  teste_inicializa_baralho();
  teste_obter_cartas_restantes();
  teste_retira_cartas();
  teste_embaralha_cartas();
  teste_baralho_vazio();
  teste_libera_baralho();
  printf("Testes de baralho concluidos com sucesso!\n");


  printf("Testando funcoes de jogador...\n");
  teste_inicializa_jogadores();
  teste_calcula_pontuacao();
  teste_adiciona_carta();
  teste_altera_dinheiro();
  teste_revela_cartas();
  teste_limpa_mao();
  teste_free_jogador();
 
  printf("Testes de jogador concluidos com sucesso!\n");

  


  printf("====================================\n");

  libera_baralho();
  free_jogadores();
  return 0;
}

int teste_inicia_jogo(void){
  int resume, aposta, ret;
  ret = inicia_jogo(&resume, &aposta);
  if (ret != INICIA_JOGO_SEM_ARQUIVO){
    print_resultado("Falha com arquivo db.json não existente.\n", 0);
  }
  else
    print_resultado("Falha com arquivo db.json não existente.\n", 1);

  FILE* file = fopen("db.json", "w");
  fclose(file);
  ret = inicia_jogo(NULL, &aposta);
  if (ret != INICIA_JOGO_PARAM_RESUME_INVALIDO){
    print_resultado("Falha com parâmetro resume inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro resume inválido.\n", 1);

  ret = inicia_jogo(&resume, NULL);
  if (ret != INICIA_JOGO_PARAM_APOSTA_INVALIDO){
    print_resultado("Falha com parâmetro aposta inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro aposta inválido.\n", 1);

  FILE* file2 = fopen("db.json", "w");
  fwrite("batata", sizeof(char), 7, file2);
  fclose(file2);

  ret = inicia_jogo(&resume, &aposta);
  if (ret != INICIA_JOGO_ARQUIVO_INVALIDO){
    print_resultado("Falha com arquivo em formato inválido.\n", 0);
  }
  else
    print_resultado("Falha com arquivo em formato inválido.\n", 1);

  FILE *f_origem = fopen("db_mock.json", "rb");
  FILE *f_destino = fopen("db.json", "wb");

  char buffer[1024];
  size_t bytes;

  while ((bytes = fread(buffer, 1, sizeof(buffer), f_origem)) > 0) {
    fwrite(buffer, 1, bytes, f_destino);
  }

  fclose(f_origem);
  fclose(f_destino);

  ret = inicia_jogo(&resume, &aposta);
  if (ret != INICIA_JOGO_OK){
    print_resultado("Chama função normalmente.\n", 0);
  }
  else
    print_resultado("Chama função normalmente.\n", 1);
  
  printf("Teste de inicia_jogo OK!\n\n");
  return 0;
}

int teste_chama_menu(void){
  int resume, ret, escolha;

  resume = 1;
  ret = chama_menu(NULL, resume);
  if (ret != CHAMA_MENU_PARAM_ESCOLHA_INVALIDO){
    print_resultado("Falha com parâmetro escolha inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro escolha inválido.\n", 1);
  
  ret = chama_menu(&escolha, 2);
  if (ret != CHAMA_MENU_PARAM_RESUME_INVALIDO){
    print_resultado("Falha com parâmetro resume inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro resume inválido.\n", 1);

  printf("\nChama com escolha continuar.");
  ret = chama_menu(&escolha, 1);
  if (ret != CHAMA_MENU_OK){
    print_resultado("Funciona ao chamar continuar com dados.\n", 0);
  }
  else
    print_resultado("Funciona ao chamar continuar com dados.\n", 1);

  printf("\nChama com escolha novo jogo.");
  ret = chama_menu(&escolha, 1);
  if (ret != CHAMA_MENU_OK){
    print_resultado("Funciona ao chamar novo jogo.\n", 0);
  }
  else
    print_resultado("Funciona ao chamar novo jogo.\n", 1);

  printf("\nChama com escolha sair.");
  ret = chama_menu(&escolha, 1);
  if (ret != CHAMA_MENU_OK){
    print_resultado("Funciona ao chamar sair.\n", 0);
  }
  else
    print_resultado("Funciona ao chamar sair.\n", 1);

  printf("Teste de chama_menu OK\n\n");
  return 0;
}

int teste_fecha_jogo(void){
  int aposta, resume, ret;

  aposta = -1;
  ret = fecha_jogo(aposta, 1);
  if (ret != FECHA_JOGO_PARAM_APOSTA_INVALIDO){
    print_resultado("Falha com parâmetro aposta inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro aposta inválido.\n", 1);
  
  ret = fecha_jogo(2500, 2);
  if (ret != FECHA_JOGO_PARAM_RESUME_INVALIDO){
    print_resultado("Falha com parâmetro resume inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro resume inválido.\n", 1);

  FILE *f_origem = fopen("db_mock.json", "rb");
  FILE *f_destino = fopen("db.json", "wb");

  char buffer[1024];
  size_t bytes;

  while ((bytes = fread(buffer, 1, sizeof(buffer), f_origem)) > 0) {
    fwrite(buffer, 1, bytes, f_destino);
  }

  fclose(f_origem);
  fclose(f_destino);

  inicia_jogo(&resume, &aposta);
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    print_resultado("Funciona ao iniciar o jogo com dados anteriores e chamar a função escolhendo salvar.\n", 0);
  }
  else
    print_resultado("Funciona ao iniciar o jogo com dados anteriores e chamar a função escolhendo salvar.\n", 1);

  resume = 0;
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    print_resultado("Funciona ao iniciar o jogo com dados anteriores e chamar a função escolhendo não salvar.\n", 0);
  }
  else
    print_resultado("Funciona ao iniciar o jogo com dados anteriores e chamar a função escolhendo não salvar.\n", 1);

  inicia_jogo(&resume, &aposta);
  resume = 1;
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    print_resultado("Funciona ao iniciar o jogo sem dados anteriores e chamar a função escolhendo salvar.\n", 0);
  }
  else
    print_resultado("Funciona ao iniciar o jogo sem dados anteriores e chamar a função escolhendo salvar.\n", 1);

  resume = 0;
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    print_resultado("Funciona ao iniciar o jogo sem dados anteriores e chamar a função escolhendo não salvar.\n", 0);
  }
  else
    print_resultado("Funciona ao iniciar o jogo sem dados anteriores e chamar a função escolhendo não salvar.\n", 1);

  printf("Teste de fecha_jogo OK\n\n");
  return 0;
}

int teste_inicia_rodada(void){
  int aposta, ret;

  ret = inicia_rodada(NULL);
  if (ret != INICIA_PARAM_APOSTA_INVALIDO){
    print_resultado("Falha com parâmetro aposta inválido.\n", 0);
  }
  else 
    print_resultado("Falha com parâmetro aposta inválido.\n", 1);

  ret = inicia_rodada(&aposta);
  if (ret != INICIA_OK){
    print_resultado("Funciona com parâmetro válido.\n", 0);
  }
  else
    print_resultado("Funciona com parâmetro válido.\n", 1);

  printf("Teste de inicia_rodada OK\n\n");
  return 0;
}

int teste_turno_usuario(void){
  int aposta, voltar_menu, ret, resume;
  inicia_jogo(&resume, &aposta);

  ret = turno_usuario(-3, &voltar_menu);
  if (ret != USUARIO_PARAM_APOSTA_INVALIDO){
    print_resultado("Falha com parâmetro aposta inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro aposta inválido.\n", 1);

  ret = turno_usuario(50, NULL);
  if (ret != USUARIO_PARAM_VOLTAR_MENU_INVALIDO){
    print_resultado("Falha com parâmetro voltar_menu inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro voltar_menu inválido.\n", 1);
 
  printf("\nCompra uma carta e depois escolhe stand.");
  ret = turno_usuario(50, &voltar_menu);
  if (ret != USUARIO_OK){
    print_resultado("Funciona ao comprar uma carta e escolher stand.\n", 0);
  }
  else
    print_resultado("Funciona ao comprar uma carta e escolher stand.\n", 1);

  printf("\nEscolhe voltar ao menu.");
  ret = turno_usuario(50, &voltar_menu);
  if (ret != USUARIO_OK || voltar_menu != 1){
    print_resultado("Funciona ao escolher voltar ao menu.\n", 0);
  }
  else
    print_resultado("Funciona ao escolher voltar ao menu.\n", 1);

  printf("\nCompra até ter 21 ou mais.");
  ret = turno_usuario(50, &voltar_menu);
  if (ret != USUARIO_OK){
    print_resultado("Funciona ao comprar uma carta até ter 21 ou mais pontos.\n", 0);
  }
  else
    print_resultado("Funciona ao comprar uma carta até ter 21 ou mais pontos.\n", 1);

  printf("Teste de turno_usuario OK!\n\n");
  return 0;
}

int teste_turno_dealer(void){
  int aposta, ret, resume;
  inicia_jogo(&resume, &aposta);

  ret = turno_dealer(-3);
  if (ret != DEALER_PARAM_APOSTA_INVALIDO){
    print_resultado("Falha com parâmetro aposta inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro aposta inválido.\n", 1);

  ret = turno_dealer(50);
  if (ret != DEALER_OK){
    print_resultado("Funciona ao chamar com parâmetros válidos.\n", 0);
  }
  else
    print_resultado("Funciona ao chamar com parâmetros válidos.\n", 1);

  printf("Teste de turno_dealer OK!\n\n");
  return 0;
}

int teste_fim_de_rodada(void){
  int ret, aposta, deseja_continuar, resume;
  Espelho_Jogador jogadores[2], jogadorAux;
  inicializa_baralho(NULL, 0);

  ret = fim_de_rodada(-3, &deseja_continuar, &resume);
  if (ret != FIM_PARAM_APOSTA_INVALIDO){
    print_resultado("Falha com parâmetro aposta inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro aposta inválido.\n", 1);

  ret = fim_de_rodada(50, NULL, &resume);
  if (ret != FIM_PARAM_CONTINUAR_INVALIDO){
    print_resultado("Falha com parâmetro deseja_continuar inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro deseja_continuar inválido.\n", 1);

  ret = fim_de_rodada(50, &deseja_continuar, NULL);
  if (ret != FIM_PARAM_RESUME_INVALIDO){
    print_resultado("Falha com parâmetro resume inválido.\n", 0);
  }
  else
    print_resultado("Falha com parâmetro resume inválido.\n", 1);

  jogadores[0].dinheiro_total = 2500;
  jogadores[1].dinheiro_total = 0;

  // Inicializa mãos dos jogadores como vazias
  for (int i = 0; i < 11; i++) {
      jogadores[0].v_mao[i] = NULL;
      jogadores[1].v_mao[i] = NULL;
  }

  jogadores[1].v_mao[0] = (Carta*)malloc(sizeof(Carta));
  jogadores[1].v_mao[0]->naipe = 0;
  jogadores[1].v_mao[0]->valor_naipe = 1;
  jogadores[1].v_mao[0]->revelada = 1;

  inicializa_jogador(&jogadores[0], &jogadores[1]);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2500){
    print_resultado("Funciona com o dealer com pontuação que ganha do usuário.\n", 0);
  }
  else
    print_resultado("Funciona com o dealer com pontuação que ganha do usuário.\n", 1);

  jogadores[0].v_mao[0] = (Carta*)malloc(sizeof(Carta));
  jogadores[0].v_mao[0]->naipe = 0;
  jogadores[0].v_mao[0]->valor_naipe = 1;
  jogadores[0].v_mao[0]->revelada = 1;

  inicializa_jogador(&jogadores[0], &jogadores[1]);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2550){
    print_resultado("Funciona com o dealer com pontuação que empata com o usuário.\n", 0);
  }
  else
    print_resultado("Funciona com o dealer com pontuação que empata com o usuário.\n", 1);

  jogadores[0].v_mao[1] = (Carta*)malloc(sizeof(Carta));
  jogadores[0].v_mao[1]->naipe = 0;
  jogadores[0].v_mao[1]->valor_naipe = 5;
  jogadores[0].v_mao[1]->revelada = 1;

  inicializa_jogador(&jogadores[0], &jogadores[1]);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2600){
    print_resultado("Funciona com o dealer com pontuação que perde do usuário.\n", 0);
  }
  else
    print_resultado("Funciona com o dealer com pontuação que perde do usuário.\n", 1);

  jogadores[0].v_mao[2] = (Carta*)malloc(sizeof(Carta));
  jogadores[0].v_mao[2]->naipe = 0;
  jogadores[0].v_mao[2]->valor_naipe = 5;
  jogadores[0].v_mao[2]->revelada = 1;

  inicializa_jogador(&jogadores[0], &jogadores[1]);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2625){
    print_resultado("Funciona com o usuário com pontuação de blackjack que ganha do dealer.\n", 0);
  }
  else
    print_resultado("Funciona com o usuário com pontuação de blackjack que ganha do dealer.\n", 1);

  Carta* baralho[52];
  for (int i = 0; i<52; i++)
    baralho[i] = NULL;

  baralho[0] = jogadores[0].v_mao[2];
  inicializa_baralho(baralho, 1);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);  
  if (ret != FIM_OK){
    print_resultado("Funciona com o baralho iniciado com 20 cartas.\n", 0);
  }
  else
    print_resultado("Funciona com o baralho iniciado com 20 cartas.\n", 1);

  free(jogadores[0].v_mao[2]);
  jogadores[0].v_mao[2] = NULL;
  free(jogadores[0].v_mao[1]);
  jogadores[0].v_mao[1] = NULL;
  free(jogadores[0].v_mao[0]);
  jogadores[0].v_mao[0] = NULL;
  jogadores[0].dinheiro_total = 0;
  inicializa_jogador(&jogadores[0], &jogadores[1]);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);  
  if (ret != FIM_OK){
    print_resultado("Funciona com o usuário perdendo e com 0 dinheiros.\n", 0);
  }
  else
    print_resultado("Funciona com o usuário perdendo e com 0 dinheiros.\n", 1);

  free(jogadores[1].v_mao[0]);

  printf("Teste de fim_de_rodada OK!\n\n");
  return 0;
}

int teste_libera_jogador(void){
  int ret;
  Espelho_Jogador jogadores[2];

  jogadores[0].dinheiro_total = 2500;
  jogadores[1].dinheiro_total = 0;

  // Inicializa mãos dos jogadores como vazias
  for (int i = 0; i < 11; i++) {
    jogadores[0].v_mao[i] = NULL;
    jogadores[1].v_mao[i] = NULL;
  }

  inicializa_jogador(&jogadores[0], &jogadores[1]);

  ret = libera_jogador();  
  if (ret != LIBERA_JOGADOR_OK){
    print_resultado("Funciona com o jogador inicializado.\n", 0);
  }
  else
    print_resultado("Funciona com o jogador inicializado.\n", 1);

  ret = libera_jogador();  
  if (ret != LIBERA_JOGADOR_N_INIC){
    print_resultado("Falha com os jogadores não inicialidados.\n", 0);
  }
  else
    print_resultado("Falha com os jogadores não inicialidados.\n", 1);

  printf("Teste de libera_jogador OK!\n\n");
  return 0;
}

int teste_free_baralho(void){
  int ret;

  inicializa_baralho(NULL, 0);
  
  ret = free_baralho();  
  if (ret != FREE_BARALHO_OK){
    print_resultado("Funciona com o baralho inicializado.\n", 0);
  }
  else
    print_resultado("Funciona com o baralho inicializado.\n", 1);

  ret = free_baralho();  
  if (ret != FREE_BARALHO_N_INIC){
    print_resultado("Falha com o baralho não inicializado.\n", 0);
  }
  else
    print_resultado("Falha com o baralho não inicializado.\n", 1);

  printf("Teste de free_baralho OK!\n\n");
  return 0;
}

/////FUNÇÕES DE TESTE DO MÓDULO JOGADOR/////
void print_resultado(const char* nome_teste, int sucesso) {
    if (sucesso) {
        printf("PASSOU: %s", nome_teste);
    } else {
        printf("FALHOU: %s", nome_teste);
    }
}

void teste_inicializa_jogadores() {
    printf("\n--- Testando inicializa_jogador ---\n");
    Espelho_Jogador jogadores[2], p, d;

    jogadores[0].dinheiro_total = 2500;
    jogadores[1].dinheiro_total = 0;

    // Inicializa mãos dos jogadores como vazias
    for (int i = 0; i < 11; i++) {
      jogadores[0].v_mao[i] = NULL;
      jogadores[1].v_mao[i] = NULL;
    }
    p = jogadores[0];
    d = jogadores[1];

    inicializa_returns res = inicializa_jogador(&p, &d);
    print_resultado("Inicializacao com sucesso\n", res == INICIA_JOGADORES_INIC_CORR);
    print_resultado("Dinheiro inicial do jogador (2500)\n", p.dinheiro_total == 2500);
    print_resultado("Dinheiro inicial do jogador (0)\n",d.dinheiro_total == 0);

    res = inicializa_jogador(NULL, &d);
    print_resultado("Falha com ponteiro do jogador nulo\n", res == INICIA_JOGADOR_N_INIC);
}

void teste_adiciona_carta() {
    printf("\n--- Testando adiciona_carta ---\n");
    Espelho_Jogador p, d;
    inicializa_jogador(&p, &d);
    inicializa_baralho(NULL, 0);

    // Teste 1: Adicionar 2 cartas com sucesso
    adic_returns res = adiciona_carta(2, 0);
    print_resultado("Adicionar 2 cartas com sucesso\n", res == ADIC_CARTA_ADIC_CORR);

    // Teste 2: Falha ao adicionar quantidade invalida (3)
    res = adiciona_carta(3, 0);
    print_resultado("Falha com quantidade de cartas invalida (3)\n", res == ADIC_QTD_CARTAS_INV);
    
    // Teste 3: Falha ao adicionar para jogador invalido (2)
    res = adiciona_carta(1, 2);
    print_resultado("Falha com tipo de jogador invalido (2)\n", res == ADIC_JOGADOR_INVAL);
  
}

void teste_calcula_pontuacao() {
    printf("\n--- Testando calcula_pontuacao ---\n");
    Espelho_Jogador p, d;
    inicializa_jogador(&p, &d);
    
    int pontos;

    // Teste 1: Falha com ponteiro de valor nulo
    calc_returns res = calcula_pontuacao(0, NULL);
    print_resultado("Falha com ponteiro de valor nulo\n", res == CALC_VALOR_INVAL);

    // Teste 2: Falha com jogador invalido
    res = calcula_pontuacao(3, &pontos);
    print_resultado("Falha com jogador invalido (3)\n", res == CALC_JOGADOR_INVAL);
    
    // Teste 3: Pontuacao correta (0 para mao vazia)
    res = calcula_pontuacao(0, &pontos);
    print_resultado("Pontuacao de mao vazia e 0\n", res == PONTUACAO_CORR && pontos == 0);

}

void teste_altera_dinheiro() {
    printf("\n--- Testando altera_dinheiro ---\n");
    Espelho_Jogador p, d;
    inicializa_jogador(&p, &d);

    // Teste 1: Adicionar dinheiro com sucesso
    altera_returns res = altera_dinheiro(500); // 2500 + 500 = 3000
    print_resultado("Adicionar 500 ao dinheiro\n", res == ALTERA_DINHEIRO_ALT_CORR);
    
    // Teste 2: Subtrair dinheiro com sucesso
    res = altera_dinheiro(-1000); // 3000 - 1000 = 2000
    print_resultado("Subtrair 1000 do dinheiro\n", res == ALTERA_DINHEIRO_ALT_CORR);

    // Teste 3: Falha com valor invalido (muito alto)
    res = altera_dinheiro(1000000);
    print_resultado("Falha com valor invalido (1000000)\n", res == ALTERA_VALOR_INVAL);
}

void teste_revela_cartas() {
    printf("\n--- Testando revela_cartas ---\n");
    Espelho_Jogador p, d;
    inicializa_jogador(&p, &d);

    adiciona_carta(1, 0);
    int pontos_antes, pontos_depois;
    calcula_pontuacao(0, &pontos_antes); // Deve ser 0, carta nao revelada

    // Teste 1: Sucesso ao revelar
    revela_returns res = revela_cartas(0);
    print_resultado("Revelar cartas com sucesso\n", res == CARTAS_REVEL_CORR);

    // Teste 2: Falha com jogador invalido
    res = revela_cartas(-1);
    print_resultado("Falha ao revelar para jogador invalido\n", res == REVELA_JOGADOR_INVAL);
}

void teste_limpa_mao() {
    printf("\n--- Testando limpa_mao ---\n");
    Espelho_Jogador p, d;

    p.dinheiro_total = 2500;
    d.dinheiro_total = 0;

  // Inicializa mãos dos jogadores como vazias
  for (int i = 0; i < 11; i++) {
      p.v_mao[i] = NULL;
      d.v_mao[i] = NULL;
  }

  d.v_mao[0] = (Carta*)malloc(sizeof(Carta));
  d.v_mao[0]->naipe = 0;
  d.v_mao[0]->valor_naipe = 1;
  d.v_mao[0]->revelada = 1;

  p.v_mao[0] = (Carta*)malloc(sizeof(Carta));
  p.v_mao[0]->naipe = 0;
  p.v_mao[0]->valor_naipe = 1;
  p.v_mao[0]->revelada = 1;

  inicializa_jogador(&p, &d);

   
  // Teste 1: Limpar mao do player com sucesso
  limpa_returns res = limpa_mao(0);
  print_resultado("Limpar mao para o Player funcionou\n", res == LIMPA_CARTA_REMOV_CORR);

  res = limpa_mao(1);
  print_resultado("Limpar mao para o Dealer funcionou\n", res == LIMPA_CARTA_REMOV_CORR);

  // Teste 2: Falha com jogador invalido
  res = limpa_mao(5);
  print_resultado("Falha ao limpar mao de jogador invalido\n", res == LIMPA_TIPO_JOGADOR_INVAL);
}

void teste_free_jogador() {
    printf("\n--- Testando free_jogador ---\n");
    int ret;
    Espelho_Jogador p, d;

    p.dinheiro_total = 2500;
    d.dinheiro_total = 0;

  // Inicializa mãos dos jogadores como vazias
  for (int i = 0; i < 11; i++) {
      p.v_mao[i] = NULL;
      d.v_mao[i] = NULL;
  }

  d.v_mao[0] = (Carta*)malloc(sizeof(Carta));
  d.v_mao[0]->naipe = 0;
  d.v_mao[0]->valor_naipe = 1;
  d.v_mao[0]->revelada = 1;

  p.v_mao[0] = (Carta*)malloc(sizeof(Carta));
  p.v_mao[0]->naipe = 0;
  p.v_mao[0]->valor_naipe = 1;
  p.v_mao[0]->revelada = 1;

  inicializa_jogador(&p, &d);

   
  // Teste 1: Lberar jogadores iniciados
  ret = libera_jogador();  
  if (ret != 0){
    print_resultado("Funciona com o jogador inicializado.\n", 0);
  }
  else
    print_resultado("Funciona com o jogador inicializado.\n", 1);

  // Teste 2: Falha com jogador não iniciado
  ret = libera_jogador();  
  if (ret != 1){
    print_resultado("Falha com o jogador não inicializado.\n", 0);
  }
  else
    print_resultado("Falha com o jogador não inicializado.\n", 1);
}
/////////


///FUNÇÕES DE TESTE DO MÓDULO BARALHO///
void teste_inicializa_baralho() {
    printf("\n--- Testando inicializa_baralho ---\n");
    int ret;

    // Teste 1: Inicialização de um baralho novo (52 cartas)
    ret = inicializa_baralho(NULL, 0);
    print_resultado("Inicializacao de baralho novo ocorreu corretamente\n", ret == 0);
}

void teste_obter_cartas_restantes() {
    printf("\n--- Testando obter_cartas_restantes ---\n");
    Carta* cartas[52];
    int qtd;
    int ret;

    // Setup: Garante que o baralho está inicializado
    inicializa_baralho(NULL, 0);

    // Teste 1: Obter cartas com sucesso
    ret = obter_cartas_restantes(cartas, &qtd);
    print_resultado("Obter cartas com sucesso (retorno 0)\n", ret == 0);
    print_resultado("Verifica se a quantidade retornada e 52\n", qtd == 52);

    // Teste 2: Falha com ponteiro de cartas nulo
    ret = obter_cartas_restantes(NULL, &qtd);
    print_resultado("Falha com ponteiro de cartas nulo (retorno 1)\n", ret == 1);

    // Teste 3: Falha com ponteiro de quantidade nulo
    ret = obter_cartas_restantes(cartas, NULL);
    print_resultado("Falha com ponteiro de quantidade nulo (retorno 1)\n", ret == 1);
}


void teste_retira_cartas() {
    printf("\n--- Testando retira_cartas ---\n");
    Carta* mao[10];
    int ret, qtd_antes, qtd_depois;
    Carta* baralho_estado[52];

    inicializa_baralho(NULL, 0);
    obter_cartas_restantes(baralho_estado, &qtd_antes); // qtd_antes = 52

    // Teste 1: Retirar 5 cartas com sucesso
    ret = retira_cartas(mao, 5);
    print_resultado("Retirar 5 cartas com sucesso (retorno 0)\n", ret == 0);
    obter_cartas_restantes(baralho_estado, &qtd_depois);
    print_resultado("Verifica se o baralho tem 47 cartas apos retirada\n", qtd_depois == 47);

    // Teste 2: Falha ao tentar retirar mais cartas do que existem
    ret = retira_cartas(mao, 50); // Só existem 47
    print_resultado("Falha ao retirar mais cartas que o disponivel (retorno 1)\n", ret == 1);

    // Teste 3: Falha com quantidade inválida (< 0)
    ret = retira_cartas(mao, -2);
    print_resultado("Falha ao retirar quantidade negativa (retorno 3)\n", ret == 3);

    // Teste 4: Falha com ponteiro de saída nulo
    ret = retira_cartas(NULL, 2);
    print_resultado("Falha com ponteiro de saida nulo (retorno 5)\n", ret == 5);

    // Teste 5: Falha com baralho vazio
    inicializa_baralho(baralho_estado, 0); // Força o baralho a ficar vazio
    ret = retira_cartas(mao, 1);
    print_resultado("Falha ao retirar de baralho vazio (retorno 4)\n", ret == 4);
}

void teste_embaralha_cartas() {
    printf("\n--- Testando embaralha_cartas ---\n");
    Carta* antes[52];
    Carta* depois[52];
    int qtd;

    inicializa_baralho(NULL, 0);

    obter_cartas_restantes(antes, &qtd);

    // Teste 1: Embaralhar com sucesso
    int ret = embaralha_cartas();
    print_resultado("Embaralhar com sucesso (retorno 0)\n", ret == 0);

    obter_cartas_restantes(depois, &qtd);

    // Teste 2: Verifica se a ordem das cartas mudou
    // memcmp compara duas áreas de memória. Se forem diferentes, o resultado não é 0.
    int mudou_a_ordem = memcmp(antes, depois, sizeof(antes)) != 0;
    print_resultado("Verifica se a ordem das cartas mudou\n", mudou_a_ordem);

    // Teste 3: Falha ao embaralhar baralho vazio
    inicializa_baralho(antes, 0); // Esvazia o baralho
    ret = embaralha_cartas();
    print_resultado("Falha ao embaralhar baralho vazio (retorno 2)\n", ret == 2);
}

void teste_baralho_vazio() {
    printf("\n--- Testando baralho_vazio ---\n");
    Carta* mao[40];

    // Teste 1: Baralho com mais de 20 cartas
    inicializa_baralho(NULL, 0); // 52 cartas
    int ret = baralho_vazio();
    print_resultado("Baralho com 52 cartas nao esta vazio (retorno 0)\n", ret == 0);

    // Teste 2: Baralho com exatamente 20 cartas (limite)
    retira_cartas(mao, 32); // 52 - 32 = 20
    ret = baralho_vazio();
    print_resultado("Baralho com 20 cartas e considerado vazio (retorno 1)\n", ret == 1);
    
    // Teste 3: Baralho com menos de 20 cartas
    retira_cartas(mao, 1); // 20 - 1 = 19
    ret = baralho_vazio();
    print_resultado("Baralho com 19 cartas e considerado vazio (retorno 1)\n", ret == 1);
}

void teste_libera_baralho() {
    printf("\n--- Testando libera_baralho ---\n");

    // Teste 1: Baralho inicializado
    inicializa_baralho(NULL, 0); // 52 cartas
    int ret = free_baralho();  
    if (ret != 0){
      print_resultado("Funciona com o baralho inicializado.\n", 0);
    }
    else
      print_resultado("Funciona com o baralho inicializado.\n", 1);

    // Teste 2: Baralho não inicializado
    ret = free_baralho();  
    if (ret != 1){
        print_resultado("Falha com o baralho não inicializado.\n", 0);
    }
    else
      print_resultado("Falha com o baralho não inicializado.\n", 1);
}
