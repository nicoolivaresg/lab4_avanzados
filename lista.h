#include <stdlib.h>
#include <stdio.h>

typedef struct nodo{
	char * id;
	int volumen;
	int largo;
	int alto;
	int ancho;
	struct nodo * sig;
}NODO;

typedef struct lista{
  NODO * primero;
  NODO * ultimo;
}LISTA;

/*
void swap(NODO * a, NODO * b){
	if(a!=NULL && b!= NULL){
		char * idAUX = (char*)malloc(20*sizeof(char));
	  double largoAUX;
	  double altoAUX;
	  double anchoAUX;
		double volumenAUX;
		idAUX = a->id;
		largoAUX = a->largo;
		altoAUX = a->alto;
		anchoAUX = a->ancho;
		volumenAUX = a->volumen;
		a->id = b->id;
		a->largo = b->largo;
		a->alto = b->alto;
		a->ancho = b->ancho;
		a->volumen = b->volumen;
		b->id = idAUX;
		b->largo = largoAUX;
		b->alto = altoAUX;
		b->ancho = anchoAUX;
		b->volumen = volumenAUX;
	}
}

LISTA * ordenar_por_volumen(LISTA * L){
	if (L!=NULL){
		if(L->primero !=NULL){
			NODO * i = L->primero;
			NODO * j= NULL;
			while(i!=NULL){
				j= i->sig;
				while(j!=NULL){
					if (j->volumen <= i->volumen) {
						swap(j,i);
					}
					j=j->sig;
				}
				i=i->sig;
			}
			return L;
		}
	}

}
*/
int empty(LISTA* L){
	if(L!=NULL){
		if(L->primero==NULL && L->ultimo==NULL){
			return 1;
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

LISTA* crearLista(){
	LISTA * nueva_L = (LISTA*)malloc(sizeof(LISTA));
	nueva_L->primero =NULL;
	nueva_L->ultimo =NULL;
	return nueva_L;
}

NODO* crearNodo(char * id, int largo, int alto, int ancho){
	NODO * nuevo_nodo = (NODO*)malloc(sizeof(NODO));
	nuevo_nodo->id = id;
	nuevo_nodo->largo = largo;
	nuevo_nodo->alto = alto;
	nuevo_nodo->ancho = ancho;
	nuevo_nodo->volumen = largo * alto * ancho;
	nuevo_nodo->sig = NULL;
	return nuevo_nodo;
}


void verLista(LISTA* L){
	if(L !=NULL){
		if(!empty(L)){
			NODO* aux = L->primero;
			while(aux!=NULL){
				printf(" %s %d cm³.\n", aux->id,aux->volumen);
				aux=aux->sig;
			}
			printf("\n");
		}else{
      printf("Lista vacía\n" );
    }
	}
}


LISTA* eliminar_inicio(LISTA* L){
	if(L!=NULL){
		if(empty(L)){
			return NULL;
		}else{
			NODO* aux = L->primero;
			if(aux->sig == NULL){
				L->primero=NULL;
				L->ultimo=NULL;
				free(aux);
				return L;
			}else{
				L->primero = aux->sig;
				free(aux);
				return L;
			}
		}
	}else{
		return NULL;
	}
	return NULL;
}

LISTA* eliminar_final(LISTA * L){
	if(L!=NULL){
		if(empty(L)){
			return NULL;
		}else{
			NODO* aux = L->primero;
			if(aux->sig == NULL){
				L->primero=NULL;
				L->ultimo=NULL;
				free(aux);
				return L;
			}else{
				while(aux->sig!=L->ultimo){
					aux =aux->sig;
				}
				aux->sig=NULL;
				free(L->ultimo);
				L->ultimo = aux;
				return L;
			}
		}
	}else{
		return NULL;
	}
	return NULL;
}

LISTA* insertar_final(LISTA * L, char * id, int largo, int alto, int ancho){
	if(L!=NULL){
		NODO* aux = L->ultimo;
		NODO * nuevo = crearNodo(id,largo,alto,ancho);
		if(aux==NULL){
			L->ultimo = nuevo;
			L->primero = nuevo;
			return L;
		}else{
			L->ultimo->sig=nuevo;
			L->ultimo = nuevo;
			return L;
		}
	}else{
		return NULL;
	}
	return NULL;
}

LISTA* insertar_inicio(LISTA* L, char * id, int largo, int alto, int ancho){
	if(L!=NULL){
		NODO* aux = L->primero;
		NODO * nuevo = crearNodo(id,largo,alto,ancho);
		if(aux==NULL){
			L->primero = nuevo;
			L->ultimo = nuevo;
		}else{
			nuevo->sig= aux;
			L->primero = nuevo;
		}
		return L;
	}else{
		return NULL;
	}
	return NULL;
}
