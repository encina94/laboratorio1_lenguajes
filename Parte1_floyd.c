#include <stdlib.h>
#include <stdio.h>


//TODO parametrizar (pantalla ?))
int nodos = 16;
char filename[] = "Datos distancias.csv";

int main(){
    printf("\nCreando la matriz");
    unsigned int **adjacencyMatrix = getMatrix();
    floyd(adjacencyMatrix);
}

void floyd (unsigned int **matriz)
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
    for (int i = 0; i < nodos; i++)
    {
        for (int j = 0; j < nodos; j++)
        {
            printf (" %7d", matriz_distancias[i][j]);
        }
        printf("\n");
    }
}


int getMatrix()
{
    FILE* fh;
    fopen_s(&fh, filename, "r");

    //check if file exists
    if (fh == NULL){
        printf("file does not exists %s", filename);
        return 0;
    }

    unsigned int **adjacencyMatrix = malloc(nodos * sizeof(unsigned int *));
	for(int i = 0; i < nodos; i++)
		adjacencyMatrix[i] = malloc(nodos * sizeof(unsigned int));

    //TODO argument
    //read line by line
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineCount = 0;
    while (fgets(line, line_size, fh) != NULL)  {
        //skip header
        if(lineCount > 0){
            char * token = strtok(line, ";");
            // loop through the string to extract all other tokens
            //token count to skip column of node name
            int tokenCount = 0;
            while( token != NULL) {
                if(tokenCount > 0){
                    adjacencyMatrix[lineCount-1][tokenCount-1] = atoi(token);
                }
                token = strtok(NULL, ";");
                tokenCount++;
            }
        }
        lineCount++;
    }
    free(line);    // dont forget to free heap memory
    return adjacencyMatrix;
}
