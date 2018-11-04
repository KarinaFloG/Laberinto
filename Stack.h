/*-----------------------------------------------------------------------------
 *                           Lista Doblemente Enlazada 
 *-----------------------------------------------------------------------------*/
#include<stdlib.h>

#include<stdio.h>

#define TAM 4 //Cambiar en caso de que se desee cambiar el tamano del laberinto
/*-----------------------------------------------------------------------------*/
enum {FALSE = 0, TRUE = !FALSE};
typedef unsigned int Bool;
/*-----------------------------------------------------------------------------*/
struct Node_Type 
{
	int Coord_x; //Guarda la coordenada en x del tablero
    int Coord_y; //Guarda la coordenada en y del tablero
	struct Node_Type* next;
	struct Node_Type* prev;
};
typedef struct Node_Type Node;
/*-----------------------------------------------------------------------------*/
struct DLL_Type 
{
	Node* first;
	Node* last;

	Bool empty;
};
typedef struct DLL_Type DLL;
/*----------------------------------------------------------------------------------------*/
static Node* newNode (int x, int y);
//Crea un nuevo nodo en la lista
//Recibe los valor x & y que correponde a los campos de la estructura del nodo
//x & y representan las coordenadas del movimiento realizado
/*----------------------------------------------------------------------------------------*/
static void deleteNode (Node* n);
//Borra un nodo cuando se hace un pop en la lista / pila
/*----------------------------------------------------------------------------------------*/
DLL* DLL_Create();
//Crea el contenedor de la pila en la que se almacenaran los movimientos
/*----------------------------------------------------------------------------------------*/
Bool DLL_RemoveBack (DLL *this, int *x, int *y);
//Hace un pop en la pila 
//Remueve al ultimo elemento que entro (x,y)
//Almacena los valores que se removieron temporalmente en x  y y
//Retorna TRUE si los valores se removieron bien 
/*----------------------------------------------------------------------------------------*/
Bool DLL_Insert (DLL* this,int x, int y);
//Recibe como parametro a la pila en donde se almacenan las coordenadas
//Recibe los valores que se deseen ingresar a la pila
// x  & y representan los movimientos realizados en filas y columnas
/*--------------------------------------------------------------------------------------------------------------*/
Bool DLL_Empty(DLL* this);
//Devuelve TRUE en caso de que la pila este vacia
//Recibe como parametro a la pila
/*--------------------------------------------------------------------------------------------------------------*/
Bool Factible(int movimiento_x, int movimiento_y,int tablero[][TAM], int tam);
//Recibe al conjunto de movimientos que se realiza para encontrar la solucion
//Recibe al tablero del laberinto que se desea resolver
//Recibe el tamano del del laberinto
//Devuelve TRUE si el candidato / moviemiento es factible para la solucion 
//Es factible si cumple con todas las condiciones
/*--------------------------------------------------------------------------------------------------------------*/
Bool Solucion(int tablero[][TAM],int movimiento_x, int movimiento_y);
//Recibe al tablero del laberinto que se desea resolver
//Recibe al conjunto de movimientos que se realizan para encontrar la solucion
//Retorna TRUE si el candidato que se esta evaluando corresponde a la solucion
//En este caso la solucion se representa con el numero 3
/*---------------------------------------------------------------------------------------------------------------*/
Bool BackTracking(DLL* this, int Conjunto_x[],int Conjunto_y[],int tablero[][TAM], int x, int y, int tam);
//Recibe como parametro a la pila en la que se almacenan los candidatos factibles
//Recibe al conjunto de movimientos que se realiza para encontrar la solucion
//Recibe al tablero del laberinto que se desea resolver
//Recibe las coordenadas x & y que corresponden al inicio del laberinto o al ultimo movimeinto
//Recibe al tamano del laberinto
//Regresa TRUE en caso de que los candidatos evaluados formen la solucion 
//Regrresa FALSE si no hubo solucion al laberinto ingresado
//COntiene a la funcion recursiva del problema
//Contienen al caso base del problema (que el candidato sea igual a 3)
/*---------------------------------------------------------------------------------------------------------------*/
Bool laberinto(DLL* this,int Conjunto_x[],int Conjunto_y[],int tablero[][TAM],int tam);
//Funcion activacion del problema
//Recibe a la pila en la que se almacenan los candidatos
//Recibe al conjunto de movimientos que se realizan para encontrar la solucion
//Recibe el tablero del laberinto que de desea resolver
//Recibe el tamano del laberinto
//Retorna TRUE en caso de que la funcion BackTracking haya devuelto TRUE (Solucion)
//Retorna FALSE en caso de que la funcion BackTracking haya devuelto FALSE (No hubo solucion)
/*---------------------------------------------------------------------------------------------------------------*/
void DLL_Destroy (DLL* this);
//Recibe como parametro a la pila con la que se esta trabajando 
//Devuelve la memoria pedida al sistema para crear la pila
