#define _GNU_SOURCE
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



