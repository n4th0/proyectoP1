#include <stdio.h>

#define tamanox 27
#define tamanoy 100

void mapa1(int tablero2[tamanox][tamanoy]){
  for (int i = 0; i < tamanox; i++) {
    for (int j = 0; j < tamanoy; j++) {
      if (j == 0 | j == tamanoy - 1 | i == 0 | i == tamanox - 1 | j == 1 |
          j == tamanoy - 2) {
        tablero2[i][j] = 1;
      } else {
        tablero2[i][j] = 0;
      }

      
    }
  }
    
}