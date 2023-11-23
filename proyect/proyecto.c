#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
// el tamaño así esta bien? o es demasiado pequeño?

#define tamañox 27
#define tamañoy 100
#define POSICION_INICIAL_PLMANX 1
#define POSICION_INICIAL_PLMANY 27
#define POSICION_INICIAL_SAVEZONEX 1
#define POSICION_INICIAL_SAVEZONEY 3

void dibujar_tablero(int tablero[tamañox][tamañoy]){
    printf("\n");
    for (int i =0; i<tamañox; i++) {
        printf("          ");
        for (int j =0; j<tamañoy; j++) {

                switch (tablero[i][j]) {
                    case 0:
                        //nada
                        printf(" ");
                        break;
                    case 1:
                        //pared
                        printf("\x1b[37m" "\x1b[47m" " " "\x1b[0m");
                        break;
                    case 2:
                        //enemigo
                        printf("\x1b[31m" "\x1b[41m" " " "\x1b[0m");
                        break;
                    case 3:
                        //plman
                        printf( "\x1b[33m" "\x1b[43m"" " "\x1b[0m");
                        break;
                    case 4:
                        //save zone
                        printf( "\x1b[32m" "\x1b[42m"" " "\x1b[0m");
                        break;
                    default:
                        // codigo de error
                        printf("\x1b[31m" "E" "\x1b[0m");
                        
                        break;
                }
        }
        printf("\n");
    }
}

char preguntardireccion(){
    char direccion;
    // esto funcionaba regular, imprime dos veces la pregunta
        initscr();
        raw();
        keypad(stdscr, true);
        noecho();
    do{
        direccion = getch();
        if (direccion=='p') {
            printf("\e[1;1H\e[2J");
            printf("el juego ha sido interrumpido\n");
            endwin();
            exit(0);
        }
        if (direccion!='w'&&direccion!='d'&&direccion!='s'&&direccion!='a'){
            break;
        }

        endwin();
    }
    while (direccion!='w'&&direccion!='d'&&direccion!='s'&&direccion!='a');
    return direccion;
}
void mapa1(int tablero2[tamañox][tamañoy]){

    // inicializa el tablero, cuando se puedan usar arrays bien 
    // se hará en una función a parte (preguntar a la profesora)
    for (int i = 0; i<tamañox; i++) {
        for (int j = 0; j<tamañoy; j++) {
            if (j==0 | j==tamañoy-1 | i ==0 | i==tamañox-1) {
                tablero2[i][j]=1;
            
            }else {
            
                tablero2[i][j]=0;
            }
        }
    }
}

int menumapa(){
    
    printf("\e[1;1H\e[2J");
    printf("          ");
    printf("      MENU MAPA\n");
    printf("          ");
    printf("1.- mapa 1");
    printf("          ");
    printf("2.- mapa 1\n");
    printf("          ");
    printf("3.- salir");


}

int menu(){
    
    int elección1;
    printf("          ");
    printf("      MENU\n");
    printf("          ");
    printf("1.- elegir mapa ");
    printf("          ");
    printf("2.- mapa aleatorio\n");
    printf("          ");
    printf("0.- salir");
    scanf(" %d", &elección1);

    switch (elección1) {
        case 1:
            return menumapa();
    }
    
}


int main(){

    char c=' ';
    // posición inicial de plman
    int posx=POSICION_INICIAL_PLMANX,posy=POSICION_INICIAL_PLMANY;
    int posy1=posy-1;

    int posex=8,posey=5;
    int posey1=posey-1;

    int posSx=POSICION_INICIAL_SAVEZONEX,posSy=POSICION_INICIAL_SAVEZONEY;
    int posSy1=posSy-1;

    int tablero2[tamañox][tamañoy];

    // estado de game, cambiar para terminar el juego 
    // segun el estado final (si ha ganado ) enviar un mensaje
    // y si ha perdido otro
    int game =1;

    /*
     * ejemplo de 
     opción poco elegante de inicialización del tablero 
    int tablero[10][15]={
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
        1,1,1,1,1,1,1,1,1,1,1,1,1,1,1
    };
    */

    // hay que hacer un menú de selección (decidir cuantos mapas más hacer...)
    //
    //hay que hacer más mapas, es decir funciones en las que se necesita un array y se inicializa 
    // con valores 1 y 0 ()
    // uno tiene que ser un especial navidad
    // otro con referencias a plman ()
    //
    
    int estado = 1;

    do  {
    
        mapa1(tablero2);
        printf("\e[1;1H\e[2J");
    
        mapa1(tablero2);

        // indica la posicion de plman
        tablero2[posx][posy1]=3;
        tablero2[posx][posy]=3;

        // indica la posicion de enemigos
        tablero2[posex][posey1]=2;
        tablero2[posex][posey]=2;

        // indica la posición de la save zone 
        tablero2[posSx][posSy1]=4;
        tablero2[posSx][posSy]=4;

        dibujar_tablero(tablero2);

        c=preguntardireccion();
        // esto se podría poner en una función (hay que esperar que la profesora nos pase la librería)
        // actualización de plman 
        switch (c) {
            case 'w':
                if(tablero2[posx-1][posy]!=1 && tablero2[posx-1][posy1]!=1){
                    posx = posx-1;
                }
                break;
            case 's':
                
                if(tablero2[posx+1][posy]!=1 && tablero2[posx+1][posy1]!=1){
                    posx = posx+1;
                }
                break;
            case 'd':
                if(tablero2[posx][posy+2]!=1&& tablero2[posx][posy+1]!=1){
                    posy = posy+2;
                    posy1 = posy1+2;
                }else if (tablero2[posx][posy+1]!=1) {
                    posy = posy+1;
                    posy1 = posy1+1;
                }
                break;
            case 'a':
                if(tablero2[posx][posy1-2]!=1&&tablero2[posx][posy1-1]!=1){
                    posy = posy-2;
                    posy1 = posy1-2;
                }else if (tablero2[posx][posy1-1]!=1) {
                
                    posy = posy-1;
                    posy1 = posy1-1;
                }
                break;
        }


        //actualización enemigo 1
        if (estado==1) {
            posex++;
        }else if (estado==2) {
            posex--;
        }
        if (posex==1) {
            estado=1;
        }else if (posex==tamañox-2) {
            estado=2;
        }

        // colisiones 
        if(posex==posx && posey1==posy1 || posex==posx && posey==posy1 || posex==posx && posey1==posy ) {
            game=2;
        }
        // colision save zone
        if(posSx==posx && posSy1==posy1 || posSx==posx && posSy==posy1 || posSx==posx && posSy1==posy ) {
            game=3;
        }
    }while(game==1);
   
    printf("\e[1;1H\e[2J");

    // for (int i =0; i<tamañox; i++) {
    //     printf("          ");
    //     for (int j =0; j<tamañoy; j++) {
    //         printf("%d",tablero2[i][j]);
    //     }
    //     printf("\n");
    // }

    // mensajes de salida (se puede hacer algun patron bonito para celebrar o paralamentar
    // el ganar o perder) @Luca esta es la tuya (lo quiero en gfx )
    if (game==2) {
        printf("Te han matado los enemigos!!!\n");
    
    }else if (game==3) {
        printf("Has llegado a salvo, enhorabuena!!!\n");
    
    }
    
}
