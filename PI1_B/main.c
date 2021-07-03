/*
 * main.c
 *
 *  Created on: 9 nov. 2019
 *      Author: josan
 */

#include <stdio.h>
#include <stdlib.h>

#include "types/types.h"
#include "types/list.h"
#include "types/iterables.h"
#include "types/hash_table.h"


//Ejercicio 3
bool ejercicio3Iterativo(string p);
bool ejercicio3RecursivoNoFinal(string cadena);
bool ejercicio3RecursivoNoFinalAux(string cadena, int i);
bool ejercicio3RecursivoFinal(string cadena);
bool ejercicio3RecursivoFinalAux(string cadena, int i, bool acum);
void ejercicio3Mostrar(char * fichero);
//Ejercicio 4
list ejercicio4Iterativo(list l, bool (*pred)(punto p));
list ejercicio4RecursivoNoFinal(list l, bool (*pred)(punto p));
list ejercicio4RecursivoNoFinalAux(list l, bool (*pred)(punto p), int i);
list ejercicio4RecursivoFinal(list l, bool (*pred)(punto p));
list ejercicio4RecursivoFinalAux(list l, bool (*pred)(punto p), int i, list * acum);
bool primerCuadrante(punto p);
bool segundoCuadrante(punto p);
bool tercerCuadrante(punto p);
bool cuartoCuadrante(punto p);
void ejercicio4Mostrar(char * fichero);
//Ejercicio 5
int_pair ejercicio5Iterativo(int a, int b);
int_pair ejercicio5RecursivoNoFinal(int a, int b);
int_pair ejercicio5RecursivoFinal(int a, int b);
int_pair ejercicio5RecursivoFinalAux(int a, int b, int acum);
void ejercicio5Mostrar(char * fichero);

int main(){
	ejercicio3Mostrar("ficheros/PI1Ej3DatosEntrada.txt");

//	ejercicio4Mostrar("ficheros/PI1Ej4DatosEntrada..txt");
//
//
//	ejercicio5Mostrar("ficheros/PI1Ej5DatosEntrada..txt");

	return EXIT_SUCCESS;
}


//Lee fichero
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



/*
 *********************************
 * Ejercicio 3
 *********************************
 */

//Ejercicio 3 Iterativo
bool ejercicio3Iterativo(string cadena){
	bool res = true;
	int i = 0;
	char* letra = cadena.data;
	while((i < cadena.size/2) && res){
		res = letra[i] == letra[cadena.size-1-i];
		i++;
	}
	return res;

}


//Ejercicio 3 No final
bool ejercicio3RecursivoNoFinal(string cadena){
	return ejercicio3RecursivoNoFinalAux(cadena, 0);
}

bool ejercicio3RecursivoNoFinalAux(string cadena, int i){
	bool res;
	char* letra = cadena.data;
	bool b = letra[i] == letra[cadena.size-1-i];
	if(i < cadena.size/2){
		res = ejercicio3RecursivoNoFinalAux(cadena, i+1) && b;
	} else {
		res = b;
	}
	return res;
}


//Ejercicio 3 Final
bool ejercicio3RecursivoFinal(string cadena){
	return ejercicio3RecursivoFinalAux(cadena, 0, true);
}

bool ejercicio3RecursivoFinalAux(string cadena, int i, bool acum){
	bool res;
	char* letra = cadena.data;
	if(acum && (i < cadena.size/2)){
		acum = letra[i] == letra[cadena.size-1-i];
		res = ejercicio3RecursivoFinalAux(cadena, i+1,acum);
	} else {
		res = acum;
	}
	return res;
}

void ejercicio3Mostrar(char * fichero){
	list lineas = leeFichero(fichero);
	char buff[256];
	int tamanyo = lineas.size;
	int i = 0;
	int palindromo = 0;
	while(i < lineas.size){
		string elemento = *(string*) list_get(&lineas,i);
		char * res = "false";
		if(ejercicio3Iterativo(elemento)) {
			palindromo++;
			res = "true";
		}
		printf("esPalindromoIterativa(%s)=%s\n", string_tostring(&elemento, buff), res);
		i++;
	}
	printf("%d palindromos de %d palabras\n\n", palindromo, tamanyo);

	i = 0;
	palindromo = 0;
	while(i < lineas.size){
		string elemento = *(string*) list_get(&lineas,i);
		char * res = "false";
		if(ejercicio3RecursivoNoFinal(elemento)) {
			palindromo++;
			res = "true";
		}
		printf("esPalindromoNoFinal(%s)=%s\n", string_tostring(&elemento, buff), res);
		i++;
	}
	printf("%d palindromos de %d palabras\n\n", palindromo, tamanyo);


	i = 0;
	palindromo = 0;
	while(i < lineas.size){
			string elemento = *(string*) list_get(&lineas,i);
			char * res = "false";
			if(ejercicio3RecursivoFinal(elemento)) {
				palindromo++;
				res = "true";
			}
			printf("esPalindromoFinal(%s)=%s\n", string_tostring(&elemento, buff), res);
			i++;
		}
		printf("%d palindromos de %d palabras\n\n", palindromo, tamanyo);
}


/*
 *********************************
 * Ejercicio 4
 *********************************
 */

//Ejercicio 4 predicados
bool primerCuadrante(punto p){
	if(punto_cuadrante(&p) == PRIMERO){
		return true;
	} else {
		return false;
	}
}

bool segundoCuadrante(punto p){
	if(punto_cuadrante(&p) == SEGUNDO){
		return true;
	} else {
		return false;
	}
}

bool tercerCuadrante(punto p){
	if(punto_cuadrante(&p) == TERCERO){
		return true;
	} else {
		return false;
	}
}

bool cuartoCuadrante(punto p){
	if(punto_cuadrante(&p) == CUARTO){
		return true;
	} else {
		return false;
	}
}

list ejercicio4Iterativo(list l, bool (*pred)(punto p)){
	int i = 0;
	list acum = list_empty(punto_type);

	while(i < l.size){
		punto p = *(punto*) list_get(&l,i);
		if(pred(p)){
			list_add(&acum, &p);
		}
		i++;
	}
	return acum;
}


//Ejercicio 4 Recursivo No Final
list ejercicio4RecursivoNoFinal(list l, bool (*pred)(punto p)){
	return ejercicio4RecursivoNoFinalAux(l, pred, 0);
}

list ejercicio4RecursivoNoFinalAux(list l, bool (*pred)(punto p), int i){
	list res = list_empty(punto_type);
	if(i < l.size){
		res = ejercicio4RecursivoNoFinalAux(l, pred, i+1);
		punto p = *(punto*) list_get(&l,i);
		if(pred(p)){
			list_add(&res, &p);
		}
	}
	return res;

}


//Ejercicio 4 Recursivo Final
list ejercicio4RecursivoFinal(list l, bool (*pred)(punto p)){
	list acum = list_empty(punto_type);
	return ejercicio4RecursivoFinalAux(l, pred, 0, &acum);
}

list ejercicio4RecursivoFinalAux(list l, bool (*pred)(punto p), int i, list * acum){
	if(i < l.size){

		punto p = *(punto*) list_get(&l,i);
		if(pred(p)){
			list_add(acum, &p);
		}
		*(list*) acum = ejercicio4RecursivoFinalAux(l, pred, i+1, acum);
	}
	return *(list*) acum;

}

void ejercicio4Mostrar(char * fichero){
	list lineas = leeFichero(fichero);
	list puntos = list_empty(punto_type);


	char buff[256];
	char buff2[1000];
	char buff3[256];

	int i = 0;
	while(i < lineas.size){
		string s = *(string*) list_get(&lineas,i);
		punto elemento = punto_parse_s(string_tostring(&s, buff));
		list_add(&puntos, &elemento);
		i++;
	}

	char * mostrarLista = list_tostring(&puntos, buff2);

	list iterPrimer = ejercicio4Iterativo(puntos, primerCuadrante);
	list iterSegundo = ejercicio4Iterativo(puntos, segundoCuadrante);
	list iterTercer = ejercicio4Iterativo(puntos, tercerCuadrante);
	list iterCuarto = ejercicio4Iterativo(puntos, cuartoCuadrante);

	printf("-------------------- TEST DEL MÉTODO ITERATIVO --------------------\n");
	printf("Entrada: %s; Selecc. puntos del primer cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&iterPrimer, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del segundo cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&iterSegundo, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del tercer cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&iterTercer, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del cuarto cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&iterCuarto, buff3));
	printf("========================================\n\n");

	list recFPrimer = ejercicio4RecursivoFinal(puntos, primerCuadrante);
	list recFSegundo = ejercicio4RecursivoFinal(puntos, segundoCuadrante);
	list recFTercer = ejercicio4RecursivoFinal(puntos, tercerCuadrante);
	list recFCuarto = ejercicio4RecursivoFinal(puntos, cuartoCuadrante);

	printf("-------------------- TEST DEL MÉTODO RECURSIVO FINAL --------------------\n");
	printf("Entrada: %s; Selecc. puntos del primer cuadrante\n", mostrarLista );
	printf("Salida: %s\n", list_tostring(&recFPrimer, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del segundo cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&recFSegundo, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del tercer cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&recFTercer, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del cuarto cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&recFCuarto, buff3));
	printf("========================================\n\n");


	list recNFPrimer = ejercicio4RecursivoNoFinal(puntos, primerCuadrante);
	list recNFSegundo = ejercicio4RecursivoNoFinal(puntos, segundoCuadrante);
	list recNFTercer = ejercicio4RecursivoNoFinal(puntos, tercerCuadrante);
	list recNFCuarto = ejercicio4RecursivoNoFinal(puntos, cuartoCuadrante);

	printf("-------------------- TEST DEL MÉTODO RECURSIVO NO FINAL --------------------\n");
	printf("Entrada: %s; Selecc. puntos del primer cuadrante\n", mostrarLista );
	printf("Salida: %s\n", list_tostring(&recNFPrimer, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del segundo cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&recNFSegundo, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del tercer cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&recNFTercer, buff3));
	printf("========================================\n");

	printf("Entrada: %s; Selecc. puntos del cuarto cuadrante\n", mostrarLista);
	printf("Salida: %s\n", list_tostring(&recNFCuarto, buff3));
	printf("========================================\n\n");

}

/*
 *********************************
 * Ejercicio 5
 *********************************
 */
//Ejercicio 5 iterativo
int_pair ejercicio5Iterativo(int a, int b){
	int_pair res;
	int acum = 0;
	while(a >= b){
		acum++;
		a -= b;
	}
	res.a = acum;
	res.b = a;

	return res;

}

//Ejercicio 5 Recursivo No Final
int_pair ejercicio5RecursivoNoFinal(int a, int b){
	int_pair res;
	if(a < b){
		res.a = 0;
		res.b = a;
	} else {
		res = ejercicio5RecursivoNoFinal(a-b, b);
		res.a = res.a+1;
	}
	return res;
}



int_pair ejercicio5RecursivoFinal(int a, int b){
	return ejercicio5RecursivoFinalAux(a, b, 0);
}

int_pair ejercicio5RecursivoFinalAux(int a, int b, int acum){
	int_pair res;
	if(a < b){
		res.a = acum;
		res.b = a;
	} else {
		acum++;
		res = ejercicio5RecursivoFinalAux(a-b, b, acum);
	}
	return res;
}


void ejercicio5Mostrar(char * fichero){
	list lineas = leeFichero(fichero);
	char buff[256];
	char buff2[256];
	char buff3[256];
	char buff4[256];

	printf("-------------------- TEST DEL MÉTODO ITERATIVO --------------------\n");
	int i = 0;
	while(i < lineas.size){
		list numeros = list_empty(int_type);
		string s = *(string*) list_get(&lineas,i);
		char * c = string_tostring(&s, buff);
		iterator it = split_iterable_pchar(c, ",");

		while(iterable_has_next(&it)){
			char * iterable = (char*) iterable_next(&it);
			int numeroSolo = int_parse_s(iterable);
			list_add(&numeros, &numeroSolo);
		}
		int a = *(int*) list_get(&numeros,0);
		int b = *(int*) list_get(&numeros,1);
		int_pair res = ejercicio5Iterativo(a, b);


		printf("Entrada: (%s)\n", c);
		printf("Salida: %s\n", int_pair_tostring(&res, buff2));
		printf("========================================\n\n");
		i++;
	}


	printf("-------------------- TEST DEL MÉTODO RECURSIVO FINAL --------------------\n");
		i = 0;
		while(i < lineas.size){
			list numeros = list_empty(int_type);
			string s = *(string*) list_get(&lineas,i);
			char * c = string_tostring(&s, buff);
			iterator it = split_iterable_pchar(c, ",");

			while(iterable_has_next(&it)){
				char * iterable = (char*) iterable_next(&it);
				int numeroSolo = int_parse_s(iterable);
				list_add(&numeros, &numeroSolo);
			}
			int a = *(int*) list_get(&numeros,0);
			int b = *(int*) list_get(&numeros,1);
			int_pair res = ejercicio5RecursivoFinal(a, b);


			printf("Entrada: (%s)\n", c);
			printf("Salida: %s\n", int_pair_tostring(&res, buff3));
			printf("========================================\n\n");
			i++;
		}


		printf("-------------------- TEST DEL MÉTODO RECURSIVO NO FINAL --------------------\n");
				i = 0;
				while(i < lineas.size){
					list numeros = list_empty(int_type);
					string s = *(string*) list_get(&lineas,i);
					char * c = string_tostring(&s, buff);
					iterator it = split_iterable_pchar(c, ",");

					while(iterable_has_next(&it)){
						char * iterable = (char*) iterable_next(&it);
						int numeroSolo = int_parse_s(iterable);
						list_add(&numeros, &numeroSolo);
					}
					int a = *(int*) list_get(&numeros,0);
					int b = *(int*) list_get(&numeros,1);
					int_pair res = ejercicio5RecursivoNoFinal(a, b);


					printf("Entrada: (%s)\n", c);
					printf("Salida: %s\n", int_pair_tostring(&res, buff4));
					printf("========================================\n\n");
					i++;
				}

}







