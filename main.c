#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

int main(void) {
    int resume;
    int escolha_menu;
    int continuar = 1;
    int aposta;
    int voltar_menu;

    inicia_jogo(&resume, &aposta);
    
    while (1){
        chama_menu(&escolha_menu, resume);

        if(escolha_menu == 2){ // usuário escolheu sair
            fecha_jogo(aposta, resume);
            exit(1);
        }

        while(continuar){
            if(escolha_menu == 0) inicia_rodada(&aposta); // usuário escolheu novo jogo

            turno_usuario(aposta, &voltar_menu);
            if(voltar_menu == 1) { // usuário escolheu voltar ao menu
                resume = 1;
                break; 
            }

            turno_dealer(aposta);
            fim_de_rodada(aposta, &continuar, &resume);
        }
    }
    


  return 0;
}
