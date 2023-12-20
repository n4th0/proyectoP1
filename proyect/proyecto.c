
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
      case 12:
        // azul cian
        printf("\x1b[36m"
               "\x1b[46m"
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
      printf("Game has been interrupted.\n");
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
    mapaRelleno1(tablero);
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
    numeroDeEnemigos=75;

    // sala 1
    enemigos[0].state=0;
    enemigos[0].posey=23;  
    enemigos[0].posex=48;
    enemigos[1].posex=40;  
    enemigos[1].posey=21;
    enemigos[2].posex=48;   
    enemigos[2].posey=19;  
    enemigos[3].posex=40;  
    enemigos[3].posey=17;

    // sala 2
    enemigos[4].state=0;
    enemigos[5].state=0;
    enemigos[4].posex=48;  
    enemigos[4].posey=1;
    enemigos[5].posex=47;  
    enemigos[5].posey=1;
    enemigos[6].posex=46;  
    enemigos[6].posey=1;
    enemigos[7].posex=45;  
    enemigos[7].posey=1;
    enemigos[8].posex=44;  
    enemigos[8].posey=1;
    enemigos[9].posex=43;  
    enemigos[9].posey=1;
    enemigos[10].posex=42;  
    enemigos[10].posey=1;
    enemigos[11].posex=41;  
    enemigos[11].posey=1;
    enemigos[12].posex=40;  
    enemigos[12].posey=1;


    // sala 3

    enemigos[19].posex=32;  
    enemigos[19].posey=5;
    enemigos[20].posex=32;  
    enemigos[20].posey=10;


    // sala 4
    enemigos[13].posex=34;  
    enemigos[13].posey=20;

    enemigos[14].posex=34;  
    enemigos[14].posey=16;

    enemigos[15].posex=27;  
    enemigos[15].posey=20;

    enemigos[16].posex=27;  
    enemigos[16].posey=22;

    enemigos[17].posex=27;  
    enemigos[17].posey=18;

    enemigos[18].posex=27;  
    enemigos[18].posey=16;

    // sala 5
    enemigos[21].state=0;
    enemigos[22].state=0;
    enemigos[23].state=0;
    enemigos[24].state=0;


    enemigos[21].posex=10;  
    enemigos[21].posey=6;

    enemigos[22].posex=20;  
    enemigos[22].posey=6;

    enemigos[23].posex=10;  
    enemigos[23].posey=20;

    enemigos[24].posex=20;  
    enemigos[24].posey=20;

    enemigos[57].posex=10;  
    enemigos[57].posey=13;

    enemigos[58].posex=20;  
    enemigos[58].posey=13;

    break;

  case '8':
    // mapa enemigo2
    mapaEnemigos2(tablero);
    existeSavezone = true;
    // se inicializan las variables de los enemigos
    numeroDeEnemigos = 67;

    enemigos[0].posey = 25;       //enemigo 0, del inicio
    enemigos[0].posex = 40;
    enemigos[0].state = 0;

    //enemigos de las primeras barras horizontales

    enemigos[1].posey = 22;       //enemigo 1
    enemigos[1].posex = 45;
    enemigos[1].state = 0;
    enemigos[2].posey = 19;       //enemigo 2
    enemigos[2].posex = 39;
    enemigos[2].state = 0;
    enemigos[3].posey = 16;       //enemigo 3
    enemigos[3].posex = 45;
    enemigos[3].state = 0;

    //enemigos de la primera sala grande

    enemigos[4].posey = 7;        //enemigo 4
    enemigos[4].posex = 35;
    enemigos[4].state = 0;
    enemigos[5].posey = 7;        //enemigo 5
    enemigos[5].posex = 35;
    enemigos[5].state = 0;
    enemigos[6].posey = 7;        //enemigo 6
    enemigos[6].posex = 35;
    enemigos[6].state = 0;
    enemigos[7].posey = 7;        //enemigo 7
    enemigos[7].posex = 35;
    enemigos[7].state = 0;
    enemigos[8].posey = 7;        //enemigo 8
    enemigos[8].posex = 35;
    enemigos[8].state = 0;
    enemigos[9].posey = 7;        //enemigo 9
    enemigos[9].posex = 35;
    enemigos[9].state = 0;
    enemigos[10].posey = 7;       //enemigo 10
    enemigos[10].posex = 35;
    enemigos[10].state = 0;
    enemigos[11].posey = 7;       //enemigo 11
    enemigos[11].posex = 35;
    enemigos[11].state = 0;

    //enemigos de las segundas barras horizontales

    enemigos[12].posey = 16;      //enemigo 12
    enemigos[12].posex = 31;
    enemigos[12].state = 0;
    enemigos[13].posey = 19;      //enemigo 13
    enemigos[13].posex = 37;
    enemigos[13].state = 0;
    enemigos[14].posey = 22;      //enemigo 14
    enemigos[14].posex = 31;
    enemigos[14].state = 0;

    //enemigos giratorios del rectángulo

    enemigos[15].posey = 13;      //enemigo 15
    enemigos[15].posex = 28;
    enemigos[15].state = 0;
    enemigos[16].posey = 20;      //enemigo 16
    enemigos[16].posex = 24;
    enemigos[16].state = 2;

    //enemigos muy juntos de la izquierda de la primera sala

    enemigos[17].posey = 9;       //enemigo 17
    enemigos[17].posex = 27;
    enemigos[17].state = 0;
    enemigos[18].posey = 8;       //enemigo 18
    enemigos[18].posex = 27;
    enemigos[19].posey = 7;       //enemigo 19
    enemigos[19].posex = 27;
    enemigos[20].posey = 6;       //enemigo 20
    enemigos[20].posex = 27;
    enemigos[21].posey = 5;       //enemigo 21
    enemigos[21].posex = 27;
    enemigos[22].posey = 9;       //enemigo 22
    enemigos[22].posex = 25;
    enemigos[22].state = 0;
    enemigos[23].posey = 8;       //enemigo 23
    enemigos[23].posex = 25;
    enemigos[24].posey = 7;       //enemigo 24
    enemigos[24].posex = 25;
    enemigos[25].posey = 6;       //enemigo 25
    enemigos[25].posex = 25;
    enemigos[26].posey = 5;       //enemigo 26
    enemigos[26].posex = 25;

    //enemigos que van hacia arriba y hacia abajo

    enemigos[27].posey = 13;      //enemigo 27
    enemigos[27].posex = 19;
    enemigos[27].state = 0;
    enemigos[28].posey = 19;      //enemigo 28
    enemigos[28].posex = 17;
    enemigos[28].state = 0;
    enemigos[29].posey = 13;      //enemigo 29
    enemigos[29].posex = 15;
    enemigos[30].posey = 19;      //enemigo 30
    enemigos[30].posex = 13;
    enemigos[31].posey = 13;      //enemigo 31
    enemigos[31].posex = 11;

    //enemigos del rectángulo horizontal de abajo

    enemigos[32].posey = 21;      //enemigo 32
    enemigos[32].posex = 20;
    enemigos[33].posey = 21;      //enemigo 33
    enemigos[33].posex = 19;
    enemigos[34].posey = 21;      //enemigo 34
    enemigos[34].posex = 18;
    enemigos[35].posey = 21;      //enemigo 35
    enemigos[35].posex = 17;
    enemigos[36].posey = 21;      //enemigo 36
    enemigos[36].posex = 16;
    enemigos[37].posey = 21;      //enemigo 37
    enemigos[37].posex = 15;
    enemigos[38].posey = 21;      //enemigo 38
    enemigos[38].posex = 14;
    enemigos[39].posey = 21;      //enemigo 39
    enemigos[39].posex = 13;
    enemigos[39].state = 0;
    enemigos[40].posey = 25;      //enemigo 40
    enemigos[40].posex = 12;
    enemigos[41].posey = 25;      //enemigo 41
    enemigos[41].posex = 13;

    //enemigos del cuadrado pequeño de la esquina izquierda abajo

    enemigos[42].posey = 22;      //enemigo 42
    enemigos[42].posex = 4;
    enemigos[42].state = 0;
    enemigos[43].posey = 22;      //enemigo 43
    enemigos[43].posex = 2;
    enemigos[43].state = 0;
    enemigos[44].posey = 21;      //enemigo 44
    enemigos[44].posex = 3;
    enemigos[44].state = 0;
    enemigos[45].posey = 20;      //enemigo 45
    enemigos[45].posex = 4;
    enemigos[45].state = 0;
    enemigos[46].posey = 20;      //enemigo 46
    enemigos[46].posex = 2;
    enemigos[46].state = 0;

    // enemigos que te dejan pasar a completar el nivel

    enemigos[47].posey = 5;       //enemigo 47
    enemigos[47].posex = 4;
    enemigos[48].posey = 5;       //enemigo 48
    enemigos[48].posex = 3;

    //enemigos de la segunda sala grande, el molino
    
    enemigos[49].state=0;
    enemigos[50].state=0;

    enemigos[49].posex=8; // enemigo19
    enemigos[49].posey=5;

    enemigos[50].posex=15; // enemigo19
    enemigos[50].posey=5;



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
        enemigos[25].posex=enemigos[21].posex;  
        enemigos[25].posey=enemigos[21].posey+2;
        enemigos[26].posex=enemigos[21].posex;  
        enemigos[26].posey=enemigos[21].posey+3;
        enemigos[27].posex=enemigos[21].posex+2;  
        enemigos[27].posey=enemigos[21].posey;
        enemigos[28].posex=enemigos[21].posex+3;  
        enemigos[28].posey=enemigos[21].posey;
        enemigos[29].posex=enemigos[21].posex;  
        enemigos[29].posey=enemigos[21].posey-2;
        enemigos[30].posex=enemigos[21].posex; 
        enemigos[30].posey=enemigos[21].posey-3;
        enemigos[31].posex=enemigos[21].posex-2;  
        enemigos[31].posey=enemigos[21].posey;
        enemigos[32].posex=enemigos[21].posex-3;  
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
        enemigos[33].posex=enemigos[22].posex;  
        enemigos[33].posey=enemigos[22].posey+2;
        enemigos[34].posex=enemigos[22].posex;  
        enemigos[34].posey=enemigos[22].posey+3;
        enemigos[35].posex=enemigos[22].posex+2;  
        enemigos[35].posey=enemigos[22].posey;
        enemigos[36].posex=enemigos[22].posex+3;  
        enemigos[36].posey=enemigos[22].posey;
        enemigos[37].posex=enemigos[22].posex;  
        enemigos[37].posey=enemigos[22].posey-2;
        enemigos[38].posex=enemigos[22].posex;  
        enemigos[38].posey=enemigos[22].posey-3;
        enemigos[39].posex=enemigos[22].posex-2;  
        enemigos[39].posey=enemigos[22].posey;
        enemigos[40].posex=enemigos[22].posex-3;  
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
        enemigos[41].posex=enemigos[23].posex;  
        enemigos[41].posey=enemigos[23].posey+2;
        enemigos[42].posex=enemigos[23].posex;  
        enemigos[42].posey=enemigos[23].posey+3;
        enemigos[43].posex=enemigos[23].posex+2;  
        enemigos[43].posey=enemigos[23].posey;
        enemigos[44].posex=enemigos[23].posex+3;  
        enemigos[44].posey=enemigos[23].posey;
        enemigos[45].posex=enemigos[23].posex;  
        enemigos[45].posey=enemigos[23].posey-2;
        enemigos[46].posex=enemigos[23].posex;  
        enemigos[46].posey=enemigos[23].posey-3;
        enemigos[47].posex=enemigos[23].posex-2;  
        enemigos[47].posey=enemigos[23].posey;
        enemigos[48].posex=enemigos[23].posex-3;  
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
        enemigos[49].posex=enemigos[24].posex;  
        enemigos[49].posey=enemigos[24].posey+2;
        enemigos[50].posex=enemigos[24].posex;  
        enemigos[50].posey=enemigos[24].posey+3;
        enemigos[51].posex=enemigos[24].posex+2;  
        enemigos[51].posey=enemigos[24].posey;
        enemigos[52].posex=enemigos[24].posex+3;  
        enemigos[52].posey=enemigos[24].posey;
        enemigos[53].posex=enemigos[24].posex;  
        enemigos[53].posey=enemigos[24].posey-2;
        enemigos[54].posex=enemigos[24].posex;  
        enemigos[54].posey=enemigos[24].posey-3;
        enemigos[55].posex=enemigos[24].posex-2;  
        enemigos[55].posey=enemigos[24].posey;
        enemigos[56].posex=enemigos[24].posex-3;  
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

      if (enemigos[57].state==0) {
        enemigos[59].posex=enemigos[57].posex;  
        enemigos[59].posey=enemigos[57].posey+2;
        enemigos[60].posex=enemigos[57].posex;  
        enemigos[60].posey=enemigos[57].posey+3;
        enemigos[61].posex=enemigos[57].posex+2;  
        enemigos[61].posey=enemigos[57].posey;
        enemigos[62].posex=enemigos[57].posex+3;  
        enemigos[62].posey=enemigos[57].posey;
        enemigos[63].posex=enemigos[57].posex; 
        enemigos[63].posey=enemigos[57].posey-2;
        enemigos[64].posex=enemigos[57].posex;  
        enemigos[64].posey=enemigos[57].posey-3;
        enemigos[65].posex=enemigos[57].posex-2;  
        enemigos[65].posey=enemigos[57].posey;
        enemigos[66].posex=enemigos[57].posex-3;  
        enemigos[66].posey=enemigos[57].posey;

        enemigos[57].state++;
      }
      else if (enemigos[57].state==1) {
        enemigos[60].posex--;
        enemigos[62].posey++;
        enemigos[64].posex++; 
        enemigos[66].posey--;

        enemigos[57].state++;
      }
      else if (enemigos[57].state==2) {
        enemigos[59].posex--;
        enemigos[60].posex--;
        enemigos[61].posey++;
        enemigos[62].posey++;
        enemigos[63].posex++; 
        enemigos[64].posex++; 
        enemigos[65].posey--;
        enemigos[66].posey--;

        enemigos[57].state++;
      }else if (enemigos[57].state==3){
        enemigos[59].posex--;
        enemigos[60].posex--;
        enemigos[61].posey++;
        enemigos[62].posey++;
        enemigos[63].posex++; 
        enemigos[64].posex++; 
        enemigos[65].posey--;
        enemigos[66].posey--;

        enemigos[57].state++;
      }else if (enemigos[57].state==4) {
        enemigos[59].posey--;
        enemigos[61].posex--;
        enemigos[63].posey++;
        enemigos[65].posex++;
        enemigos[60].posey--;
        enemigos[62].posex--;
        enemigos[64].posey++;
        enemigos[66].posex++;

        enemigos[57].state=0;
      }

      if (enemigos[58].state==0) {
        enemigos[67].posex=enemigos[58].posex;  
        enemigos[67].posey=enemigos[58].posey+2;
        enemigos[68].posex=enemigos[58].posex;  
        enemigos[68].posey=enemigos[58].posey+3;
        enemigos[69].posex=enemigos[58].posex+2;  
        enemigos[69].posey=enemigos[58].posey;
        enemigos[70].posex=enemigos[58].posex+3;  
        enemigos[70].posey=enemigos[58].posey;
        enemigos[71].posex=enemigos[58].posex;  
        enemigos[71].posey=enemigos[58].posey-2;
        enemigos[72].posex=enemigos[58].posex;  
        enemigos[72].posey=enemigos[58].posey-3;
        enemigos[73].posex=enemigos[58].posex-2;  
        enemigos[73].posey=enemigos[58].posey;
        enemigos[74].posex=enemigos[58].posex-3;  
        enemigos[74].posey=enemigos[58].posey;

        enemigos[58].state++;
      }
      else if (enemigos[58].state==1) {
        enemigos[68].posex--;
        enemigos[70].posey++;
        enemigos[72].posex++; 
        enemigos[74].posey--;

        enemigos[58].state++;
      }
      else if (enemigos[58].state==2) {
        enemigos[67].posex--;
        enemigos[68].posex--;
        enemigos[69].posey++;
        enemigos[70].posey++;
        enemigos[71].posex++; 
        enemigos[72].posex++; 
        enemigos[73].posey--;
        enemigos[74].posey--;

        enemigos[58].state++;
      }else if (enemigos[58].state==3){
        enemigos[67].posex--;
        enemigos[68].posex--;
        enemigos[69].posey++;
        enemigos[70].posey++;
        enemigos[71].posex++; 
        enemigos[72].posex++; 
        enemigos[73].posey--;
        enemigos[74].posey--;

        enemigos[58].state++;
      }else if (enemigos[58].state==4) {
        enemigos[67].posey--;
        enemigos[68].posey--;
        enemigos[69].posex--;
        enemigos[70].posex--;
        enemigos[71].posey++;
        enemigos[72].posey++;
        enemigos[73].posex++;
        enemigos[74].posex++;
        enemigos[58].state=0;
      }
      break;

    case '8':
      mapaEnemigos2(tablero);
      tablero[POSICION_INICIAL_SAVEZONEX][POSICION_INICIAL_SAVEZONEY] = 4;
      for (int i = 0; i<numeroDeEnemigos; i++){
        tablero[enemigos[i].posey][enemigos[i].posex] = 2;
      }

      // actualización enemigo 0
      
      if (enemigos[0].state == 0) {
        enemigos[0].posex++;
      } else if (enemigos[0].state == 1) {
        enemigos[0].posex += 0;
      }
      if (enemigos[0].posex == 48) {
        enemigos[0].state= 1;
      }

      // actualizaciones enemigos 1 a 3

      if (enemigos[1].state == 0) {
        enemigos[1].posex--;
      }
      else if (enemigos[1].state == 1) {
        enemigos[1].posex++;
      }

      if(enemigos[1].posex == 39) enemigos[1].state = 1;
      else if(enemigos[1].posex == 45) enemigos[1].state = 0;

      if (enemigos[2].state == 0) {
        enemigos[2].posex++;
      }
      else if (enemigos[2].state == 1) {
        enemigos[2].posex--;
      }

      if(enemigos[2].posex == 45) enemigos[2].state = 1;
      else if(enemigos[2].posex == 39) enemigos[2].state = 0;

      if (enemigos[3].state == 0) {
        enemigos[3].posex--;
      }
      else if (enemigos[3].state == 1) {
        enemigos[3].posex++;
      }

      if(enemigos[3].posex == 39) enemigos[3].state = 1;
      else if(enemigos[3].posex == 45) enemigos[3].state = 0;

      //actualizaciones enemigos 4 a 11
      
      if (enemigos[4].state == 0) enemigos[4].posey++;
      if (enemigos[4].state == 1) enemigos[4].posey--;
      if (enemigos[4].posey == 12) enemigos[4].state = 1;
      if (enemigos[4].posey == 7) enemigos[4].state = 0;

      if (enemigos[5].state == 0) enemigos[5].posex++;
      if (enemigos[5].state == 1) enemigos[5].posex--;
      if (enemigos[5].posex == 40) enemigos[5].state = 1;
      if (enemigos[5].posex == 35) enemigos[5].state = 0;

      if (enemigos[6].state == 0) enemigos[6].posex--;
      if (enemigos[6].state == 1) enemigos[6].posex++;
      if (enemigos[6].posex == 30) enemigos[6].state = 1;
      if (enemigos[6].posex == 35) enemigos[6].state = 0;

      if (enemigos[7].state == 0) enemigos[7].posey--;
      if (enemigos[7].state == 1) enemigos[7].posey++;
      if (enemigos[7].posey == 2) enemigos[7].state = 1;
      if (enemigos[7].posey == 7) enemigos[7].state = 0;
      
      if (enemigos[8].state == 0) {
        enemigos[8].posex++;
        enemigos[8].posey--;
      }
      if (enemigos[8].state == 1) {
        enemigos[8].posex--;
        enemigos[8].posey++;
      }     
      if (enemigos[8].posey == 2 && enemigos[8].posex == 40) enemigos[8].state = 1;
      if (enemigos[8].posey == 7 && enemigos[8].posex == 35) enemigos[8].state = 0;
      
      if (enemigos[9].state == 0) {
        enemigos[9].posey--;
        enemigos[9].posex--;
      }
      if (enemigos[9].state == 1) {
        enemigos[9].posey++;
        enemigos[9].posex++;
      }
      if (enemigos[9].posey == 2 && enemigos[9].posex == 30) enemigos[9].state = 1;
      if (enemigos[9].posey == 7 && enemigos[9].posex == 35) enemigos[9].state = 0;
      
      if (enemigos[10].state == 0) {
        enemigos[10].posey++;
        enemigos[10].posex++;
      }
      if (enemigos[10].state == 1) {
        enemigos[10].posey--;
        enemigos[10].posex--;
      }
      if (enemigos[10].posey == 12 && enemigos[10].posex == 40) enemigos[10].state = 1;
      if (enemigos[10].posey == 7 && enemigos[10].posex == 35) enemigos[10].state = 0;

      if (enemigos[11].state == 0) {
        enemigos[11].posey++;
        enemigos[11].posex--;
      }
      if (enemigos[11].state == 1) {
        enemigos[11].posey--;
        enemigos[11].posex++;
      }
      if (enemigos[11].posey == 12 && enemigos[11].posex == 30) enemigos[11].state = 1;
      if (enemigos[11].posey == 7 && enemigos[11].posex == 35) enemigos[11].state = 0;

      //actualizaciones enemigos 12 a 14

      if (enemigos[12].state == 0) enemigos[12].posex++;
      if (enemigos[12].state == 1) enemigos[12].posex--;
      if (enemigos[12].posex == 37) enemigos[12].state = 1;
      if (enemigos[12].posex == 31) enemigos[12].state = 0;

      if (enemigos[13].state == 0) enemigos[13].posex--;
      if (enemigos[13].state == 1) enemigos[13].posex++;
      if (enemigos[13].posex == 31) enemigos[13].state = 1;
      if (enemigos[13].posex == 37) enemigos[13].state = 0;

      if (enemigos[14].state == 0) enemigos[14].posex++;
      if (enemigos[14].state == 1) enemigos[14].posex--;
      if (enemigos[14].posex == 37) enemigos[14].state = 1;
      if (enemigos[14].posex == 31) enemigos[14].state = 0;

      //actualizaciones enemigos 15 y 16

      if (enemigos[15].state == 0) enemigos[15].posex--;
      if (enemigos[15].state == 1) enemigos[15].posey++;
      if (enemigos[15].state == 2) enemigos[15].posex++;
      if (enemigos[15].state == 3) enemigos[15].posey--;

      if (enemigos[15].posex == 24 && enemigos[15].posey == 13) enemigos[15].state = 1;
      if (enemigos[15].posex == 24 && enemigos[15].posey == 20) enemigos[15].state = 2;
      if (enemigos[15].posex == 28 && enemigos[15].posey == 20) enemigos[15].state = 3;
      if (enemigos[15].posex == 28 && enemigos[15].posey == 13) enemigos[15].state = 0;

      if (enemigos[16].state == 0) enemigos[16].posex--;
      if (enemigos[16].state == 1) enemigos[16].posey++;
      if (enemigos[16].state == 2) enemigos[16].posex++;
      if (enemigos[16].state == 3) enemigos[16].posey--;

      if (enemigos[16].posex == 24 && enemigos[16].posey == 13) enemigos[16].state = 1;
      if (enemigos[16].posex == 24 && enemigos[16].posey == 20) enemigos[16].state = 2;
      if (enemigos[16].posex == 28 && enemigos[16].posey == 20) enemigos[16].state = 3;
      if (enemigos[16].posex == 28 && enemigos[16].posey == 13) enemigos[16].state = 0;

      //actualizacion enemigos 17 a 26

      if (posx == 26 && posy == 7) {
        if (enemigos[17].state == 0) {
          for (int i = 17 ; i <= 21 ; i++){
            enemigos[i].posex--;
            enemigos[17].state = 1;
          }
        }
      }
      if (posx == 26 && posy == 7) {
        if (enemigos[22].state == 0) {
          for (int i = 22 ; i <= 26 ; i++){
            enemigos[i].posex++;
            enemigos[22].state = 1;
          }
        }
      }

      //actualizaciones enemigos 27 a 31

      if (enemigos[27].state == 0) {
        enemigos[27].posey++;
        enemigos[29].posey++;
        enemigos[31].posey++;
      }
      if (enemigos[28].state == 0) {
        enemigos[28].posey--;
        enemigos[30].posey--;
      }
      if (enemigos[27].state == 1) {
        enemigos[27].posey--;
        enemigos[29].posey--;
        enemigos[31].posey--;
      }
      if (enemigos[28].state == 1) {
        enemigos[28].posey++;
        enemigos[30].posey++;
      }
      if (enemigos[27].posey == enemigos[28].posey) {
        enemigos[27].state = 1;
        enemigos[28].state = 1;
      }
      if (enemigos[27].posey == 13) enemigos[27].state = 0;
      if (enemigos[28].posey == 19) enemigos[28].state = 0;

      //actualizaciones enemigos 32 a 41

      if (posx == enemigos[39].posex + 2) {
        if (enemigos[39].state == 0){
          enemigos[39].posey++;
          enemigos[39].posey++;
        }
      }
      if (posx == enemigos[39].posex + 1 && posy == enemigos[39].posey) enemigos[39].state = 1;
      if (enemigos[39].state == 1) {
        for (int i = 38; i >= 33; i--) {
          if (posx == enemigos[i].posex) {
            enemigos[i].posey++;
            enemigos[i].posey++;
          }
        }
      }
      if (enemigos[33].posey == 23 && enemigos[39].state == 1) {
        for (int i = 1; i <= 7; i++) enemigos[32].posex--;
        enemigos[32].posey++;
        enemigos[39].state = 2;
      }
      if (enemigos[39].state == 2){
        enemigos[40].posex--;
        enemigos[40].posey--;

        enemigos[41].posex--;
        enemigos[41].posex--;
        enemigos[41].posey--;

        enemigos[39].state = 3;
      }

      //actualizaciones enemigos 42 a 46

      for (int i = 42; i <= 46; i++) {
        if (enemigos[i].posey == 20 && enemigos[i].posex == 4) enemigos[i].state = 1;
        if (enemigos[i].posey == 20 && enemigos[i].posex == 2) enemigos[i].state = 2;
        if (enemigos[i].posey == 22 && enemigos[i].posex == 2) enemigos[i].state = 3;
        if (enemigos[i].posey == 22 && enemigos[i].posex == 4) enemigos[i].state = 4;

        if (enemigos[i].state == 1) enemigos[i].posex--;
        if (enemigos[i].state == 2) enemigos[i].posey++;
        if (enemigos[i].state == 3) enemigos[i].posex++;
        if (enemigos[i].state == 4) enemigos[i].posey--;
      }

      // actualizaciones enemigos 48 y 49
      
      if (posx == 17 && posy == 3) {
        enemigos[47].posey = 25;
        enemigos[47].posex = 48;

        enemigos[48].posey = 25;
        enemigos[48].posex = 48;
      }

      //molinos = sufrimiento para los desarrolladores
      if (enemigos[49].state==0) {
        enemigos[51].posex=enemigos[49].posex;  
        enemigos[51].posey=enemigos[49].posey+2;
        enemigos[52].posex=enemigos[49].posex;  
        enemigos[52].posey=enemigos[49].posey+3;
        enemigos[53].posex=enemigos[49].posex+2;  
        enemigos[53].posey=enemigos[49].posey;
        enemigos[54].posex=enemigos[49].posex+3;  
        enemigos[54].posey=enemigos[49].posey;
        enemigos[55].posex=enemigos[49].posex;  
        enemigos[55].posey=enemigos[49].posey-2;
        enemigos[56].posex=enemigos[49].posex;  
        enemigos[56].posey=enemigos[49].posey-3;
        enemigos[57].posex=enemigos[49].posex-2;  
        enemigos[57].posey=enemigos[49].posey;
        enemigos[58].posex=enemigos[49].posex-3;  
        enemigos[58].posey=enemigos[49].posey;

        enemigos[49].state++;
      }
      else if (enemigos[49].state==1) {
        enemigos[52].posex--;
        enemigos[54].posey++;
        enemigos[56].posex++; 
        enemigos[58].posey--;

        enemigos[49].state++;
      }
      else if (enemigos[49].state==2) {
        enemigos[51].posex--;
        enemigos[52].posex--;
        enemigos[53].posey++;
        enemigos[54].posey++;
        enemigos[55].posex++; 
        enemigos[56].posex++; 
        enemigos[57].posey--;
        enemigos[58].posey--;

        enemigos[49].state++;
      }else if (enemigos[49].state==3){
        enemigos[51].posex--;
        enemigos[52].posex--;
        enemigos[53].posey++;
        enemigos[54].posey++;
        enemigos[55].posex++; 
        enemigos[56].posex++; 
        enemigos[57].posey--;
        enemigos[58].posey--;

        enemigos[49].state++;
      }else if (enemigos[49].state==4) {
        enemigos[51].posey--;
        enemigos[52].posey--;
        enemigos[53].posex--;
        enemigos[54].posex--;
        enemigos[55].posey++;
        enemigos[56].posey++;
        enemigos[57].posex++;
        enemigos[58].posex++;

        enemigos[49].state=0;
      }
      
      if (enemigos[50].state==0) {
        enemigos[59].posex=enemigos[50].posex;  
        enemigos[59].posey=enemigos[50].posey+2;
        enemigos[60].posex=enemigos[50].posex;  
        enemigos[60].posey=enemigos[50].posey+3;
        enemigos[61].posex=enemigos[50].posex+2;  
        enemigos[61].posey=enemigos[50].posey;
        enemigos[62].posex=enemigos[50].posex+3;  
        enemigos[62].posey=enemigos[50].posey;
        enemigos[63].posex=enemigos[50].posex;  
        enemigos[63].posey=enemigos[50].posey-2;
        enemigos[64].posex=enemigos[50].posex;  
        enemigos[64].posey=enemigos[50].posey-3;
        enemigos[65].posex=enemigos[50].posex-2;  
        enemigos[65].posey=enemigos[50].posey;
        enemigos[66].posex=enemigos[50].posex-3;  
        enemigos[66].posey=enemigos[50].posey;

        enemigos[50].state++;
      }
      else if (enemigos[50].state==1) {
        enemigos[60].posex--;
        enemigos[62].posey++;
        enemigos[64].posex++; 
        enemigos[66].posey--;

        enemigos[50].state++;
      }
      else if (enemigos[50].state==2) {
        enemigos[59].posex--;
        enemigos[60].posex--;
        enemigos[61].posey++;
        enemigos[62].posey++;
        enemigos[63].posex++; 
        enemigos[64].posex++; 
        enemigos[65].posey--;
        enemigos[66].posey--;

        enemigos[50].state++;
      }else if (enemigos[50].state==3){
        enemigos[59].posex--;
        enemigos[60].posex--;
        enemigos[61].posey++;
        enemigos[62].posey++;
        enemigos[63].posex++; 
        enemigos[64].posex++; 
        enemigos[65].posey--;
        enemigos[66].posey--;

        enemigos[50].state++;
      }else if (enemigos[50].state==4) {
        enemigos[59].posey--;
        enemigos[60].posey--;
        enemigos[61].posex--;
        enemigos[62].posex--;
        enemigos[63].posey++;
        enemigos[64].posey++;
        enemigos[65].posex++;
        enemigos[66].posex++;

        enemigos[50].state=0;
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
    if (opcion=='7' || opcion=='8') {
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
