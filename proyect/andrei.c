#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
// hay que mejorar este menu, para poder seleccionar los modos y 
// los mapas en específico

int menu(char *m) {		//para realizar el menu

  char eleccion, mapaElegido;
  //elegir la opcion
  bool salir, sinEleccion;
  //salir del programa
  //en caso de que se elija salir del seleccionador de mapas
  int contador;
  //para que solo la primera vez se ejecute el sleep()

  salir = false;


	while (salir == false) {

		printf("\e[1;1H\e[2J");
		printf("Iniciando...\n");
		if (contador == 0) sleep(1);			//para que la primera vez que se inicie haya retardo visual
		printf(".\n");
		if (contador == 0) sleep(1);
		printf(".\n");
		if (contador == 0) sleep(1);
		printf(".\n");
		if (contador == 0) sleep(1);

		printf("Bienvenido/a a...");
		printf(												//nombre con tipografía chula
		"\n      _____ ______   ________  ___      ___ _______\n     |\\   _ "
		"\\  _   \\|\\   __  \\|\\  \\    /  /|\\  ___ \\\n     \\ \\  "
		"\\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\n      \\ \\ "
		" \\\\|__| \\  \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/__\n       "
		"\\ \\  \\    \\ \\  \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\\n  "
		"      \\ \\__\\    \\ \\__\\ \\_______\\ \\__/ /     \\ \\_______\\\n "
		"        \\|__|     \\|__|\\|_______|\\|__|/       \\|_______|\n");
		printf("\n ____ \n||I ||\n||__|| Instrucciones. \n|/__\\|\n");
		printf(" ____ \n||J ||\n||__|| Modos de juego. \n|/__\\|\n");
		printf(" ____ \n||S ||\n||__|| Salir. \n|/__\\|\n");
		printf("\n");

		scanf(" %c", &eleccion);

		switch (eleccion) {

		case 'i':
		case 'I':										//instrucciones
			contador = 1;
			printf("\e[1;1H\e[2J");
			printf(
			  "En MOVE tendrás *N* modos de juego para "
			  "elegir.\n--------------------------\n-------------------------\nEl "
			  "primer modo de juego se llama 'LABIRINTH', el cual consiste en la "
			  "resolución de un laberinto, pero tendrás que darte prisa, ya que "
			  "perderás si no lo resuelves antes de que se acabe el "
			  "tiempo.\n-------------------------\n-------------------------\nEl "
			  "segundo modo de juego "
			  "*...*.\n-------------------------\n-------------------------\nEl "
			  "tercer modo de juego "
			  "*...*.\n-------------------------\n-------------------------\nY por "
			  "último, el cuarto modo de juego es "
			  "*...*.\n-------------------------\n-------------------------\nPara "
			  "moverte, tendrás que utiizar las teclas W,A,S y D, que van en las "
			  "direcciones izquierda(A), arriba(W), derecha(D) y abajo(S).");
			printf("\n\nIntroduce S tecla para salir.\n");
			scanf(" %c", &eleccion);
			if (eleccion != '0') salir = false;
			break;

		case 'j':
		case 'J':										//modos de juego
			sinEleccion = false;
			contador = 1;

			while(sinEleccion == false){
				printf("\e[1;1H\e[2J");
				printf(" ____ \n||1 ||\n||__|| Resuelve el laberinto. \n|/__\\|\n");
				printf(" ____ \n||2 ||\n||__|| Escapa del enemigo. \n|/__\\|\n");
				printf(" ____ \n||3 ||\n||__|| ************ \n|/__\\|\n");
				printf(" ____ \n||4 ||\n||__|| ************ \n|/__\\|\n");
				printf(" ____ \n||S ||\n||__|| Volver al menú. \n|/__\\|\n\n");
				scanf(" %c", &eleccion);
				if (eleccion == 's') salir = false;
				else if (eleccion == '1' || eleccion == '2' || eleccion == '3' || eleccion == '4') {

					if (eleccion == '1') {
						int a;
						srand(time(NULL));
						a = rand()%3;
						//para elegir el mapa del laberinto de forma aleatoria

						if (a == 0) *m = '2';
						else if (a == 1) *m = '3';
						else if (a == 2) *m = '4';
						
						//elección del modo de laberinto
						salir = true;
						break;
					}
					/*
					else if (eleccion != '1') {
					
						do {
							printf("\e[1;1H\e[2J");
							if (mapaElegido != '1' && mapaElegido != '2' && mapaElegido != '3' && mapaElegido != 's' && mapaElegido != '0') printf("Elección invalida.");
							printf("Elige uno de los mapas\n");
							printf(" ____ \n||1 ||\n||__||\n|/__\\|\n");
							printf(" ____ \n||2 ||\n||__||\n|/__\\|\n");
							printf(" ____ \n||3 ||\n||__||\n|/__\\|\n");
							printf("\n\nIntroduce S para salir.\n\n");
							scanf(" %c", &mapaElegido);
						} while (mapaElegido != '2' && mapaElegido != '3' && mapaElegido != 's');
					
						if (mapaElegido == '1' && eleccion == '2') {
							*m = 21;
							salir = true;
							break;
						}
						if (mapaElegido == '2' && eleccion == '2') {
							*m = 22;
							salir = true;
							break;
						}
						if (mapaElegido == '3' && eleccion == '2') {
							*m = 23;
							salir = true;
							break;
						}
						if (mapaElegido == '1' && eleccion == '3') {
							*m = 31;
							salir = true;
							break;
						}
						if (mapaElegido == '2' && eleccion == '3') {
							*m = 32;
							salir = true;
							break;
						}
						if (mapaElegido == '3' && eleccion == '3') {
							*m = 33;
							salir = true;
							break;
						}
						if (mapaElegido == '1' && eleccion == '4') {
							*m = 41;
							salir = true;
							break;
						}
						if (mapaElegido == '2' && eleccion == '4') {
							*m = 42;
							salir = true;
							break;
						}
						if (mapaElegido == '3' && eleccion == '4') {
							*m = 43;
							salir = true;
							break;
						}
					
					}
					*/
				}
			}
			
		break;

		case 's':
		case 'S':										//salir del programa
			salir = true;
			printf("\e[1;1H\e[2J");
			exit(0);
			break;
		}
	}
}
