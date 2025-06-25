#ifndef INTERFACE_H
#define INTERFACE_H

/*
===============================================================================
Módulo: Interface
===============================================================================
Objetivo:
Fornecer todas as funções de exibição e interação do usuário com o jogo de Blackjack
via terminal. Este módulo apresenta menus, cartas, resultados e mensagens
visuais relevantes, além de obter a escolha do jogador.

Descrição:
Este módulo atua como a camada de interface textual entre o jogador e o jogo.
Ele apresenta as informações da rodada, solicita decisões do jogador, exibe
o resultado final e trata situações como fim de jogo, exibição das cartas
e strings auxiliares para cartas e naipes.
*/

/*
------------------------------------------------------------------------------
Função: menu_principal
------------------------------------------------------------------------------
Objetivo:
Exibir o menu principal do jogo e capturar a escolha do jogador.

Acoplamento:
 - Parâmetros:
   *escolha: ponteiro para armazenar a opção do jogador.
   resume: inteiro que indica se há jogo salvo (0 = não, 1 = sim).

 - Retornos:
   0 se menu executado com sucesso;
   -1 caso ocorra erro ao obter a escolha.

Condições de Acoplamento:
 - Assertivas de Entrada:
   *escolha deve ser um ponteiro válido.
   resume deve ser 0 ou 1.

 - Assertivas de Saída:
   *escolha recebe 0 (novo jogo), 1 (continuar), ou 2 (sair).
*/
int menu_principal(int* escolha, int resume);

/*
------------------------------------------------------------------------------
Função: interface_rodada
------------------------------------------------------------------------------
Objetivo:
Exibir o estado atual da rodada e capturar a ação do jogador (hit, stand, menu).

Acoplamento:
 - Parâmetros:
   tipo_jogador: inteiro (0 = usuário, 1 = dealer).
   aposta: valor atual da aposta.
   *jogada: ponteiro para armazenar a decisão do jogador.

 - Retornos:
   0 se executado com sucesso;
   -1 em caso de falha ao processar entrada.

Condições de Acoplamento:
 - Assertivas de Entrada:
   tipo_jogador ∈ {0, 1}.
   aposta ≥ 0.
   *jogada deve ser ponteiro válido.

 - Assertivas de Saída:
   Se tipo_jogador == 0, *jogada ∈ {0, 1, 2}.
   Se tipo_jogador == 1, apenas exibe cartas.
*/
int interface_rodada(int tipo_jogador, int aposta, int* jogada);

/*
------------------------------------------------------------------------------
Função: define_aposta
------------------------------------------------------------------------------
Objetivo:
Solicitar ao jogador o valor da aposta e armazenar caso seja válido.

Acoplamento:
 - Parâmetros:
   *aposta: ponteiro onde será armazenado o valor apostado.
   dinheiro_disponivel: total de dinheiro disponível do jogador.

 - Retornos:
   0 se valor válido foi informado;
   -1 se valor inválido ou entrada incorreta.

Condições de Acoplamento:
 - Assertivas de Entrada:
   *aposta deve ser um ponteiro válido.
   dinheiro_disponivel ≥ 0.

 - Assertivas de Saída:
   *aposta contém valor ∈ [1, dinheiro_disponivel].
*/
int define_aposta(int* aposta, int dinheiro_disponivel);

/*
------------------------------------------------------------------------------
Função: interface_fim
------------------------------------------------------------------------------
Objetivo:
Exibir o resultado da rodada (vitória, derrota, empate) e perguntar se o jogador
deseja continuar jogando.

Acoplamento:
 - Parâmetros:
   resultado: inteiro ∈ {0 = derrota, 1 = vitória, 2 = blackjack, 3 = empate}.
   aposta: valor apostado na rodada.
   *deseja_continuar: ponteiro onde será armazenada a decisão do jogador.

 - Retornos:
   0 se executado com sucesso;
   -1 se entrada ou leitura inválida.

Condições de Acoplamento:
 - Assertivas de Entrada:
   resultado ∈ {0, 1, 2, 3}.
   aposta ≥ 0.
   *deseja_continuar deve ser ponteiro válido.

 - Assertivas de Saída:
   *deseja_continuar ∈ {0, 1}.
*/
int interface_fim(int resultado, int aposta, int* deseja_continuar);

/*
------------------------------------------------------------------------------
Função: game_over
------------------------------------------------------------------------------
Objetivo:
Exibir mensagem de fim de jogo ao jogador.

Acoplamento:
 - Parâmetros: nenhum.
 - Retornos:
   0 após exibir mensagem com sucesso.

Condições de Acoplamento:
 - Assertivas de Entrada: nenhuma.
 - Assertivas de Saída: mensagem “GAME OVER” exibida na tela.
*/
int game_over(void);

/*
------------------------------------------------------------------------------
Função: imprime_cartas
------------------------------------------------------------------------------
Objetivo:
Exibir as cartas reveladas na mão de um jogador.

Acoplamento:
 - Parâmetros:
   tipo_jogador: inteiro ∈ {0 = usuário, 1 = dealer}.

 - Retornos: nenhum.

Condições de Acoplamento:
 - Assertivas de Entrada:
   tipo_jogador ∈ {0, 1}.

 - Assertivas de Saída:
   As cartas reveladas são impressas corretamente com valor e naipe.
*/
void imprime_cartas(int tipo_jogador);

/*
------------------------------------------------------------------------------
Função: naipe_to_string
------------------------------------------------------------------------------
Objetivo:
Converter o valor numérico do naipe para seu nome textual correspondente.

Acoplamento:
 - Parâmetros:
   naipe: inteiro ∈ {0, 1, 2, 3}.

 - Retornos:
   String correspondente ao naipe ("Copas", "Espadas", etc).

Condições de Acoplamento:
 - Assertivas de Entrada:
   naipe ∈ {0, 1, 2, 3}.

 - Assertivas de Saída:
   String válida correspondente ao naipe.
*/
const char* naipe_to_string(int naipe);

/*
------------------------------------------------------------------------------
Função: valor_to_string
------------------------------------------------------------------------------
Objetivo:
Converter o valor numérico da carta para string ("A", "2"... "K").

Acoplamento:
 - Parâmetros:
   valor: inteiro ∈ [1, 13] (ou seja, de Ás a Rei)

 - Retornos:
   String correspondente ao valor da carta ("A", "2", ..., "10", "J", "Q", "K").

Condições de Acoplamento:
 - Assertivas de Entrada:
   valor ∈ [1, 13].

 - Assertivas de Saída:
   String válida correspondente ao valor.
*/
const char* valor_to_string(int valor);

#endif
