#include <stdio.h>
#include <unistd.h>		//para usar o sleep(); -> é usado para "parar" o programa antes de continuá-lo
#include <stdlib.h>		//para usar o system ("Cls"); -> é usado para "limpar" a tela do sistema /// para usar o srand()/rand() -> randomicos
#include <conio.h>		//para usar o getch(); -> é usado para "pegar" o caracter teclado pelo usuário (espera até que um caactere seja teclado)
#include <time.h>		//para usar o time(); -> é usado para "pegar" o tempo em milisegundos
#include <locale.h>		//para usar o setlocale -> é usado para add caracteres de escrita como 'ç', '~', '^', etc


//--------------------------VARIÁVEIS GLOBAIS--------------------------//
int i; 
int game = 0; 															//game = 0,  rodando X game = 1, game over
int posicaoMenu = 1, posicaoJogo = 1;									//posição inicial da seta no menu/jogo ("Iniciar jogo"/"Puxar carta" respectivamente)
int teclaPressionadaMenu = 0, teclaPressionadaJogo = 0;					//teclas que vão ser pressionadas no menu/jogo (valores em ASCII)
int high = 0;															//auxiliar que guarda o maior score

int soma = 0;			//auxiliar para somar as cartas
int as = 4, dois = 4, tres = 4, quatro = 4, cinco = 4, seis = 4, sete = 4, oito = 4, nove = 4, dez = 4, valete = 4, rainha = 4, rei = 4;	//limitar a quantidade de vezes que as cartas aparecem (no caso, 4 vezes cada)
int valorCarta;			//quanto a carta vale de 1 ~ 13															

FILE *arquivo;

//--------------------------------FUNÇÕES-------------------------------//



void setaJogo(int posicaoApontadaJogo, int posicaoDesejadaJogo){	/*FUNÃ‡ÃƒO: seta no jogo (somente o desenho, nÃ£o movimentos)*/	//posicaoApontadaJogo = posiÃ§Ã£o em que a seta aponta; posicaoDesejadaJogo = posiÃ§Ã£o que eu quero que a seta aponte
	
	if(posicaoApontadaJogo == posicaoDesejadaJogo){
		printf("    %c ", 16);
	}
	else{
		printf("    ");
	}
	
}

int ComprarCarta(){
	srand(time(NULL)); 
	int CartaValor = rand() %10;
	CartaValor += 1;
	if(CartaValor == 11){
		int As;
		do{
			printf("Vc tem um As\n");
			printf("Digite o valor da opcao\n");
			printf("O As Vale:\n");
			setaJogo(1, posicaoJogo); printf(" Numero 1\t\t");
			setaJogo(2, posicaoJogo); printf(" Numero 11\t\t");
			
			teclaPressionadaJogo = getch();	
				if(teclaPressionadaJogo == 75 && posicaoJogo == 2){		/*75 representa a tecla esquerda*/
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
			
			
			if(teclaPressionadaJogo ==13 && posicaoJogo == 1){
				CartaValor=1;
				As=1;
			}
			else if(teclaPressionadaJogo ==13 && posicaoJogo == 2){
				CartaValor=11;
				As=1;
			}
			else{
				system("cls");
			}
		}while(As!=1);
		system("cls");
	}
	srand(time(NULL));
	if(CartaValor == 1){
		int As;
		do{
			printf("Vc tem um As\n");
			printf("Digite o valor da opcao\n");
			printf("O As Vale:\n");
			setaJogo(1, posicaoJogo); printf(" Numero 1\t\t");
			setaJogo(2, posicaoJogo); printf(" Numero 11\t\t");
			
			teclaPressionadaJogo = getch();	
				if(teclaPressionadaJogo == 75 && posicaoJogo == 2){		/*75 representa a tecla esquerda*/
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
			
			
			if(teclaPressionadaJogo ==13 && posicaoJogo == 1){
				CartaValor=1;
				As=1;
			}
			else if(teclaPressionadaJogo ==13 && posicaoJogo == 2){
				CartaValor=11;
				As=1;
			}
			else{
				system("cls");
			}
		}while(As!=1);
		system("cls");
	}
	srand(time(NULL)); 
	return CartaValor;
}

int Jogador(){
	int SN;
	int Ver=0;
	printf("Vc quer comprar uma carta?\n");
	setaJogo(1, posicaoJogo); printf(" Comprar carta\t\t");
	setaJogo(2, posicaoJogo); printf(" Terminar jogada");
	
	teclaPressionadaJogo = getch();	
		if(teclaPressionadaJogo == 75 && posicaoJogo == 2){		/*75 representa a tecla esquerda*/
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
	
	if(teclaPressionadaJogo ==13 && posicaoJogo == 1){
		SN=1;
		Ver=1;
	}
	else if(teclaPressionadaJogo ==13 && posicaoJogo == 2){
		SN=2;
		Ver=1;
	}
	system("cls");
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

void setaMenu(int posicaoApontaMenu, int posicaoDesejadaMenu){	/*FUNÇÃO: seta no menu (somente o desenho, não movimentos)*/	//posicaoApontadaMenu = posição em que a seta aponta; posicaoDesejadaMenu = posição que eu quero que a seta aponte
	
	if(posicaoApontaMenu == posicaoDesejadaMenu){		//se a posição que a seta se encontra é igual a que eu quero, então mostrar a seta na frente
		printf("  >> ");
	}
	else{
		printf("   ");		//se a posição que a seta se encontra é diferente a que eu quero, então mostrar espaço vazio na frente
	}
	
}

void menuMovimento(){	/*FUNÇÃO: menu (com movimentos da seta)*/
	system ("Cls");
	
	while(teclaPressionadaMenu != 13){		/*13 representa a tecla ENTER*/		//enquanto não clicar na tecla 'ENTER' continuar nessa função
		system("Cls");
		
		printf("        MENU\n\n");
		setaMenu(1, posicaoMenu); printf(" Iniciar jogo\n");	//chama a função setaMenu e atribui os valores
		setaMenu(2, posicaoMenu); printf(" Configurações\n");
		setaMenu(3, posicaoMenu); printf(" Regras\n");
		setaMenu(4, posicaoMenu); printf(" High score\n");
		setaMenu(5, posicaoMenu); printf(" Créditos\n");
		
		teclaPressionadaMenu = getch();		//pegar a ultima tecla digitada	
			if(teclaPressionadaMenu == 80 && posicaoMenu != 5){		/*80 representa a tecla baixo*/		//se clicar na tecla 'baixo' em qualquer posição que não a 5ª/ultima, a seta desce
				printf("\a");	//barulho 'beep' para quando mexe a seta/aperta as teclas cima-baixo
				posicaoMenu++;
			}
			else{
				if(teclaPressionadaMenu == 72 && posicaoMenu != 1){		/*72 representa a tecla cima*/		//se clicar na tecla 'cima' em qualquer posição que não a 1ª, a seta sobe
					printf("\a");
					posicaoMenu--;
				}
				else{
					posicaoMenu = posicaoMenu;	//se clicar em outra tecla que não seja tecla 'cima', 'baixo' ou 'ENTER', não mudar a posição
				}						
			}
	}
}



void jogoMovimento(){		/*FUNÇÃO: jogo (com movimentos da seta)*/

	
	if(teclaPressionadaMenu == 13 && posicaoMenu == 1){
		system("Cls");
		
		int Parada=0;
		int DeckJogador=0;
		int DeckBot=0;
		DeckJogador = ComprarCarta();
		do{
			int VerificarJogador;
			printf("Vc tem um total de %d\n\n", DeckJogador);
			if(DeckJogador >20){
				Parada=1;
			}
			else{
				VerificarJogador = Jogador();
			}
			if(VerificarJogador == 404){
				Parada=1;
			}
			else if(VerificarJogador != 0){
				if(DeckJogador > 20){
					Parada=1;
				}
				else if(Parada==0){
					DeckJogador += VerificarJogador;
				}
			}
		}while(Parada != 1);
		srand(time(NULL)); 
		int CartaBOT = rand() %18;//Maximo do valor do deck do bot 23
		CartaBOT += 5;//Minimo do valor do deck do bot 5
		if(CartaBOT == DeckJogador){
			printf("Empate");
		}
		else if(CartaBOT > 21){
			printf("Voce Ganhou");
		}
		else if(DeckJogador > 21){
			printf("Voce Perdeu");
		}
		else if(CartaBOT > DeckJogador){
			printf("Voce Perdeu");
		}
		else if(CartaBOT < DeckJogador){
			printf("Voce Ganhou");
		}
		
		
		/*
		while(teclaPressionadaJogo != 13){
			system("Cls");
			setaJogo(1, posicaoJogo); printf(" Puxar carta\t\t\t");
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
		} 
	} else{
		
		while(teclaPressionadaJogo != 13){
			
			setaJogo(1, posicaoJogo); printf(" Puxar carta\t\t\t");
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
		}	
	} */ } 
}

void voltar(){		/*FUNÇÃO: voltar ao menu*/
		do{	
			teclaPressionadaMenu = getch();	
		}while(teclaPressionadaMenu != 8);		/*8 representa a tecla BACKSPACE*/	
		
		menuMovimento();
}

void configuracoes(){		/*FUNÇÃO: digitar quantas vezes deseja jogar e dizer seu nome*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 2){
		system("Cls");
		
		printf("===============================================\n");
		printf("\t\t CONFIGURAÇÕES\n");
		printf("===============================================\n\n");
		
		int vezes;
		char nome[3];	
			
		do{
			printf("\n\n\t\tInforme quantas vezes deseja jogar: "); scanf("%d", &vezes);		
		}while(vezes <= 0);		
	
		do{
			printf("\n\n\t\tInforme as três primeiras letras do seu nome: "); 
			for(i = 0; i < 3; i++){
				scanf("%c", &nome[i]);
			}
		}while(nome[3] == '0');
		
		printf("\n\n -> Pressione BACKSPACE para voltar ao menu");
		voltar();		
	}
}

void instrucao(){		/*FUNÇÃO: mostrar as instruções do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 3){
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
		       printf("\n\n - Ás vale 11 pontos.");
		       printf("\n\n - Ao ganhar uma partida, 10 pontos serão\n"
			   		  "   adicionados ao score.");
		       printf("\n\n - Ao perder uma partida, 10 pontos serão\n"
			   		  "   subtraidos do score.\n");
		       printf("\n\n - Ao ganhar uma partida com exatamente 21\n"
			   		  "   pontos, 20 pontos serão adicionados ao score.");
			   		  
		voltar();
	}
}

void consultarHighScore(){		//NÃO ESTÁ FUNCIONANDO!		/*FUNÇÃO: mostrar o highscore do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 4){
		system("Cls");
		
		printf("================================================\n");
		printf("\t\t HIGH SCORE  \t\t        -> Pressione BACKSPACE para voltar ao menu\n");
		printf("================================================\n\n");
		
		arquivo = fopen("HighScore21.txt", "a");
		for(i = 0; i < 3; i++){
			fprintf(arquivo, "%d pontos\n", &high);
		}
		fclose(arquivo);
		
	voltar();
	}
}

void creditos(){		/*FUNÇÃO: mostrar os créditos/criadores do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 5){
		system("Cls");
		
		printf("================================================\n");
		printf("\t\tCRÉDITOS  \t\t        -> Pressione BACKSPACE para voltar ao menu\n");
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

//-------------------------------INT MAIN------------------------------//

int main(){
	setlocale(LC_ALL, "");

	while(game == 0){
		menuMovimento();

		configuracoes();
		instrucao();
		consultarHighScore();
		creditos();

		jogoMovimento();

	}
	
	return 0;
}

//-------------------------------Logica Jogo------------------------------//


