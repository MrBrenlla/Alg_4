#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define TAM_MAX 1000

void dijkstra(int ** m , int ** Dis , int n){
  int inicial,escollido,destino,i,min;
  int nonVisitados[n];

  for (inicial = 0 ; inicial<n; inicial++){
    for (i=0;i<n;i++){
       nonVisitados[i]=1;
       Dis[inicial][i]=m[inicial][i];
     }
    nonVisitados[inicial]=0;

    for (i = 1 ;  i<n; i++){
      min = INT_MAX;
      for (destino = 0; destino < n; destino++)
        if (Dis[inicial][destino]<min && nonVisitados[destino]==1){
          escollido = destino;
          min = Dis[inicial][destino];
        }
      nonVisitados[escollido]=0;
      for (destino =0 ; destino < n ; destino++)
      if(Dis[inicial][destino]>Dis[inicial][escollido]+m[escollido][destino]
            && nonVisitados[destino]==1)
      Dis[inicial][destino] = Dis[inicial][escollido]+m[escollido][destino];
    }
  }
}
/*
--------------------------------------------------------------------------------
*/
int** crearMatriz(int n) {
  int i;
  int** aux;
  if ((aux = malloc(n*sizeof(int *))) == NULL)
    return NULL;
  for (i=0; i<n; i++)
    if ((aux[i] = malloc(n*sizeof(int))) == NULL) return NULL;
  return aux;
}
/*
--------------------------------------------------------------------------------
*/
void iniMatriz(int ** m, int n) {

/* Inicializacion pseudoaleatoria [1..TAM_MAX] de un grafo completo
no dirigido con n nodos, representado por su matriz de adayencia */

  int i, j;
  for (i=0; i<n; i++)
    for (j=i+1; j<n; j++)
      m[i][j] = rand() % TAM_MAX + 1;
  for (i=0; i<n; i++)
    for (j=0; j<=i; j++)
      if (i==j)
        m[i][j] = 0;
      else
        m[i][j] = m[j][i];
}

/*
--------------------------------------------------------------------------------
*/
void liberarMatriz(int ** m, int n) {
  int i;
  for (i=0; i<n; i++)
    free(m[i]);
  free(m);
}
/*
--------------------------------------------------------------------------------
*/
void mostarTabla ( int ** m, int n){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<n;j++) printf("%3d ", m[i][j] );
    printf("\n" );
  }
  printf("\n");

}
/*
--------------------------------------------------------------------------------
*/
void proba1(){
  int ** m ;
  int ** dis;
  m=crearMatriz(5);
  dis=crearMatriz(5);
  m[0][0]=0;  m[0][1]=1;  m[0][2]=8;  m[0][3]=4;  m[0][4]=7;
  m[1][0]=1;  m[1][1]=0;  m[1][2]=2;  m[1][3]=6;  m[1][4]=5;
  m[2][0]=8;  m[2][1]=2;  m[2][2]=0;  m[2][3]=9;  m[2][4]=5;
  m[3][0]=4;  m[3][1]=6;  m[3][2]=9;  m[3][3]=0;  m[3][4]=3;
  m[4][0]=4;  m[4][1]=5;  m[4][2]=5;  m[4][3]=3;  m[4][4]=0;
  mostarTabla(m,5);
  dijkstra(m, dis, 5);
  mostarTabla(dis,5);
  liberarMatriz(m,5);
  liberarMatriz(dis,5);
}
/*
--------------------------------------------------------------------------------
*/
void proba2(){
  int ** m;
  int ** dis;
  m=crearMatriz(4);
  dis=crearMatriz(4);
  m[0][0]=0; m[0][1]=1; m[0][2]=4; m[0][3]=7;
  m[1][0]=1; m[1][1]=0; m[1][2]=2; m[1][3]=8;
  m[2][0]=4; m[2][1]=2; m[2][2]=0; m[2][3]=3;
  m[3][0]=7; m[3][1]=8; m[3][2]=3; m[3][3]=0;
  mostarTabla(m,4);
  dijkstra(m, dis, 4);
  mostarTabla(dis,4);
  liberarMatriz(m,4);
  liberarMatriz(dis,4);
}
/*
--------------------------------------------------------------------------------
*/
int main(){
  proba1();
  proba2();
}
