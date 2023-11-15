#include <stdio.h>
#include <stdlib.h>

#define tamañox 10
#define tamañoy 30

#define POSICION_INICIAL_PLMANX 1
#define POSICION_INICIAL_PLMANY 27

#define POSICION_INICIAL_SAVEZONEX 1
#define POSICION_INICIAL_SAVEZONEY 3


void dibujar_tablero(int tablero[tamañox][tamañoy]){
    printf("\n");
    for (int i =0; i<tamañox; i++) {
        printf("          ");
        for (int j =0; j<tamañoy; j++) {

                // printf( "\x1b[33m" "\x1b[43m"" " "\x1b[0m");
                
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

/*
 * concatenado a la pregunta a la profesora xd
 * para aprender a inicializar el tablero, 
 * (args el tablero ) return un tablero con valores
 *
int  mapa1(int tablero[10][15]){

    for (int i = 0; i<10; i++) {

        for (int j = 0; j<15; j++) {
            if(i == 0 || i == 9 || j ==0 || j == 14){
                tablero[i][j]=1;

            }else {
                tablero[i][j]=0;
            }
        
        }
    
    }
    return tablero[10][15];
}
*/

char preguntardireccion(){
    char direccion;
    // esto funcionaba regular, imprime dos veces la pregunta
    printf("\ndime la dirección a la que quieres ir: ");
    do{
        scanf("%c",&direccion);
    }
    while (direccion!='w'&&direccion!='d'&&direccion!='s'&&direccion!='a');
    return direccion;
}


int main(){


    // posición inicial de plman
    int posx=POSICION_INICIAL_PLMANX,posy=POSICION_INICIAL_PLMANY;
    int posy1=posy-1;

    int posex=8,posey=5;
    int posey1=posey-1;

    int posSx=POSICION_INICIAL_SAVEZONEX,posSy=POSICION_INICIAL_SAVEZONEY;
    int posSy1=posSy-1;

    int tablero2[10][30];

    // estado de game, cambiar para terminar el juego 
    // segun el estado final (si ha ganado ) enviar un mensaje
    // y si ha perdido otro
    int game =1;

    /*
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


    // inicializa el tablero, cuando se puedan usar arrays bien 
    // se hará en una función a parte (preguntar a la profesora)


    //hay que hacer más mapas, es decir funciones en las que se necesita un array y se inicializa 
    // con valores 1 y 0 ()
    // uno tiene que ser un especial navidad
    // otro con referencias a plman ()
    //

    


    int estado = 1;
    

    do  {
    
        printf("\e[1;1H\e[2J");
        // se le podrían poner colores a esto 
        printf("         ");
        printf("         ");
        printf("TABLERO DE JUEGO \n");
        printf("      ");
        printf("--------------------------------------\n");
    

        // inicializa el tablero, cuando se puedan usar arrays bien 
        // se hará en una función a parte (preguntar a la profesora)
        for (int i = 0; i<10; i++) {
            for (int j = 0; j<30; j++) {

                if(i == 0 || i == 9 || j ==0 || j==1 || j == 28 || j==29){
                    tablero2[i][j]=1;
                }else{
                    if (  j==13 ||  j==19 || j== 25  ) {
                        if (i>0 && i<8) {
                            tablero2[i][j]=1;
                        }
                        else {
                            tablero2[i][j]=0;
                        }
                    }else if (  j == 16 || j== 22 ) {

                        if (i>1 && i<=8) {
                            tablero2[i][j]=1;
                        }
                        else {
                            tablero2[i][j]=0;
                        }
                    }else {
                        
                        tablero2[i][j]=0;
                    }
                    
                    // tablero2[i][j]=0;
                }
            }
        }

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
        // esto se podría poner en una función 
        // actualización de plman 
        switch (preguntardireccion()) {
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
                if(tablero2[posx][posy+1]!=1){
                    posy = posy+1;
                    posy1 = posy1+1;
                }
                break;
            case 'a':
                if(tablero2[posx][posy1-1]!=1){
                    posy = posy-1;
                    posy1 = posy1-1;
                }
                break;
        }


        //actualización enemigo 1
        if (estado==1) {
            posex--;
        }else {

            posex++;
        }
        if (posex==1) {
            estado=2;
        }
        if (posex==8) {
            estado=1;
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
   

    // for (int i =0; i<tamañox; i++) {
    //     printf("          ");
    //     for (int j =0; j<tamañoy; j++) {
    //         printf("%d",tablero2[i][j]);
    //     }
    //     printf("\n");
    // }

    // mensajes de salida (se puede hacer algun patron bonito para celebrar o paralamentar
    // el ganar o perder)
    if (game==2) {
        printf("Te han matado los enemigos!!!\n");
    
    }
    if (game==3) {
        printf("Has llegado a salvo, enhorabuena!!!\n");
    
    }

    
}
