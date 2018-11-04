#include "Stack.h"
/*-----------------------------------------------------------------------------*/
static Node* newNode (int x, int y)
{
	Node* n = (Node *) malloc (sizeof (Node));

	n -> Coord_x = x;
    n -> Coord_y = y;
	n -> next = n -> prev = NULL;

	return n;
}
/*-----------------------------------------------------------------------------*/
static void deleteNode (Node* n)
{
	if (n){	
		free (n);
	}
}

/*-----------------------------------------------------------------------------*/
DLL* DLL_Create()
{
	DLL* n = (DLL*) malloc (sizeof (DLL));

	n -> first = n -> last = NULL;
	n -> empty = TRUE;		
		
	return n;
}


/*-----------------------------------------------------------------------------*/
Bool DLL_RemoveBack (DLL *this, int *x, int *y)
{
	if (this -> first != this -> last) //2 o + Nodos
	{
        *y = this -> last -> Coord_y;
		*x = this -> last -> Coord_x;

		Node *tmp = this -> last -> prev;

		deleteNode (this -> last);

		this -> last = tmp;
		this -> last -> next = this -> first;
		this -> first -> prev = this -> last;

		return TRUE;
	}
	else if (this -> empty == FALSE) // Un Nodo
	{	
		*x = this -> last -> Coord_x;
        *y = this -> last -> Coord_y;
		deleteNode (this -> last);
		this -> first = this -> last = NULL;
		this -> empty = TRUE;
		return TRUE;
	}
	else {return FALSE;}
}

/*-----------------------------------------------------------------------------*/
Bool DLL_Insert (DLL* this,int x, int y)	
{
	//Crear nuevo Nodo
	Node* n = newNode (x,y);

	//La lista esta vacia
	if (this -> empty == TRUE) 
	{ 
		this -> first = this -> last = n;
		this -> last -> next = this -> first;
		this -> first -> prev = this -> last;
		this -> empty = FALSE;
	}
	//Si la lista NO esta vacia
	else
		{
			this -> last -> next = n;
			n -> prev = this -> last;
			this -> last = n;        
			this -> last -> next = this -> first;
			this -> first -> prev = this -> last;
		}/*----------------------------------------------------------------------------------------*/

	
	return TRUE;
			
}

/*-----------------------------------------------------------------------------*/
Bool DLL_Empty(DLL* this)
{
		//Si esta vacia devuelve TRUE
		if (this->first !=  NULL) {return FALSE;}	
		else
		{
			return TRUE;
		}
}
/*----------------------------------------------------------------------------------------*/
Bool Factible(int movimiento_x, int movimiento_y,int tablero[][TAM], int tam)
{
	int espacio; // candidato en tablero
	
	if ((movimiento_x >= 0) & (movimiento_x <= tam)) // que no se salga de los limites en x
	{
		if((movimiento_y >= 0) & (movimiento_y <= tam)) //que no se salga de los limites en y
		{
			espacio = tablero[movimiento_x][movimiento_y];
            
			if(espacio != 0) //que no sea pared
			{
				if(espacio != 4) //que no haya sido visitado
				{
					if(espacio != 3) //Que no sea la solucion
					{
						return TRUE; //Es factible
					}
					else{return FALSE;} //Que no sea la solucion
				}
				else{ return FALSE;} //Espacio != 4
			}
			else{return FALSE;} //Espacio != 0
		} //movimiento en y 
		else{return FALSE;} //movimiento_y factible
	} //movimiento en x factible
	else {return FALSE;} // movimiento_x factible
}//Bool Factible
/*-----------------------------------------------------------------------------------------------*/

Bool Solucion(int tablero[][TAM],int movimiento_x, int movimiento_y)
{
    int pSolucion = tablero[movimiento_x][movimiento_y]; //Asigna el valor del candidato a pSolucion
    
    if (pSolucion == 3)
    {
        return TRUE; //ES SOLUCION
    }
    else {return FALSE;} //if NO ES SOLUCION
} //Solucion

/*-------------------------------------------------------------------------------------------------*/
Bool BackTracking(DLL* this, int Conjunto_x[],int Conjunto_y[],int tablero[][TAM], int x, int y, int tam)
{
	int regresar = 0; //Para retroceder en candidatos
    Bool success; //Bandera para llevar el control
    int i = 0; //indice
    int movimiento_x, movimiento_y; //control de movimientos 
    
    success = FALSE; //Bandera para llevar el control del resultado
    
    for (i = 0; i < tam; i++)
    {
    
        if (success == TRUE){return TRUE;}

        //Movimientos realizados
      	movimiento_x = x+Conjunto_x[i];
      	movimiento_y = y+Conjunto_y[i];
        
      	
    	//Probar si el movimiento esta permitido
        if((Factible(movimiento_x, movimiento_y ,tablero,tam)) == TRUE)
        {
        	//Se marca como visitada la casilla
        	tablero[movimiento_x][movimiento_y] = 4;
            
        	
        	//La registramos
        	DLL_Insert (this,movimiento_x, movimiento_y);	
            

        	//Revisa si es solucion
        	if (Solucion(tablero, movimiento_x, movimiento_y) == TRUE) //CASO BASE
        	{
        		success = TRUE;
        		return TRUE;
			} //If solucion
			else
			{
				regresar = i;
                
				//llamada recursiva para seguir probando candidatos
				success = BackTracking(this, Conjunto_x,Conjunto_y, tablero, movimiento_x, movimiento_y, tam);
				if(success == FALSE)
				{
					//Cancela el registro
					DLL_RemoveBack(this, &movimiento_x, &movimiento_y);
					
                    //Se regresa
					movimiento_x = movimiento_x - Conjunto_x[regresar];
					movimiento_y = movimiento_y - Conjunto_y[regresar];
					
				} //if success == FALSE
			} //else solucion
		} // if factible
	i++; // aumenta el indice para el if 
	}
    return success;
} //bt
/*-----------------------------------------------------------------------------*/
Bool laberinto(DLL* this,int Conjunto_x[],int Conjunto_y[],int tablero[][TAM],int tam)
{
	Bool res; //Bandera de control
    int x, y; //Para las posiciones de entrada
    
    for( int fila = 0; fila < tam; fila++) //Control del tablero
    {
    	for(int colum = 0; colum < tam; colum++)
    	{
    		if(tablero[fila][colum] == 2) //Es la entrada
    		{
    			//Posiciones de entrada
    			x = fila;
    			y = colum;
			}
		}
	}
	
	res = BackTracking(this,Conjunto_x,Conjunto_y,tablero, x, y, tam);
	
	if(res == TRUE)
	{
		if (DLL_Empty(this) != TRUE)
		{
			return TRUE; //La pila contiene elementos
		}
		else{return FALSE;}
	}
	else {return FALSE;}
	
} //laberinto
/*-------------------------------------------------------------------------------*/
void DLL_Destroy (DLL* this)
{
	while (this -> first != NULL){
		Node* tmp = this -> first -> next;
		deleteNode (this -> first);
		this -> first = tmp;
	}
	free (this);
}

