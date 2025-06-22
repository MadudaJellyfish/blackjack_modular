#ifndef PARTIDA_H
#define PARTIDA_H

typedef enum {
   FIM_OK = 0,
   FIM_VERIFICA_VENCEDOR_FALHA = 1,
   FIM_ALTERA_DINHEIRO_FALHA = 2,
   FIM_LER_JOGADOR_FALHA = 3,
   FIM_GAME_OVER_FALHA = 4,
   FIM_BARALHO_VAZIO_FALHA = 5,
   FIM_INICIALIZA_BARALHO_FALHA = 6,
   FIM_EMBARALHA_CARTAS_FALHA = 7,
   FIM_INTERFACE_FIM_FALHA = 8,
   FIM_PARAM_APOSTA_INVALIDO = 9,
   FIM_PARAM_CONTINUAR_INVALIDO = 10,
   FIM_FALHA_TERMINAR = 11,
   FIM_PARAM_RESUME_INVALIDO = 12
} fim_cond_ret;

fim_cond_ret fim_de_rodada(int aposta, int* deseja_continuar, int* resume);
/*
Objetivo:
Determinar o resultado da partida, alterando o dinheiro do usuário
como necessário. Caso o dinheiro seja 0, exibirá uma tela de 
game over, e, caso o jogador decida parar, o encaminhará para o menu principal.
Caso o baralho esteja com 20 ou menos cartas, ele retorna ao estado inicial e é embaralhado.

Descrição:
1. A vitória do jogador-usuário é validada seguindo as seguinte regra:
Se a soma das suas cartas for maior que a soma das cartas do dealer, então o jogador é o vencedor.
2. Após o fim de uma rodada são dadas as seguintes opções ao usuário: iniciar nova rodada ou ir ao menu principal.
3. Quando o usuário ganha, ele recebe 2x o dinheiro apostado na rodada.
4. Quando o usuário ganha com 21, ele recebe 2,5x o dinheiro apostado na rodada.
5. Quando o usuário perde, ele não recebe dinheiro de volta.
6. Quando o usuário fica com 0 dinheiros, o jogo exibe uma tela de Game Over e acaba a partida.
7. Se um jogador passa de 21 com a soma das  cartas, ele perde a rodada.
8. Se os dois jogadores passarem de 21 ou conseguirem a mesma soma das cartas, é um empate.
9. Se houver empate, o usuário recebe 1x o dinheiro apostado na rodada.
10. Quando uma rodada acaba com 20 ou menos cartas no baralho, ele volta para o estado inicial e é embaralhado.

Acoplamento:
 - Parâmetros:
   aposta: inteiro com a aposta da rodada para adicionar ao jogador.
   deseja_continuar: inteiro onde será armazenada a escolha de continuar do usuário.
   resume: inteiro que define se há como continuar o jogo ou se foi game over.

 - Retornos:
   0 caso o processo de encerrar a rodada tenha ocorrido com sucesso;
   1 caso a função chamada Verifica_Vencedor não funcione corretamente;
   2 caso a função chamada Altera_Dinheiro não funcione corretamente;
   3 caso a função chamada Ler_Jogador não funcione corretamente;
   4 caso a função chamada Game_Over não funcione corretamente;
   5 caso a função chamada Baralho_Vazio não funcione corretamente;
   6 caso a função chamada Inicializa_Baralho não funcione corretamente;
   7 caso a função chamada Embaralha_Cartas não funcione corretamente;
   8 caso a função Interface_Fim não funcione corretamente;
   9 caso o parâmetro de aposta seja inválido;
   10 caso o parâmetro de deseja_continuar seja inválido;
   11 caso a rodada continue após a função Game_Over;
   12 caso o parâmetro resume seja inválido

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. A aposta deve ser um valor inteiro positivo maior que 0.
   2. O ponteiro deseja_continuar deve ser não nulo.
   3. O ponteiro resume deve ser não nulo.

 - Assertivas de Saída:
   1. O dinheiro do jogador foi alterado corretamente conforme o resultado da rodada.
   2. A variável deseja_continuar contém 0 (parar) ou 1 (continuar).
   3. Se o jogador ficou com 0 de dinheiro, o jogo foi encerrado corretamente (Game Over exibido).
   4. Se o baralho tinha ≤ 20 cartas, ele foi reinicializado e embaralhado.
*/

typedef enum {
   INICIA_OK = 0,
   INICIA_DEFINE_APOSTA_FALHA = 1,
   INICIA_ALTERA_DINHEIRO_FALHA = 2,
   INICIA_LIMPA_MAO_FALHA = 3,
   INICIA_ADICIONA_CARTA_FALHA = 4,
   INICIA_REVELA_CARTAS_FALHA = 5,
   INICIA_PARAM_APOSTA_INVALIDO = 6
} inicia_cond_ret;

inicia_cond_ret inicia_rodada(int* aposta);
/*
Objetivo:
Função responsável por definir a aposta, retirando-a do dinheiro do 
usuário, limpar as mãos dos jogadores e distribuir as cartas iniciais, 
com uma do dealer não revelada.

Descrição:
1. O jogo é iniciado com duas cartas para o dealer e o usuário.
2. Antes da rodada ser iniciada, é perguntado ao usuário o valor de sua aposta para aquela rodada.
3. A segunda carta inicial do dealer começa virada para baixo.

Acoplamento:
 - Parâmetros:
   aposta: inteiro no qual a aposta da rodada será depositada;

 - Retornos:
   0 caso a rodada tenha sido iniciada com sucesso;
   1 caso a função chamada Define_Aposta não funcione corretamente;
   2 caso a função chamada Altera_Dinheiro não funcione corretamente;
   3 caso a função chamada Limpa_Mão não funcione corretamente;
   4 caso a função chamada Adiciona_Carta não funcione corretamente;
   5 caso a função chamada Revela_Cartas não funcione corretamente;
   6 caso o parâmetro de aposta seja inválido;

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. O ponteiro aposta deve ser não nulo.

 - Assertivas de Saída:
   1. A aposta foi registrada corretamente.
   2. O dinheiro foi subtraído corretamente.
   3. As mãos dos jogadores foram reiniciadas.
   4. Foram distribuídas 4 cartas (2 para cada jogador).
   5. As cartas que precisavam ser reveladas foram reveladas. 
*/

typedef enum {
   DEALER_OK = 0,
   DEALER_REVELA_CARTAS_FALHA = 1,
   DEALER_CALCULA_PONTUACAO_FALHA = 2,
   DEALER_ADICIONA_CARTA_FALHA = 3,
   DEALER_COMPROU_COM_17 = 4,
   DEALER_INTERFACE_RODADA_FALHA = 5,
   DEALER_PARAM_APOSTA_INVALIDO = 6
} dealer_cond_ret;

dealer_cond_ret turno_dealer(int aposta);
/*
Objetivo:
Função responsável por realizar as ações do dealer. 
Ele começará o turno revelando suas cartas e comprará até obter um 
resultado de 17 ou mais.

Descrição:
1. A aplicação deve destacar de quem é o turno atual.
2. Quando o turno do dealer começa, suas cartas são viradas para cima.
3. Quando a carta é utilizada na rodada, ela não volta para o baralho.
4. A carta “Ás” tem valor 11.
5. Caso a soma das cartas exceda 21 e o jogador possua um “Ás”, o valor dele passa a ser 1.
6. O processo de mudança de valor do “Ás” pode ocorrer até o valor da soma ser menor que 21
ou até o jogador não possuir mais nenhum “Ás” com valor 11.
7. O jogo disponibiliza as seguintes opções para o jogador: Hit, Stand.
8. A opção “Hit” deve adicionar uma carta à mão do jogador.
9. A opção “Stand” deve encerrar o turno do jogador.
10. O dealer deve escolher “Hit” até a soma de suas cartas dar 17 ou mais e depois escolher “Stand”.
11. O limite de cartas na mão de um jogador é 11.

Acoplamento:
 - Parâmetros:
   aposta: inteiro com o valor da aposta para a montagem da interface;

 - Retornos:
   0 caso o turno tenha sido executado corretamente;
   1 caso a função chamada Revela_Cartas não funcione corretamente;
   2 caso a função Calcula_Pontuação não funcione corretamente;
   3 caso a função Adiciona_Carta não funcione corretamente;
   4 caso o dealer compre uma carta tendo 17 ou mais de pontuação;
   5 caso a função chamada Interface_Rodada não funcione corretamente;
   6 caso o parâmetro aposta seja inválido;

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. aposta deve ser um inteiro positivo.

 - Assertivas de Saída:
   1. As cartas do dealer foram reveladas corretamente.
   2. O dealer termina o turno com pontuação ≥ 17.
   3. Nenhuma carta adicional foi comprada após alcançar 17.
   4. A interface foi exibida corretamente ao usuário em cada ação.
*/

typedef enum {
   USUARIO_OK = 0,
   USUARIO_CALCULA_PONTUACAO_FALHA = 1,
   USUARIO_INTERFACE_RODADA_FALHA = 2,
   USUARIO_ADICIONA_CARTA_FALHA = 3,
   USUARIO_COMPRA_INVALIDA = 4,
   USUARIO_STAND_FALHA = 5,
   USUARIO_PARAM_APOSTA_INVALIDO = 6,
   USUARIO_PARAM_VOLTAR_MENU_INVALIDO = 7,
   USUARIO_REVELA_CARTAS_FALHA = 8
} usuario_cond_ret;

usuario_cond_ret turno_usuario(int aposta, int* voltar_menu);
/*
Objetivo:
Função responsável por realizar as ações de comprar cartas, 
encerrar o turno, ou voltar ao menu principal de acordo com o desejo do usuário.

Descrição:
1. A aplicação deve destacar de quem é o turno atual.
2. O primeiro turno é do usuário.
3. Se um jogador passa de 21 com a soma das  cartas, ele encerra o turno.
4. Quando a carta é utilizada na rodada, ela não volta para o baralho.
5. A carta “Ás” tem valor 11.
6. Caso a soma das cartas exceda 21 e o jogador possua um “Ás”, o valor dele passa a ser 1.
7. O processo de mudança de valor do “Ás” pode ocorrer até o valor da soma ser menor que 21
ou até o jogador não possuir mais nenhum “Ás” com valor 11.
8. O jogo disponibiliza as seguintes opções para o jogador: Hit, Stand.
9. A opção “Hit” deve adicionar uma carta à mão do jogador.
10. A opção “Stand” deve encerrar o turno do jogador.
11. Caso o jogador consiga 21 com a soma das cartas, ele escolherá “Stand” automaticamente.
12. O limite de cartas na mão de um jogador é 11.

Acoplamento:
 - Parâmetros:
   aposta: inteiro com o valor da aposta para a montagem da interface;
   voltar_menu: inteiro onde será guardado se o usuário quer voltar ao menu;

 - Retornos:
   0 caso o turno tenha sido executado corretamente;
   1 caso a função chamada Calcula_Pontuação não funcione corretamente;
   2 caso a função chamada Interface_Rodada não funcione corretamente;
   3 caso a função chamada Adiciona_Carta não funcione corretamente;
   4 caso o usuário compre uma carta tendo uma pontuação de 21 ou mais;
   5 caso a opção de Stand não funcione corretamente;
   6 caso o parâmetro aposta seja inválido;
   7 caso o parâmetro voltar_menu seja inválido;
   8 caso a função Revela_Cartas não funcione corretamente;

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. aposta deve ser um inteiro positivo.
   2. O ponteiro voltar_menu deve ser não nulo.

 - Assertivas de Saída:
   1. O turno do jogador termina com Stand manual ou automático (≥21).
   2. A interface foi exibida corretamente ao usuário em cada ação.
*/

typedef enum {
   INICIA_JOGO_OK = 0,
   INICIA_JOGO_INICIA_JOGADOR_FALHA = 1,
   INICIA_JOGO_INICIA_BARALHO_FALHA = 2,
   INICIA_JOGO_PARAM_RESUME_INVALIDO = 3,
   INICIA_JOGO_PARAM_APOSTA_INVALIDO = 4,
   INICIA_JOGO_SEM_ARQUIVO = 5,
   INICIA_JOGO_ARQUIVO_INVALIDO = 6
} iniciajogo_cond_ret;

iniciajogo_cond_ret inicia_jogo(int* resume, int* aposta);
/*
Objetivo:
Função responsável por inicializar os jogadores, a aposta e o baralho com os 
valores iniciais ou do jogo anterior. 

Descrição:
1. O usuário começa a partida com 2500 dinheiros.
2. O jogo salva o dinheiro, a aposta, a mão dos jogadores e o baralho do jogo anterior à inicialização atual.
3. A aplicação utiliza no jogo um baralho de cartas do tipo convencional, seguindo o modelo Copag 139.

Acoplamento:
 - Parâmetros:
   resume: inteiro que define se existe partida anterior para ser retomada;
   aposta: inteiro que define a aposta da partida;

 - Retornos:
   0 caso o jogo tenha sido iniciado com sucesso;
   1 caso a função chamada Inicializa_Jogador não funcione corretamente;
   2 caso a função chamada Inicializa_Baralho não funcione corretamente;
   3 caso o parâmetro resume seja inválido;
   4 caso o parâmetro aposta seja inválido;
   5 caso o arquivo do jogo anterior não exista;

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. O ponteiro resume deve ser não nulo.
   2. O ponteiro aposta deve ser não nulo.
   3. Existe um arquivo json com os dados da partida anterior (vazio caso primeira inicialização).

 - Assertivas de Saída:
   1. Jogadores inicializados com os dados padrão ou anteriores (dinheiro, cartas).
   2. Baralho inicializado com os dados padrão ou anteriores.
*/

typedef enum {
   CHAMA_MENU_OK = 0,
   CHAMA_MENU_MENU_PRINCIPAL_FALHA = 1,
   CHAMA_MENU_INICIA_BARALHO_FALHA = 2,
   CHAMA_MENU_EMBARALHA_CARTAS_FALHA = 3,
   CHAMA_MENU_INICIA_JOGADOR_FALHA = 4,
   CHAMA_MENU_DADOS_ANTERIORES_FALTANTES = 5,
   CHAMA_MENU_PARAM_ESCOLHA_INVALIDO = 6,
   CHAMA_MENU_PARAM_RESUME_INVALIDO = 7
} menu_cond_ret;

menu_cond_ret chama_menu(int* escolha, int resume);
/*
Objetivo:
Função responsável por chamar o menu principal e, ou inicializar os dados default
ou continuar com os dados anteriores.

Descrição:
1. A aplicação utiliza no jogo um baralho de cartas do tipo convencional, seguindo o modelo Copag 139.
2. A aplicação deve dar ao usuário as seguintes opções: iniciar o jogo, continuar jogo e sair do mesmo.
3. O usuário começa a partida com 2500 dinheiros.

Acoplamento:
 - Parâmetros:
   escolha: inteiro que define a escolha do jogador (novo jogo, continuar jogo ou sair);
   resume: inteiro que define se existem dados anteriores alocados e se existirá a opção de continuar jogo;

 - Retornos:
   0 caso nenhum erro tenha ocorrido.
   1 caso a função Menu_Principal não funcione corretamente.
   2 caso a função Inicializa_Baralho não funcione corretamente.
   3 caso a função Embaralha_Cartas não funcione corretamente.
   4 caso a função Inicializa_Jogador não funcione corretamente.
   5 caso o jogador tenha escolhido continuar partida e não foram encontrados dados anteriores.
   6 caso o parâmetro escolha seja inválido.
   7 caso o parâmetro resume seja inválido.

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. O ponteiro escolha deve ser não nulo.
   2. Resume deve ser um inteiro 0 ou 1.

 - Assertivas de Saída:
   1. A escolha do jogador reflete o processo executado.
   2. Caso a escolha seja iniciar novo jogo, os jogadores e baralho foram retornados ao default.
   3. Caso a escolha seja continuar jogo, os jogadores e baralho foram mantidos.
   4. Caso a escolha seja fechar o jogo, ele foi fechado com sucesso.
*/

typedef enum {
   FECHA_JOGO_OK = 0,
   FECHA_JOGO_DADOS_NAO_SALVOS = 1,
   FECHA_JOGO_PARAM_APOSTA_INVALIDO = 2,
   FECHA_JOGO_PARAM_RESUME_INVALIDO = 3,
   FECHA_JOGO_LER_JOGADOR_FALHA = 4,
   FECHA_JOGO_LER_BARALHO_FALHA = 5
} fecha_cond_ret;

fecha_cond_ret fecha_jogo(int aposta, int resume);
/*
Objetivo:
Função responsável por salvar os dados em um arquivo.

Descrição:
1. O jogo salva o dinheiro, a aposta, a mão dos jogadores e o baralho do jogo anterior à inicialização atual.

Acoplamento:
 - Parâmetros:
   aposta: inteiro que representa a aposta da rodada a ser salva;
   resume: inteiro que define se deve salvar a rodada ou não;

 - Retornos:
   0 caso o jogo tenha sido salvo e fechado corretamente.
   1 caso os dados não tenham sido salvos corretamente.
   2 caso o parâmetro aposta seja inválido.
   3 caso o parâmetro resume seja inválido.
   4 caso a função Ler_Jogador não funcione corretamente.
   5 caso a função Ler_Baralho não funcione corretamente.

Condições de Acoplamento:
 - Assertivas de Entrada:
   1. Aposta deve ser um inteiro.
   2. Resume deve ser um inteiro 0 ou 1. 

 - Assertivas de Saída:
   1. Os dados de jogador foram salvos corretamente no arquivo.
   2. Os dados de aposta foram salvos corretamente no arquivo.
   3. Os dados de baralho foram salvos corretamente no arquivo.
*/

#endif
