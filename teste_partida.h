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
    4. Continuar jogo sem dados prévios.
    5. Escolha de fechar jogo mantida.

Casos Valorados:
    1 e 2. Chama com parâmetros inválidos.
    3. Chama com escolha continuar e sem dados.
    4. Chama com escolha continuar e com dados.
    5. Chama com escolha novo jogo.
    6. Chama com escolha sair.
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

#endif
