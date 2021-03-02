#include <stdio.h>
#include <math.h>
#include <stdlib.h>

struct condicion {
  float temperaturaInicial;
  float temperaturaAmbiente;
  int tiempoFinal;
  float coeficienteK;
};
typedef struct condicion datos;

struct punto {
  float temperaturaT;
  int tiempoT;
  struct punto *siguiente;
};
typedef struct punto pActual;


void ingresarDatos(datos *puntero);
float calculoEcuacion(datos *puntero, int tiempoT);
pActual *anadirPunto(datos *puntero, pActual *p, int tiempoActual);
pActual *generarLista(datos *puntero, pActual *pointer);
void crearCSV(pActual *pointer);

int main (void) {

  pActual *lista=NULL;
  datos datosNecesarios;
  
  ingresarDatos(&datosNecesarios);
  lista= generarLista(&datosNecesarios,lista);
  crearCSV(lista);
  
  return 0;
}


void ingresarDatos(datos *puntero)
{  
  printf("\nTemperatura inicial [°C]: ");
  scanf(" %f", &puntero->temperaturaInicial);
  printf("\nTemperatura ambiente [°C]: ");
  scanf(" %f", &puntero->temperaturaAmbiente);
  printf("\nTiempo requerido [Minutos]: ");
  scanf(" %d", &puntero->tiempoFinal);
  printf("\nCoeficiente K: ");
  scanf(" %f", &puntero->coeficienteK);

  
  return;
}

float calculoEcuacion(datos *puntero, int tiempoT)
{
  double constanteAux, doubleAux;
  float temperaturaActual;
  
  doubleAux =puntero->coeficienteK*tiempoT;
  
  temperaturaActual = puntero->temperaturaAmbiente + ((puntero->temperaturaInicial - puntero->temperaturaAmbiente)*exp(-doubleAux));
  return temperaturaActual;
}


pActual *anadirPunto(datos *puntero, pActual *p, int tiempoActual)
{
  pActual *aux;
  
  aux = (pActual *)malloc(sizeof(pActual));
  if (aux == NULL)
    {
      printf("Error. No hay espacio en la memoria");
      exit(1);
    }
  
  aux->siguiente = p;
  aux->tiempoT = tiempoActual;
  aux->temperaturaT = calculoEcuacion(puntero,tiempoActual);
  p = aux;
  
  return p;
}

pActual *generarLista(datos *puntero, pActual *pointer)
{
  int contadorTiempo=puntero->tiempoFinal;
  
  while(contadorTiempo>=0) {
    pointer = anadirPunto(puntero,pointer,contadorTiempo);
    contadorTiempo--;
  }

  return pointer;
}

void crearCSV(pActual *pointer)
{
  FILE *fp;
 
  fp = fopen("enfriamientoNewton.csv","wt");

  
  while(pointer != NULL)
    {
      fprintf(fp, "%d,",pointer->tiempoT);
      fprintf(fp, "%f\n",pointer->temperaturaT);
      printf("%d,",pointer->tiempoT);
      printf("%f\n",pointer->temperaturaT);
      pointer=pointer->siguiente;
  }
  fclose(fp);
  return;
}
