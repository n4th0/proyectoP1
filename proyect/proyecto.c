
// incluyo los archivos de mis compañeros
#include "andrei.c"
#include "luca.c"
#include "nathan.c"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/////
///// 	LAS COORDENADAS ESTAN INTERCAMBIADAS, LA X = Y ; LA Y = X.
/////

#define tamanox 27
#define tamanoy 100

#define POSICION_INICIAL_PLMANX 24
#define POSICION_INICIAL_PLMANY 97
#define POSICION_INICIAL_SAVEZONEX 1
#define POSICION_INICIAL_SAVEZONEY 3

void dibujar_tablero(int tablero[tamanox][tamanoy]) {
  printf("\n");
  for (int i = 0; i < tamanox; i++) {
    printf("          ");
    for (int j = 0; j < tamanoy; j++) {

      switch (tablero[i][j]) {
      case 0:
        // nada
        printf(" ");
        break;
      case 1:
        // pared
        printf("\x1b[37m"
               "\x1b[47m"
               " "
               "\x1b[0m");
        break;
      case 2:
        // enemigo
        printf("\x1b[31m"
               "\x1b[41m"
               " "
               "\x1b[0m");
        break;
      case 3:
        // plman
        printf("\x1b[33m"
               "\x1b[43m"
               " "
               "\x1b[0m");
        break;
      case 4:
        // save zone
        printf("\x1b[32m"
               "\x1b[42m"
               " "
               "\x1b[0m");
        break;
      default:
        // codigo de error
        printf("\x1b[31m"
               "E"
               "\x1b[0m");

        break;
      }
    }
    printf("\n");
  }
}

char preguntardireccion() {
  char direccion;
  initscr();
  raw();
  keypad(stdscr, true);
  noecho();
  do {
    direccion = getch();
    if (direccion == 'p') {
      printf("\e[1;1H\e[2J");
      printf("el juego ha sido interrumpido\n");
      endwin();
      exit(0);
    }
    if (direccion != 'w' && direccion != 'd' && direccion != 's' &&
        direccion != 'a') {
      break;
    }

    endwin();

  } while (direccion != 'w' && direccion != 'd' && direccion != 's' &&
           direccion != 'a');
  return direccion;
}



/// patorjk.com/software/taag para usar el menu del mapa
// usar small keyboard para poner las opciones
// usar o8 para poner el "menu mapa"
// larry 3d para el nombre del juego

int main() {
char c = ' ';
  // posición inicial de plman
  int posx = POSICION_INICIAL_PLMANX, posy = POSICION_INICIAL_PLMANY;
  int posy1 = posy - 1;

  int posex = 8, posey = 5;
  int posey1 = posey - 1;

  int posSx = POSICION_INICIAL_SAVEZONEX, posSy = POSICION_INICIAL_SAVEZONEY;
  int posSy1 = posSy - 1;

  int tablero2[tamanox][tamanoy];

  // estado de game, cambiar para terminar el juego
  // segun el estado final (si ha ganado ) enviar un mensaje
  // y si ha perdido otro
  int game = 1;


  int estado = 1;
  char opcion;

  // funcion de andrei.c
  menu(&opcion);

  do {

    printf("\e[1;1H\e[2J");

    switch (opcion) {
    case '1':
      mapa1(tablero2);
      break;

    }

    // indica la posicion de plman
    tablero2[posx][posy1] = 3;
    tablero2[posx][posy] = 3;

    // indica la posicion de enemigos
    tablero2[posex][posey1] = 2;
    tablero2[posex][posey] = 2;

    // indica la posición de la save zone
    tablero2[posSx][posSy1] = 4;
    tablero2[posSx][posSy] = 4;

    dibujar_tablero(tablero2);

    c = preguntardireccion();
    // esto se podría poner en una función (hay que esperar que la profesora nos
    // pase la librería) actualización de plman
    switch (c) {
    case 'w':
      if (tablero2[posx - 1][posy] != 1 && tablero2[posx - 1][posy1] != 1) {
        posx = posx - 1;
      }
      break;
    case 's':

      if (tablero2[posx + 1][posy] != 1 && tablero2[posx + 1][posy1] != 1) {
        posx = posx + 1;
      }
      break;
    case 'd':
      if (tablero2[posx][posy + 2] != 1 && tablero2[posx][posy + 1] != 1) {
        posy = posy + 2;
        posy1 = posy1 + 2;
      } else if (tablero2[posx][posy + 1] != 1) {
        posy = posy + 1;
        posy1 = posy1 + 1;
      }
      break;
    case 'a':
      if (tablero2[posx][posy1 - 2] != 1 && tablero2[posx][posy1 - 1] != 1) {
        posy = posy - 2;
        posy1 = posy1 - 2;
      } else if (tablero2[posx][posy1 - 1] != 1) {

        posy = posy - 1;
        posy1 = posy1 - 1;
      }
      break;
    }

    // esto varía según el mapa
    // actualización enemigo 1
    if (estado == 1) {
      posex++;
    } else if (estado == 2) {
      posex--;
    }
    if (posex == 1) {
      estado = 1;
    } else if (posex == tamanox - 2) {
      estado = 2;
    }

    // colisiones
    if (posex == posx && posey1 == posy1 || posex == posx && posey == posy1 ||
        posex == posx && posey1 == posy) {
      game = 2;
    }
    // colision save zone
    if (posSx == posx && posSy1 == posy1 || posSx == posx && posSy == posy1 ||
        posSx == posx && posSy1 == posy) {
      game = 3;
    }
  } while (game == 1);

  printf("\e[1;1H\e[2J");

  // for (int i =0; i<tamañox; i++) {
  //     printf("          ");
  //     for (int j =0; j<tamañoy; j++) {
  //         printf("%d",tablero2[i][j]);
  //     }
  //     printf("\n");
  // }

  // mensajes de salida (se puede hacer algun patron bonito para celebrar o
  // paralamentar el ganar o perder) @Luca esta es la tuya (lo quiero en gfx )
  if (game == 2) {
    printf("Te han matado los enemigos!!!\n");

  } else if (game == 3) {
    printf("Has llegado a salvo, enhorabuena!!!\n");
  }
}
