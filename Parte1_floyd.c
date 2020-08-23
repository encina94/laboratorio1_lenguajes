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

char nombreDelArchivo[] = "Datos distancias.csv";
int matrizFinalDistancias[nodos][nodos];
unsigned int **matrizAdyacencias;
char nodeNames[nodos][nodos][100];
char matrizFinalRutas[nodos][nodos][100];
char caminos[nodos][100];

//******************
 char origen[256];
 char destino[256];
 int indiceOrigen, indiceDestino;
 int velocidades[]={90,120,160,180};
 float velocidadMedia=0;
 float tiempo;
 float distanciaPorRecorrer;
 int EstadoActual, EstadoAnterior;

int main(){
    printf("\nCreando la matriz\n");
    matrizAdyacencias = getMatrix();

    for(int i = 0; i < nodos; i++){
        for(int j = 0; j < nodos; j++){
            printf(" %7d ",matrizAdyacencias[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    floyd(matrizAdyacencias);

    for(int i = 0; i < nodos; i++){
        for(int j = 0; j < nodos; j++){
            printf(" %s ",matrizFinalRutas[i][j]);
        }
        printf("\n");
    }

    SegundaParte();
}

bool ciudadValida(ciudad){
    for(int i = 0; i < nodos; i++){
        if(strcmp(nodeNames[0][i],ciudad) == 0){
            return true;
        }
    }
    return false;
}

void getMejorCamino(char origen[], char destino[]){
    printf("El mejor camino desde %s a %s es: \n",origen,destino);
    printf("%s ",origen);
    imprimirMejorCamino(origen,destino);
}

/**
nodeNames[0]  es un arreglo (listado) de los 16 nombres de los nodos
indiceOrigen  es la posicion del nodo origen en el listado de arriba
indiceDestino es la posicion del nodo destino en el listado de arriba

*/
void imprimirMejorCamino(char origen[], char destino[]){
    int nodoVisitado = 0;
    for(int i = 0; i < nodos; i++){
        if(strcmp(caminos[i],origen) == 0){
            nodoVisitado = 1;
        }
        if(strcmp(nodeNames[0][i],origen) == 0){
            indiceOrigen = i;
        }
        if(strcmp(nodeNames[0][i],destino) == 0){
            indiceDestino = i;
        }
    }
    char *nodoIntermedio = matrizFinalRutas[indiceOrigen][indiceDestino];
    //imprimimos de la matriz final el nombre que esté en la posicion "como llegar a destino" (fila del nodo origen, columna nodo destino)
    printf("-> %s ", nodoIntermedio);
    int llegoADestino = strcmp(nodoIntermedio,destino);
    if(llegoADestino == 0 || nodoVisitado == 1){
        if(llegoADestino != 0){
            printf("-> %s",destino);
        }
        printf("\n");
    }else{
        strcpy(caminos[indiceOrigen],nodoIntermedio);
        imprimirMejorCamino(nodoIntermedio,destino);
    }
}

void floyd (unsigned int **matriz)
{
    //Creamos una nueva matriz para colocar los nuevos valores de distancias o usamos la misma que creamos????
    int k, i, j;
    //Inicializamos la matriz resultante que va a ser la de distancias
    for (i = 0; i < nodos; i++)
        for (j = 0; j < nodos; j++){
            matrizFinalDistancias[i][j] = matriz[i][j];
            strcpy(matrizFinalRutas[i][j],nodeNames[i][j]);
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
                if ((matrizFinalDistancias[i][k] + matrizFinalDistancias[k][j]) < matrizFinalDistancias[i][j]){
                    //Se actualiza la distancia
                    matrizFinalDistancias[i][j] = matrizFinalDistancias[i][k] + matrizFinalDistancias[k][j];
                    if(i != j){
                        strcpy(matrizFinalRutas[i][j],nodeNames[i][k]);
                    }
                }
            }
        }
    }

    printf("\n");

    //Se coloca directamente la distancia de la posicion en la matriz [8][0] que corresponde a Chacabuco como origen y mar del plata como destino
    printf("\nLa distancia minima entre las ciudades de Chacabuco y Mar del Plata es de: %d kms. \n", matrizFinalDistancias[8][0]);

    show_matrizFinalDistancias(matrizFinalDistancias);
}

void show_matrizFinalDistancias(int matrizFinalDistancias[nodos][nodos])
{
    for (int i = 0; i < nodos; i++)
    {
        for (int j = 0; j < nodos; j++)
        {
            printf (" %7d", matrizFinalDistancias[i][j]);
        }
        printf("\n");
    }
}


int getMatrix()
{
    FILE* fh;
    fopen_s(&fh, nombreDelArchivo, "r");

    //check if file exists
    if (fh == NULL){
        printf("file does not exists %s", nombreDelArchivo);
        return 0;
    }

    unsigned int **matrizAdyacencias = malloc(nodos * sizeof(unsigned int *));
	for(int i = 0; i < nodos; i++){
        matrizAdyacencias[i] = malloc(nodos * sizeof(unsigned int));
	}
    //read line by line
    const size_t line_size = 300;
    char* line = malloc(line_size);
    int lineCount = 0;
    while (fgets(line, line_size, fh) != NULL)  {

        size_t length = strlen(line);
        if (line[length - 1] == '\n')
            line[--length] = '\0';
        char * token = strtok(line, ";");
        // loop through the string to extract all other tokens
        //token count to skip column of node name
        int tokenCount = 0;
        while(token != NULL) {
            if(lineCount == 0){
                for(int i = 0; i < nodos; i++){
                    strcpy(nodeNames[i][(tokenCount)],token);
                    strcpy(matrizFinalRutas[i][(tokenCount)],token);
                }
                //strcpy(nodeNames[tokenCount],token);
            }
            if((lineCount > 0) && tokenCount > 0){
                matrizAdyacencias[lineCount-1][tokenCount-1] = atoi(token);
            }
            token = strtok(NULL, ";");
            tokenCount++;
        }
        lineCount++;
    }
    free(line);    // dont forget to free heap memory
    return matrizAdyacencias;
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

    if(ciudadValida(origen)){
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

 if(ciudadValida(destino)){
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
    getMejorCamino(origen, destino);
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
     int dist_faltante= matrizFinalDistancias[indiceOrigen][indiceDestino];
     int dist_a_mostrar = matrizFinalDistancias[indiceOrigen][indiceDestino];
    distanciaPorRecorrer = ((float)matrizFinalDistancias[indiceOrigen][indiceDestino]) * 1.0;
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
