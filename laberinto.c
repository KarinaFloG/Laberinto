#include "Stack.c"
/*-----------------------------------------------------------------------------
*                           Driver Program
*-----------------------------------------------------------------------------*/

int main()
{
    DLL* miLista = DLL_Create ();
    int tablero[TAM][TAM];
    int Conjunto_x[TAM]={-1,0,1,0}; //Representa los movimientos de derecha a izquierda
    int Conjunto_y[TAM] = {0,1,0,-1}; //Representa los movimientos arriba y abajo
    
    printf("\n\t*****************LABERINTO**************************\n");
    printf("\nPor favor ingrese las coordenadas del laberinto a resolver...");
    printf("\n0---Paredes");
    printf("\n1---Libre");
    printf("\n2---Entrada");
    printf("\n3---Salida\n");
    
    
    for (int i = 0; i< TAM; i++)
    {
        for(int j = 0; j < TAM; j++)
        {
            printf("\nPosicion <%d %d>:",i+1,j+1);
            scanf("%d", &tablero[i][j]);
        }
    }
    
    
    if (laberinto(miLista,Conjunto_x,Conjunto_y,tablero,TAM) == TRUE)
    {
    	printf("\n\tHubo solucion al laberinto\n");
	}
	else
	{
		printf("\n\tNO hubo solucion al laberinto\n");
        
        if(DLL_Empty(miLista) == TRUE)
        {
            printf("\n\t No hay elementos en la pila\n");
        }
	}
	
	DLL_Destroy (miLista); //Devuelve memoria pedida al sistema

	return 0;
}
