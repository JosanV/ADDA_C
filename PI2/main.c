/*
 * main.c
 *
 *  Created on: 29 nov. 2019
 *      Author: josan
 */

#include <stdio.h>
#include <stdlib.h>

#include "types/types.h"
#include "types/list.h"
#include "types/iterables.h"
#include "types/hash_table.h"

list leeFichero(char * file);
bool ejercicio1Rec(int entrada[100][100], int l);
bool ejercicio1RecAux(int entrada[100][100], int x1, int y1, int x2, int y2, int n);
void muestraEjercicio1(char * fichero);
int ejercicio2Rec(int entrada[], int l);
int ejercicio2RecAux(int entrada[], int i, int j);
void muestraEjercicio2(char * fichero);
int ejercicio4Rec(int n, int k);
int ejercicio4RecMem(int n, int k);
int ejercicio4RecMemAux(int n, int k, hash_table * mem);
int ejercicio4Iter(int n, int k);
void muestraEjercicio4(char * fichero);

int main(int argc, char **argv) {

	muestraEjercicio1("ficheros/PI2Ej1DatosEntrada.txt");

	muestraEjercicio2("ficheros/PI2Ej2DatosEntrada.txt");

	muestraEjercicio4("ficheros/PI2Ej4DatosEntrada.txt");

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


////////////////////////////////////////////
//				Ejercicio 1 			  //
////////////////////////////////////////////

bool ejercicio1Rec(int entrada[100][100], int l){
	return ejercicio1RecAux(entrada, 0, 0, l-1, l-1, l);
}

bool ejercicio1RecAux(int entrada[100][100], int x1, int y1, int x2, int y2, int n){
	bool res;
	if(n == 2){
		res = entrada[x1][y1] < entrada[x2][y2];
	} else {
		int fX=(x1+x2)/2;	//Formula recurrente de x
		int fY=(y1+y2)/2;	//Formula recurrente de y
		res = (entrada[x1][y1] < entrada[x2][y2])
			&& ejercicio1RecAux(entrada, x1, y1, fX, fY, n/2)					//Arriba izquierda
			&& ejercicio1RecAux(entrada, x1, y1 + (n/2), fX, y2, n/2)			//Arriba derecha
			&& ejercicio1RecAux(entrada, x1 + (n/2), y1, x2, fY, n/2)			//Abajo izquierda
			&& ejercicio1RecAux(entrada, x1 + (n/2), y1 + (n/2), x2, y2, n/2);	//Abajo derecha
	}
	return res;
}


void muestraEjercicio1(char * fichero){
	list lineas = leeFichero(fichero);
	int i = 0;
	char buff[256];

	while(i < lineas.size){
		string elemento = *(string*) list_get(&lineas,i);
		char * c = string_tostring(&elemento,buff);

		printf("La matriz: %s\n", c);

		iterator it = split_iterable_pchar(c, ",");
		int cont = 0;
		list lfilas = list_empty(string_type);
		while (iterable_has_next(&it)) {
			char * iterable = (char*) iterable_next(&it);
			string slinea = string_of_pchar(iterable);
			list_add(&lfilas, &slinea);
			cont++;
		}
		int m[100][100];

		for (int j = 0; j < cont; j++) {
			string elem = *(string*) list_get(&lfilas,j);
			char * ch = string_tostring(&elem,buff);

			char* chmod = ch + 1;	//eliminar {
			chmod[strlen(chmod)-1] = 0;	//eliminar }

			iterator it = split_iterable_pchar(chmod, " ");
			int y1 = 0;
			while (iterable_has_next(&it)) {
				char * divide = (char*) iterable_next(&it);
				m[j][y1] = int_parse_s(divide);
				y1++;
				;
			}
		}


		i++;

		bool res = ejercicio1Rec(m, cont);
		if(res){
			printf("Cumple la propiedad\n\n");
		} else{
			printf("NO Cumple la propiedad\n\n");
		}
	}
}




////////////////////////////////////////////
//				Ejercicio 2				  //
////////////////////////////////////////////
int ejercicio2Rec(int entrada[], int l){
	return ejercicio2RecAux(entrada, 0, l-1);
}

int ejercicio2RecAux(int entrada[], int i, int j){
	int res;
	int n = (i+j)/2;
	if((entrada[n] > entrada[n-1] && entrada[n] > entrada[n+1]) || (i == j)){	//Si el numero que comparamos es ya el mas grande o solo queda uno
		res = entrada[n];
	}else if(entrada[n-1] > entrada[n]){							//Si el que comparamos tiene justo al mas grande antes
		res = entrada[n-1];
	} else if(entrada[i] > entrada[n]){								//Si el primer elemento es mayor que n es porque esta en la primera mitad
		res = ejercicio2RecAux(entrada, i, n-1);
	} else {														//ECOC: Esta en la segunda mitad
		res = ejercicio2RecAux(entrada, n+1, j);
	}
	return res;
}

void muestraEjercicio2(char * fichero){
	list lineas = leeFichero(fichero);
	int i = 0;
	char buff[256];
	while(i < lineas.size){
		string elemento = *(string*) list_get(&lineas,i);
		char * c = string_tostring(&elemento,buff);
		iterator it = split_iterable_pchar(c, ",");

		int acum[256];
		int cont = 0;
		while (iterable_has_next(&it)) {
			char * iterable = (char*) iterable_next(&it);
			int j = int_parse_s(iterable);
			acum[cont] = j;
			cont++;
		}

		printf("Entrada: %s\n", c);
		printf("Salida: %d\n", ejercicio2Rec(acum, cont));
		printf("=====================================================================\n");

		i++;
	}

}





////////////////////////////////////////////
//				Ejercicio 4				  //
////////////////////////////////////////////

//Recursivo sin memoria
int ejercicio4Rec(int n, int k){
    int res = 0;
    if(k == 0 || k == n) {
        res = 1;
    } else if(k == 1 || k == n-1) {
        res = n;
    } else{
        res = ejercicio4Rec(n-1,k-1) + ejercicio4Rec(n-1,k);
    }
    return res;
}

//Recursivo con memoria
int ejercicio4RecMem(int n, int k){
	hash_table mem = hash_table_empty(int_pair_type, int_type);
	return ejercicio4RecMemAux(n, k, &mem);
}
int ejercicio4RecMemAux(int n, int k, hash_table * mem){
    int res = 0;
    int_pair aux;
    aux.a = n;
    aux.b = k;
    if(hash_table_contains(mem, &aux)){
//    	printf("He entrado en memoria con el valor n:%d k:%d\n", n,k);	//Comprobante
    	res =  *(int*) hash_table_get(mem,&aux);
    }else if(k == 0 || k == n) {
        res = 1;
        hash_table_put(mem,&aux, &res);
    } else if(k == 1 || k == n-1) {
        res = n;
        hash_table_put(mem,&aux, &res);
    } else{
        res = ejercicio4RecMemAux(n-1,k-1,mem) + ejercicio4RecMemAux(n-1,k,mem);
        hash_table_put(mem,&aux, &res);
    }
    return res;
}

int ejercicio4Iter(int n, int k) {
	int C[n+1][k+1];
	int i, j;
	int min;
	for (i = 0; i <= n; i++)
	{
		if(i<k){
			min = i;
		} else {
			min = k;
		}
		for (j = 0; j <= min; j++)
		{
			if (j == 0 || j == i)
				C[i][j] = 1;
			else
				C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
	return C[n][k];

}


void muestraEjercicio4(char * fichero){
	list lineas = leeFichero(fichero);

	printf("\n==================================== TEST RECURSIVO SIN MEMORIA ====================================\n");
	int i = 0;
	char buff[256];
	while(i < lineas.size){
		string elemento = *(string*) list_get(&lineas,i);
		char * c = string_tostring(&elemento,buff);

		char* chmod = c + 1;	//eliminar {
		chmod[strlen(chmod)-1] = 0;	//eliminar }

		iterator it = split_iterable_pchar(chmod, ",");

		list acum = list_empty(int_type);
		while (iterable_has_next(&it)) {
			char * iterable = (char*) iterable_next(&it);
			int j = int_parse_s(iterable);
			list_add(&acum, &j);
		}
		int n = *(int*)list_get(&acum, 0);
		int k = *(int*)list_get(&acum, 1);

		printf("Entrada: %s); Salida = %d\n", c, ejercicio4Rec(n, k));

		i++;
	}



	printf("\n==================================== TEST RECURSIVO CON MEMORIA ====================================\n");
	i = 0;
	while(i < lineas.size){
		string elemento = *(string*) list_get(&lineas,i);
		char * c = string_tostring(&elemento,buff);

		char* chmod = c + 1;	//eliminar {
		chmod[strlen(chmod)-1] = 0;	//eliminar }

		iterator it = split_iterable_pchar(chmod, ",");

		list acum = list_empty(int_type);
		while (iterable_has_next(&it)) {
			char * iterable = (char*) iterable_next(&it);
			int j = int_parse_s(iterable);
			list_add(&acum, &j);
		}
		int n = *(int*)list_get(&acum, 0);
		int k = *(int*)list_get(&acum, 1);

		printf("Entrada: %s); Salida = %d\n", c, ejercicio4RecMem(n, k));

		i++;
	}

	printf("\n==================================== TEST ITERATIVO ====================================\n");
		i = 0;
		while(i < lineas.size){
			string elemento = *(string*) list_get(&lineas,i);
			char * c = string_tostring(&elemento,buff);

			char* chmod = c + 1;	//eliminar {
			chmod[strlen(chmod)-1] = 0;	//eliminar }

			iterator it = split_iterable_pchar(chmod, ",");

			list acum = list_empty(int_type);
			while (iterable_has_next(&it)) {
				char * iterable = (char*) iterable_next(&it);
				int j = int_parse_s(iterable);
				list_add(&acum, &j);
			}
			int n = *(int*)list_get(&acum, 0);
			int k = *(int*)list_get(&acum, 1);

			printf("Entrada: %s); Salida = %d\n", c, ejercicio4Iter(n, k));

			i++;
		}
}


