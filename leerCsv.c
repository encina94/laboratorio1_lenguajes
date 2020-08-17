#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    //open and get the file handle
    char filename[] = "Datos distancias.csv";
    FILE* fh;
    fopen_s(&fh, filename, "r");

    //check if file exists
    if (fh == NULL){
        printf("file does not exists %s", filename);
        return 0;
    }

    //TODO argument (cantidad de nodos que va a procesar)
    int nrows = 16;
    int ncolumns = 16;

    unsigned int **adjacencyMatrix = malloc(nrows * sizeof(unsigned int *));
	for(int i = 0; i < nrows; i++)
		adjacencyMatrix[i] = malloc(ncolumns * sizeof(unsigned int));

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


    for(int i = 0; i < nrows; i++){
        printf("El nodo %d tiene las siguientes adyacencias: ",i);
        for(int j = 0; j < ncolumns; j++){
            printf("%d, ",adjacencyMatrix[i][j]);
        }
        printf("\n");
    }



    free(line);    // dont forget to free heap memory
return 0;
}



/**

//Se crea una matriz de adyacencia con todos los pesos de tamaño 16 X 16
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

*/


