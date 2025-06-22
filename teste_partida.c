#include <stdio.h>
#include <stdlib.h>
#include "partida.h"
#include "jogador.h"
#include "teste_partida.h"

int main(void) {
  teste_inicia_jogo();
  teste_chama_menu();
  teste_fecha_jogo();
  teste_inicia_rodada();
  teste_turno_usuario();
  teste_turno_dealer();
  teste_fim_de_rodada();

  return 0;
}

int teste_inicia_jogo(void){
  int resume, aposta, ret;
  ret = inicia_jogo(&resume, &aposta);
  if (ret != INICIA_JOGO_SEM_ARQUIVO){
    printf("Erro no primeiro caso de inicia_jogo!\n");
    return 0;
  }

  FILE* file = fopen("db.json", "w");
  fclose(file);
  ret = inicia_jogo(NULL, &aposta);
  if (ret != INICIA_JOGO_PARAM_RESUME_INVALIDO){
    printf("Erro no segundo caso de inicia_jogo!\n");
    return 0;
  }

  ret = inicia_jogo(&resume, NULL);
  if (ret != INICIA_JOGO_PARAM_APOSTA_INVALIDO){
    printf("Erro no terceiro caso de inicia_jogo!\n");
    return 0;
  }

  FILE* file2 = fopen("db.json", "w");
  fwrite("batata", sizeof(char), 7, file2);
  fclose(file2);

  ret = inicia_jogo(&resume, &aposta);
  if (ret != INICIA_JOGO_ARQUIVO_INVALIDO){
    printf("Erro no quarto caso de inicia_jogo!\n");
    return 0;
  }

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
    printf("Erro no quinto caso de inicia_jogo!\n");
    return 0;
  }
  
  printf("Teste de inicia_jogo OK!\n");
  return 0;
}

int teste_chama_menu(void){
  int resume, ret;
  int* escolha = (int*)malloc(sizeof(int));

  resume = 1;
  ret = chama_menu(NULL, resume);
  if (ret != CHAMA_MENU_PARAM_ESCOLHA_INVALIDO){
    printf("Erro no primeiro caso de chama_menu!\n");
    return 0;
  }
  
  *escolha = 1;
  ret = chama_menu(escolha, 2);
  if (ret != CHAMA_MENU_PARAM_RESUME_INVALIDO){
    printf("Erro no segundo caso de chama_menu!\n");
    return 0;
  }
  
  ret = chama_menu(escolha, 0);
  if (ret != CHAMA_MENU_DADOS_ANTERIORES_FALTANTES){
    printf("Erro no terceiro caso de chama_menu!\n");
    return 0;
  }

  ret = chama_menu(escolha, 1);
  if (ret != CHAMA_MENU_OK){
    printf("Erro no quarto caso de chama_menu!\n");
    return 0;
  }

  *escolha = 2;
  ret = chama_menu(escolha, 1);
  if (ret != CHAMA_MENU_OK){
    printf("Erro no quinto caso de chama_menu!\n");
    return 0;
  }

  ret = chama_menu(escolha, 1);
  if (ret != CHAMA_MENU_OK){
    printf("Erro no sexto caso de chama_menu!\n");
    return 0;
  }

  printf("Teste de chama_menu OK\n");
  free(escolha);
  return 0;
}

int teste_fecha_jogo(void){
  int aposta, resume, ret;
  
  aposta = -1;
  ret = fecha_jogo(aposta, 1);
  if (ret != FECHA_JOGO_PARAM_APOSTA_INVALIDO){
    printf("Erro no primeiro caso de fecha_jogo!\n");
    return 0;
  }
  
  ret = fecha_jogo(2500, 2);
  if (ret != FECHA_JOGO_PARAM_RESUME_INVALIDO){
    printf("Erro no segundo caso de fecha_jogo!\n");
    return 0;
  }

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
    printf("Erro no terceiro caso de fecha_jogo!\n");
    return 0;
  }

  resume = 0;
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    printf("Erro no quarto caso de fecha_jogo!\n");
    return 0;
  }

  inicia_jogo(&resume, &aposta);
  resume = 1;
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    printf("Erro no quinto caso de fecha_jogo!\n");
    return 0;
  }

  resume = 0;
  ret = fecha_jogo(aposta, resume);
  if (ret != FECHA_JOGO_OK){
    printf("Erro no sexto caso de fecha_jogo!\n");
    return 0;
  }

  printf("Teste de fecha_jogo OK\n");
  return 0;
}

int teste_inicia_rodada(void){
  int aposta, ret;

  ret = inicia_rodada(NULL);
  if (ret != INICIA_PARAM_APOSTA_INVALIDO){
    printf("Erro no primeiro caso de inicia_rodada!\n");
    return 0;
  }

  ret = inicia_rodada(&aposta);
  if (ret != INICIA_OK){
    printf("Erro no segundo caso de inicia_rodada!\n");
    return 0;
  }

  printf("Teste de inicia_rodada OK\n");
  return 0;
}

int teste_turno_usuario(void){
  int aposta, voltar_menu, ret, resume;
  inicia_jogo(&resume, &aposta);

  ret = turno_usuario(-3, &voltar_menu);
  if (ret != USUARIO_PARAM_APOSTA_INVALIDO){
    printf("Erro no primeiro caso de turno_usuario!\n");
    return 0;
  }

  ret = turno_usuario(50, NULL);
  if (ret != USUARIO_PARAM_VOLTAR_MENU_INVALIDO){
    printf("Erro no segundo caso de turno_usuario!\n");
    return 0;
  }

  ret = turno_usuario(50, &voltar_menu);
  if (ret != USUARIO_OK){
    printf("Erro no terceiro ou quarto caso de turno_usuario!\n");
    return 0;
  }

  ret = turno_usuario(50, &voltar_menu);
  if (ret != USUARIO_OK || voltar_menu != 1){
    printf("Erro no quinto caso de turno_usuario!\n");
    return 0;
  }

  ret = turno_usuario(50, &voltar_menu);
  if (ret != USUARIO_OK){
    printf("Erro no sexto caso de turno_usuario!\n");
    return 0;
  }

  printf("Teste de turno_usuario OK!\n");
  return 0;
}

int teste_turno_dealer(void){
  int aposta, ret, resume;
  inicia_jogo(&resume, &aposta);

  ret = turno_dealer(-3);
  if (ret != DEALER_PARAM_APOSTA_INVALIDO){
    printf("Erro no primeiro caso de turno_dealer!\n");
    return 0;
  }

  ret = turno_dealer(50);
  if (ret != DEALER_OK){
    printf("Erro no segundo caso de turno_dealer!\n");
    return 0;
  }

  printf("Teste de turno_dealer OK!\n");
  return 0;
}
//fim_cond_ret fim_de_rodada(int aposta, int* deseja_continuar, int* resume);
int teste_fim_de_rodada(void){
  int ret, aposta, deseja_continuar, resume;
  Espelho_Jogador jogadores[2], jogadorAux;
  inicializa_baralho(NULL);

  ret = fim_de_rodada(-3, &deseja_continuar, &resume);
  if (ret != FIM_PARAM_APOSTA_INVALIDO){
    printf("Erro no primeiro caso de fim_de_rodada!\n");
    return 0;
  }

  ret = fim_de_rodada(50, NULL, &resume);
  if (ret != FIM_PARAM_CONTINUAR_INVALIDO){
    printf("Erro no segundo caso de fim_de_rodada!\n");
    return 0;
  }

  ret = fim_de_rodada(50, &deseja_continuar, NULL);
  if (ret != FIM_PARAM_RESUME_INVALIDO){
    printf("Erro no terceiro caso de fim_de_rodada!\n");
    return 0;
  }

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

  inicializa_jogador(jogadores);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2500){
    printf("Erro no terceiro caso de fim_de_rodada!\n");
    return 0;
  }

  jogadores[0].v_mao[0] = (Carta*)malloc(sizeof(Carta));
  jogadores[0].v_mao[0]->naipe = 0;
  jogadores[0].v_mao[0]->valor_naipe = 1;
  jogadores[0].v_mao[0]->revelada = 1;

  inicializa_jogador(jogadores);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2550){
    printf("Erro no quarto caso de fim_de_rodada!\n");
    return 0;
  }

  jogadores[0].v_mao[1] = (Carta*)malloc(sizeof(Carta));
  jogadores[0].v_mao[1]->naipe = 0;
  jogadores[0].v_mao[1]->valor_naipe = 5;
  jogadores[0].v_mao[1]->revelada = 1;

  inicializa_jogador(jogadores);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2600){
    printf("Erro no quinto caso de fim_de_rodada!\n");
    return 0;
  }

  jogadores[0].v_mao[2] = (Carta*)malloc(sizeof(Carta));
  jogadores[0].v_mao[2]->naipe = 0;
  jogadores[0].v_mao[2]->valor_naipe = 5;
  jogadores[0].v_mao[2]->revelada = 1;

  inicializa_jogador(jogadores);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);
  ler_jogador(0, &jogadorAux);
  if (ret != FIM_OK || jogadorAux.dinheiro_total != 2625){
    printf("Erro no sexto caso de fim_de_rodada!\n");
    return 0;
  }

  Carta* baralho[52];
  for (int i = 0; i<52; i++)
    baralho[i] = NULL;

  baralho[0] = jogadores[0].v_mao[2];
  inicializa_baralho(baralho);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);  
  if (ret != FIM_OK){
    printf("Erro no sétimo caso de fim_de_rodada!\n");
    return 0;
  }

  free(jogadores[0].v_mao[2]);
  jogadores[0].v_mao[2] = NULL;
  free(jogadores[0].v_mao[1]);
  jogadores[0].v_mao[1] = NULL;
  free(jogadores[0].v_mao[0]);
  jogadores[0].v_mao[0] = NULL;
  jogadores[0].dinheiro_total = 0;
  inicializa_jogador(jogadores);

  ret = fim_de_rodada(50, &deseja_continuar, &resume);  
  if (ret != FIM_OK){
    printf("Erro no oitavo caso de fim_de_rodada!\n");
    return 0;
  }

  free(jogadores[1].v_mao[0]);

  printf("Teste de fim_de_rodada OK!\n");
  return 0;
}
