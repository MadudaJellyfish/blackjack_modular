#ifndef JOGADOR_H
#define JOGADOR_H
#include "baralho.h"

typedef struct jogador Jogador;

struct espel_jogador
{
    Carta* v_mao[11]; // ponteiro para as cartas na mão do jogador, máximo de 11 cartas
    int dinheiro_total; // Dinheiro do jogador
};

typedef struct espel_jogador Espelho_Jogador;

//todas a funções presentes aqui são funções de acesso para os clientes

typedef enum 
{
    PONTUACAO_CORR = 1,
    PONTUACAO_INCORR,
    CALC_JOGADOR_INIC_INCORR,
    CALC_VALOR_INVAL,
    CALC_JOGADOR_INVAL,


} calc_returns;

/*
Objetivo: O objetivo desta função é calcular a pontuação atual do jogador dependendo
das suas cartas atuais

Descrição: 
1.Dependendo do tipo do jogador passado como parâmetro a função calcula a pontuação desse jogador
2. Se o tipo_jogador for 0 é calculada a pontuação do usuário, se for 1 é calculada a pontuação do
dealer
3. Os pontos dos jogadores depende apenas de quais cartas estão em sua posse
4. A função leva em conta qual a pontuação atual do jogador, pois o valor do "Ás" pode mudar a depen-
der de quantos pontos o jogador possui

Acoplamentos:

--> Parâmetros: 
    int tipo_jogador: especificar qual o tipo do jogador que deve ser acessado pelo módulo Jogador
    int* valor: variável que "devolve" o valor calculado para o cliente

-->Retornos: 
    - 0 caso a pontuação tenha sido calculada corretamente;
    - 1 caso a pontuação tenha sido calculada errado;
    - 2 caso o jogador não esteja inicializado corretamente;
    - 3 caso o parâmetro de valor seja inválido;
    - 4 caso o parâmetro jogador seja inválido;

Condições de aclopamento: 

--> Assertivas de entrada:
    - O valor recebido no primeiro parâmetro, tipo_jogador, necessita ser um inteiro i tal que i pertença ao conjunto {0 (player), 1 (dealer)}
    - O segundo parâmetro precisa ser um ponteiro para um inteiro


--> Assertivas de saída:
    - O valor da pontuação do jogador é calculado corretamento e retornado ao módulo cliente através do ponteiro para int recebido
    como parâmetro
*/


calc_returns calcula_pontuacao(int tipo_jogador, int* valor);

typedef enum
{
    LER_JOGADOR_CORR = 1,
    LER_JOGADOR_INCORR,
    LER_JOGADOR_INIC_INCORR,
    LER_TIPO_INVAL,
    LER_JOGADOR_INVAL,


} ler_returns;

/*
Objetivo: A função Ler_Jogador é responsável por fornecer as informações de um jogador específico. 

Descrição:
1. Esta função recupera os dados de um jogador (usuário ou dealer) e os "devolve" através de um ponteiro para uma estrutura `tpJogador`. 
2. O parâmetro 'tipo' especifica qual jogador deve ser acessado. 

Acoplamentos:

--> Parâmetros:
    int tipo: inteiro que define qual jogador se deseja obter as informações (0 para usuário, 1 para dealer). 
    tpJogador* jogador: ponteiro para uma estrutura onde as informações do jogador serão copiadas. 

-->Retornos:
    - 0 caso o jogador tenha sido devolvido com sucesso. 
    - 1 caso o jogador devolvido não esteja correto. 
    - 2 caso o parâmetro 'jogador' (o ponteiro para a struct) seja inválido. 
    - 3 caso o parâmetro 'tipo' seja inválido. 

Condições de acoplamento:

--> Assertivas de entrada:
    - O valor recebido no primeiro parâmetro, 'tipo', necessita ser um inteiro i tal que i pertença ao conjunto {0 (usuário), 1 (dealer)}. 
    - O segundo parâmetro, 'jogador', precisa ser um ponteiro válido para uma estrutura `tpJogador`.

--> Assertivas de saída:
    - As informações do jogador solicitado são preenchidas corretamente na estrutura apontada por 'jogador', e a função retorna o status da operação.
*/

ler_returns ler_jogador(int tipo_jogador, Espelho_Jogador* jogador);

typedef enum 
{
    ADIC_CARTA_ADIC_CORR = 1,
    ADIC_RETIRA_CARTAS_INCORR,
    ADIC_QTD_CARTAS_INV,
    ADIC_JOGADOR_INIC_INCORR,
    ADIC_JOGADOR_INVAL,


} adic_returns;

/*
Objetivo: A função Adiciona_Carta é responsável por retirar cartas do baralho e adicioná-las à mão de um jogador (dealer(1) ou player(0)). 

Descrição:
1. Esta função gerencia a distribuição de cartas do baralho para a mão do jogador especificado no primeiro parâmetro da função. 
2. O número de cartas a serem adicionadas pode ser 1 ou 2. 
3. O parâmetro 'jogador' define se as cartas serão adicionadas ao player (0) ou ao dealer (1). 

Acoplamentos:

--> Parâmetros:
    int qtd_cartas: inteiro que especifica a quantidade de cartas a serem adicionadas (1 ou 2). 
    int jogador: inteiro que define qual jogador receberá as cartas (0 para player, 1 para dealer). 

-->Retornos:
    - 0 caso a carta tenha sido adicionada com sucesso. 
    - 2 caso a função interna "Retira_Cartas" não funcione corretamente. 
    - 3 caso a quantidade de cartas seja inválida (não seja 1 ou 2). 
    - 4 caso o jogador não esteja inicializado corretamente. 
    - 5 caso o parâmetro 'jogador' seja inválido (não seja 0 ou 1). 

Condições de acoplamento:

--> Assertivas de entrada:
    - O valor recebido no parâmetro 'qtd_cartas' necessita ser um inteiro i tal que i pertença ao conjunto {1, 2}. 
    - O valor recebido no parâmetro 'jogador' necessita ser um inteiro j tal que j pertença ao conjunto {0 (player), 1 (dealer)}. 

--> Assertivas de saída:
    - As cartas são adicionadas corretamente à mão do jogador especificado, se todas as condições de entrada forem satisfeitas e as operações internas forem bem-sucedidas.
*/


adic_returns adiciona_carta(int qtd_cartas, int tipo_jogador);

typedef enum
{
    LIMPA_CARTA_REMOV_CORR = 1,
    LIMPA_CARTA_REMOV_INCORR,
    LIMPA_TIPO_JOGADOR_INVAL,


} limpa_returns;

/*
Objetivo: A função Limpa_Mão é responsável por remover todas as cartas da mão de um jogador desejado. 

Descrição:
1. Esta função reinicializa ou esvazia a "mão" de cartas de um jogador específico. 
2. O parâmetro 'jogador' permite especificar se a mão do usuário ou do dealer será limpa.

Acoplamentos:

--> Parâmetros:
    int jogador: inteiro que define qual jogador terá suas cartas removidas da mão. 

-->Retornos:
    - 0 caso as cartas tenham sido removidas com sucesso. 
    - 1 caso as cartas não tenham sido removidas. 
    - 2 caso o parâmetro 'jogador' seja inválido. 

Condições de acoplamento:

--> Assertivas de entrada:
    - O valor recebido no parâmetro 'jogador' necessita ser um inteiro i tal que i pertença ao conjunto {0 (usuário), 1 (dealer)}.

--> Assertivas de saída:
    - A mão do jogador especificado é esvaziada corretamente, e a função retorna o status da operação.
*/

limpa_returns limpa_mao(int tipo_jogador);

typedef enum 
{
    CARTAS_REVEL_CORR = 1,
    CARTAS_REVEL_INCORR,
    REVELA_JOGADOR_INVAL,

} revela_returns;

/*
Objetivo: A função Revela_Cartas é responsável por marcar que as cartas de um jogador serão exibidas na interface. 

Descrição:
1. Esta função define um sinalizador ou estado que indica que as cartas do jogador especificado devem ser visíveis para o usuário na interface do jogo. 
2. O parâmetro 'jogador' permite especificar se as cartas do usuário (0) ou do dealer (1) serão reveladas. 

Acoplamentos:

--> Parâmetros:
    int jogador: inteiro que define qual jogador terá suas cartas marcadas para revelação (0 para usuário, 1 para dealer). 

-->Retornos:
    - 0 caso as cartas tenham sido marcadas para revelar com sucesso. 
    - 1 caso as cartas não tenham sido marcadas para revelar. 
    - 2 caso o parâmetro 'jogador' seja inválido. 

Condições de acoplamento:

--> Assertivas de entrada:
    - O valor recebido no parâmetro 'jogador' necessita ser um inteiro i tal que i pertença ao conjunto {0 (usuário), 1 (dealer)}. 

--> Assertivas de saída:
    - O estado de revelação das cartas do jogador é definido corretamente, e a função retorna o status da operação.
*/

revela_returns revela_cartas(int tipo_jogador);

typedef enum
{
    ALTERA_DINHEIRO_ALT_CORR = 1,
    ALTERA_DINHEIRO_ALT_INCORR,
    ALTERA_VALOR_INVAL,
    ALTERA_JOGADOR_INVAL,

} altera_returns;

/*
Objetivo: A função Altera_Dinheiro é responsável por modificar o valor do dinheiro restante do player. 

Descrição:
    1. Esta função adiciona ou subtrai um valor recebido pela função do total de dinheiro do jogador. 
    2. O 'valor' pode ser positivo (para adicionar dinheiro) ou negativo (para subtrair/apostar).

Acoplamentos:

--> Parâmetros:
    int valor: inteiro que representa a quantia de dinheiro a ser adicionada (ou subtraída) ao total do jogador. 

-->Retornos:
    - 0 caso o dinheiro tenha sido alterado corretamente. 
    - 1 caso o jogador não esteja inicializado corretamente. 
    - 2 caso o valor da aposta (parâmetro 'valor') seja inválido. 

Condições de acoplamento:

--> Assertivas de entrada:
    - O parâmetro 'valor' deve ser um inteiro válido para a operação de alteração de dinheiro (o valor do dinheiro do usuário não pode ser maior que 999999).

--> Assertivas de saída:
    - O dinheiro do jogador é atualizado corretamente de acordo com o 'valor' fornecido, e o status da operação é retornado.
*/

altera_returns altera_dinheiro(int valor);

typedef enum 
{
    INICIA_JOGADORES_INIC_CORR = 1,
    INICIA_JOGADOR_N_INIC,

} inicializa_returns;

/*
Objetivo: A função Inicializa_Jogador é responsável por inicializar os jogadores com os seus valores iniciais. 

Descrição:
    1. Esta função configura o estado inicial dos jogadores do jogo. 
    2. A função repassa esses valores configurados ao espelho da estrutura do módulo do Jogador recebido com parâmetro para o módulo cliente. 

Acoplamentos:

--> Parâmetros:
    Jogador* v_jogadores: esse parâmetro recebe os valores configurados armazenados dentro do módulo Jogador para o usuário e o dealer
    e devolve esses valores ao módulo cliente que chamou a função inicializa_jogador.

-->Retornos:
    - 0 caso o jogador tenha sido inicializado corretamente. 
    - 1 caso o jogador não tenha sido inicializado. 
    - 2 caso o jogador tenha sido inicializado com as informações erradas. 

Condições de acoplamento:

--> Assertivas de entrada:
    - Jogador* v_jogadores é não nulo.
    - Jogador* v_jogadores é um vetor de apenas duas posições.

--> Assertivas de saída:
    - Os jogadores são inicializados corretamente e o módulo cliente recebe o espelho das estrutura de dados do dealer e do usuário
*/

inicializa_returns inicializa_jogador(Espelho_Jogador* player, Espelho_Jogador* dealer);

/*
Objetivo:
    Liberar toda a memoria alocada dinamicamente para as cartas e jogadores, e resetar o estado do modulo Jogador.

Descricao:
    1. A funcao percorre o vetor de ponteiros de cartas dos jogadores e o vetor de jogadores.
    2. Para cada ponteiro de carta valido, a função chama free() para liberar a memoria alocada individualmente.
    3. Apos liberar toda a memoria, reseta o estado do modulo para "nao inicializado", a fim de prevenir erros.
    4. Esta funcao deve ser chamada ao final do jogo para evitar vazamentos de memoria 

Acoplamento:
- Parametros:
    Nenhum.

- Retorno:
    0 caso os jogadores sejam liberados corretamente.
    1 caso os jogadores não estejam inicializados.

Condicao de acoplamento:
- Assertiva de entrada:
    Nenhuma.

- Assertiva de saida:
    1. Toda a memoria que foi alocada dinamicamente para as cartas e jogadores devolvida ao sistema.
    2. O modulo Jogadore e logicamente resetado ao seu estado "nao inicializado", prevenindo o uso de ponteiros agora invalidos.
*/

int free_jogadores(void);

#endif 
