#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void verTabla(int** tabla,int n,int vmax){
  int i,j;
  for(i=0;i<n;i++){
    for(j=0;j<vmax;j++){
      printf("%d ", tabla[i][j]);
    }
    printf("\n");
  }
}

/*Función que se encarga de llenar la tabla de valores
@params: n número de libros
         Vmax númeroo máximo de volúmen del cajon
@output: matriz con informacion
*/
int ** algoritmo1(int n, int Vmax, NODO * S){
  int ** V = (int**)malloc(n*sizeof(int*));
  int z = 0;
  int j = 0;
  int i=0;
  int v =0;
  int v_i;
  for (z=0; z<n; z++){
    V[z] = (int*)malloc(Vmax*sizeof(int));
  }

  for (v=0; v<Vmax; v++){
    V[0][v] = 0;
  }

  for (i=0; i<n; i++){
    V[i][0] = 0;
  }
  for (i=1; i<n; i++){
    for (v=0; v<Vmax; v++){
      v_i = S[i].volumen;
      if (v_i <= v){
        if(v_i + V[i-1][v-v_i] >  V[i-1][v]){
          V[i][v] = v_i + V[i-1][v- v_i];
        }else{
          V[i][v] = V[i-1][v];
        }
      }else{
        V[i][v] = V[i-1][v];
      }
    }
  }
  //verTabla(V,n,Vmax);
  return V;
}

/*Funcion que se encarga de agregar a los libros
que deben ir en el cajón dados los resultados de una tabla
@params: n número de libros
         Vmax númeroo máximo de volúmen del cajon
@output: conjunto de libros
*/
LISTA ** algoritmo2(int n, int Vmax, NODO * S,int ** tabla){
  int i = n-1;
  int k = Vmax-1;
  LISTA ** resultados = (LISTA**)malloc(2*sizeof(LISTA*));
  resultados[0] = crearLista();
  resultados[1] = crearLista();
  while (i>0 && k>0){
    if(tabla[i][k] != tabla[i-1][k]){
      resultados[0] = insertar_final(resultados[0],S[i].id,S[i].largo,S[i].alto,S[i].ancho);
      i=i-1;
      k=k-1;
    }else{
      resultados[1] = insertar_final(resultados[1],S[i].id,S[i].largo,S[i].alto,S[i].ancho);
      i=i-1;
    }
  }
  return resultados;
}

int volumenLista(LISTA* L){
  if(L!=NULL){
    int vol=0;
    NODO* aux = L->primero;
    while(aux!= NULL){
      vol = vol + aux->volumen;
      aux = aux->sig;
    }
    return vol;
  }else{
    return -1;
  }
}

void salida(LISTA ** resultados, int Vfinal, int Vmax, FILE * file){
  NODO * aux = resultados[0]->primero;
  NODO * aux1 = resultados[1]->primero;
  fprintf(file, "En la caja:\n" );
  while(aux!=NULL){
    fprintf(file,"%s %d %d %d\n", aux->id, aux ->largo, aux->alto, aux->ancho);
    aux = aux->sig;
  }
  fprintf(file, "\nFuera de la caja:\n" );
  while(aux1!=NULL){
    fprintf(file,"%s %d %d %d\n", aux1->id, aux1 ->largo, aux1->alto, aux1->ancho);
    aux1 = aux1->sig;
  }
  fprintf(file, "Espacio libre dentro de la caja:\n%d centímetros cúbicos", Vmax-Vfinal);
}

int main(int argc, char const *argv[]) {
  //Definicion de variables///
  int N,VMAX;
  char * ident;
  int largo,alto,ancho;
  int LARGO,ALTO,ANCHO;
  double LARGO_MAX,ALTO_MAX,ANCHO_MAX;
  int ** V;
  NODO * S;
  NODO *aux;
  int vol;
  LISTA ** resultados = NULL;
  //Verificacion de entrada////
  if(argc == 3){
    FILE * in = fopen(argv[1],"r");
    FILE * out = fopen(argv[2],"w");
    if(in){
      if(out){
        /////////////////////PROCESAMIENTO DE ENTRADA /////////////
        fscanf(in,"%lf %lf %lf\n",&LARGO_MAX,&ALTO_MAX,&ANCHO_MAX);
        LARGO = (int)(LARGO_MAX*100);
        ALTO = (int)(ALTO_MAX*100);
        ANCHO = (int)(ANCHO_MAX*100);
        VMAX = LARGO*ANCHO*ALTO;
        N=0;
        LISTA * L= crearLista();
        while(!feof(in)){
          ident = (char *)malloc(20*sizeof(char));
          fscanf(in,"%s %d %d %d\n",ident,&largo,&alto,&ancho);
          L =insertar_final(L,ident,largo,alto,ancho);

          N++;
        }
        aux = L->primero;
        S = (NODO *)malloc(N*sizeof(NODO));
        int i =0;
        for(i=0;i<N;i++){
          S[i] = *aux;
          aux = aux->sig;
        }
        fclose(in);
        //////////////////////PROCESAMIENTO DE DATOS//////////////
        in = fopen(argv[1],"r");
        //DIMENSIONES CAJA
        printf("La caja que contendrá los libros tiene las siguientes medidas:\n\t LARGO: %d cm.\n\t ALTO: %d cm.\n\t ANCHO: %d cm.\n\nEstos son los posibles libros a introducir en la caja:\n\n", LARGO, ALTO, ANCHO);
        verLista(L);
        printf("\n\tConsiderando que los libros son líquidos y que pueden usar todo el espacio sin problemas de sobrelapamiento entre ellos.\n");
        printf("Estos deben cumplir con cubrir el volumen máximo de la caja que es de %d cm³\n\n", LARGO * ALTO*ANCHO);
        //verLista(L);
        V = algoritmo1(N,VMAX,S);
        resultados = algoritmo2(N,VMAX,S,V);
        vol =volumenLista(resultados[0]);
        printf("Este es el volumen dentro del cajón %d cm³\n", vol);
        salida(resultados,vol,VMAX,out);
        printf("Revise archivo %s\n",argv[2]);
        fclose(out);
      }else{
          printf("Error en la lectura de archivos: %s\n", argv[2]);
      }
    }else{
      printf("Error en la lectura de archivos: %s\n", argv[1]);
    }
  }else{
    printf("Para ejecutar ingrese:\n\n\t");
    printf("./main [nombre_entrada] [nombre_salida]\n");
    return 1;
  }
  return 0;
}
