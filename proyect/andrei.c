#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int menu(char *m) { // para realizar el menu

  char eleccion, mapaElegido;
  // elegir la opcion
  bool salir, sinEleccion;
  // salir del programa
  // en caso de que se elija salir del seleccionador de mapas
  int contador = 0;
  // para que solo la primera vez se ejecute el sleep()

  salir = false;

  while (!salir) {

    printf("\e[1;1H\e[2J");
    printf("Initializing...\n");
    if (contador == 0)
      sleep(1); // para que la primera vez que se inicie haya retardo visual
    printf(".\n");
    if (contador == 0)
      sleep(1);
    printf(".\n");
    if (contador == 0)
      sleep(1);
    printf(".\n");
    if (contador == 0)
      sleep(1);

    printf("Welcome to...");
    printf( // nombre con tipografía chula
        "\n      _____ ______   ________  ___      ___ _______\n     |\\   _ "
        "\\  _   \\|\\   __  \\|\\  \\    /  /|\\  ___ \\\n     \\ \\  "
        "\\\\\\__\\ \\  \\ \\  \\|\\  \\ \\  \\  /  / | \\   __/|\n      \\ \\ "
        " \\\\|__| \\  \\ \\  \\\\\\  \\ \\  \\/  / / \\ \\  \\_|/__\n       "
        "\\ \\  \\    \\ \\  \\ \\  \\\\\\  \\ \\    / /   \\ \\  \\_|\\ \\\n  "
        "      \\ \\__\\    \\ \\__\\ \\_______\\ \\__/ /     \\ \\_______\\\n "
        "        \\|__|     \\|__|\\|_______|\\|__|/       \\|_______|\n");
    printf("\n ____ \n||I ||\n||__|| Instructions. \n|/__\\|\n");
    printf(" ____ \n||G ||\n||__|| Game modes. \n|/__\\|\n");
    printf(" ____ \n||E ||\n||__|| Exit. \n|/__\\|\n");
    printf("\n\n\n");
    printf("To select an option, type the letter and press enter.");

    scanf(" %c", &eleccion);

    switch (eleccion) {

    case 'i':
    case 'I': // instrucciones
      contador = 1;
      printf("\e[1;1H\e[2J");
      printf(
          "\n\nThe first game mode is called LABYRINTH, and your scope is to "
          "solve it. Your character (yellow square) must arrive to the end "
          "(green square)."
          " Each time the map will be generated "
          "randomly.\n-------------------------\nThe second game mode is "
          "called FILL THE MAP. In this one, you have to "
          "choose a map between the options and fill it with your colour. To "
          "accomplish this, your character will leave a trail behind, marking "
          "the gaps you "
          "stepped over.\n-------------------------\nThe third game mode is "
          "called SAFE ZONE, in which you will have to avoid the red enemies "
          "that will spawn "
          "in order to reach the green zone and be safe. But be careful, as "
          "touching an enemy will end your game. Also you might find coloured "
          "squares, and you will have to step over them in order to open the "
          "way to the safe zone. \n-------------------------\nThe fourth and "
          "last game mode is called PSYCHEDELIC. In this mode your purpose is "
          "to reach the green square, but the map will be changing every time "
          "you move, so "
          "you will have to calculate your movement in order to finish "
          "correctly. \n-------------------------\nYour movement will be "
          "controlled with the WASD keys. Press W to move up, D to go right, S "
          "to move down and lastly A to go left. You can press P whenever you "
          "want to exit the game.\n-------------------------\nGood luck "
          "player, choose whichever game mode drew "
          "your attention and play it as many times as you "
          "like.\n\n\n\n\n\n\n\n\n\nAnd... Who knows... If you are discerning "
          "enough"
          "... You might find our little "
          "secret.\n-------------------------\nSincerely, the developers.");

      printf("\n\n\n\n\n\nType any character to return.\n");
      scanf(" %c", &eleccion);
      if (eleccion != '0')
        salir = false;
      break;

    case 'g':
    case 'G': // modos de juego
      contador = 1;

      printf("\e[1;1H\e[2J");
      printf(" ____ \n||1 ||\n||__|| Labyrinth. \n|/__\\|\n");
      printf(" ____ \n||2 ||\n||__|| Fill the map. \n|/__\\|\n");
      printf(" ____ \n||3 ||\n||__|| Safe zone. \n|/__\\|\n");
      printf(" ____ \n||4 ||\n||__|| Psychedelic. \n|/__\\|\n");
      printf(" ____ \n||E ||\n||__|| Return. \n|/__\\|\n\n");
      scanf(" %c", &eleccion);
      if (eleccion == 's' || eleccion == 'S')
        salir = false;
      else if (eleccion == '1' || eleccion == '2' || eleccion == '3' ||
               eleccion == '4' || eleccion == '5' || eleccion == '6' ||
               eleccion == '7') {

        if (eleccion == '1') {
          int a;
          srand(time(NULL));
          a = rand() % 3;
          // para elegir el mapa del laberinto de forma aleatoria

          if (a == 0)
            *m = '1';
          else if (a == 1)
            *m = '2';
          else if (a == 2)
            *m = '3';

          salir = true;
          break;
        }

        if (eleccion == '2') {

          while (*m != '4' && *m != '5' && *m != '6') {

            printf("\e[1;1H\e[2J");
            printf(" ____ \n||1 ||\n||__|| Map 1. \n|/__\\|\n");
            printf(" ____ \n||2 ||\n||__|| Map 2. \n|/__\\|\n");
            printf(" ____ \n||3 ||\n||__|| Map 3. \n|/__\\|\n");
            printf("\n");

            scanf(" %c", &eleccion);

            if (eleccion == '1') {
              *m = '4'; // primer mapa de relleno
              salir = true;
            }
            if (eleccion == '2') {
              *m = '5'; // segundo mapa de relleno
              salir = true;
            }
            if (eleccion == '3') {
              *m = '6'; // tercer mapa de relleno
              salir = true;
            }
          }

          break;
        }

        if (eleccion == '3') {

          while (*m != '7' && *m != '8') {

            printf("\e[1;1H\e[2J");
            printf(" ____ \n||1 ||\n||__|| Map 1. \n|/__\\|\n");
            printf(" ____ \n||2 ||\n||__|| Map 2. \n|/__\\|\n");
            printf("\n");

            scanf(" %c", &eleccion);

            if (eleccion == '1') {
              *m = '7'; // primer mapa de enemigos
              salir = true;
            }
            if (eleccion == '2') {
              *m = '8'; // segundo mapa de enemigos
              salir = true;
            }
          }

          break;
        }

        if (eleccion == '4') {

          *m = '9'; // mapa modo psicodélico
          salir = true;
          break;
        }

        if (eleccion == 'E' || eleccion == 'e') {

          salir = false;
          break;
        }
      }

      break;

    case 'e':
    case 'E': // salir del programa
      salir = true;
      printf("\e[1;1H\e[2J");
      exit(0);
      break;
    }
  }
}
