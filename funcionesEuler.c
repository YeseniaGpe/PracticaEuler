#include "tiposEuler.h"

/*
 * @brief          Esta función pide y lee los datos básicos necesarios para que el programa funcione correctamente
 * @author         Monica Ivette Vergara y Yesenia Oliva.
 *
 * @param *puntero  La estructura vacía donde se agregarán los datos.
 *
 * @return void     Esta función no regresa nigún dato.
 */
extern void ingresarDatos(datos *puntero)
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


/*
 * @brief          Esta función realiza el cáculo de la ley de enfriamiento de Newton evaluando en un tiempo
 *                 específico 
 * @author         Monica Ivette Vergara y Yesenia Oliva.
 *
 * @param *puntero La estructura que contiene los datos necesarios para la función.
 * @param tiempoT  El punto donde se evaluará la función.
 *
 * @return temperaturaActual La temperatura actual en el punto especificado.
 */
extern float calculoEcuacion(datos *puntero, int tiempoT)
{
  double constanteAux, doubleAux;
  float temperaturaActual;
  
  doubleAux =puntero->coeficienteK*tiempoT;
  
  temperaturaActual = puntero->temperaturaAmbiente + ((puntero->temperaturaInicial - puntero->temperaturaAmbiente)*exp(-doubleAux));
  return temperaturaActual;
}


/*
 * @brief              Esta función añade los puntos a una lista simple
 * @author             Monica Ivette Vergara y Yesenia Oliva.
 *
 * @param *puntero     La estructura que contiene los datos necesarios que utilizará la función.
 * @param tiempoActual El punto donde se evaluará la función.
 * @param *p           La lista -al comienzo vacía- donde se van añadiendo los puntos.
 *
 * @return p           La lista actualizada
 */
extern pActual *anadirPunto(datos *puntero, pActual *p, int tiempoActual)
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


/*
 * @brief              Esta función genera una lista simple que contiene la temperatura en cada tiempo
 * @author             Monica Ivette Vergara y Yesenia Oliva.
 *
 * @param *puntero     La estructura que contiene los datos necesarios que utilizará la función.
 * @param *pointer     La lista -al comienzo vacía- donde se añadirá cada punto.
 *
 * @return pointer     La lista con los datos añadidos
 */
extern pActual *generarLista(datos *puntero, pActual *pointer)
{
  int contadorTiempo=puntero->tiempoFinal;
  
  while(contadorTiempo>=0) {
    pointer = anadirPunto(puntero,pointer,contadorTiempo);
    contadorTiempo--;
  }

  return pointer;
}



/*
 * @brief              Esta función crea un archivo con extensión CSV con los puntos necesarios para crear una gráfica
 * @author             Monica Ivette Vergara y Yesenia Oliva.
 *
 * @param *pointer     La lista con los datos que se imprimirán dentro del documento.
 *
 * @return void	Esta función no regresa ningún dato
 */
extern void crearCSV(pActual *pointer)
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
