/*
 * main.c
 *
 *  Created on: 17 oct. 2019
 *      Author: josan
 */


#include <stdio.h>
#include <stdlib.h>

#include "types/types.h"
#include "types/list.h"
#include "types/iterables.h"
#include "types/hash_table.h"


list leeFichero(char * file);

list fIter(list l);
void ejercicio1a(char * fichero);

hash_table gIter(list l);
void ejercicio1b(char * fichero);

int main(){
	ejercicio1a("ficheros/PI1Ej1DatosEntrada..txt");

//	ejercicio1b("ficheros/PI1Ej2DatosEntrada.txt");

	return EXIT_SUCCESS;
}

list leeFichero(char * file) {
	iterator f = file_iterable_pchar(file);
	list lista = list_empty(string_type);
	while (iterable_has_next(&f)) {
		char * linea = iterable_next(&f);
		string slinea = string_of_pchar(linea);
		list_add(&lista, &slinea);
	}
	return lista;
}

//Ejercicio 1-A
list fIter(list l){

	char buff[256];
	list acum = list_empty(int_type);
	int i = 0;
	while(i < l.size){

		string s = *(string *) list_get(&l,i);	//Obtiene el string de la posicion i de la lista &l
		char * c = string_tostring(&s,buff);	//String a char*
		int j = int_parse_s(c);					//char* a int

		if((j % 2) == 0 ){
			j = j*j;
			list_add(&acum, &j);
		}
		i++;
	}
	return acum;

}


void ejercicio1a(char * fichero){
	list lineas = leeFichero(fichero);
	char buff[256];
	char buff2[256];
	char * tokens[256];

	int i = 0;
	while(i < lineas.size){
		char * elemento = list_get_string(&lineas, i, buff);
		printf("Entrada: [%s]\n", elemento);
		int nSplit = split_text(elemento,",", tokens);

		list aux = list_empty(string_type);
		int j = 0;
		while(j < nSplit){
			list_add(&aux, &tokens[j-1]);
			j++;
		}
		list auxSalida = fIter(aux);
		char * salida = list_tostring(&auxSalida, buff2);
		printf("Salida: [%s]\n========================================\n", salida);
		i++;
	}
}



hash_table gIter(list l){
	hash_table acum = hash_table_empty(int_type, list_type);
	int i = 0;
	char buff[256];
	while(i < l.size){

		string s = *(string *) list_get(&l,i);	//Obtiene el string de la posicion i de la lista &l
		char * c = string_tostring(&s,buff);	//String a char*
		int j = strlen(c);						//Cuenta las letras del char*

		if(hash_table_contains(&acum, &j)){
			list aux = *(list*) hash_table_get(&acum,&j);
			list_add(&aux, &s);
			hash_table_put(&acum,&j, &aux);
		} else {
			list aux = list_empty(string_type);
			list_add(&aux, &s);
			hash_table_put(&acum, &j, &aux);
		}
		i++;
	}

	return acum;
}



void ejercicio1b(char * fichero){
	list lista = leeFichero(fichero);
	char buff[256];
	hash_table t = gIter(lista);

	int i = 1;
	while(i <= hash_table_size(&t)){
		list aux = *(list*) hash_table_get(&t,&i);
		char * list = list_tostring(&aux, buff);
		printf("%d: %s\n", i,list);
		i++;
	}


}



