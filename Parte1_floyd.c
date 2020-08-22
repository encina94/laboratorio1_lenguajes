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
#include <stdbool.h>

//TODO parametrizar (pantalla ?))
//int nodos = 16;
char filename[] = "Datos distancias.csv";
int matriz_distancias[nodos][nodos];
unsigned int **adjacencyMatrix;
char nodeNames[nodos][nodos][100];
char routeMatrix[nodos][nodos][100];
char wayArray[nodos][100];
char currentLocation[];
char destination[];

//******************
 char origen[256];
 char destino[256];
 char des[256];
 int indiceOrigen, indiceDestino;
 int velocidades[]={90,120,160,180};
 float velocidadMedia=0;
 float tiempo;
 float distanciaPorRecorrer;
 int EstadoActual, EstadoAnterior;

int main(){
    printf("\nCreando la matriz");
    unsigned int **adjacencyMatrix = getMatrix();
    floyd(adjacencyMatrix);
    SegundaParte();
}

bool IsValidOrigin(ciudadOrigen){
    for(int i = 0; i < nodos; i++){
        if(strcmp(nodeNames[0][i],ciudadOrigen) == 0){
            return true;
        }
    }
    return false;
}

bool IsValidDestiny(ciudadDestino){

    for(int i = 0; i < nodos; i++){
        if(strcmp(nodeNames[0][i],ciudadDestino) == 0){
            return true;
        }
    }
    return false;
}

void getBestWay(char origin[], char destiny[]){
    printf("El mejor camino desde %s a %s es: \n",origin,destiny);
    printf("%s ",origin);
    calculateBestWay(origin,destiny);
}

/**
nodeNames[0]  es un arreglo (listado) de los 16 nombres de los nodos
indiceOrigen  es la posicion del nodo origen en el listado de arriba
indiceDestino es la posicion del nodo destino en el listado de arriba

*/
void calculateBestWay(char origin[], char destiny[]){
    int nodeAlreadyVisited = 0;
    for(int i = 0; i < nodos; i++){
        if(strcmp(wayArray[i],origin) == 0){
            nodeAlreadyVisited = 1;
        }
        if(strcmp(nodeNames[0][i],origin) == 0){
            indiceOrigen = i;
        }
        if(strcmp(nodeNames[0][i],destiny) == 0){
            indiceDestino = i;
        }
    }
    char *adjNode = routeMatrix[indiceOrigen][indiceDestino];
    if((strcmp(adjNode,destiny) == 0) || (nodeAlreadyVisited == 1)){
        printf("-> %s",destiny);
        printf("\n");
    }else{
        //imprimimos de la matriz final el nombre que esté en la posicion "como llegar a destino" (fila del nodo origen, columna nodo destino)
        printf("-> %s ", adjNode);
        strcpy(wayArray[indiceOrigen],adjNode);
        calculateBestWay(adjNode,destiny);
    }
}

void getBestWayOld(char origen[], char destino[]){
    for(int i = 0; i < nodos; i++){
        if(strcmp(nodeNames[0][i],origen) == 0){
            indiceOrigen = i;
        }
        if(strcmp(nodeNames[0][i],destino) == 0){
            indiceDestino = i;
        }
    }


    do{
        //imprimimos de la matriz final el nombre que esté en la posicion "como llegar a destino" (fila del nodo origen, columna nodo destino)
        printf("-> %s ", routeMatrix[indiceOrigen][indiceDestino]);
        for(int i = 0; i < nodos; i++){
            //busco el índice para ese nuevo nodo por el que tiene que pasar para saber que fila buscar
            if(strcmp(nodeNames[0][i],routeMatrix[indiceOrigen][indiceDestino]) != 0){
                indiceOrigen = nodeNames[0][i];
            }
        }
    }
    //Si desde el nuevo nodo (nueva fila) no llega al destino, volver a hacer lo mismo
    while(strcmp(routeMatrix[indiceOrigen][indiceDestino],destino) != 0);
    printf("-> %s",nodeNames[0][indiceDestino]);
    printf("\n");
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
                    strcpy(nodeNames[i][(tokenCount)],token);
                    strcpy(routeMatrix[i][(tokenCount)],token);
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

 void SegundaParte()
{
    MostrarMenu();
}


void Actualizar_GPS(){
    EstadoActual= 1;
    printf("\n Estado Actual: %i", EstadoActual);
    printf("\n Las ciudades disponibles son:");
    for(int i = 0; i < nodos ; i++){
        printf(" %s ",nodeNames[0][i]);
    }
    printf("\n");
    printf("Ingrese la ciudad actual: ");
    fgets(origen,256,stdin);
    scanf(" %[^\n]s",origen);
   // printf("%s",origen);

    if(IsValidOrigin(origen)){
      Seleccionar_Destino();
    }else{
        printf("La ciudad ingresada no se encuentra dentro de la matriz, por favor intente nuevamente: ");
        Actualizar_GPS();
    }

  //  GPS = origen;
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
    fgets(destino,256,stdin);
    scanf(" %[^\n]s",destino);
   // printf("%s",destino);

 if(IsValidDestiny(destino)){
    Imprimir_Recorrido();
    }
    else{
        printf("La ciudad ingresada no se encuentra dentro de la matriz, por favor intente nuevamente: ");
        EstadoActual = 1;
        Seleccionar_Destino();
    }

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
    getBestWay(origen, destino);
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
     int dist_faltante= matriz_distancias[indiceOrigen][indiceDestino];
     int dist_a_mostrar = matriz_distancias[indiceOrigen][indiceDestino];
    distanciaPorRecorrer = ((float)matriz_distancias[indiceOrigen][indiceDestino]) * 1.0;
printf("\n distancia por reccorrer %i km, tiempo inicial: 0. Iniciando Viaje...",dist_a_mostrar);
      Sleep(20000);

    for (i = 0; i < 4; i++){
        velocidadMedia += velocidades[i];
        velocidadMedia = velocidadMedia/ (i+1);
        if(velocidadMedia > distanciaPorRecorrer){
             printf("\n Ha recorrido: %i km, 0km por recorrer. ", dist_faltante);
                             Finalizar_Camino();
            break;
        }
        dist_a_mostrar = velocidadMedia;
        dist_faltante  -= velocidadMedia;
        tiempo = distanciaPorRecorrer / velocidadMedia;
        printf("\n Ha recorrido: %i km, ", dist_a_mostrar);
        printf(" Tiempo Restante: %2f hs. Continuando viaje, %i km por recorrer... ", tiempo, dist_faltante);
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
   printf("\n MENU \n 1:  Actualizar GPS. \n 2: Seleccionar Destino. \n 3: Mostrar Recorrido. \n 4: Iniciar Camino.\n 5: Finalizar Camino. \n Seleccione una opcion del menu: ");
   scanf("%i", &opcionMenu);

   if(opcionMenu == 1){
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
