
// incluyo los archivos de mis compañeros
#include "andrei.c"
#include "mapasLaberintos.c"
#include "nathan.c"
#include "luca.c"

#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int direccionEnemigoRandom(){
    return rand()%4  +1;
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

  struct enemigo enemigos[100];
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
    // inicialización de enemigos
    numeroDeEnemigos=57;

    // sala 1
    enemigos[0].state=0;
    enemigos[0].posey=23; //enemigo 1
    enemigos[0].posex=48;
    enemigos[1].posex=40; // enemigo2
    enemigos[1].posey=21;
    enemigos[2].posex=48; // enemigo3 
    enemigos[2].posey=19;  
    enemigos[3].posex=40; // enemigo4
    enemigos[3].posey=17;

    // sala 2
    enemigos[4].state=0;
    enemigos[5].state=0;
    enemigos[4].posex=48; // enemigo5
    enemigos[4].posey=1;
    enemigos[5].posex=47; // enemigo6
    enemigos[5].posey=1;
    enemigos[6].posex=46; // enemigo7
    enemigos[6].posey=1;
    enemigos[7].posex=45; // enemigo8
    enemigos[7].posey=1;
    enemigos[8].posex=44; // enemigo9
    enemigos[8].posey=1;
    enemigos[9].posex=43; // enemigo10
    enemigos[9].posey=1;
    enemigos[10].posex=42; // enemigo11
    enemigos[10].posey=1;
    enemigos[11].posex=41; // enemigo12
    enemigos[11].posey=1;
    enemigos[12].posex=40; // enemigo13
    enemigos[12].posey=1;


    // sala 3

    enemigos[19].posex=32; // enemigo20
    enemigos[19].posey=5;
    enemigos[20].posex=32; // enemigo21
    enemigos[20].posey=10;


    // sala 4
    enemigos[13].posex=34; // enemigo14
    enemigos[13].posey=20;

    enemigos[14].posex=34; // enemigo15
    enemigos[14].posey=16;

    enemigos[15].posex=27; // enemigo16
    enemigos[15].posey=20;

    enemigos[16].posex=27; // enemigo17
    enemigos[16].posey=22;

    enemigos[17].posex=27; // enemigo18
    enemigos[17].posey=18;

    enemigos[18].posex=27; // enemigo19
    enemigos[18].posey=16;

    // sala 5
    enemigos[21].state=0;
    enemigos[22].state=0;
    enemigos[23].state=0;
    enemigos[24].state=0;

    enemigos[21].posex=10; // enemigo19
    enemigos[21].posey=5;

    enemigos[22].posex=20; // enemigo19
    enemigos[22].posey=5;

    enemigos[23].posex=10; // enemigo19
    enemigos[23].posey=20;

    enemigos[24].posex=20; // enemigo19
    enemigos[24].posey=20;





    break;

  case '8':
    // mapa enemigo2
    mapa1(tablero);
    existeSavezone = true;
    // se inicializan las variables de los enemigos
    enemigos[0].posey = 8;
    enemigos[0].posex = 8;
    enemigos[0].state = 1;

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
      for (int i = 0; i<numeroDeEnemigos; i++) {
        tablero[enemigos[i].posey][enemigos[i].posex] = 2;
      }

      // sala 1
      if (enemigos[0].state==0) {
        enemigos[0].posex--;
        enemigos[2].posex--;
        enemigos[1].posex++;
        enemigos[3].posex++;
      }else {
        enemigos[0].posex++;
        enemigos[2].posex++;
        enemigos[1].posex--;
        enemigos[3].posex--;
      }

      if (enemigos[0].posex==40) {
        enemigos[0].state=1;
      }else if (enemigos[0].posex==48) {
        enemigos[0].state=0;
      }

      // sala 2
      if (posx ==48 && posy==10 && enemigos[5].state==0) {
        enemigos[4].state=1;
      }
      if (enemigos[4].state==1 ) {
        for (int i = 4; i<13; i++) {
          enemigos[i].posey++;
        }
      }else if (enemigos[4].state==2) {
        for (int i = 4; i<13; i++) {
          enemigos[i].posey=20;
          enemigos[i].posex=34;
        }
        enemigos[5].state=1;

      }
      if (enemigos[4].posey==10) {
        enemigos[4].state=2;
      }
      // sala 3

      srand(time(NULL));
      enemigos[19].state=direccionEnemigoRandom();
      if (enemigos[19].state==1 && tablero[enemigos[19].posey+1][enemigos[19].posex]!=1 &&  !(enemigos[19].posey+1>12)) {
      enemigos[19].posey++;
      }
      if (enemigos[19].state==2 && tablero[enemigos[19].posey-1][enemigos[19].posex]!=1 && !(enemigos[19].posey-1<4)) {
      enemigos[19].posey--;
      }
      if (enemigos[19].state==3 && tablero[enemigos[19].posey][enemigos[19].posex+1]!=1) {
      enemigos[19].posex++;
      }
      if (enemigos[19].state==4 && tablero[enemigos[19].posey][enemigos[19].posex-1]!=1) {
      enemigos[19].posex--;
      }

      enemigos[20].state=direccionEnemigoRandom();
      if (enemigos[20].state==1 && tablero[enemigos[20].posey+1][enemigos[20].posex]!=1 &&  !(enemigos[20].posey+1>12)) {
      enemigos[20].posey++;
      }
      if (enemigos[20].state==2 && tablero[enemigos[20].posey-1][enemigos[20].posex]!=1 && !(enemigos[20].posey-1<4)) {
      enemigos[20].posey--;
      }
      if (enemigos[20].state==3 && tablero[enemigos[20].posey][enemigos[20].posex+1]!=1) {
      enemigos[20].posex++;
      }
      if (enemigos[20].state==4 && tablero[enemigos[20].posey][enemigos[20].posex-1]!=1) {
      enemigos[20].posex--;
      }

      // sala 5
      
      if (enemigos[21].state==0) {
        enemigos[25].posex=enemigos[21].posex; // enemigo19
        enemigos[25].posey=enemigos[21].posey+2;
        enemigos[26].posex=enemigos[21].posex; // enemigo19
        enemigos[26].posey=enemigos[21].posey+3;
        enemigos[27].posex=enemigos[21].posex+2; // enemigo19
        enemigos[27].posey=enemigos[21].posey;
        enemigos[28].posex=enemigos[21].posex+3; // enemigo19
        enemigos[28].posey=enemigos[21].posey;
        enemigos[29].posex=enemigos[21].posex; // enemigo19
        enemigos[29].posey=enemigos[21].posey-2;
        enemigos[30].posex=enemigos[21].posex; // enemigo19
        enemigos[30].posey=enemigos[21].posey-3;
        enemigos[31].posex=enemigos[21].posex-2; // enemigo19
        enemigos[31].posey=enemigos[21].posey;
        enemigos[32].posex=enemigos[21].posex-3; // enemigo19
        enemigos[32].posey=enemigos[21].posey;

        enemigos[21].state++;
      }
      else if (enemigos[21].state==1) {
        enemigos[26].posex--;
        enemigos[28].posey++;
        enemigos[30].posex++; 
        enemigos[32].posey--;

        enemigos[21].state++;
      }
      else if (enemigos[21].state==2) {
        enemigos[25].posex--;
        enemigos[26].posex--;
        enemigos[27].posey++;
        enemigos[28].posey++;
        enemigos[29].posex++; 
        enemigos[30].posex++; 
        enemigos[31].posey--;
        enemigos[32].posey--;

        enemigos[21].state++;
      }else if (enemigos[21].state==3){
        enemigos[25].posex--;
        enemigos[26].posex--;
        enemigos[27].posey++;
        enemigos[28].posey++;
        enemigos[29].posex++; 
        enemigos[30].posex++; 
        enemigos[31].posey--;
        enemigos[32].posey--;

        enemigos[21].state++;
      }else if (enemigos[21].state==4) {
        enemigos[25].posey--;
        enemigos[27].posex--;
        enemigos[29].posey++;
        enemigos[31].posex++;
        enemigos[26].posey--;
        enemigos[28].posex--;
        enemigos[30].posey++;
        enemigos[32].posex++;

        enemigos[21].state=0;
      }


      if (enemigos[22].state==0) {
        enemigos[33].posex=enemigos[22].posex; // enemigo19
        enemigos[33].posey=enemigos[22].posey+2;
        enemigos[34].posex=enemigos[22].posex; // enemigo19
        enemigos[34].posey=enemigos[22].posey+3;
        enemigos[35].posex=enemigos[22].posex+2; // enemigo19
        enemigos[35].posey=enemigos[22].posey;
        enemigos[36].posex=enemigos[22].posex+3; // enemigo19
        enemigos[36].posey=enemigos[22].posey;
        enemigos[37].posex=enemigos[22].posex; // enemigo19
        enemigos[37].posey=enemigos[22].posey-2;
        enemigos[38].posex=enemigos[22].posex; // enemigo19
        enemigos[38].posey=enemigos[22].posey-3;
        enemigos[39].posex=enemigos[22].posex-2; // enemigo19
        enemigos[39].posey=enemigos[22].posey;
        enemigos[40].posex=enemigos[22].posex-3; // enemigo19
        enemigos[40].posey=enemigos[22].posey;

        enemigos[22].state++;
      }
      else if (enemigos[22].state==1) {
        enemigos[34].posex--;
        enemigos[36].posey++;
        enemigos[38].posex++; 
        enemigos[40].posey--;

        enemigos[22].state++;
      }
      else if (enemigos[22].state==2) {
        enemigos[33].posex--;
        enemigos[34].posex--;
        enemigos[35].posey++;
        enemigos[36].posey++;
        enemigos[37].posex++; 
        enemigos[38].posex++; 
        enemigos[39].posey--;
        enemigos[40].posey--;

        enemigos[22].state++;
      }else if (enemigos[22].state==3){
        enemigos[33].posex--;
        enemigos[34].posex--;
        enemigos[35].posey++;
        enemigos[36].posey++;
        enemigos[37].posex++; 
        enemigos[38].posex++; 
        enemigos[39].posey--;
        enemigos[40].posey--;

        enemigos[22].state++;
      }else if (enemigos[22].state==4) {
        enemigos[33].posey--;
        enemigos[35].posex--;
        enemigos[37].posey++;
        enemigos[39].posex++;
        enemigos[34].posey--;
        enemigos[36].posex--;
        enemigos[38].posey++;
        enemigos[40].posex++;

        enemigos[22].state=0;
      }

      if (enemigos[23].state==0) {
        enemigos[41].posex=enemigos[23].posex; // enemigo19
        enemigos[41].posey=enemigos[23].posey+2;
        enemigos[42].posex=enemigos[23].posex; // enemigo19
        enemigos[42].posey=enemigos[23].posey+3;
        enemigos[43].posex=enemigos[23].posex+2; // enemigo19
        enemigos[43].posey=enemigos[23].posey;
        enemigos[44].posex=enemigos[23].posex+3; // enemigo19
        enemigos[44].posey=enemigos[23].posey;
        enemigos[45].posex=enemigos[23].posex; // enemigo19
        enemigos[45].posey=enemigos[23].posey-2;
        enemigos[46].posex=enemigos[23].posex; // enemigo19
        enemigos[46].posey=enemigos[23].posey-3;
        enemigos[47].posex=enemigos[23].posex-2; // enemigo19
        enemigos[47].posey=enemigos[23].posey;
        enemigos[48].posex=enemigos[23].posex-3; // enemigo19
        enemigos[48].posey=enemigos[23].posey;

        enemigos[23].state++;
      }
      else if (enemigos[23].state==1) {
        enemigos[42].posex--;
        enemigos[44].posey++;
        enemigos[46].posex++; 
        enemigos[48].posey--;

        enemigos[23].state++;
      }
      else if (enemigos[23].state==2) {
        enemigos[41].posex--;
        enemigos[42].posex--;
        enemigos[43].posey++;
        enemigos[44].posey++;
        enemigos[45].posex++; 
        enemigos[46].posex++; 
        enemigos[47].posey--;
        enemigos[48].posey--;

        enemigos[23].state++;
      }else if (enemigos[23].state==3){
        enemigos[41].posex--;
        enemigos[42].posex--;
        enemigos[43].posey++;
        enemigos[44].posey++;
        enemigos[45].posex++; 
        enemigos[46].posex++; 
        enemigos[47].posey--;
        enemigos[48].posey--;

        enemigos[23].state++;
      }else if (enemigos[23].state==4) {
        enemigos[41].posey--;
        enemigos[43].posex--;
        enemigos[45].posey++;
        enemigos[47].posex++;
        enemigos[42].posey--;
        enemigos[44].posex--;
        enemigos[46].posey++;
        enemigos[48].posex++;

        enemigos[23].state=0;
      }

      if (enemigos[24].state==0) {
        enemigos[49].posex=enemigos[24].posex; // enemigo19
        enemigos[49].posey=enemigos[24].posey+2;
        enemigos[50].posex=enemigos[24].posex; // enemigo19
        enemigos[50].posey=enemigos[24].posey+3;
        enemigos[51].posex=enemigos[24].posex+2; // enemigo19
        enemigos[51].posey=enemigos[24].posey;
        enemigos[52].posex=enemigos[24].posex+3; // enemigo19
        enemigos[52].posey=enemigos[24].posey;
        enemigos[53].posex=enemigos[24].posex; // enemigo19
        enemigos[53].posey=enemigos[24].posey-2;
        enemigos[54].posex=enemigos[24].posex; // enemigo19
        enemigos[54].posey=enemigos[24].posey-3;
        enemigos[55].posex=enemigos[24].posex-2; // enemigo19
        enemigos[55].posey=enemigos[24].posey;
        enemigos[56].posex=enemigos[24].posex-3; // enemigo19
        enemigos[56].posey=enemigos[24].posey;

        enemigos[24].state++;
      }
      else if (enemigos[24].state==1) {
        enemigos[50].posex--;
        enemigos[52].posey++;
        enemigos[54].posex++; 
        enemigos[56].posey--;

        enemigos[24].state++;
      }
      else if (enemigos[24].state==2) {
        enemigos[49].posex--;
        enemigos[50].posex--;
        enemigos[51].posey++;
        enemigos[52].posey++;
        enemigos[53].posex++; 
        enemigos[54].posex++; 
        enemigos[55].posey--;
        enemigos[56].posey--;

        enemigos[24].state++;
      }else if (enemigos[24].state==3){
        enemigos[49].posex--;
        enemigos[50].posex--;
        enemigos[51].posey++;
        enemigos[52].posey++;
        enemigos[53].posex++; 
        enemigos[54].posex++; 
        enemigos[55].posey--;
        enemigos[56].posey--;

        enemigos[24].state++;
      }else if (enemigos[24].state==4) {
        enemigos[49].posey--;
        enemigos[51].posex--;
        enemigos[53].posey++;
        enemigos[55].posex++;
        enemigos[50].posey--;
        enemigos[52].posex--;
        enemigos[54].posey++;
        enemigos[56].posex++;

        enemigos[24].state=0;
      }

      break;

    case '8':
      mapa1(tablero);

      tablero[enemigos[0].posey][enemigos[0].posex] = 2;
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;

      // actualización enemigo 1
      if (enemigos[0].state == 1) {
        enemigos[0].posey++;
      } else if (enemigos[0].state == 2) {
        enemigos[0].posey--;
      }
      if (enemigos[0].posey == 1) {
        enemigos[0].state= 1;
      } else if (enemigos[0].posey == tamanoy - 2) {
        enemigos[0].state=2;
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

      break;
    case 's':

      if (tablero[posy + 1][posx] != 1 && tablero[posy + 1][posx] != 9 &&
          tablero[posy + 1][posx] != 8) {
        tablero[posy][posx] = 4;
        posy = posy + 1;
      }
      break;
    case 'd':
      if (tablero[posy][posx + 1] != 1 && tablero[posy][posx + 1] != 9 &&
          tablero[posy][posx + 1] != 8) {
        tablero[posy][posx] = 4;
        posx = posx + 1;
      }
      break;
    case 'a':
      if (tablero[posy][posx - 1] != 1 && tablero[posy][posx - 1] != 9 &&
          tablero[posy][posx - 1] != 8) {
        tablero[posy][posx] = 4;
        posx = posx - 1;
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

    // las colisiones con los enemigos para cada mapa
    if (opcion=='7') {
        for (int i =0 ; i< numeroDeEnemigos ; i++) {
          if (enemigos[i].posex==posx && enemigos[i].posey==posy ) {
            gameState=2;
          }
        }
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
