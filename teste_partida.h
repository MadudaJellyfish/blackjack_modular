#ifndef TESTE_PARTIDA_H
#define TESTE_PARTIDA_H

int teste_inicia_jogo(void);
/*
Casos Abstratos:
    1. Valores desejados inicializados.
    2. Parâmetros inválidos.
    3. Inicialização sem arquivo de dados.
    4. Arquivo não em formato json.

Casos Semânticos:
    1. Chama sem arquivo.
    2 e 3. Cria arquivo vazio e chama com ponteiros nulos.
    4. Chama com arquivo em formato não json.
    5. Chama função com parâmetros válidos.
*/

int teste_chama_menu(void);
/*
Casos Abstratos:
    1. Parâmetros inválidos.
    2. Dados mantidos ao continuar jogo.
    3. Dados reiniciados ao default em novo jogo.
    4. Escolha de fechar jogo mantida.

Casos Valorados:
    1 e 2. Chama com parâmetros inválidos.
    3. Chama com escolha continuar e com dados.
    4. Chama com escolha novo jogo.
    5. Chama com escolha sair.
*/

int teste_fecha_jogo(void);
/*
Casos Abstratos:
    1. Parâmetros inválidos
    2. Escolha de salvar dados anteriores com dados
    3. Escolha de não salvar dados anteriores com dados
    4. Escolha de salvar dados anteriores sem dados
    5. Escolha de não salvar dados anteriores sem dados

Casos Valorados:
    1 e 2. Chama com parâmetros inválidos
    3. Inicia o jogo com dados anteriores e chama a função escolhendo salvar
    4. Inicia o jogo com dados anteriores e chama a função escolhendo não salvar
    5. Inicia o jogo sem dados anteriores e chama a função escolhendo salvar
    6. Inicia o jogo sem dados anteriores e chama a função escolhendo não salvar
*/

int teste_inicia_rodada(void);
/*
Casos Abstratos:
    1. Parâmetros inválidos

Casos Valorados:
    1. Chama com parâmetros inválidos
    2. Chama com parâmetros válidos
*/

int teste_turno_usuario(void);
/*
Casos Abstratos:
    1. Parâmetros inválidos
    2. Comprar carta
    3. Escolher stand
    4. Escolher voltar ao menu
    5. Comprar até ter 21
    6. Comprar até passar de 21

Casos Valorados:
    1 e 2. Chama com parâmetros inválidos
    3. Chama e compra uma carta
    4. Escolhe stand
    5. Chama e escolhe voltar ao menu
    6. Chama e compra até ter 21 ou mais
*/

int teste_turno_dealer(void);
/*
Casos Abstratos:
    1. Parâmetros inválidos
    2. Chamar normalmente

Casos Valorados:
    1. Chama com parâmetros inválidos
    2. Chama normalmente
*/

int teste_fim_de_rodada(void);
/*
Casos Abstratos:
    1. Parâmetros inválidos
    2. Usuário perde
    3. Usuário ganha
    4. Usuário ganha com blackjack
    5. Baralho termina com 20 ou menos cartas
    6. Usuário termina sem dinheiro

Casos Valorados:
    1 2 e 3. Chama com parâmetros inválidos
    4. Chama com o dealer com pontuação que ganha do usuário
    5. Chama com o dealer com pontuação que empata com o usuário
    6. Chama com o usuário com pontuação que ganha do dealer
    7. Chama com o usuário com pontuação de blackjack que ganha do dealer
    8. Chama com o baralho iniciado com 20 cartas
    9. Chama com o usuário perdendo e com 0 dinheiros
*/

int teste_libera_jogador(void);
/*
Casos Abstratos:
    1. Chamada da função

Casos Valorados:
    1. Chamada da função
    2. Chamada com o jogador não inicializado
*/

int teste_free_baralho(void);
/*
Casos Abstratos:
    1. Chamada da função

Casos Valorados:
    1. Chamada da função
    2. Chamada com o baralho não inicializado
*/

void teste_inicializa_jogadores(void);
/*
Casos Abstratos:
    1. Inicialização com ponteiros válidos
    2. Inicialização com ponteiros nulos

Casos Valorados:
    1. Jogador com dinheiro total 2500 e dealer com 0
    2. Ponteiro do jogador é NULL
*/

void teste_calcula_pontuacao(void);
/*
Casos Abstratos:
    1. Jogador com mão vazia
    2. Jogador inválido
    3. Ponteiro de retorno de pontuação nulo

Casos Valorados:
    1. Valor nulo no ponteiro de pontuação
    2. Jogador inválido (tipo 3)
    3. Jogador 0 com mão vazia deve retornar pontuação 0
*/

void teste_adiciona_carta(void);
/*
Casos Abstratos:
    1. Adicionar 1 ou 2 cartas
    2. Adicionar quantidade inválida (>2)
    3. Jogador inválido

Casos Valorados:
    1. Adicionar 2 cartas ao jogador 0
    2. Adicionar 3 cartas deve retornar erro
    3. Jogador 2 (inválido)
*/

void teste_limpa_mao(void);
/*
Casos Abstratos:
    1. Jogador com mão preenchida
    2. Jogador inválido

Casos Valorados:
    1. Limpar mão do jogador 0
    2. Limpar mão do jogador 1
    3. Jogador inválido (tipo 5)
*/

void teste_revela_cartas(void);
/*
Casos Abstratos:
    1. Jogador com cartas não reveladas
    2. Jogador inválido

Casos Valorados:
    1. Jogador 0 com uma carta não revelada passa a revelada
    2. Jogador inválido (-1)
*/

void teste_altera_dinheiro(void);
/*
Casos Abstratos:
    1. Alteração positiva
    2. Alteração negativa
    3. Valor fora do intervalo aceitável

Casos Valorados:
    1. Adicionar 500 ao jogador
    2. Subtrair 1000 do jogador
    3. Adicionar 1.000.000 (erro)
*/

void teste_free_jogador(void);
/*
Casos Abstratos:
    1. Chamada da função

Casos Valorados:
    1. Chamada da função
    2. Chamada com o jogador não inicializado
*/

///

void teste_inicializa_baralho(void);
/*
Casos Abstratos:
    1. Inicialização padrão de baralho com 52 cartas

Casos Valorados:
    1. Chamada com seed nula e baralho padrão
*/


void teste_obter_cartas_restantes(void);
/*
Casos Abstratos:
    1. Baralho inicializado
    2. Parâmetros inválidos

Casos Valorados:
    1. Obter cartas de baralho recém inicializado (52 cartas)
    2. Chamar com vetor de cartas nulo
    3. Chamar com vetor de quantidade nulo
*/

void teste_retira_cartas(void);
/*
Casos Abstratos:
    1. Retirada de cartas de baralho com cartas
    2. Retidada de mais cartas que existem no baralho
    3. Retirada de quantidade inválida
    4. Chamada com ponteiro de saída inválido
    5. Retirada de um baralho vazio

Casos Valorados:
    1. Retirar 5 carta do baralho de 52 cartas
    2. Tentar retirar 50 cartas de um baralho de 47
    3. Tentar retirar -2 cartas
    4. Chamar com vetor de saída nulo
    5. Esvaziar o baralho e tentar retirar uma carta
*/


void teste_embaralha_cartas(void);
/*
Casos Abstratos:
    1. Baralho com cartas
    2. Baralho vazio

Casos Valorados:
    1. Embaralhar baralho com 52 cartas
    2. Embaralhar baralho vazio
*/

void teste_baralho_vazio(void);
/*
Casos Abstratos:
    1. Verificar se baralho está vazio
    2. Baralho não inicializado

Casos Valorados:
    1. Verificar baralho inicializado como não vazio
    2. Após esvaziar e deixar com 20 cartas (limite), verificar se função retorna que está vazio
    3. Após deixar com 19 cartas, verificar se função retorna que está vazio
*/

void teste_libera_baralho(void);
/*
Casos Abstratos:
    1. Chamada da função

Casos Valorados:
    1. Chamada da função
    2. Chamada com o baralho não inicializado
*/

/*
===============================================================================
Testes do módulo INTERFACE
===============================================================================
*/

int teste_interface_menu_principal(void);
/*
Casos Abstratos:
    1. Entrada válida com resume = 1.
    2. Entrada inválida (resume = 0 e escolha = 1).
    3. Parâmetro *escolha inválido (NULL).
    4. Parâmetro resume inválido (≠ 0 e ≠ 1).

Casos Valorados:
    - Escolhas 0 e 2 aceitas com resume = 1.
    - Escolha 1 rejeitada com resume = 0.
    - Retorna -1 para ponteiros inválidos ou resume fora do domínio.
*/

int teste_interface_define_aposta(void);
/*
Casos Abstratos:
    1. Entrada de aposta válida dentro do limite.
    2. Entrada inválida: valor acima do disponível.
    3. Parâmetro *aposta inválido (NULL).
    4. Parâmetro dinheiro_disponivel inválido (≤ 0).

Casos Valorados:
    - Aposta de 100 com R$1000 disponíveis → sucesso.
    - Entrada inválida (ex: aposta 0 ou maior que disponível) → rejeitada.
    - Retorna -1 em caso de ponteiro nulo ou dinheiro_disponivel ≤ 0.
*/

int teste_interface_rodada(void);
/*
Casos Abstratos:
    1. Jogador escolhe: comprar, stand ou voltar.
    2. Dealer apenas imprime cartas.
    3. Parâmetro *jogada inválido (NULL).
    4. Parâmetro tipo_jogador inválido (≠ 0 e ≠ 1).
    5. Parâmetro aposta inválido (< 0).

Casos Valorados:
    - Jogador escolhe 1 e depois 0.
    - Dealer imprime pontuação e cartas.
    - Retorna -1 para qualquer entrada inválida.
*/

int teste_interface_fim(void);
/*
Casos Abstratos:
    1. Resultados: derrota, vitória, blackjack, empate.
    2. Jogador decide continuar ou sair.
    3. Parâmetro *deseja_continuar inválido (NULL).
    4. Resultado fora do domínio (≠ 0,1,2,3).
    5. Aposta inválida (< 0).

Casos Valorados:
    - Vitória com aposta → exibe prêmio.
    - Empate → exibe mensagem.
    - Retorna -1 se ponteiro for NULL ou valores fora do domínio.
*/

int teste_interface_game_over(void);
/*
Casos Abstratos:
    1. Exibição da mensagem de fim do jogo.

Casos Valorados:
    - Apenas imprime "GAME OVER" e retorna 0.
    - Não possui validações ou parâmetros.
*/

int teste_interface_valor_naipe_to_string(void);
/*
Casos Abstratos:
    1. Conversão de valores válidos (1 a 13) em string.
    2. Conversão de naipes válidos (0 a 3) em string.
    3. Valores fora do domínio.

Casos Valorados:
    - valor = 1 → "A", 10 → "10", 12 → "Q".
    - naipe = 1 → "copas".
    - valor/naipe inválido → "desconhecido".
*/

///

#endif
