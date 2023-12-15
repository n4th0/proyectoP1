#include<stdio.h>
#include "./tigr/tigr.h"
#include<stdlib.h>
#include<unistd.h>


/*
    --->Para compilar el programa:
            gcc tigr.c win.c -o win -I./tigr -lGLU -lGL -lX11 -lm

    --->Hay que instalar librerias adicionales -lGLU -lGL -lX11:
            Para instalar lX11: sudo apt install libx11-dev
            Para instalar Opengl: sudo apt install freeglut3-dev


    --->Los archivos tigr.c y tigr.h deben estar en la misma caperta que main.c
*/

void victoria();
void derrota();




void victoria()
{
    Tigr *screen;
    Tigr *imagen = tigrLoadImage("./imagenes/Victoria11.png");
    if (!imagen)
    {
        printf("Ha ocurrido un error :(\n");
    }

    int i;
    int id;

    id = fork();
    //we enter the child process
    if (id == 0)
    {
        //ponemos las musica
        fflush(stdout);
        i = system("ffplay audio/victoria.mp3 -nodisp -loglevel quiet");
            
    }
    else
    {
        //iniciamos la ventana
        screen = tigrWindow(1282, 684, "Ventana de Victoria", 1);


        
        while (!tigrClosed(screen))
        {
            tigrClear(screen, tigrRGB(255,255,255));//ponemos la ventana en blanco
            
            //ponemos la imagne de victoria
            // Copies bitmap data.
            // dx/dy = dest co-ordinates
            // sx/sy = source co-ordinates
            // w/h   = width/height
            tigrBlit(screen, imagen, 0, 0, 0,0, 1280, 720);//(Tigr *dest, Tigr *src, int dx, int dy, int sx, int sy, int w, int h)

            tigrUpdate(screen);//actualizamos la ventana
        }
        //cerramos la pestaña de tigr
	int i;
	i = system("pkill ffplay");
        tigrFree(screen);
    }
}

void derrota()
{
    Tigr *screen;
    Tigr *imagen = tigrLoadImage("./imagenes/Derrota2.png");
    if (!imagen)
    {
        printf("Ha ocurrido un error :(\n");
    }

    int i;
    int id;

    id = fork();
    //we enter the child process
    if (id == 0)
    {
        //ponemos las musica
        fflush(stdout);
        i = system("ffplay audio/derrota.mp3 -nodisp -loglevel quiet");
            
    }
    else
    {
        //iniciamos la ventana
        screen = tigrWindow(594, 786, "Ventana de Derrota", 1);

        //valores iniciales

        
        while (!tigrClosed(screen))
        {
            tigrClear(screen, tigrRGB(255,255,255));//ponemos la ventana en blanco
            
            //ponemos la imagne de victoria
            // Copies bitmap data.
            // dx/dy = dest co-ordinates
            // sx/sy = source co-ordinates
            // w/h   = width/height
            tigrBlit(screen, imagen, 0, 0, 0,0, 1280, 720);//(Tigr *dest, Tigr *src, int dx, int dy, int sx, int sy, int w, int h)


            tigrUpdate(screen);//actualizamos la ventana
        }
        //cerramos la pestaña de tigr
	int i;
	i = system("kill ffplay");
        tigrFree(screen);
    }
}
