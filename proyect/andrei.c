#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// hay que mejorar este menu, para poder seleccionar los modos y 
// los mapas en específico

int menu(char *m);

int menu(char *m) {		//para realizar el menu

  char x;
  bool s;
  int c;

  *m = 0;
  s = false;

  while (s == false) {

    printf("\e[1;1H\e[2J");
    printf("Iniciando...\n");
    if (c == 0) sleep(1);			//para que la primera vez que se inicie haya retardo visual
    printf(".\n");
    if (c == 0) sleep(1);
    printf(".\n");
    if (c == 0) sleep(1);
    printf(".\n");
    if (c == 0) sleep(1);

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

    scanf(" %c", &x);

    switch (x) {

    case 'i':
    case 'I':										//instrucciones
      c = 1;
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
      printf("\n\nIntroduce cualquier tecla para salir.\n");
      scanf(" %c", &x);
      if (x != '0')
        s = false;
      break;

    case 'j':
    case 'J':										//modos de juego
      c = 1;
      printf("\e[1;1H\e[2J");
      printf(" ____ \n||1 ||\n||__|| Resuelve el laberinto. \n|/__\\|\n");
      printf(" ____ \n||2 ||\n||__|| Escapa del enemigo. \n|/__\\|\n");
      printf(" ____ \n||3 ||\n||__|| ************ \n|/__\\|\n");
      printf(" ____ \n||4 ||\n||__|| ************ \n|/__\\|\n");
      printf(" ____ \n||S ||\n||__|| Volver al menú. \n|/__\\|\n\n");
      scanf(" %c", &x);
      if (x == 's')
        s = false;
      else if (x == '1' || x == '2' || x == '3' || x == '4' || x == '7') {
        *m = x;
        s = true;
      }
      break;

    case 's':
    case 'S':										//salir del programa
      s = true;
      printf("\e[1;1H\e[2J");
      exit(0);
      break;
    }
  }
  
}

























