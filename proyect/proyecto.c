
// incluyo los archivos de mis compañeros
#include "andrei.c"
#include "mapasLaberintos.c"
#include "nathan.c"
#include "luca.c"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define tamanoy 27
#define tamanox 50

#define POSICION_INICIAL_PLMANX 25
#define POSICION_INICIAL_PLMANY 48
#define POSICION_INICIAL_SAVEZONEX 1
#define POSICION_INICIAL_SAVEZONEY 1

struct enemigo {
  int posey;
  int posex;
  int state;
};

void dibujarTablero(int tablero[tamanoy][tamanox]) {
  printf("\n");
  for (int i = 0; i < tamanoy; i++) {
    printf("          ");
    for (int j = 0; j < tamanox; j++) {

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
      case 8:
        // azul cian
        printf("\x1b[36m"
               "\x1b[46m"
               "  "
               "\x1b[0m");
        break;
      case 9:
        // azul
        printf("\x1b[30m"
               "\x1b[40m"
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

char preguntarDireccion() {
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

int colisionSave(int posy, int posx, bool existeSavezone) {

  if (POSICION_INICIAL_SAVEZONEX == posy &&
      POSICION_INICIAL_SAVEZONEY == posx && existeSavezone) {
    return 3;
  } else {
    return 1;
  }
}

void copiarAuxiliar(int tablero[tamanoy][tamanox],
                    int tableroAuxiliar[tamanoy][tamanox]) {
  for (int i = 0; i < tamanoy; i++) {
    for (int j = 0; j < tamanox; j++) {
      tablero[i][j] = tableroAuxiliar[i][j];
    }
  }
}

int main() {

  // posición inicial de plman
  int posy = POSICION_INICIAL_PLMANX, posx = POSICION_INICIAL_PLMANY;

  bool existeSavezone = false;
  bool stateEasterEgg = false;

  struct enemigo enemigo1[50];
  int choqueEnemigo=0;
  int numeroDeEnemigos;

  int tablero[tamanoy][tamanox];
  int tableroAuxiliar[tamanoy][tamanox];

  int contadorRelleno;

  // estado del juego
  // 1-> jugando
  // 2-> perdido
  // 3-> ganado
  int gameState = 1;

  // funcion de andrei.c
  char opcion;
  menu(&opcion);

  switch (opcion) {

// mapas de resolver laberintos
  case '1':
    mapaLC(tablero);

    tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;
    existeSavezone = true;
    for (int i = 0; i < tamanoy; i++) {
      for (int j = 0; j < tamanox; j++) {
        tableroAuxiliar[i][j] = tablero[i][j];
      }
    }

    break;
  case '2':
    mapaLA(tablero);

    tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;
    existeSavezone = true;
    for (int i = 0; i < tamanoy; i++) {
      for (int j = 0; j < tamanox; j++) {
        tableroAuxiliar[i][j] = tablero[i][j];
      }
    }
    break;
  case '3':
    mapaLB(tablero);

    tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;
    existeSavezone = true;
    // esto se hace ya que el mapa tiene componentes aleatorias
    for (int i = 0; i < tamanoy; i++) {
      for (int j = 0; j < tamanox; j++) {
        tableroAuxiliar[i][j] = tablero[i][j];
      }
    }
    break;

// mapas de rellenar
  case '4':
    mapaRelleno1Actu(tablero);
    break;
  case '5':
    mapaRelleno2(tablero);
    break;
  case '6':
    mapaRelleno3(tablero);
    posy = POSICION_INICIAL_PLMANX / 2, posx = POSICION_INICIAL_PLMANY / 2;
    break;

// mapas con enemigos (durísimo)
  case '7':
    // mapa enemigo1
    enemigosMapa1(tablero);

    existeSavezone = true;

    break;

  case '8':
    // mapa enemigo2
    mapa1(tablero);
    existeSavezone = true;


    // se inicializan las variables de los enemigos
    enemigo1[0].posey = 8;
    enemigo1[0].posex = 8;
    enemigo1[0].state = 1;

    break;

// mapa aleatorio 
  case '9':
    existeSavezone = true;
    psicodeliaMapa(tablero);

    break;
  }

  do {

    switch (opcion) {
// mapas de resolver el laberinto
    case '1':

      copiarAuxiliar(tablero, tableroAuxiliar);
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;

      break;
    case '2':

      copiarAuxiliar(tablero, tableroAuxiliar);
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;

      break;
    case '3':

      copiarAuxiliar(tablero, tableroAuxiliar);
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;

      break;
// mapas con enemigos
    case '7':
      enemigosMapa1(tablero);
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;

      break;

    case '8':
      mapa1(tablero);

      tablero[enemigo1[0].posey][enemigo1[0].posex] = 2;
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;

      // actualización enemigo 1
      if (enemigo1[0].state == 1) {
        enemigo1[0].posey++;
      } else if (enemigo1[0].state == 2) {
        enemigo1[0].posey--;
      }
      if (enemigo1[0].posey == 1) {
        enemigo1[0].state= 1;
      } else if (enemigo1[0].posey == tamanoy - 2) {
        enemigo1[0].state=2;
      }

      break;

    case '9':
      if (!stateEasterEgg) {
        psicodeliaMapa(tablero);

      } else {
        // mapa easteregg
        easterEgg(tablero);
      }
      if (posx == 48 && posy == 1) {
        stateEasterEgg = true;
      }
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;
      break;
    }

    printf("\e[1;1H\e[2J");

    // indica la posicion de plman
    tablero[posy][posx] = 3;

    dibujarTablero(tablero);

    // movimiento del personaje y colisiones con paredes (1)
    switch (preguntarDireccion()) {
    case 'w':
      if (tablero[posy - 1][posx] != 1 && tablero[posy - 1][posx] != 9 &&
          tablero[posy - 1][posx] != 8) {
        tablero[posy][posx] = 4;
        posy = posy - 1;
      }
      if(tablero[posy - 1][posx] == 2 ){
        choqueEnemigo=1;
      }

      break;
    case 's':

      if (tablero[posy + 1][posx] != 1 && tablero[posy + 1][posx] != 9 &&
          tablero[posy + 1][posx] != 8) {
        tablero[posy][posx] = 4;
        posy = posy + 1;
      }
      if(tablero[posy + 1][posx] == 2 ){
        choqueEnemigo=1;
      }
      break;
    case 'd':
      if (tablero[posy][posx + 1] != 1 && tablero[posy][posx + 1] != 9 &&
          tablero[posy][posx + 1] != 8) {
        tablero[posy][posx] = 4;
        posx = posx + 1;
      }
      if(tablero[posy][posx+1] == 2 ){
        choqueEnemigo=1;
      }
      break;
    case 'a':
      if (tablero[posy][posx - 1] != 1 && tablero[posy][posx - 1] != 9 &&
          tablero[posy][posx - 1] != 8) {
        tablero[posy][posx] = 4;
        posx = posx - 1;
      }
      if(tablero[posy][posx-1] == 2 ){
        choqueEnemigo=1;
      }
      break;
    }

    gameState = colisionSave(posy, posx, existeSavezone);

    // necesario para mapas con relleno
    contadorRelleno = 0;
    for (int i = 0; i < tamanoy; i++) {
      for (int j = 0; j < tamanox; j++) {
        if (tablero[i][j] == 0) {
          contadorRelleno++;
        }
      }
    }

    if (contadorRelleno == 0 && !existeSavezone) {
      gameState = 3;
    }
    if (choqueEnemigo==1) {
      gameState=2;
    
    }

  } while (gameState == 1);

  printf("\e[1;1H\e[2J");

  // mensajes de salida (se puede hacer algun patron bonito para celebrar o
  // paralamentar el ganar o perder) @Luca esta es la tuya (lo quiero en gfx )
  if (gameState == 2) {
    derrota();

  } else if (gameState == 3) {
    victoria();
  }
}
