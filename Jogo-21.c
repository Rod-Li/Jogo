#include "funcoes.h"		//para usar a minha biblioteca de funções

//-------------------------------INT MAIN------------------------------//

int main(){
	setlocale(LC_ALL, "");

	while(game == 0){
	
		menuMovimento();
		jogoMovimento();
		instrucao();
		consultarHighScore();
		creditos();
		
	}
	
	return 0;
}
