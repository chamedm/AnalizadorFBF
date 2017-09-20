/*
 ============================================================================
 Name        : mainPrinProy.c
 Author      : Chavez,M & Madriz,O.
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "functAn.h"
#include <string.h>
#include "theStackSet.h"

#define MAX 5000


int main(void) {
	Stack stackA, stackB;
	Set tree;
	stackA = stack_create();
	stackB = stack_create();
	tree = set_create(printChar);

	char lexA[MAX];
	char * p1 = lexA;
	int i;
	bool sortie = false;

	setbuf(stdout, NULL);


	printf("Bienvenidx a su analizador de fórmulas favorito \n");

	//Analizador Lexico

	do{
		printf("Introduzca la fórmula que desea analizar:\n");
		gets(lexA);
		cleanArr(&p1);
	}while(!validChars(lexA));

	//Analizador Sintactico

	for(i=0; lexA[i]!='\0' && !sortie ; i++){
		if(lexA[i] != ')'){
			PUSH(stackA, lexA[i]);
		}
		else{
			PUSH(stackA, lexA[i]);
			if(POP(stackA, stackB, tree) == false){
				sortie = true;
			}
		}
		if(lexA[i+1] == '\0')
			if(POP(stackA, stackB, tree) == false)
				sortie = true;
	}

	if(sortie == false){
		printf("¡Yeih! lo haz logrado, es una fórmula bien formada, tienes la lógica ;) \n");
		printf("Notación polaca: ");
		set_print(tree);
	}
	else
		printf("No es una fórmula bien formada, suerte para la proxima \n");

	set_destroy(tree);
	stack_destroy(stackA);
	stack_destroy(stackB);

	printf("¡Hasta luego!");

	return 0;
}


