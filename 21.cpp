#include <stdio.h>
#include <unistd.h>		//para usar o sleep(); -> é usado para "parar" o programa antes de continuá-lo
#include <stdlib.h>		//para usar o system ("Cls"); -> é usado para "limpar" a tela do sistema /// para usar o srand()/rand() -> randomicos
#include <conio.h>		//para usar o getch(); -> é usado para "pegar" o caracter teclado pelo usuário (espera até que um caactere seja teclado)
#include <time.h>		//para usar o time(); -> é usado para "pegar" o tempo em milisegundos
#include <locale.h>		//para usar o setlocale -> é usado para add caracteres de escrita como 'ç', '~', '^', etc


//--------------------------VARIÁVEIS GLOBAIS--------------------------//
int i; 
int game = 0; 							//game = 0, jogo rodando X game = 1, game over
int posicaoMenu = 1, posicaoJogo = 1;				//posição inicial da seta no menu/jogo ("Iniciar jogo"/"Puxar carta" respectivamente)
int teclaPressionadaMenu = 0, teclaPressionadaJogo = 0;		//teclas que vão ser pressionadas no menu/jogo (valores em ASCII)
int high = 0;							//auxiliar que guarda o maior score

int soma = 0;							//auxiliar para somar as cartas
int as = 4, dois = 4, tres = 4, quatro = 4, cinco = 4, seis = 4, sete = 4, oito = 4, nove = 4, dez = 4, valete = 4, rainha = 4, rei = 4;	//limitar a quantidade de vezes que as cartas aparecem (no caso, 4 vezes cada)
int valorCarta;							//quanto a carta vale de 1 ~ 13															

FILE *arquivo;

//--------------------------------FUNÇÕES-------------------------------//

void setaMenu(int posicaoApontaMenu, int posicaoDesejadaMenu){	/*FUNÇÃO: seta no menu (somente o desenho, não movimentos)*/	//posicaoApontadaMenu = posição em que a seta aponta; posicaoDesejadaMenu = posição que eu quero que a seta aponte
	
	if(posicaoApontaMenu == posicaoDesejadaMenu){		//se a posição que a seta se encontra é igual a que eu quero, então mostrar a seta na frente
		printf("  >> ");
	} else{
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
			} else{
				if(teclaPressionadaMenu == 72 && posicaoMenu != 1){		/*72 representa a tecla cima*/		//se clicar na tecla 'cima' em qualquer posição que não a 1ª, a seta sobe
					printf("\a");
					posicaoMenu--;
				} else{
					posicaoMenu = posicaoMenu;	//se clicar em outra tecla que não seja tecla 'cima', 'baixo' ou 'ENTER', não mudar a posição
				}						
			}
	}
}

void setaJogo(int posicaoApontaJogo, int posicaoDesejadaJogo){	/*FUNÇÃO: seta no jogo (somente o desenho, não movimentos)*/		//posicaoApontadaJogo = posição em que a seta aponta; posicaoDesejadaJogo = posição que eu quero que a seta aponte
	
	if(posicaoApontaJogo == posicaoDesejadaJogo){
		printf("    >> ");
	} else{
		printf("    ");
	}
}

void jogoMovimento(){		/*FUNÇÃO: jogo (com movimentos da seta)*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 1){
		system("Cls");
		while(teclaPressionadaJogo != 13){
			system("Cls");
			setaJogo(1, posicaoJogo); printf(" Puxar carta\t\t\t");
			setaJogo(2, posicaoJogo); printf(" Terminar jogada");
			
			teclaPressionadaJogo = getch();	
				if(teclaPressionadaJogo == 75 && posicaoJogo == 2){		/*75 representa a tecla esquerda*/
					printf("\a");
					posicaoJogo--;
				} else{
					if(teclaPressionadaJogo == 77 && posicaoJogo == 1){		/*77 representa a tecla direita*/
						printf("\a");
						posicaoJogo++;
					} else{
						posicaoJogo = posicaoJogo;
					}						
				}
		}
	} else{
		while(teclaPressionadaJogo != 13){
			
			setaJogo(1, posicaoJogo); printf(" Puxar carta\t\t\t");
			setaJogo(2, posicaoJogo); printf(" Terminar jogada");
			
			teclaPressionadaJogo = getch();	
				if(teclaPressionadaJogo == 75 && posicaoJogo == 2){		/*75 representa a tecla esquerda*/
					printf("\a");
					posicaoJogo--;
				} else{
					if(teclaPressionadaJogo == 77 && posicaoJogo == 1){		/*77 representa a tecla direita*/
						printf("\a");
						posicaoJogo++;
					} else{
						posicaoJogo = posicaoJogo;
					}						
				}
		}	
	}
}

void puxarCarta(){		/*FUNÇÃO: puxar carta no jogo*/				//(1- 'Puxar' mais uma carta)		  (2- Se a prox carta gerar uma soma maior que 21 encerrar o jogo, se não, continuar)
	if(teclaPressionadaJogo == 13 && posicaoJogo == 1){
		
		srand(time(0));
		do{
			printf("\n");
			teclaPressionadaJogo = getch();
			jogoMovimento();
			
			valorCarta = rand() % 13+1;
		
			switch(valorCarta){
				case 1:
					as--;
					if(as < 0){
						break;	
					} else{
						printf("\n\nÁs");
						soma += 11;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
						break;
					}
				break;
				
				case 2:
					dois--;
					if(dois < 0){
						break;
					} else{
						printf("\n\n2");
						soma += 2;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
						break;	
					}
				break;
				
				case 3:
					tres--;
					if(tres < 0){
						break;
					} else{
						printf("\n\n3");
						soma += 3;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
						break;	
					}
				break;
				
				case 4:
					quatro--;
					if(quatro < 0){
						break;
					} else{
						printf("\n\n4");
						soma += 4;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
						break;	
					}
				break;
				
				case 5:
					cinco--;
					if(cinco < 0){
						break;
					} else{
						printf("\n\n5");
						soma += 5;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
						break;	
					}
				break;
				
				case 6:
					seis--;
					if(seis < 0){
						break;
					} else{
						printf("\n\n6");
						soma += 6;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 7:
					sete--;
					if(sete < 0){
						break;
					} else{
						printf("\n\n7");
						soma += 7;
						printf("\n Soma atual de %d", soma);	
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 8:
					oito--;
					if(oito < 0){
					} else{
						printf("\n\n8");
						soma += 8;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 9:
					nove--;
					if(nove <= 0){
					} else{
						printf("\n\n9");
						soma += 9;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 10:
					dez--;
					if(dez <= 0){
					} else{
						printf("\n\n10");
						soma += 10;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 11:
					valete--;
					if(valete <= 0){
					} else{
						printf("\n\nValete");
						soma += 10;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 12:
					rainha--;
					if(rainha <= 0){
					} else{
						printf("\n\nRainha");
						soma += 10;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
				
				case 13:
					rei--;
					if(rei <= 0){
					} else{
						printf("\n\nRei");
						soma += 10;
						printf("\n Soma atual de %d", soma);
						
						if(soma > 21){
							printf("\n\nVocê perdeu o jogo.");
						
							sleep(3);
							system("Cls");
							printf("Fim");
						} else if(soma == 21){
							printf("\n\nVocê ganhou o jogo");
							
							sleep(3);
							system("Cls");
							printf("Fim");
						}
					}
				break;
			}
		
		printf("\n");
		
		}while(teclaPressionadaJogo == 13 && posicaoJogo == 1);
	}
}

void terminarJogada(){		/*FUNÇÃO: encerrar a jogada no jogo*/				//(1- Verificar se a próxima carta passava ou não de 21)		  (2- Se a prox carta gerar uma soma maior que 21 add pontos, se não subtrair pontos)		  (3- Verificar se highscore ou não)
	if(teclaPressionadaJogo == 13 && posicaoJogo == 2){
		srand(time(0));
		valorCarta = rand() % 13+1;
		
		switch(valorCarta){
			case 1:
				as--;
				if(as < 0){
					break;	
				} else{
					printf("\n\nA próxima carta seria um Ás");
					soma += 11;
					printf("\n A soma seria de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
					break;
				}
			break;
			
			case 2:
				dois--;
				if(dois < 0){
					break;
				} else{
					printf("\n\n2");
					soma += 2;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
					break;	
				}
			break;
			
			case 3:
				tres--;
				if(tres < 0){
					break;
				} else{
					printf("\n\n3");
					soma += 3;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
					break;	
				}
			break;
			
			case 4:
				quatro--;
				if(quatro < 0){
					break;
				} else{
					printf("\n\n4");
					soma += 4;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
					break;	
				}
			break;
			
			case 5:
				cinco--;
				if(cinco < 0){
					break;
				} else{
					printf("\n\n5");
					soma += 5;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
					break;	
				}
			break;
			
			case 6:
				seis--;
				if(seis < 0){
					break;
				} else{
					printf("\n\n6");
					soma += 6;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 7:
				sete--;
				if(sete < 0){
					break;
				} else{
					printf("\n\n7");
					soma += 7;
					printf("\n Soma atual de %d", soma);	
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 8:
				oito--;
				if(oito < 0){
				} else{
					printf("\n\n8");
					soma += 8;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 9:
				nove--;
				if(nove <= 0){
				} else{
					printf("\n\n9");
					soma += 9;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 10:
				dez--;
				if(dez <= 0){
				} else{
					printf("\n\n10");
					soma += 10;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 11:
				valete--;
				if(valete <= 0){
				} else{
					printf("\n\nValete");
					soma += 10;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 12:
				rainha--;
				if(rainha <= 0){
				} else{
					printf("\n\nRainha");
					soma += 10;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
			
			case 13:
				rei--;
				if(rei <= 0){
				} else{
					printf("\n\nRei");
					soma += 10;
					printf("\n Soma atual de %d", soma);
					
					if(soma > 21){
						printf("\n\nA soma seria maior que 21, você ganhou o jogo.");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else if(soma == 21){
						printf("\n\nA soma seria igual a 21, você perdeu o jogo");
						
						sleep(3);
						system("Cls");
						printf("Fim");
					} else{
						printf("\n\nA soma seria menor que 21, você perdeu o jogo");
					}
				}
			break;
		}
		
		printf("\n");
		
		
		printf("Fim");
	}
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
		
		printf("\n\n -> Pressione Espaço para voltar ao menu");
		voltar();		
	}
}

void instrucao(){		/*FUNÇÃO: mostrar as instruções do jogo*/
	if(teclaPressionadaMenu == 13 && posicaoMenu == 3){
		system("Cls");
		
		printf("===============================================\n");
		printf("\t\t  REGRAS  \t\t       -> Pressione Espaço para voltar ao menu\n");
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
		printf("\t\t HIGH SCORE  \t\t        -> Pressione Espaço para voltar ao menu\n");
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
		printf("\t\tCRÉDITOS  \t\t        -> Pressione Espaço para voltar ao menu\n");
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
		puxarCarta();
		terminarJogada();

	}
	
	return 0;
}
