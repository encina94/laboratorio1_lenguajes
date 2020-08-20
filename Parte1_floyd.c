#define INF 99999999
#define nodos 16
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <time.h>
#include <windows.h>

//TODO parametrizar (pantalla ?))
//int nodos = 16;
char filename[] = "Datos distancias.csv";
int matriz_distancias[nodos][nodos];
unsigned int **adjacencyMatrix;
char nodeNames[nodos][nodos][100];
char routeMatrix[nodos][nodos][100];
char currentLocation[] = "Saladillo";
char destination[] = "Chacabuco";


int main(){
    printf("\nCreando la matriz");
    unsigned int **adjacencyMatrix = getMatrix();
    floyd(adjacencyMatrix);
    getBestWay();
    SegundaParte();
}

void getBestWay(){
    int isValidOrigin = 0;
    int isValidDestiny = 0;
    int originIndex = 0;
    int destinyIndex = 0;

    for(int i = 0; i < nodos; i++){
        if(strcmp(nodeNames[0][i],currentLocation) == 0){
            isValidOrigin = 1;
            originIndex = i;
        }
        if(strcmp(nodeNames[0][i],destination) == 0){
            isValidDestiny = 1;
            destinyIndex = i;
        }
    }

    if(isValidOrigin && isValidDestiny){
        printf("\n El mejor camino desde %s a %s es:  %s -> %s -> %s ",
               nodeNames[0][originIndex],nodeNames[0][destinyIndex],nodeNames[0][originIndex],
               routeMatrix[originIndex][destinyIndex],nodeNames[0][destinyIndex]);
    }
}

void floyd (unsigned int **matriz)
{
    //Creamos una nueva matriz para colocar los nuevos valores de distancias o usamos la misma que creamos????
    int k, i, j;

    //Inicializamos la matriz resultante que va a ser la de distancias
    for (i = 0; i < nodos; i++)
        for (j = 0; j < nodos; j++){
            matriz_distancias[i][j] = matriz[i][j];
            strcpy(routeMatrix[i][j],nodeNames[i]);
        }

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
                if ((matriz_distancias[i][k] + matriz_distancias[k][j]) < matriz_distancias[i][j]){
                    //Se actualiza la distancia
                    matriz_distancias[i][j] = matriz_distancias[i][k] + matriz_distancias[k][j];
                    strcpy(routeMatrix[i][j],nodeNames[i][k]);
                }
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
	for(int i = 0; i < nodos; i++){
        adjacencyMatrix[i] = malloc(nodos * sizeof(unsigned int));
	}
    //read line by line
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineCount = 0;
    while (fgets(line, line_size, fh) != NULL)  {
        char * token = strtok(line, ";");
        // loop through the string to extract all other tokens
        //token count to skip column of node name
        int tokenCount = 0;
        while(token != NULL) {
            if(lineCount == 0){
                for(int i = 0; i < nodos; i++){
                    strcpy(nodeNames[i][(tokenCount+1)],token);
                    strcpy(routeMatrix[i][(tokenCount+1)],token);
                }
                for(int i = 0; i < nodos; i++){
                    strcpy(nodeNames[i][0],nodeNames[0][i]);
                }
                //strcpy(nodeNames[tokenCount],token);
            }
            if((lineCount > 0) && tokenCount > 0){
                adjacencyMatrix[lineCount-1][tokenCount-1] = atoi(token);
            }
            token = strtok(NULL, ";");
            tokenCount++;
        }
        lineCount++;
    }

    free(line);    // dont forget to free heap memory
    return adjacencyMatrix;
}







//**********************PARTE 2 AUTOMATAS*********************************************


 char *ciudades[16]= {"Mar del Plata", "Balcarce", "Tandil", "Azul", "Tapalque", "Saladillo", "25 de mayo", "Chivilcoy", "Chacabuco", "Dolores", "Castelli", "Gral Belgrano", "San miguel del monte", "Lobos", "Roque Perez", "Ayacucho"};
 char ciudadesDisponibles[] = "Mar del Plata, Balcarce, Tandil, Azul, Tapalque, Saladillo, 25 de mayo, Chivilcoy, Chacabuco, Dolores, Castelli, Gral Belgrano, San miguel del monte, Lobos, Roque Perez, Ayacucho";
 char origen[20];
 char GPS[20];
 char destino[20];
 char des[20];
 int indiceOrigen, indiceDestino;
 int velocidades[]={90,120,160,180};
 float velocidadMedia=0;
 float tiempo;
 float distanciaPorRecorrer;
 int EstadoActual, EstadoAnterior;

 void SegundaParte()
{
    MostrarMenu();
}


void Actualizar_GPS(){
    EstadoActual= 1;
    printf("\n Estado Actual: %i", EstadoActual);
    printf("\n Las ciudades disponibles son: %s\n",ciudadesDisponibles );
    printf("\nIngrese la ciudad actual: ");
	scanf("%s", origen);
    sprintf( GPS, "%s", origen );
   // printf("\n %s", GPS);
  //  GPS = origen;
    Seleccionar_Destino();
}


void Seleccionar_Destino(){
    EstadoAnterior = EstadoActual;
    EstadoActual = 2;
    printf("\n Estado Actual: %i", EstadoActual);

    if(EstadoAnterior != 1){
       printf("\n Debe Actualizar GPS");
        Actualizar_GPS();
        return;
    }
    printf("\nIngrese la ciudad de destino: ");
	scanf("%s", des);
	sprintf( destino, "%s", des );
    //printf("\n %s", destino);
    //destino = destino;
    Imprimir_Recorrido();
}

void Imprimir_Recorrido(){
     EstadoAnterior = EstadoActual;
    EstadoActual = 3;
    printf("\n Estado Actual: %i", EstadoActual);

    if(EstadoAnterior != 2){
         printf("\n Debe Seleccionar Destino");
        Seleccionar_Destino();
        return;
    }

    int j,i;
     for (j = 0; j < 16; j++)
    {
         if (strcmp(ciudades[j], GPS) == 0) {
            indiceOrigen = j;
           // printf("\n %i", indiceOrigen);
         }
         else if(strcmp(ciudades[j], destino) == 0){
            indiceDestino = j;
           // printf("\n %i", indiceDestino);

         };
    };

     printf("\n El recorrido sera el siguiente:");

     for (i=indiceOrigen; i <= indiceDestino; i++)
        {
            printf("\n %s", ciudades[i]);
        }
    Iniciar_Recorrido();

}


 Iniciar_Recorrido(){
    EstadoAnterior = EstadoActual;
    EstadoActual = 4;
    printf("\n Estado Actual: %i", EstadoActual);

    if(EstadoAnterior != 3){
         printf("\n Debe Mostrar Recorrido");
        Imprimir_Recorrido();
        return;
    }
     int i;
    distanciaPorRecorrer = ((float)matriz_distancias[indiceOrigen][indiceDestino]) * 1.0;
printf("\n distancia por reccorrer %2f km, tiempo inicial: 0",distanciaPorRecorrer);
      Sleep(20000);

    for (i = 0; i < 4; i++){
        velocidadMedia += velocidades[i];
        velocidadMedia = velocidadMedia/ (i+1);
        tiempo = distanciaPorRecorrer / velocidadMedia;
        printf("\n Ha recorrido: %2f km", velocidadMedia);
        printf("Tiempo Restante: %6f hs ", tiempo);
        distanciaPorRecorrer -= velocidadMedia;
        if(distanciaPorRecorrer < 0){
                Finalizar_Camino();
           break;
        }
        if(i == 3){
            velocidadMedia = 0;
            i=0;
        }
        Sleep(20000);
    }

 }

 void Finalizar_Camino(){
    EstadoAnterior = EstadoActual;
    EstadoActual = 5;
    printf("\n Estado Actual: %i", EstadoActual);

    if(EstadoAnterior != 4){
         printf("\n Debe Iniciar el Camino");
        Iniciar_Recorrido();
        return;
    }
            printf("\n Haz llegado a destino %s!!", destino );
 }


 MostrarMenu(){
     int opcionMenu;
   printf("\n Seleccione una opcion del menu");
   printf("\n 1:  Actualizar GPS., 2: Seleccionar Destino., 3: Mostrar Recorrido., 4: Iniciar Camino., 5: Finalizar Camino.");
   scanf("%i", &opcionMenu);

   if(opcionMenu == 1){
        printf("if 1");
        Actualizar_GPS();
   }
   else if(opcionMenu == 2){
            Seleccionar_Destino();
   }
   else if(opcionMenu == 3){
        Imprimir_Recorrido();
   }
   else if(opcionMenu == 4){
            Iniciar_Recorrido();
     }
   else if(opcionMenu == 5){
            Finalizar_Camino();
   }
 }
