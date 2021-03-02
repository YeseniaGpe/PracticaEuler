//Libreria local
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


extern void ingresarDatos(datos *puntero);
extern float calculoEcuacion(datos *puntero, int tiempoT);
extern pActual *anadirPunto(datos *puntero, pActual *p, int tiempoActual);
extern pActual *generarLista(datos *puntero, pActual *pointer);
extern void crearCSV(pActual *pointer);
