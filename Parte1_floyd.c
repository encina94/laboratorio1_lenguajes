#define INF 99999999
#define nodos 16
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <time.h>

 int matriz_distancias[nodos][nodos];
int main(){

printf("\nCreando la matriz");

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
    floyd(matriz);
    SegundaParte();

}

void floyd (int matriz[nodos][nodos])
{
    //Creamos una nueva matriz para colocar los nuevos valores de distancias o usamos la misma que creamos????
   int k, i, j;

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
printf("\n distancia por reccorrer %2f tiempo inicial: 0",distanciaPorRecorrer);
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

















