/*
 ============================================================================
 Name        : megaSockets.c
 Author      : Franco
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>

int* sumarOptimizado(void*);
int* sumarMuchosNumeros(void*);
void sumarMuchosThread(int, ...); //max 256


int main(int argc, char *argv[]) {

	if (argc < 2) {
	 fprintf(stderr, "Debe dar al menos un parametro\n");
	 return EXIT_FAILURE;
	 }
	 int numeros[argc];
	 int i, ret1;
	 int res = 0;
	 int *re = &res;
	 pthread_t t1;
	 for (i = 0; i < (argc - 1); i++) {
	 numeros[i] = atoi(argv[i + 1]);
	 }
	 numeros[argc - 1] = 0;
	 ret1 = pthread_create(&t1, NULL, sumarOptimizado, numeros);
	 if (ret1) {
	 fprintf(stderr, "Error - pthread_create() return code: %d\n", ret1);
	 exit(EXIT_FAILURE);
	 }
	 pthread_join(t1, re);
	 printf("%u \n", res);
	 return 0;
}



int* sumarOptimizado(void* args) {
	int i = 0, x, y, j, ret1, ret2;
	int *p1, *p2 = NULL, sum = 0, res1, res2 = 0, *r1 = &res1, *r2 = &res2;
	pthread_t t1, t2;
	int* nums = (int*) args;		//
	while (nums[i] != 0) {			// cuenta la longitud del array
		i++;						//
	}

	if (i <= 3) {                	//
		for (j = 0; j < i; j++) {	//
			sum += nums[j];			// Cuando tiene longitud menor a 3 suma todo
		}							//   y devuelve el valor
		return sum;					//
	} else {

		x = i / 2;             //y es mayor que x
		y = i - x;
		p1 = (int*) malloc(y * (sizeof(int)) + 5);
		p2 = (int*) malloc(x * (sizeof(int)) + 5);
		for (j = 0; j < x; j++) {
			p2[j] = nums[j + y];
			p2[j + 1] = 0;
		}
		p2[i] = 0;
		for (j = 0; j < y; j++) {
			p1[j] = nums[j];
			p1[j + 1] = 0;
		}
		ret1 = pthread_create(&t1, NULL, sumarOptimizado, (void*) p1);
		if (ret1) {
			fprintf(stderr, "Error - pthread_create() return code: %d\n", ret1);
			exit(EXIT_FAILURE);
		}
		ret2 = pthread_create(&t2, NULL, sumarOptimizado, (void*) p2);
		if (ret2) {
			fprintf(stderr, "Error - pthread_create() return code: %d\n", ret2);
			exit(EXIT_FAILURE);
		}
		pthread_join(t1, r1);
		pthread_join(t2, r2);
		free(p1);
		free(p2);
		return res1 + res2;
	}
}

void sumarMuchosThread(int n, ...) {
	va_list lista;
	pthread_t th;
	int i, res, ret1;
	int* args = malloc(1024);
	int* tores = &res;
	va_start(lista, n);
	for (i = 0; i < n; i++) {
		args[i] = va_arg(lista, int);
		args[i + 1] = NULL;
	}
	ret1 = pthread_create(&th, NULL, sumarMuchosNumeros, (void*) args);
	pthread_join(th, tores);
	printf("%d", res);
	free(args);
	return;
}

int* sumarMuchosNumeros(void* args) {
	int* nums = (int*) args;
	int ac = 0;
	int i = 0;
	while (nums[i] != NULL) {
		ac += nums[i];
		i++;
	}
	return ac;
}
