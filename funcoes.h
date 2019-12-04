#include <stdio.h>
#include <unistd.h>		//para usar o sleep(); -> é usado para "parar" o programa antes de continuá-lo
#include <stdlib.h>		//para usar o system ("Cls"); -> é usado para "limpar" a tela do sistema /// para usar o srand()/rand() -> randomicos
#include <conio.h>		//para usar o getch(); -> é usado para "pegar" o caracter teclado pelo usuário (espera até que um caactere seja teclado)
#include <time.h>		//para usar o time(); -> é usado para "pegar" o tempo em milisegundos
#include <locale.h>		//para usar o setlocale -> é usado para add caracteres de escrita como 'ç', '~', '^', etc

//--------------------------VARIÁVEIS GLOBAIS--------------------------//
int i; 
int game = 0; 							//game = 0,  rodando X game = 1, game over
int posicaoMenu = 1, posicaoJogo = 1;				//posição inicial da seta no menu/jogo ("Iniciar jogo"/"Puxar carta" respectivamente)
int teclaPressionadaMenu = 0, teclaPressionadaJogo = 0;		//teclas que vão ser pressionadas no menu/jogo (valores em ASCII)
int score = 0;							//auxiliar que guarda o score															
int high = 0;							//auxiliar que guarda o maior score
char nome[3];

int valorCarta;							//quanto a carta vale de 1 ~ 13															

FILE *numeros;							//arquivo que guarda os high scores
FILE *nomes;							//arquivo que guarda os nomes dos jogadores (dos high scores)

//--------------------------------FUNÇÕES-------------------------------//

void setaMenu(int posicaoApontaMenu, int posicaoDesejadaMenu){		/*FUNÇÃO: seta no menu (somente o desenho, não movimentos)*/	//posicaoApontadaMenu = posição em que a seta aponta; posicaoDesejadaMenu = posição que eu quero que a seta aponte
	
	if(posicaoApontaMenu == posicaoDesejadaMenu){		//se a posição que a seta se encontra é igual a que eu quero, então mostrar a seta na frente
		printf("    %c ", 16);
	}
	else{
		printf("    ");					//se a posição que a seta se encontra é diferente a que eu quero, então mostrar espaço vazio na frente
	}	
}

void menuMovimento(){		/*FUNÇÃO: menu (com movimentos da seta)*/
	system ("Cls");
	
	while(teclaPressionadaMenu != 13){	/*13 representa a tecla ENTER*/		//enquanto não clicar na tecla 'ENTER' continuar nessa função
		system("Cls");
		
		printf("        MENU\n\n");
		setaMenu(1, posicaoMenu); printf(" Iniciar jogo\n");			//chama a função setaMenu e atribui os valores
		setaMenu(2, posicaoMenu); printf(" Regras\n");
		setaMenu(3, posicaoMenu); printf(" High score\n");
		setaMenu(4, posicaoMenu); printf(" Créditos\n");
		
		teclaPressionadaMenu = getch();						//pegar a ultima tecla digitada	
			if(teclaPressionadaMenu == 80 && posicaoMenu != 4){	/*80 representa a tecla baixo*/		//se clicar na tecla 'baixo' em qualquer posição que não a 4ª/ultima, a seta desce
				printf("\a");						//barulho 'beep' para quando mexe a seta/aperta as teclas cima-baixo
				posicaoMenu++;
			}
			else{
				if(teclaPressionadaMenu == 72 && posicaoMenu != 1){	/*72 representa a tecla cima*/		//se clicar na tecla 'cima' em qualquer posição que não a 1ª, a seta sobe
					printf("\a");
					posicaoMenu--;
				}
				else{
					posicaoMenu = posicaoMenu;			//se clicar em outra tecla que não seja tecla 'cima', 'baixo' ou 'ENTER', não mudar a posição
				}						
			}
	}
}

void setaJogo(int posicaoApontadaJogo, int posicaoDesejadaJogo){		/*FUNÇÃO: seta no jogo (somente o desenho, não movimentos)*/	//posicaoApontadaJogo = posiÃ§Ã£o em que a seta aponta; posicaoDesejadaJogo = posiÃ§Ã£o que eu quero que a seta aponte
	if(posicaoApontadaJogo == posicaoDesejadaJogo){
		printf("    %c ", 16);
	}
	else{
		printf("    ");
	}	
}

int ComprarCarta(){		/*FUNÇÃO: comprar carta(gerar random) + ás vale 1 ou 11*/
	srand(time(NULL)); 
	int CartaValor = rand() %10;
	CartaValor += 1;
	if(CartaValor == 11){
		int As;
		do{
			printf("Você recebeu um Ás\n");
			printf("\nEscolha uma opção\n");
			printf("\nO Ás Vale:\n");
			setaJogo(1, posicaoJogo); printf(" 1 ponto\t\t");
			setaJogo(2, posicaoJogo); printf(" 11 pontos\t\t");
			
			teclaPressionadaJogo = getch();	
				if(teclaPressionadaJogo == 75 && posicaoJogo == 2){	/*75 representa a tecla esquerda*/
					printf("\a");
					posicaoJogo--;
				}
				else{
					if(teclaPressionadaJogo == 77 && posicaoJogo == 1){	/*77 representa a tecla direita*/
						printf("\a");
						posicaoJogo++;
					}
					else{
						posicaoJogo = posicaoJogo;
					}						
				}
			
			if(teclaPressionadaJogo == 13 && posicaoJogo == 1){
				CartaValor=1;
				As=1;
			}
			else if(teclaPressionadaJogo == 13 && posicaoJogo == 2){
				CartaValor=11;
				As=1;
			}
			else{
				system("Cls");
			}
		}while(As!=1);
		system("Cls");
	}
	srand(time(NULL));
	if(CartaValor == 1){
		int As;
		do{
			printf("Você recebeu um Ás\n");
			printf("\nEscolha uma opção\n");
			printf("O Ás Vale:\n");
			setaJogo(1, posicaoJogo); printf(" 1 ponto\t\t");
			setaJogo(2, posicaoJogo); printf(" 11 pontos\t\t");
			
			teclaPressionadaJogo = getch();	
				if(teclaPressionadaJogo == 75 && posicaoJogo == 2){
					printf("\a");
					posicaoJogo--;
				}
				else{
					if(teclaPressionadaJogo == 77 && posicaoJogo == 1){
						printf("\a");
						posicaoJogo++;
					}
					else{
						posicaoJogo = posicaoJogo;
					}						
				}
			if(teclaPressionadaJogo == 13 && posicaoJogo == 1){
				CartaValor=1;
				As=1;
			}
			else if(teclaPressionadaJogo == 13 && posicaoJogo == 2){
				CartaValor=11;
				As=1;
			}
			else{
				system("Cls");
			}
		}while(As!=1);
		system("Cls");
	}
	srand(time(NULL)); 
	return CartaValor;
}

int Jogador(){		/*FUNÇÃO: ?*/
	int SN;
	int Ver=0;
	printf("Escolha uma opção\n");
	setaJogo(1, posicaoJogo); printf(" Comprar carta\t\t");
	setaJogo(2, posicaoJogo); printf(" Terminar jogada");
	
	teclaPressionadaJogo = getch();	
		if(teclaPressionadaJogo == 75 && posicaoJogo == 2){
			printf("\a");
			posicaoJogo--;
		}
		else{
			if(teclaPressionadaJogo == 77 && posicaoJogo == 1){
				printf("\a");
				posicaoJogo++;
			}
			else{
				posicaoJogo = posicaoJogo;
			}						
		}
	
	if(teclaPressionadaJogo == 13 && posicaoJogo == 1){
		SN=1;
		Ver=1;
	}
	else if(teclaPressionadaJogo == 13 && posicaoJogo == 2){
		SN=2;
		Ver=1;
	}
	system("Cls");
	if(Ver ==1){
		if (SN == 2){
			return 404;
		}
		else{
			int DeckJogador = ComprarCarta();
			return DeckJogador;
		}
	}
}

void voltar(){		/*FUNÇÃO: voltar ao menu*/
		do{	
			teclaPressionadaMenu = getch();	
		}while(teclaPressionadaMenu != 8);	/*8 representa a tecla BACKSPACE*/	
		
		menuMovimento();
}

int highScore(){		/*FUNÇÃO: verificar se highscore*/				
	if(score > high){
		high = score;
		printf("        ------------------");
		printf("\n        Novo High Score!!!");
		printf("\n        ------------------");
		
		printf("\n\n         Seu Score foi: %d\n", score);
		
		numeros = fopen("HighScore.txt", "a");
		fprintf(numeros, "%d ", high);
		fclose(numeros);
		
		printf("\n\n  Digite 3 Letras do seu Nome: ");
		gets(nome);
		
		nomes = fopen("Ganhador.txt", "a");
		fprintf(nomes, "%s ", nome);
		fclose(nomes);
		
		score = 0;
		printf("\n\nPressione BACKSPACE para voltar ao menu");
		teclaPressionadaMenu = getch();
	}
	else{
		printf("Seu Score foi: %d", score);
		score = 0;
		printf("\n\nTente novamente");
		printf("\n\nPressione BACKSPACE para voltar ao menu");
		teclaPressionadaMenu = getch();
	}
	voltar();
}

int jogoMovimento(){		/*FUNÇÃO: jogo ? (com movimentos da seta)*/

	if(teclaPressionadaMenu == 13 && posicaoMenu == 1){
		system("Cls");
		
		int Parada=0;
		int DeckJogador=0;
		int DeckBot=0;
		DeckJogador = ComprarCarta();
		do{
			int VerificarJogador;
			printf("Você tem um total de %d\n\n", DeckJogador);
			if(DeckJogador >20){
				Parada = 1;
			}
			else{
				VerificarJogador = Jogador();
			}
			if(VerificarJogador == 404){
				Parada = 1;
			}
			else if(VerificarJogador != 0){
				if(DeckJogador > 20){
					Parada = 1;
				}
				else if(Parada == 0){
					DeckJogador += VerificarJogador;
				}
			}
		}while(Parada != 1);

		srand(time(NULL)); 
		int CartaBOT = rand() %11;	//Maximo do valor do deck do bot 23
		CartaBOT += 12;				//Minimo do valor do deck do bot 12
			
		if(CartaBOT == DeckJogador){				/* Jogador e Bot empatam */
			score += 0;
			system("Cls");
			for(i = 3; i > 0; i--){		
				printf(" >> O Bot terminou com %d\n", CartaBOT);
				printf(" >> Você terminou com %d\n\n", DeckJogador);
				printf("Você Empatou essa Rodada\n\n");
				printf("Score atual: %d pontos", score);
			
				printf("\n\nO jogo vai recomeçar em %d...", i);
				sleep(1);
				system("Cls");	
			}
		}
		else{
			if(CartaBOT > 21 && DeckJogador > 21){
			system("Cls");
				if(CartaBOT > DeckJogador){		/* Jogador e Bot com mais de 21, Bot maior que jogador */
					score += DeckJogador;
					system("Cls");
					for(i = 3; i > 0; i--){		
						printf("O Bot terminou com %d\n", CartaBOT);
						printf(" >> Você terminou com %d\n\n", DeckJogador);
						printf("Você Ganhou essa Rodada\n\n");
						printf("Score atual: %d pontos", score);
						
						printf("\n\nO jogo vai recomeçar em %d...", i);
						sleep(1);
						system("Cls");	
					}
				}
				else{		/* Jogador e Bot com mais de 21, Bot menor que jogador */
					for(i = 3; i > 0; i--){		
						printf(" >> O Bot terminou com %d\n", CartaBOT);
						printf("Você terminou com %d\n\n", DeckJogador);
						printf("Você Perdeu essa Rodada");
					
						printf("\n\nCalculando o resultado...");
						sleep(1);
						system("Cls");	
					}
					highScore();
				}
			}
			if(CartaBOT > 21 && DeckJogador <= 21){		/* Bot com mais de 21 */
				score += DeckJogador;
				system("Cls");
				for(i = 3; i > 0; i--){		
					printf("O Bot terminou com %d\n", CartaBOT);
					printf(" >> Você terminou com %d\n\n", DeckJogador);
					printf("Você Ganhou essa Rodada\n\n");
					printf("Score atual: %d pontos", score);
								
					printf("\n\nO jogo vai recomeçar em %d...", i);
					sleep(1);
					system("Cls");	
				}
			}
			if(CartaBOT <= 21 && DeckJogador > 21){		/* Jogador com mais de 21 */
				system("Cls");
				for(i = 3; i > 0; i--){		
					printf(" >> O Bot terminou com %d\n", CartaBOT);
					printf("Você terminou com %d\n\n", DeckJogador);
					printf("Você Perdeu essa Rodada");

					printf("\n\nCalculando o resultado...");
					sleep(1);
					system("Cls");	
				}
				highScore();
			}
			if(CartaBOT <= 21 && DeckJogador <= 21){
				system("Cls");
				if(CartaBOT > DeckJogador){		/* Jogador e Bot com menos de 21, Bot maior que jogador */
					for(i = 3; i > 0; i--){		
						printf(" >> O Bot terminou com %d\n", CartaBOT);
						printf("Você terminou com %d\n\n", DeckJogador);
						printf("Você Perdeu essa Rodada");

						printf("\n\nCalculando o resultado...");
						sleep(1);
						system("Cls");	
					}
					highScore();
				}
				else{					/* Jogador e Bot com menos de 21, Bot menor que jogador */
					score += DeckJogador;
					system("Cls");
					for(i = 3; i > 0; i--){		
						printf("O Bot terminou com %d\n", CartaBOT);
						printf(" >> Você terminou com %d\n\n", DeckJogador);
						printf("Você Ganhou essa Rodada\n\n");
						printf("Score atual: %d pontos", score);

						printf("\n\nO jogo vai recomeçar em %d...", i);
						sleep(1);
						system("Cls");	
					}
				}
			}	
		}

	}
}

void instrucao(){		/*FUNÇÃO: mostrar as instruções do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 2){
		system("Cls");
		
		printf("===============================================\n");
		printf("\t\t  REGRAS  \t\t       -> Pressione BACKSPACE para voltar ao menu\n");
		printf("===============================================\n\n");
		
		printf("  'Blackjack' ou 'vinte-e-um' é um jogo de azar \n"
			   "praticado com cartas em casinos e que pode ser \n"
			   "jogado com 1 a 8 baralhos de 52 cartas, em que o\n"
			   "objetivo é ter mais pontos do que o adversário, \n"
		           "mas sem ultrapassar a soma de 21.");
		       
		printf("\n\n\n - 10, J, Q, K valem 10 pontos.");
		printf("\n\n - Ás vale 1 ou 11 pontos.");
		printf("\n\n - Ao GANHAR uma partida, a soma do Deck será\n"
			   "   adicionada ao score e o jogo continuará.");
		printf("\n\n - Ao EMPATAR uma partida, nenhum ponto será\n"
			   "   adicionado ao score e o jogo continuará.");
		printf("\n\n - Ao PERDER uma partida, nenhum ponto será\n"
			   "   adicionado ao score e o jogo terminará.\n");
			   		  
		voltar();
	}
}

void consultarHighScore(){		/*FUNÇÃO: mostrar o highscore do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 3){
		int scoreX, scoreY, scoreZ;
		char nomeX[3], nomeY[3], nomeZ[3];
		 
		system("Cls");
		
		printf("================================================\n");
		printf("\t\t HIGH SCORE  \t\t        -> Pressione BACKSPACE para voltar ao menu\n");
		printf("================================================\n\n");
		
		printf("\n");
		
		numeros = fopen("HighScore.txt", "r");
		nomes = fopen("Ganhador.txt", "r");
		
		fscanf(numeros, "%d", &scoreX);
		fgets(nomeX, 5, nomes);
			printf("\n\n\t     3º Lugar - %d", scoreX);
			printf(" - %s", nomeX);
		
		fscanf(numeros, "%d", &scoreY);
		fgets(nomeY, 5, nomes);
			printf("\n\n\t     2º Lugar - %d", scoreY);
			printf(" - %s", nomeY);
		
		fscanf(numeros, "%d", &scoreZ);
		fgets(nomeZ, 5, nomes);
			printf("\n\n\t     1º Lugar - %d", scoreZ);
			printf(" - %s", nomeZ);
			
		fclose(numeros);
		fclose(nomes);
		
		voltar();
	}
}

void creditos(){		/*FUNÇÃO: mostrar os créditos/criadores do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 4){
		system("Cls");
		
		printf("================================================\n");
		printf("\t\t  CRÉDITOS  \t\t        -> Pressione BACKSPACE para voltar ao menu\n");
		printf("================================================\n\n");
		
		printf("- Desenvolvedores: João Pedro Lima Vieira da Silva\n"
			   "\tMatrícula: 1920026791\n\n");
		printf("- Desenvolvedores: Larissa Nahan S. D. G. Dantas\n"
			   "\tMatrícula: 1920026931\n\n");
		printf("- Desenvolvedores: Rodrigo de Lucena Limeira\n"
			   "\tMatrícula: 1920026942\n\n");
		
		printf("\n\nTrabalho para o curso de Ciência da Computação");
		printf("\nDisciplina Técnicas de Desenvolvimento de Algoritmos");
		printf("\n\n1º Período - UNIPE - 2019.2");
		
		voltar();
	}
}
