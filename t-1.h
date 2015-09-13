/******************************************************************************\
|
|   Revisar información en documento t.c adjunto a este.
|
\******************************************************************************/

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "hash.h"

// When the array will be initialized, it will be of size INITIAL_SIZE
// Notice that it is empty for now
// You can modify this value
#define INITIAL_SIZE 10

typedef struct Order
{
	char *type;
	char *name;
	int qty;
}Order;

//Crear una orden
struct Order *order_create(char *type, char *name, int qty)
{
	struct Order *who = malloc(sizeof(struct Order));
	assert(who != NULL);

	who->type = strdup(type);
	who->name = strdup(name);
	who->qty = qty;

	return who;
}

typedef struct Node {
  Order *x;
  struct Node *a; //after
  struct Node *b; //before
}Node;

//Crear un nodo
struct Node *node_create(Order *x)
{
	struct Node *what = malloc(sizeof(struct Node));

	what->x = x;
	what->a = NULL;
	what->b = NULL;

	return what;
}

void print_order(Order *who)
{
	printf("Orden de (%d) pizzas tipo (%s) para (%s)\n", who->qty, who->type, who->name);
}

// typedef allows you to use Array instead of struct Array when defyning new 
// variables
typedef struct Array
{
    // Number of element in the array
    int size;
    // How many elements the current array can contain
    int capacity;
    // What is in the array, in this case we have an array of int
    // this is where you should modify the code if you want to 
    // change the type of the content
    Order **content;
}Array;

typedef struct Array0
{
    // Number of element in the array
    int size;
    // How many elements the current array can contain
    int capacity;
    // What is in the array, in this case we have an array of int
    // this is where you should modify the code if you want to 
    // change the type of the content
    Node **content;
}Array0;

/* ---------------- Memory manipulation for data structure ---------------- */

void array_alloc_test(Array *array){
    // Test if the array is allocated in memory, if not returns with error
    if (array == NULL)
    {
        exit(EXIT_FAILURE);
    }
}
void array0_alloc_test(Array0 *array){
    // Test if the array is allocated in memory, if not returns with error
    if (array == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

void order_alloc_test(Order *order){
    // Test if the array is allocated in memory, if not returns with error
    if (order == NULL)
    {
        exit(EXIT_FAILURE);
    }
}
void node_alloc_test(Node *node){
    // Test if the array is allocated in memory, if not returns with error
    if (node == NULL)
    {
        exit(EXIT_FAILURE);
    }
}

Array *array_init()
{
	// Define a pointer to an Array structure and reserves the necessary size
	Array *array = malloc(sizeof(*array));

	// Test if the pointer has been allocated
	array_alloc_test(array);

	// We define the basic elements
	array->size = 0;
	array->capacity = INITIAL_SIZE;
	array->content = calloc(array->capacity, sizeof(Order));

	// Every time you use a pointer, it needs to be allocated. We test this now
	// for the content of the array
	if (array->content == NULL)
	{
		printf("ERROR. The content of the array could not be initialize.\n");
		exit(EXIT_FAILURE);
	}

	int i=0;
	while (i<array->capacity)
	{
		array->content[i] = malloc(sizeof(Order));
		i++;
	}

	return array;
}

Array0 *array0_init()
{
	// Define a pointer to an Array structure and reserves the necessary size
	Array0 *array0 = malloc(sizeof(*array0));

	// Test if the pointer has been allocated
	array0_alloc_test(array0);

	// We define the basic elements
	array0->size = 0;
	array0->capacity = INITIAL_SIZE;
	array0->content = calloc(array0->capacity, sizeof(Node));

	// Every time you use a pointer, it needs to be allocated. We test this now
	// for the content of the array
	if (array0->content == NULL)
	{
		printf("ERROR. The content of the array could not be initialize.\n");
		exit(EXIT_FAILURE);
	}

	int i=0;
	while (i<array0->capacity)
	{
		array0->content[i] = malloc(sizeof(Node));
		array0->content[i] = NULL;
		i++;
	}

	return array0;
}

void order_destroy(struct Order *who)
{
	assert(who != NULL);

	free(who->type);
	free(who->name);
	free(who);
}

void node_destroy(struct Node *what)
{
	assert(what != NULL);

	free(what->x);
	free(what->a);
	free(what->b);
	free(what);
}

void array_destroy(Array *array)
{
	/**
	This function will now deallocate all the pointers we have used. This is 
	necessary to free the memory.

	/!\ Be careful, if the content element is an array of string (array of 
	array of char), you will need to deallocate all the different string also
	if you used a pointer to define them !
	**/
	array_alloc_test(array);

	//Libero los bloques
	int i=0;
	while (i<array->capacity)
	{
		order_destroy(array->content[i]);
		i++;
	}
	free(array->content);
	free(array);
}

void array0_destroy(Array0 *array0)
{
	/**
	This function will now deallocate all the pointers we have used. This is 
	necessary to free the memory.

	/!\ Be careful, if the content element is an array of string (array of 
	array of char), you will need to deallocate all the different string also
	if you used a pointer to define them !
	**/
	array0_alloc_test(array0);

	//Libero los bloques
	int i=0;
	while (i<array0->capacity)
	{
		if (!!array0->content[i])
		{
			node_destroy(array0->content[i]);
		}
		i++;
	}
	free(array0->content);
	free(array0);
}

//Una versión sin chequeo de si está lleno o no
void array_force_add(Array *array, Order *iValueToAdd){
	array_alloc_test(array);
	order_alloc_test(iValueToAdd);

	int position = hash(iValueToAdd->type)%array->capacity;
	if (array->content[position]->type == NULL)
	{
		array->size+=1;
		array->content[position] = iValueToAdd;
	}
	else{
		while(1){
			position++;
			if (position>=array->capacity){ position=0;}
			if (array->content[position]->type == NULL)
			{
				array->size+=1;
				array->content[position] = iValueToAdd;
				break;
			}
			else
			{
				if (position==hash(iValueToAdd->type)%array->capacity){ 
					printf("ERROR. The content could not be allocated\n");
					exit(EXIT_FAILURE);
				}
			}
			// Be careful here again, with strings, you would need to use the string.h
			// library and the strcpy function as one cannot generally assign an 
			// array with an equal sign.
		}
	}
}

//Una versión sin chequeo de si está lleno o no
void array_force_add2(Array *array, Order *iValueToAdd){
	array_alloc_test(array);
	order_alloc_test(iValueToAdd);

	long hashed_value = hash(iValueToAdd->type);
	int position = hash(iValueToAdd->type)%array->capacity;
	/*printf("AAAA: %lu\n", hashed_value); // -DEBUG-
	printf("AAAA: %d\n", array->capacity); // -DEBUG-
	printf("AAAA: %d\n", hash(iValueToAdd->type)%array->capacity); // -DEBUG-
	printf("AAAA: %d\n", position); // -DEBUG-/**/
	//Se prefirió no poblar espacios borrados, menor eficiencia al tener que desplazar los valores para mantener orden de preferencia. 
	//Se limpia al expandir el array
	if (array->content[position]->type == NULL /*|| strcmp(array->content[position]->type,"-")==0*/)	
	{
		array->size+=1;
		array->content[position] = iValueToAdd;
	}
	else
	{
		while(1){
			hashed_value = universal(hashed_value); //Segundo método de hashing entregado
			position = hashed_value%array->capacity;
			if (position>=array->capacity){ position=0;}
			if (array->content[position]->type == NULL /*|| strcmp(array->content[position]->type,"-")==0*/)
			{
				array->size+=1;
				array->content[position] = iValueToAdd;
				break;
			}
			else
			{
				if (position==hash(iValueToAdd->type)%array->capacity){ 
					printf("ERROR. The content could not be allocated\n");
					exit(EXIT_FAILURE);
				}
			}
			// Be careful here again, with strings, you would need to use the string.h
			// library and the strcpy function as one cannot generally assign an 
			// array with an equal sign.
		}
	}
}

void array0_add(Array0 *array0, Node *iValueToAdd){
	array0_alloc_test(array0);
	node_alloc_test(iValueToAdd);

	int position = hash(iValueToAdd->x->type)%array0->capacity;
	if (array0->content[position] == NULL) //Si está vacío...
	{
		array0->size+=1;
		array0->content[position] = iValueToAdd;
	}
	else	//Si ya hay un nodo, coloco el nuevo al final
	{
		Node *pointer = array0->content[position];
		while (!!pointer->a) //Voy al último nodo
		{
			pointer=pointer->a;
		}
		
		pointer->a = iValueToAdd;
		iValueToAdd->b=pointer;
	}
}

void array_double_size_if_full(Array *array){
    /**
    This function uses the realloc function to take the content array and double
    its size.
    Check for dynamic memory allocation to found out more about this.
    Functions to check are :
      - malloc
      - calloc
      - realloc
    **/

    // Test if the array exists in the first place (pointer is allocated)
    array_alloc_test(array);

    Order **contentTmp;
	
    if (array->size*2 >= array->capacity) //Agrando el array si la mitad ya está llena
    {
	int old_capacity = array->capacity;
	Order **old_content = array->content;
        // Modification of the capacity
        array->capacity *= 2;
	array->size=0;
        // Reallocation of the content in a new array two times bigger
        contentTmp = calloc(array->capacity, sizeof(Order));
        // Test if reallocation went well
        if (contentTmp == NULL)
        {
		array_destroy(array);
		printf("ERROR. The content could not be reallocated\n");
		exit(EXIT_FAILURE);
        }
        else
        {
		array->content = contentTmp;
		//"Reservo" el nuevo content
		int i=0;
		while (i<array->capacity)
		{
			array->content[i] = malloc(sizeof(Order));
			i++;
		}
		//Relleno el nuevo content
		int j=0;
		while (j<old_capacity)
		{
			if (old_content[j]->type != NULL && strcmp(old_content[j]->type,"-") != 0)
			{
				array_force_add(array, old_content[j]);
			}
			j++;
		}
        }
    }
}

void array_double_size_if_full2(Array *array){
    /**
    This function uses the realloc function to take the content array and double
    its size.
    Check for dynamic memory allocation to found out more about this.
    Functions to check are :
      - malloc
      - calloc
      - realloc
    **/

    // Test if the array exists in the first place (pointer is allocated)
    array_alloc_test(array);

    Order **contentTmp;
	
    if (array->size*2 >= array->capacity) //Agrando el array si la mitad ya está llena
    {
	int old_capacity = array->capacity;
	Order **old_content = array->content;
        // Modification of the capacity
        array->capacity *= 2;
	array->size=0;
        // Reallocation of the content in a new array two times bigger
        contentTmp = calloc(array->capacity, sizeof(Order));
        // Test if reallocation went well
        if (contentTmp == NULL)
        {
		array_destroy(array);
		printf("ERROR. The content could not be reallocated\n");
		exit(EXIT_FAILURE);
        }
        else
        {
		array->content = contentTmp;
		//"Reservo" el nuevo content
		int i=0;
		while (i<array->capacity)
		{
			array->content[i] = malloc(sizeof(Order));
			i++;
		}
		//Relleno el nuevo content
		int j=0;
		while (j<old_capacity)
		{
			if (old_content[j]->type != NULL && strcmp(old_content[j]->type,"-") != 0)
			{
				array_force_add2(array, old_content[j]);
			}
			j++;
		}
        }
    }
}

void array0_double_size_if_full(Array0 *array0){
    /**
    This function uses the realloc function to take the content array and double
    its size.
    Check for dynamic memory allocation to found out more about this.
    Functions to check are :
      - malloc
      - calloc
      - realloc
    **/

    // Test if the array exists in the first place (pointer is allocated)
    array0_alloc_test(array0);

    Node **contentTmp;
	
    if (array0->size*2 >= array0->capacity) //Agrando el array si la mitad ya está llena/usada
    {
	int old_capacity = array0->capacity;
	Node **old_content = array0->content;
        // Modification of the capacity
        array0->capacity *= 2;
	array0->size=0;
        // Reallocation of the content in a new array two times bigger
        contentTmp = calloc(array0->capacity, sizeof(Node));
        // Test if reallocation went well
        if (contentTmp == NULL)
        {
		array0_destroy(array0);
		printf("ERROR. The content could not be reallocated\n");
		exit(EXIT_FAILURE);
        }
        else
        {
		array0->content = contentTmp;
		//"Reservo" el nuevo content
		int i=0;
		while (i<array0->capacity)
		{
			array0->content[i] = malloc(sizeof(Node));
			i++;
		}
		//Relleno el nuevo content
		int j=0;
		while (j<old_capacity)
		{
			if (old_content[j] != NULL)
			{
				array0_add(array0, old_content[j]);
			}
			j++;
		}
        }
    }
}

/* ---------------- Manipulation of the data structure ---------------- */

void array_add(Array *array, Order *iValueToAdd){
	array_alloc_test(array);
	order_alloc_test(iValueToAdd);
	// Check if it is possible to add a new value, if the content array is full,
	// we need to double its size
	array_double_size_if_full(array);

	long hashed_value = hash(iValueToAdd->type);
	int position = hash(iValueToAdd->type)%array->capacity;
	//Se prefirió no poblar espacios borrados, menor eficiencia al tener que desplazar los valores para mantener orden de preferencia. 
	//Se limpia al expandir el array
	if (array->content[position]->type == NULL /*|| strcmp(array->content[position]->type,"-")==0*/)	
		{
			array->size+=1;
			array->content[position] = iValueToAdd;
		}
	else{
		while(1){
			position++;
			if (position>=array->capacity){ position=0;}
			if (array->content[position]->type == NULL /*|| strcmp(array->content[position]->type,"-")==0*/)
			{
				array->size+=1;
				array->content[position] = iValueToAdd;
				break;
			}
			else
			{
				if (position==hash(iValueToAdd->type)%array->capacity){ 
					printf("ERROR. The content could not be allocated\n");
					exit(EXIT_FAILURE);
				}
			}
			// Be careful here again, with strings, you would need to use the string.h
			// library and the strcpy function as one cannot generally assign an 
			// array with an equal sign.
		}
	}
}

//ALTERNATIVA CON SEGUNDO HASHING
void array_add2(Array *array, Order *iValueToAdd){
	array_alloc_test(array);
	order_alloc_test(iValueToAdd);
	// Check if it is possible to add a new value, if the content array is full,
	// we need to double its size
	array_double_size_if_full2(array);

	long hashed_value = hash(iValueToAdd->type);
	int position = hash(iValueToAdd->type)%array->capacity;
	/*printf("BBBB: %lu\n", hashed_value); // -DEBUG-
	printf("BBBB: %d\n", array->capacity); // -DEBUG-
	printf("BBBB: %d\n", hash(iValueToAdd->type)%array->capacity); // -DEBUG-
	printf("BBBB: %d\n", position); // -DEBUG-/**/
	//Se prefirió no poblar espacios borrados, menor eficiencia al tener que desplazar los valores para mantener orden de preferencia. 
	//Se limpia al expandir el array
	if (array->content[position]->type == NULL /*|| strcmp(array->content[position]->type,"-")==0*/)	
	{
		array->size+=1;
		array->content[position] = iValueToAdd;
	}
	else
	{
		while(1){
			hashed_value = universal(hashed_value); //Segundo método de hashing entregado
			position = hashed_value%array->capacity;
			if (position>=array->capacity){ position=0;}
			if (array->content[position]->type == NULL /*|| strcmp(array->content[position]->type,"-")==0*/)
			{
				array->size+=1;
				array->content[position] = iValueToAdd;
				break;
			}
			else
			{
				if (position==hash(iValueToAdd->type)%array->capacity){ 
					printf("ERROR. The content could not be allocated\n");
					exit(EXIT_FAILURE);
				}
			}
			// Be careful here again, with strings, you would need to use the string.h
			// library and the strcpy function as one cannot generally assign an 
			// array with an equal sign.
		}
	}
}

void array_del(Array *array, Order *iValueToDel)
{
    	array_alloc_test(array);
	order_alloc_test(iValueToDel);

	int position = hash(iValueToDel->type)%array->capacity;
	int i=0;
	while(i<array->capacity)
	{
		//Primero reviso que no sea nulo, luego que corresponda
		if (!!array->content[position]->type && hash(array->content[position]->type) == hash(iValueToDel->type))
		{
			if (strcmp(array->content[position]->type,iValueToDel->type)==0)
			{
				strcpy(array->content[position]->type,"-");
				//array->size--; No disminuimos el tamaño para limpiar al aumentar el tamaño de array en vez de desplazar
				break;
			}
		}
		else if (!array->content[position])
		{
			i = array->capacity;
			break;
		}
		else
		{
			position++;
			if (position>=array->capacity){ position=0;}
			i++;
		}
	}
	if (i == array->capacity)
	{
		printf("ERROR 1. Element not found in the array.\n");
	}
}

void array_del2(Array *array, Order *iValueToDel)
{
    	array_alloc_test(array);
	order_alloc_test(iValueToDel);

	long hashed_value = hash(iValueToDel->type);
	int position = hash(iValueToDel->type)%array->capacity;
	/*printf("CCCC: %lu\n", hashed_value); // -DEBUG-
	printf("CCCC: %d\n", array->capacity); // -DEBUG-
	printf("CCCC: %d\n", hash(iValueToDel->type)%array->capacity); // -DEBUG-
	printf("CCCC: %d\n", position); // -DEBUG-/**/
	int i=0;
	while(i<array->capacity)
	{
		//Primero reviso que no sea nulo, luego que corresponda
		if (!!array->content[position]->type && hash(array->content[position]->type) == hash(iValueToDel->type))
		{
			if (strcmp(array->content[position]->type,iValueToDel->type)==0)
			{
				strcpy(array->content[position]->type,"-");
				//array->size--; No disminuimos el tamaño para limpiar al aumentar el tamaño de array en vez de desplazar
				break;
			}
		}
		else if (!array->content[position])
		{
			i = array->capacity;
			break;
		}
		else
		{
			hashed_value = universal(hashed_value); //Segundo método de hashing entregado
			position = hashed_value%array->capacity;
			i++;
		}
	}
	if (i == array->capacity)
	{
		printf("ERROR 2. Element not found in the array.\n");
	}
}

void array0_del(Array0 *array0, Node *iValueToDel)
{
    	array0_alloc_test(array0);
	node_alloc_test(iValueToDel);

	int position = hash(iValueToDel->x->type)%array0->capacity;
	Node *test = array0->content[position];
	while(1)
	{
		if (test == NULL)
		{
			printf("ERROR 3. Element not found in the array.\n");
			break;
		}
		else
		{
			if (strcmp(test->x->type,iValueToDel->x->type)==0)
			{
				test->b->a = test->a;
				break;
			}
		}
		test = test->a;
	}
}

void *array_get(Array *array, char *item)
{
	array_alloc_test(array);
	assert(item != NULL);

	int position = hash(item)%array->capacity;
	int i=0;
	while(i<array->capacity)
	{
		//Primero una comparación con hash, luego una completa)
		if ( hash(array->content[position]->type) == hash(item) && strcmp(array->content[position]->type, item)==0) 
		{
			//Encontré alguien que quiere la pizza! :D
			//Veamos si quiere más de una o es la última
			if (array->content[position]->qty>1)
			{
				//Resto uno nada más y le pido amablemente al cliente que espere las siguientes
				array->content[position]->qty--;
				printf("%s\n", array->content[position]->name); //Imprimo nombre del cliente
			}
			else
			{
				printf("%s\n", array->content[position]->name); //Imprimo nombre del cliente
				array_del(array, array->content[position]);
			}
			break;
		}
		else if (!array->content[position]->type)
		{
			i = array->capacity;
			break;
		}
		else
		{
			position++;
			if (position>=array->capacity){ position=0;}
			i++;
		}
	}
	if (i == array->capacity)
	{
		printf("ERROR 4. Element not found in the array.\n");
	}
}

void *array_get2(Array *array, char *item)
{
	array_alloc_test(array);
	assert(item != NULL);

	long hashed_value = hash(item);
	int position = hash(item)%array->capacity;
	/*printf("DDDD: %lu\n", hashed_value); // -DEBUG-
	printf("DDDD: %d\n", array->capacity); // -DEBUG-
	printf("DDDD: %d\n", hash(item)%array->capacity); // -DEBUG-
	printf("DDDD: %d\n", position); // -DEBUG-/**/
	int i=0;
	while(i<array->capacity)
	{
		//Primero una comparación con hash, luego una completa)
		if ( hash(array->content[position]->type) == hash(item) && strcmp(array->content[position]->type, item)==0)
		{
			//Encontré alguien que quiere la pizza! :D
			//Veamos si quiere más de una o es la última
			if (array->content[position]->qty>1)
			{
				//Resto uno nada más y le pido amablemente al cliente que espere las siguientes
				array->content[position]->qty--;
				printf("%s\n", array->content[position]->name); //Imprimo nombre del cliente
			}
			else
			{
				printf("%s\n", array->content[position]->name); //Imprimo nombre del cliente
				array_del2(array, array->content[position]); //Elimino con del2
			}
			break;
		}
		else if (!array->content[position]->type)
		{
			i = array->capacity;
			break;
		}
		else
		{
			hashed_value = universal(hashed_value); //Segundo método de hashing entregado
			position = hashed_value%array->capacity;
			i++;
		}
	}
	if (i == array->capacity)
	{
		printf("ERROR 5. Element not found in the array.\n");
	}
}

void *array0_get(Array0 *array0, char *item)
{
	array0_alloc_test(array0);
	assert(item != NULL);

	int position = hash(item)%array0->capacity;
	Node *test = array0->content[position];
	//Caso simple, no hay nodos en la poscición
	if (test == NULL)
	{
		printf("ERROR 6. Element not found in the array.\n");
		return;
	}
	//Caso en que sí hay:
	//Solo hay uno:
	if (test->a == NULL)
	{
		if (strcmp(test->x->type,item)==0)
		{
			printf("%s\n", test->x->name); //Imprimo nombre del cliente
			if (array0->content[position]->x->qty > 1)
			{
				array0->content[position]->x->qty--;
			}
			else
			{
				array0->content[position] = NULL;
			}
			return;
		}
		else
		{
			printf("ERROR 7. Element not found in the array.\n");
			return;
		}
	}
	//Hay más de uno
	//Reviso el primero
	if (strcmp(test->x->type,item)==0)
		{
			printf("%s\n", test->x->name); //Imprimo nombre del cliente
			if (array0->content[position]->x->qty > 1)
			{
				array0->content[position]->x->qty--;
			}
			else
			{
				//Quito el nodo de la lista (Debería liberar el espacio)
				array0->content[position] = test->a;
			}
			return;
		}
	else
	{
		test=test->a;
	}
	//Reviso el resto
	while(1)
	{
		if (strcmp(test->x->type,item)==0)
		{
			printf("%s\n", test->x->name); //Imprimo nombre del cliente
			if (test->x->qty > 1)
			{
				test->x->qty--;
			}
			else
			{
				test->b->a=test->a;
				if (!!test->a) //Si no es nulo
				{
					test->a->b=test->b;
				}
			}
			return;
		}
		else
		{
			test = test->a;
		}
		if (test == NULL)
		{
			printf("ERROR 8. Element not found in the array.\n");
			return;
		}
	}
}

// -DEBUG- Imprimir el array completo en consola
void array_print(Array *array){
    array_alloc_test(array);

    printf("[\n");
    int i;
    for (i = 0; i < array->capacity; i++)
    {
        printf("Tipo: (%s) ||| Nombre:(%s)", array->content[i]->type, array->content[i]->name);
        if (i != array->capacity - 1)
        {
            printf("\n");
        }
    }
    printf("\n]\n");
}
