#define INF 99999999
#define nodos 16
#include <stdlib.h>
#include <stdio.h>

int main(){

printf("\nCreando la matriz");

//Se crea una matriz de adyacencia con todos los pesos de tama�o 16 X 16
    int matriz[nodos] [nodos] = { {0, 74, INF, INF, INF, INF, INF, INF,INF, 202, INF, INF, INF, INF, INF, 172},

                                        {74, 0, 108, 206, INF, INF, INF, INF, INF, 302, INF, 255, INF, INF, INF, 96},

                                        {INF, 108, 0, 103, INF, INF, INF, INF, INF, 219, INF, INF, 283, 322, INF, 76},

                                        {INF, 206, 103, 0, 51, 137, INF, INF,INF, INF, INF, INF, 260, 224, INF, 144},

                                        {INF, INF, INF, 51, 0, 88, INF, INF, INF, INF, INF, INF, INF, INF, INF, INF},

                                        {INF, INF, INF, 137, 88, 0, 50, 108, INF, INF, INF, INF, INF, 85, 55, 318},

                                        {INF, INF, INF, INF, INF, 50, 0, 74, INF, INF, INF, INF, INF, INF, 103, INF},

                                        {INF, INF, INF, INF, INF, 108, 74, 0, 51, INF, INF, INF, INF, INF, 98, 377},

                                        {INF, INF, INF, INF, INF, INF, INF, 51, 0, INF, INF, INF, INF, INF, INF, INF},

                                        {202, 203, 219, INF, INF, INF, INF, INF, INF, 0, 30, INF, INF, 195, 39, 155},

                                        {INF, INF, INF, INF, INF, INF, INF, INF, INF, 30, 0, 78, INF, INF, INF, INF},

                                        {INF, INF, INF, INF, INF, INF, INF, INF, INF, INF, 78, 0, 53, INF, INF, 167},

                                        {INF, INF, 283, 260, INF, INF, INF, INF, INF, INF, INF, 53, 0, 42, INF, 215},

                                        {INF, INF, 322, 224, INF, 85, INF, INF, INF, 195, INF, INF, 42, 0, 39, INF},

                                        {INF, INF, INF, INF, INF, 55, 103, 98, INF, 39, INF, INF, INF, 39, 0, INF},

                                        {172, 96, 76, 144, INF, 318, INF, 377, INF, 155, INF, 167, 215, INF, INF, 0}

    };
    floyd(matriz);
}

void floyd (int matriz[nodos][nodos])
{

    //Creamos una nueva matriz para colocar los nuevos valores de distancias o usamos la misma que creamos????
    int matriz_distancias[nodos][nodos], k, i, j;

    //Inicializamos la matriz resultante que va a ser la de distancias
    for (i = 0; i < nodos; i++)
        for (j = 0; j < nodos; j++)
            matriz_distancias[i][j] = matriz[i][j];

    //Seleccionamos cada nodo intermedio (k)
    for (k = 0; k < nodos; k++)
    {
        //Seleccionamos los nodos de inicio
        for (i = 0; i < nodos; i++)
        {
            //Seleccionamos los nodos de destino
            for (j = 0; j < nodos; j++)
            {
                //Verificamos si la distancia es menor a la existente
                if (matriz_distancias[i][k] + matriz_distancias[k][j] < matriz_distancias[i][j])
                    //Se actualiza la distancia
                    matriz_distancias[i][j] = matriz_distancias[i][k] + matriz_distancias[k][j];
            }
        }
    }
    //Se coloca directamente la distancia de la posicion en la matriz [8][0] que corresponde a Chacabuco como origen y mar del plata como destino
    printf("\nLa distancia minima entre las ciudades de Chacabuco y Mar del Plata es de: %d kms. \n", matriz_distancias[8][0]);
    show_matriz_distancias(matriz_distancias);
}

void show_matriz_distancias(int matriz_distancias[nodos][nodos])
{
    int i;
    for (i = 0; i < nodos; i++)
    {
        int j;
        for (j = 0; j < nodos; j++)
        {

            if (matriz_distancias[i][j] == INF)
                printf("%7s", "  INF  ");
            else
                printf (" %7d", matriz_distancias[i][j]);
        }
        printf("\n");
    }
}
