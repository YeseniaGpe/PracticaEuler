#include "tiposEuler.h"

/*
 * Práctica 1: Método de predcción de Euler: Ley de enfriamiento de Newton
 * @copyright 2021
 * @license as you wish
 * @author Team D
  *@Oliva Lopéz Yesenia Guadalupe, Vergara Mendoza Monica Ivette
 * @version 01/03/2021
*/
int main (void) {

  pActual *lista=NULL;
  datos datosNecesarios;
  
  ingresarDatos(&datosNecesarios);
  lista= generarLista(&datosNecesarios,lista);
  crearCSV(lista);
  
  return 0;
}
