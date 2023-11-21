#include<stdio.h>
#include<stdbool.h>

void menu();

void menu(){

    char x;
    bool s;

    s = false;

    while (s == false){

        printf("\e[1;1H\e[2J");
        printf("Iniciando...\n");
        printf(".\n");
        printf(".\n");
        printf(".\n");

        printf("Bienvenido/a a *nombre_del_juego*. Dentro de *nombre_del_juego* podrás seleccionar varios modos de juego, cada uno de los cuales dispone de varios mapas a tu elección.\n");
        printf("Introduce I para ver las instrucciones.\n");
        printf("Introduce J para ver los modos de juego.\n");
        printf("Introduce S para salir.\n");

        scanf(" %c", &x);

        switch(x){

            case 'I': 
                printf("\e[1;1H\e[2J");
                printf("mamabicho\n");
                printf("Introduce cualquier tecla para salir.\n");
                scanf(" %c", &x);
                if(x != '0') s = false;
            break;
            
            case 'J':
                printf("\e[1;1H\e[2J");
                printf("mamaguevo\n");
                printf("Introduce cualquier tecla para salir.\n");
                scanf(" %c", &x);
                if (x != '0') s = false;
            break;

            case 'S':
                s = true;
            break;

        }
    }
}

int main(){
    menu();
    return 0;
}