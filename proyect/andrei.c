#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// hay que mejorar este menu, para poder seleccionar los modos y 
// los mapas en específico

int menu(char *m) {		//para realizar el menu

  char eleccion;
  //elegir la opcion
  bool salir;
  //salir del programa
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
			contador = 1;
			printf("\e[1;1H\e[2J");
			printf(" ____ \n||1 ||\n||__|| Resuelve el laberinto. \n|/__\\|\n");
			printf(" ____ \n||2 ||\n||__|| Escapa del enemigo. \n|/__\\|\n");
			printf(" ____ \n||3 ||\n||__|| ************ \n|/__\\|\n");
			printf(" ____ \n||4 ||\n||__|| ************ \n|/__\\|\n");
			printf(" ____ \n||S ||\n||__|| Volver al menú. \n|/__\\|\n\n");
			scanf(" %c", &eleccion);
			if (eleccion == 's') salir = false;
			else if (eleccion == '1' || eleccion == '2' || eleccion == '3' || eleccion == '4' || eleccion == '7') {
				*m = eleccion;
				alir = true;
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
  
  
    char mapaElegido;
    
    mapaElegido = '0';
    
    do {
    	    printf("\e[1;1H\e[2J");
    	    if (mapaElegido != '1' && mapaElegido != '2' && mapaElegido != '3' && mapaElegido != 's' && mapaElegido != '0') printf("Elección invalida.");
	    printf("Elige uno de los mapas\n");
	    printf(" ____ \n||1 ||\n||__||\n|/__\\|\n");
	    printf(" ____ \n||2 ||\n||__||\n|/__\\|\n");
	    printf(" ____ \n||3 ||\n||__||\n|/__\\|\n");
	    printf("\n\nIntroduce S para salir.\n\n");
	    scanf(" %c", &mapaElegido);
    } while (mapaElegido != '1' && mapaElegido != '2' && mapaElegido != '3' && mapaElegido != 's');
    
    switch (mapaElegido) {

    case '1':
      *m = '1';
      break;

    case '2':
      *m = '2';
      break;

    case '3':
      *m = '3';
      break;

    case 's':
      *m = '0';
      return 0;
      break;
    }
  }
}






