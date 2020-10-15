#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/*
* Nombre: Alexis Sánchez
* Clave: 181074
* Programa: Registro de libros usando apuntadores
* Fecha: 22 de agosto, 2020
* */


typedef struct lib {
	int codigo;
	char nombresAutor[30];
	char apellidosAutor[30];
	char titulo[30];
	int ayoCompra;
	int cantUusarios;
	struct lib* prox;
};

void insertar_libro(struct lib** cabeza);
struct lib* crear_libro();
void mostrarLibros(struct lib* cabeza);
int numLibros(struct lib* cabeza);
bool getUnLibro(struct lib* cabeza, int codigo);
bool borraLibro(struct lib** cabeza, int codigo);

int main() {
	struct lib* cabeza = NULL;
	int opcion, resp;
	int numLib, codigo=0;
	bool elim;
	/*
	* Se crea un menu sencillo haciendo uso de switch
	* para presentar las opciones de que acciones se puede
	* realizar. 
	* */

	do {
		printf("\nREGISTRO DE LIBROS \n");
		printf("\nElija una opcion: ");
		printf("\n1.....Insertar Libro");
		printf("\n2.....Borrar Libro");
		printf("\n3.....Numero de Libros Registrados");
		printf("\n4.....Mostrar un libro");
		printf("\n5.....Mostrar todos los libros");
		scanf_s("%i", &opcion);

		switch (opcion)
		{
			case 1: insertar_libro(&cabeza);
				break;
			case 2: 
				printf("\nDame el codigo del libro para eliminarlo");
				scanf_s("%i", &codigo);
				elim=borraLibro(&cabeza,codigo);
				if(elim==false)
					printf("\nLibro para eliminar no registrado");
				break;
			case 3: 
				numLib=numLibros(cabeza);
				printf("\nLibros registrados :" + numLib);
				break;
			case 4: 
				printf("\nDame el codigo del libro para buscarlo");
				scanf_s("%i", &codigo);
				elim=getUnLibro(cabeza, codigo);
				if(elim==false)
					printf("\nLibro no registrado");
				break;
			case 5: mostrarLibros(cabeza);
				break;
			default:
				break;
		}
		printf("¿Deseas realizar otra accion? 1: si / 0: no");
		scanf_s("%i", &resp);
	} while (resp == 1);
	return 0;
}

void clean() {
	while (getchar() != '\n');
}

void insertar_libro(struct lib** cabeza) {
	struct lib* nuevoLibro = crear_libro();
	struct lib* actual;
	/*Para hacer la inseracion de un libro, primero se manda 
	* llmar al memtodo crear_libro que pide los datos
	* desde el teclado. Posteriormente, si el libro es el primero
	* de la lista se inseta inmediatamente. En caso contrario y 
	* si ya hay mas libros, entonce se va recorriendo la lista
	* hasta que encuentre el lugar para insertarse de acuerdo al orden 
	* de los codigos de los libros. 
	* */

	if (*cabeza == NULL || (*cabeza)->codigo >= nuevoLibro->codigo) {
		nuevoLibro->prox = *cabeza;
		*cabeza = nuevoLibro;
	}
	else {
		actual = *cabeza;
		while (actual->prox != NULL && actual->prox->codigo < nuevoLibro->codigo) {
			actual = actual->prox;
		}
		nuevoLibro->prox = actual->prox;
		actual->prox = nuevoLibro;
	}
}

struct lib* crear_libro() {
	int i;
	char aux;

	/*En este metodo se solicita la informacion de manera similar a 
	* como se ha realizado en clase. Las cadenas de texto se les 
	* considera como caracteres unidos que se leen mediante un for
	* */

	//como primer paso para crear el libro, se hace el espacio en memoria
	struct lib* libro= (struct lib*)malloc(sizeof(struct lib));
	printf("Libro (%d): Indicar el codigo del libro ");
	scanf_s("%i", &libro->codigo);
	printf("Libro (%d): Indicar los nombres ");
	clean();
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		libro->nombresAutor[i] = aux;
		aux = getchar();
	}
	printf("Libro (%d): Indicar los apellidos ");
	clean();
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		libro->apellidosAutor[i] = aux;
		aux = getchar();
	}
	printf("Libro (%d): Indicar el titulo ");
	clean();
	aux = getchar();
	for (i = 0; aux != '\n'; i++) {
		libro->titulo[i] = aux;
		aux = getchar();
	}
	printf("Libro (%d): Indicar el anyo de compra ");
	scanf_s("%i", &libro->ayoCompra);
	printf("Libro (%d): Indicar la cantidad de usuarios");
	scanf_s("%i", &libro->cantUusarios);
	//se determina que el proximo "nodo" esta en nulo por el momemento
	libro->prox = NULL;
	return libro; //se regresa el libro
}

void mostrarLibros(struct lib* cabeza) {
	struct lib* temp = cabeza;
	while (temp != NULL) {
		printf("\nCodigo %i\nNombre autor %s\nApellido %s\nTitulo %s \nAño compra %i \nNumero de usuarios %i\n\n", 
			temp->codigo, temp->nombresAutor, temp->apellidosAutor, temp->titulo, temp->ayoCompra, temp->cantUusarios);
		temp = temp->prox;
	}
}

int numLibros(struct lib* cabeza) {
	struct lib* actual = cabeza; 
	int num = 0;

	/*Metodo que recibe la cabeza de la lista y mientras hace el recorrido
	* sin encontrar un nulo, hace la cuenta de los elementos encontrados 
	* y al final regresa dicha cuenta
	* */
	while (actual != NULL)
	{
		num++;
		actual = actual->prox;
	}
	return num;
}

bool getUnLibro(struct lib* cabeza, int codigo)
{
	/*
	* Este metodo recibe la cabeza de la lista y el codigo del libro a buscar 
	* para desplegar la informacion. Primero el nodo actual se asigna a la cabeza
	* de la lista, mientras no se encuentre un nulo, seguira recorriendo hasta 
	* encontrar el libro y mostrar su informacion. En caso contrario, termina el ciclo
	* llegando al final de la lista e indicando que el libro con el codigo indicado no existe. 
	* */

	struct lib* actual = cabeza;  
	while (actual != NULL)
	{
		if (actual->codigo == codigo) {
			printf("\nCodigo %i\nNombre autor %s\nApellido %s\nTitulo %s \nAño compra %i \nNumero de usuarios %i\n\n",
				actual->codigo, actual->nombresAutor, actual->apellidosAutor, actual->titulo, actual->ayoCompra, actual->cantUusarios);
			return true;
		}
		actual = cabeza->prox;
	}
	return false;
}

bool borraLibro(struct lib** cabeza, int codigo)
{
	//Se recibe la cabeza de la lista y se asigna a un nodo
	//actual, el cual será quien funcione de auxiliar en la
	//busqueda del libro con el codigo indicado
	struct lib* actual = *cabeza;
	struct lib* prev=NULL;
	//En caso de que la cabeza sea el libro buscado,
	//la cabeza se reasigna al proximo al actual
	if (actual != NULL && actual->codigo == codigo)
	{
		*cabeza = actual->prox;   
		return true;
	}
	//en caso contrario, se va reocrriendo la lista hasta 
	//encontrar el libro. En ese momento, se termina el ciclo.
	//El nodo previo a proximo pasa a ser el actual de proximo
	//En este recorrido, el previo pasa a ser el actual y el actual 
	//pasa a ser el proximo. 
	while (actual != NULL && actual->codigo != codigo)
	{
		prev = actual;
		actual = actual->prox;
	}
	if (actual == NULL) 
		return false;

	prev->prox = actual->prox;
	return true;
}



