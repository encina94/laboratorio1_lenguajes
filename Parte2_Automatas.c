#define INF 99999999
#define nodos 16
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include "Parte1_floyd.c"

 char *ciudades[16]= {"Mar del Plata", "Balcarce", "Tandil", "Azul", "Tapalque", "Saladillo", "25 de mayo", "Chivilcoy", "Chacabuco", "Dolores", "Castelli", "Gral Belgrano", "San miguel del monte", "Lobos", "Roque Perez", "Ayacucho"};
 char ciudadesDisponibles[] = "Mar del Plata, Balcarce, Tandil, Azul, Tapalque, Saladillo, 25 de mayo, Chivilcoy, Chacabuco, Dolores, Castelli, Gral Belgrano, San miguel del monte, Lobos, Roque Perez, Ayacucho";
 char origen[20];
 char GPS[20];
 char destino[20];
 char des[20];
 int indiceOrigen, indiceDestino;


void Actualizar_GPS(){
    printf("\nLas ciudades disponibles son: %s\n",ciudadesDisponibles );
    printf("\nIngrese la n�meracion de la ciudad actual: ");
	scanf("%s", origen);
    sprintf( GPS, "%s", origen );
   // printf("\n %s", GPS);
  //  GPS = origen;
    Seleccionar_Destino();
}


void Imprimir_Recorrido(){
 int i;
 printf("\n El recorrido sera el siguiente:");

 for (i=indiceOrigen; i <= indiceDestino; i++)
    {
        printf("\n %s", ciudades[i]);
    }
}

void Obtener_Indices(){
    int j;
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
    Imprimir_Recorrido();

}


void Seleccionar_Destino(){
    printf("\nIngrese la n�meracion de la ciudad de destino: ");
	scanf("%s", des);
	sprintf( destino, "%s", des );
    //printf("\n %s", destino);


    //destino = destino;
    Obtener_Indices();
}




void main_SegundaParte()
{
    Actualizar_GPS();
}








