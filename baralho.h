#ifndef BARALHO_H
#define BARALHO_H

struct carta
{
    int naipe; // 0 a 3 representando os naipes
    int valor_naipe; // 1 a 13 representando os valores das cartas    
    int revelada; // 0 para não revelada, 1 para revelada

};

typedef struct carta Carta;


int inicializa_baralho(Carta* cartas_salvas[], int qtd_cartas);
/*
Objetivo:
    Inicializar o baralho, seja com um conjunto de 52 cartas novas ou a partir de um estado de jogo salvo.

Descricao:
    1. Se o ponteiro 'cartas_salvas' for NULO, a funcao deve preencher o baralho com 52 cartas.
    2. Se 'cartas_salvas' for fornecido, a funcao deve preencher o baralho com as 'qtd_cartas' especificas do vetor.
    3. O baralho deve ser composto por 4 naipes, cada um contendo 13 cartas com valores numericos diferentes.

Acoplamento:
- Parametros:
    Carta* cartas_salvas: Um ponteiro para um vetor de cartas de um jogo salvo. Passar NULL para criar um baralho novo.
    int qtd_cartas: A quantidade de cartas no vetor 'cartas_salvas'. Ignorado se 'cartas_salvas' for NULL.

- Retornos:
    0 caso o baralho tenha sido iniciado corretamente.
    1 caso tenha ocorrido uma falha na inicializacao.
    2 caso os parametro para carregar o jogo sejam invalido (ex: qtd_cartas < 0).

Condicao de acoplamento:
- Assertiva de entrada:
    1. Se estiver carregando um jogo (cartas_salvas != NULL), o ponteiro deve ser valido e 'qtd_cartas' deve ser um numero entre 0 e 52.

- Assertiva de saida:
    1. Se a funcao retornar 0, a variavel global 'baralho' conterá as cartas apropriadas (52 novas ou 'qtd_cartas' carregadas).
    2. Se a funcao retornar 1 ou 2, o estado do baralho é considerado inválido.
*/

int obter_cartas_restantes(Carta* v_cartas_saida[], int* qtd_saida);
/*
Objetivo:
    Obter o vetor de todas as cartas que ainda estao no baralho para permitir salvar o jogo.

Descricao:
    1. A funcao deve copiar todas as cartas restantes na variavel global 'baralho' para o vetor de saida 'v_cartas_saida'.
    2. A quantidade de cartas copiadas deve ser armazenada no ponteiro 'qtd_saida'.

Acoplamento:
- Parametros:
    Carta* v_cartas_saida: Ponteiro para um vetor onde as cartas restantes serao copiadas.
    int* qtd_saida: Ponteiro para um inteiro onde a quantidade de cartas copiadas sera armazenada.

- Retorno:
    0 caso as cartas tenham sido obtidas com sucesso.
    1 caso os ponteiros de parâmetro sejam inválidos (NULL).
    2 caso o baralho não esteja inicializado.

Condicao de acoplamento:
- Assertiva de entrada:
    1. O ponteiro 'v_cartas_saida' deve apontar para uma area de memoria capaz de armazenar ate 52 cartas.
    2. O ponteiro 'qtd_saida' nao deve ser nulo.
    3. O baralho deve estar inicializado.

- Assertiva de saida:
    1. Se a funcao retornar 0, 'v_cartas_saida' contem as cartas do baralho e 'qtd_saida' contem o numero exato dessas cartas.
    2. Se a funcao retornar um valor diferente de 0, os dados nos ponteiros de saida sao indefinidos.
*/


int embaralha_cartas(void);
/*
Objetivo:
    Randomizar a ordem das cartas contidas na estrutura baralho

Descricao:
    1. A funcao deve verificar se o baralho foi devidamente inicializado antes de embaralhar
    2. A funcao deve alterar aleatoriamente a posicao das cartas na estrutura

Acoplamento:
- Parametros:
    Nenhum, age sobre a variavel global estatica baralho

- Retorno:
    0 caso tenha embaralhado corretamente
    1 caso nao tenha sido embaralhada corretamente
    2 caso o baralho nao tenha sido inicializado

Condicao de acoplamento:
- Assertiva de entrada:
    A funcao deve ter sido incializada com sucesso em inicializa_baralho

- Assertiva de saida:
    1. Se a funcao retornar 0 o baralho foi randomizado
    2. Se a funcao retornar 2 o baralho nao foi inicializado
 */

int retira_cartas(Carta* v_cartas[], int qtd_ditr);
/*
Objetivo:
    Retirar uma quantidade especifica de cartas do baralho para ser usada

Descricao:
    1. A funcao deve remover uma quantidade especifica de cartas do baralho
    2. As cartas removidas devem ser colocadas em um vetor de cartas v_cartas fornecido de parametro
    3. A funcao deve validar o estado do baralho e os parametros recebidos antes de realizar a retirada

Acoplamento:
- Parametro:
    Carta v_cartas[]: Vetor onde as cartas sao armazenadas
    int qtd_distr: Quantidade de cartas que devem ser retiradas

- Retornos
    0 caso tenham sido retiradas corretamente
    1 caso nao tenha sido retirado corretamente
    2 caso o baralho nao tenha sido inicializado
    3 caso qtd_distr seja invalido
    4 caso o baralho esteja vazio
    5 caso v_cartas seja invalido

Condicao de acoplamento:
- Assertiva de entrada:
    1. O ponteiro v_cartas nao deve ser nulo e apontar para uma memoria vazia
    2. O valor qtd_distr deve ser um inteiro positivo
    3. O baralho deve estar inicializado e nao vazio

- Assertiva de saida:
    1. Se a funcao retornar 0, v_cartas contera a qtd_distr cartas retiradas e a contagem do baralho original sera decrementada
    2. Se a funcao retornar diferente de 0, o estado do baralho e vetor sera inalterado
 */
int baralho_vazio(void);
/*
Objetivo:
    Verificar se o tamanho do baralho diminuiu ao limite maximo que exige reembaralhar

Descricao:
    1. A funcao deve compara a quantidade de cartas restantes no baralho a 20 e retorna de acordo com o resultado

Acoplamento:
- Paramentro:
    Nenhun, utiliza a varivael global estatica baralho

- Retornos:
    0 caso o baralho tenha mais de 20 cartas
    1 caso o baralho tenha menos de 20 cartas
    2 caso o baralho nao tenha sido incializado corretamente

Condicao de acoplamento:
- Assertivas de entrada:
    1. O baralho deve ter sido inicializado

- Assertiva de saida:
    1. Se a funcao retornar 0, o baralho tem mais de 20 cartas e nao precisa reembaralhar
    2. Se a funcao retornar 1, o baralho tem menos de 20 cartas e precisa reembaralhar
    3. Se a funcao retornar 2 o baralho nao foi inicializado corretamente
 */
int libera_baralho(void);
/*
Objetivo:
    Liberar toda a memoria alocada dinamicamente para as cartas e resetar o estado do modulo Baralho.

Descricao:
    1. A funcao percorre o vetor de ponteiros de cartas do baralho.
    2. Para cada ponteiro de carta valido, a função chama free() para liberar a memoria alocada individualmente.
    3. Apos liberar toda a memoria, reseta o estado do modulo para "nao inicializado", a fim de prevenir erros.
    4. Esta funcao deve ser chamada ao final do jogo para evitar vazamentos de memoria 

Acoplamento:
- Parametros:
    Nenhum.

- Retorno:
    0 caso o baralho libere corretamente.
    1 caso o baralho não esteja inicializado.

Condicao de acoplamento:
- Assertiva de entrada:
    Nenhuma.

- Assertiva de saida:
    1. Toda a memoria que foi alocada dinamicamente para as cartas e devolvida ao sistema.
    2. O modulo Baralho e logicamente resetado ao seu estado "nao inicializado", prevenindo o uso de ponteiros agora invalidos.
*/
#endif
