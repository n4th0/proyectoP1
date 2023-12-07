
// incluyo los archivos de mis compañeros
#include "andrei.c"
#include "luca.c"
#include "mapasLaberintos.c"
#include "nathan.c"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

/////
///// 	LAS COORDENADAS ESTAN INTERCAMBIADAS, LA X = Y ; LA Y = X.
/////

#define tamanox 27
#define tamanoy 50

#define POSICION_INICIAL_PLMANX 25
#define POSICION_INICIAL_PLMANY 48
#define POSICION_INICIAL_SAVEZONEX 1
#define POSICION_INICIAL_SAVEZONEY 1
struct enemigo {
  int posex;
  int posey;
};

void dibujarTablero(int tablero[tamanox][tamanoy]) {
  printf("\n");
  for (int i = 0; i < tamanox; i++) {
    printf("          ");
    for (int j = 0; j < tamanoy; j++) {

      switch (tablero[i][j]) {
      case 0:
        // nada
        printf("  ");
        break;
      case 1:
        // pared
        printf("\x1b[37m"
               "\x1b[47m"
               "  "
               "\x1b[0m");
        break;
      case 2:
        // enemigo
        printf("\x1b[31m"
               "\x1b[41m"
               "  "
               "\x1b[0m");
        break;
      case 3:
        // plman
        printf("\x1b[33m"
               "\x1b[43m"
               "  "
               "\x1b[0m");
        break;
      case 4:
        // save zone
        printf("\x1b[32m"
               "\x1b[42m"
               "  "
               "\x1b[0m");
        break;
      default:
        // codigo de error
        printf("\x1b[31m"
               "EE"
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

  struct enemigo enemigo1;

  int posSx = POSICION_INICIAL_SAVEZONEX, posSy = POSICION_INICIAL_SAVEZONEY;

  int tablero2[tamanox][tamanoy];
  int tableroAuxiliar[tamanox][tamanoy];
  int contadorRelleno;

  // estado de game, cambiar para terminar el juego
  // segun el estado final (si ha ganado ) enviar un mensaje
  // y si ha perdido otro
  int game = 1;

  int estado = 1;

  // funcion de andrei.c
  char opcion;
  menu(&opcion);
  switch (opcion) {
  case '1':
    // indica la posición de la save zone (no tocar)
    tablero2[posSx][posSy] = 4;
    // inicialización del enemigo
    enemigo1.posex = 8;
    enemigo1.posey = 8;

    break;
  case '2':
    // indica la posición de la save zone (no tocar)
    tablero2[posSx][posSy] = 4;
    mapaLA(tablero2);
    for (int i = 0; i < tamanox; i++) {
      for (int j = 0; j < tamanoy; j++) {
        tableroAuxiliar[i][j] = tablero2[i][j];
      }
    }
    break;
  case '3':
    mapaLB(tablero2);
    // indica la posición de la save zone (no tocar)
    tablero2[posSx][posSy] = 4;
    for (int i = 0; i < tamanox; i++) {
      for (int j = 0; j < tamanoy; j++) {
        tableroAuxiliar[i][j] = tablero2[i][j];
      }
    }
    break;
  case '4':
    mapaLA(tablero2);
    // indica la posición de la save zone(no tocar)
    tablero2[posSx][posSy] = 4;
    for (int i = 0; i < tamanox; i++) {
      for (int j = 0; j < tamanoy; j++) {
        tableroAuxiliar[i][j] = tablero2[i][j];
      }
    }
    break;

  case '7':
    mapaRelleno(tablero2);
    for (int i = 0; i < tamanox; i++) {
      for (int j = 0; j < tamanoy; j++) {
        tableroAuxiliar[i][j] = tablero2[i][j];
      }
    }
  }

  do {

    switch (opcion) {
    case '1':
      mapa1(tablero2);

      // indica la posicion de enemigos
      tablero2[enemigo1.posex][enemigo1.posey] = 2;
      // esto varía según el mapa
      // actualización enemigo 1
      if (estado == 1) {
        enemigo1.posex++;
      } else if (estado == 2) {
        enemigo1.posex--;
      }
      if (enemigo1.posex == 1) {
        estado = 1;
      } else if (enemigo1.posex == tamanox - 2) {
        estado = 2;
      }

      // colisiones
      if (enemigo1.posex == posx && enemigo1.posey == posy) {
        game = 2;
      }
      // colision save zone
      if (posSx == posx && posSy == posy) {
        game = 3;
      }
      break;

    case '2':
      for (int i = 0; i < tamanox; i++) {
        for (int j = 0; j < tamanoy; j++) {
          tablero2[i][j] = tableroAuxiliar[i][j];
        }
      }
      // colision save zone
      if (posSx == posx && posSy == posy) {
        game = 3;
      }
      break;
    case '3':
      for (int i = 0; i < tamanox; i++) {
        for (int j = 0; j < tamanoy; j++) {
          tablero2[i][j] = tableroAuxiliar[i][j];
        }
      }
      // colision save zone
      if (posSx == posx && posSy == posy) {
        game = 3;
      }
      break;
    case '4':
      for (int i = 0; i < tamanox; i++) {
        for (int j = 0; j < tamanoy; j++) {
          tablero2[i][j] = tableroAuxiliar[i][j];
        }
      }
      // colision save zone
      if (posSx == posx && posSy == posy) {
        game = 3;
      }
      break;

    case '7':
      break;
    }

    contadorRelleno = 0;

    for (int i = 0; i < tamanox; i++) {
      for (int j = 0; j < tamanoy; j++) {
        if (tablero2[i][j] == 0) {
          contadorRelleno++;
        }
      }
    }
    if (contadorRelleno == 0) {
      game = 3;
    }

    printf("\e[1;1H\e[2J");

    // indica la posicion de plman
    tablero2[posx][posy] = 3;

    dibujarTablero(tablero2);

    c = preguntardireccion();
    // esto se podría poner en una función (hay que esperar que la profesora nos
    // pase la librería) actualización de plman
    switch (c) {
    case 'w':
      if (tablero2[posx - 1][posy] != 1) {
        posx = posx - 1;
      }
      break;
    case 's':

      if (tablero2[posx + 1][posy] != 1) {
        posx = posx + 1;
      }
      break;
    case 'd':
      if (tablero2[posx][posy + 1] != 1) {
        posy = posy + 1;
      }
      break;
    case 'a':
      if (tablero2[posx][posy - 1] != 1) {
        posy = posy - 1;
      }
      break;
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
