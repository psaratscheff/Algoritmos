/**********************************************************************************************************\
|
|	Pontificia Universidad Católida de Chile
|	Pedro Saratscheff / Student N°: 13201174
|	Date: September 6th, 2015
|
| --------------------------------------------------------------------------------
|	BIBLIOGRAFÍA UTILIZADA!!
|	http://stackoverflow.com/questions/6844739/c-implement-a-hash-table
|	http://c.learncodethehardway.org/book
|
|	GitHub: https://github.com/pvchaumier/IIC2133/tree/master/list_array 
|		-Autor: Chaumier Pierre-Victor <pvchaumier@uc.cl>
| --------------------------------------------------------------------------------
|
|
|EXPLICACIONES:
|1- Todos los comentarios que comienzen con -DEBUG- indican que el fragmento de código que le sigue tiene la única intención de ser utilizado para buscar errores en el programa, no tienen una funcionalidad para el programa en sí ni son necesarios para su funcionamiento. (Probablemente esten todos comentados)
|2-En general hay exceso de comentarios y líneas de código extra con la intención de poder revisar con facilidad que está sucediendo en caso de un comportamiento extraño. Basta descomentar las líneas correspondientes.
|
\**********************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "hash.h"
#include "t-1.h"

int main(int argc, char *argv[])
{
	//Reviso que haya colocado un modo
	if (argv[1]==NULL)
	{
		printf("ERROR: Debe seleccionar un modo.\n");
		exit(1);
	}

	//Conversión a int del modo
	int selected_mode = *argv[1] - '0';
	
	// INICIADORES
	Array *array;
	array = array_init();
	// INICIADORES
	Array0 *array0;
	array0 = array0_init();
	//Valores de uso general
	char command[3];
	char name[2048];
	int qty;
	char type[2048];

	switch (selected_mode)
	{
		/* ---------------------------- CASO 0 ------------------------- */
		case 0:
		// PROCESAR COMANDOS
		while (1)
		{
			scanf ("%s", command);	
			if (command[0]=='E')
			{ 
				//printf("Programa finalizado\n"); // -DEBUG-
				// Liberar bloques
				array0_destroy(array0);
				return(0);
			}
			else if (command[0]=='A')
			{
				scanf ("%s", name);
				scanf ("%d", &qty);
				scanf ("%s", type);
				//printf("Nombre: %s, Cantidad: %d, Tipo: %s\n",name,qty,type); // -DEBUG-
				Order *a = order_create(type,name, qty);
				Node *aa = node_create(a);
				array0_add(array0, aa);
				//array_print(array); // -DEBUG-
			}
			else if (command[0]=='R')
			{
				scanf ("%s", type);
				//printf("Tipo: %s\n",type); // -DEBUG-
				array0_get(array0, type);
				//array_print(array); // -DEBUG-
			}
			else
			{
				printf("INPUT INCORRECTO!!! %s\n",command);
				return(1);
			}
		}
		break;

		/* ---------------------------- CASO 1 ------------------------- */
		case 1:
		//printf("Modo 1 seleccionado: Tabla de Hash con direccionamiento ABIERTO usando SONDEO LINEAL... \n"); // -DEBUG-
		// PROCESAR COMANDOS
		while (1)
		{
			scanf ("%s", command);	
			if (command[0]=='E')
			{ 
				//printf("Programa finalizado\n"); // -DEBUG-
				// Liberar bloques
				array_destroy(array);
				return(0);
			}
			else if (command[0]=='A')
			{
				scanf ("%s", name);
				scanf ("%d", &qty);
				scanf ("%s", type);
				//printf("Nombre: %s, Cantidad: %d, Tipo: %s\n",name,qty,type); // -DEBUG-
				Order *a = order_create(type,name, qty);
				array_add(array, a);
				//array_print(array); // -DEBUG-
			}
			else if (command[0]=='R')
			{
				scanf ("%s", type);
				//printf("Tipo: %s\n",type); // -DEBUG-
				array_get(array, type);
				//array_print(array); // -DEBUG-
			}
			else
			{
				printf("INPUT INCORRECTO!!! %s\n",command);
				return(1);
			}
		}
		break;

		/* ---------------------------- CASO 2 ------------------------- */
		case 2:
		//printf("Modo 2 seleccionado: Tabla de Hash con direccionamiento ABIERTO usando DOBLE HASHING... \n"); // -DEBUG-
		// PROCESAR COMANDOS
		while (1)
		{
			//array_print(array); // -DEBUG-
			scanf ("%s", command);	
			if (command[0]=='E')
			{ 
				//printf("Programa finalizado\n"); // -DEBUG-
				// Liberar bloques
				array_destroy(array);
				return(0);
			}
			else if (command[0]=='A')
			{
				scanf ("%s", name);
				scanf ("%d", &qty);
				scanf ("%s", type);
				//printf("Nombre: %s, Cantidad: %d, Tipo: %s\n",name,qty,type); // -DEBUG-
				Order *a = order_create(type,name, qty);
				array_add2(array, a); //Utilizo add2 para este metodo
				//array_print(array); // -DEBUG-
			}
			else if (command[0]=='R')
			{
				scanf ("%s", type);
				//printf("Tipo: %s\n",type); // -DEBUG-
				array_get2(array, type); //Utilizo get2 para este metodo
				//array_print(array); // -DEBUG-
			}
			else
			{
				printf("¡¡¡INPUT INCORRECTO!!! ¿Evitaste colocar espacios en los nombres? %s\n",command);
				return(1);
			}
		}
		break;

		default:
		printf("ERROR: Debe seleccionar un modo válido (0, 1 o 2) \n");
		exit(1);
	}

	//Errr, no deberíamos llegar acá!!
	puts("ERROR EN EL LOOP, llegamos a la última linea del archivo, wtf?!");
	return 1;
}

