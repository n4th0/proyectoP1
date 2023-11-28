#include <stdbool.h>
#include <stdio.h>
// necesito una funcion guapa con el mensaje "has ganado" (si no quieres hacerla pasasela a luca)

int menu(char *m);

int menu(char *m) {

  char x;
  bool s;

  *m = 0;
  s = false;

  while (s == false) {

    printf("\e[1;1H\e[2J");
    printf("Iniciando...\n");
    printf(".\n");
    printf(".\n");
    printf(".\n");

    printf("Bienvenido/a a...\n");
    printf(
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
    case 'I':
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
    case 'J':
      printf("\e[1;1H\e[2J");
      printf(" ____ \n||1 ||\n||__|| Resuelve el laberinto. \n|/__\\|\n");
      printf(" ____ \n||2 ||\n||__|| Escapa del enemigo. \n|/__\\|\n");
      printf(" ____ \n||3 ||\n||__|| ************ \n|/__\\|\n");
      printf(" ____ \n||4 ||\n||__|| ************ \n|/__\\|\n");
      printf(" ____ \n||S ||\n||__|| Volver al menú. \n|/__\\|\n\n");
      scanf(" %c", &x);
      if (x == 's')
        s = false;
      else if (x == '1' || x == '2' || x == '3' || x == '4') {
        *m = x;
        s = true;
      }
      break;

    case 's':
    case 'S':
      s = true;
      printf("\e[1;1H\e[2J");
      return 0;
    }
  }
}
