#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>

#define TAM_MAX 1000
#define MAX_ITER pow(2,10)
#define MIN_ITER pow(2,2)
#define K 1000

typedef int ** matriz;
//##############################################################################
//##############################################################################
//##############################################################################

double microsegundos() { /* obtiene la hora del sistema en microsegundos */
struct timeval t;
if (gettimeofday(&t, NULL) < 0 ) return 0.0;
return (t.tv_usec + t.tv_sec * 1000000.0);
}
/*
--------------------------------------------------------------------------------
*/
void dijkstra(matriz m , matriz Dis , int n){
  int inicial,escollido,destino,i,min;
  int nonVisitados[n];

  for (inicial = 0 ; inicial<n; inicial++){
    for (i=0;i<n;i++){
       nonVisitados[i]=1;
       Dis[inicial][i]=m[inicial][i];
     }
    nonVisitados[inicial]=0;

    for (i = 1 ;  i<n-1; i++){
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
void iniMatriz(matriz m, int n) {

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
void liberarMatriz(matriz m, int n) {
  int i;
  for (i=0; i<n; i++)
    free(m[i]);
  free(m);
}
/*
--------------------------------------------------------------------------------
*/
void mostarTabla ( matriz m, int n){
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
matriz crearMatriz(int n) {
  int i;
  matriz aux;
  if ((aux = malloc(n*sizeof(int *))) == NULL)
    return NULL;
  for (i=0; i<n; i++)
    if ((aux[i] = malloc(n*sizeof(int))) == NULL) return NULL;
  return aux;
}
/*
--------------------------------------------------------------------------------
*/
void tempos(int n, void (*cal)(matriz x ,matriz v, int n),void (*ini)(matriz v, int n),
double cotainf, double cotaax, double cotasup){
  double ta, tb;
  matriz v,x;
  int i;
  char aviso=' ';
  double total1 ;
  x=crearMatriz(n);
  v=crearMatriz(n);
  ini(v,n);
  ta = microsegundos();
  cal(x,v,n);
  tb = microsegundos();
  total1 = tb-ta;
  if (total1<500){
    aviso='*';
    ta = microsegundos();
    for ( i =0 ; i<K ; i++){
      ini(v,n);
      cal(x,v,n);
    }
    tb = microsegundos();
    total1 = tb-ta;
    ta = microsegundos();
    for ( i =0 ; i<K ; i++){
      ini(v,n);
    }
    tb = microsegundos();
    total1 = (total1-(tb-ta))/K;
  }

  printf("%15i%c %15.3f %15.6f %15.6f %15.6f \n", n , aviso , total1,
  total1/cotainf, total1/cotaax,total1/cotasup);

  liberarMatriz(v,n);
  liberarMatriz(x,n);
}
/*
--------------------------------------------------------------------------------
*/
void calculoTempos(){
  int h;
  printf("\nGrafo de numeros aleatorios\n\n");
  printf("%16s %15s %15s %15s %15s\n", "n","t(n)","t(n)/n^2.8", "t(n)/n^3",
    "t(n)/n^3.2");
  for ( h = MIN_ITER; h<MAX_ITER ; h = h*2){
    tempos(h,dijkstra,iniMatriz,pow(h,2.8),pow(h,3),pow(h,3.2));
  }
}
/*
--------------------------------------------------------------------------------
*/

void proba1(){
  printf("\n Proba número 1:\n");
  matriz m ;
  matriz dis;
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
  printf("\n Proba número 2:\n");
  matriz m;
  matriz dis;
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
  calculoTempos();
}
