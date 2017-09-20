/*
 * functAn.h
 *
 *  Created on: 4 may. 2017
 *      Author: Chavez ft Madriz
 */
#include "theStackSet.h"


void cleanArr(char ** Arr){
	int i, j;

	//Quita espacios
	for(i=0, j=0;(*Arr)[i] !='\0';i++){
		if((*Arr)[i] != ' '){
			(*Arr)[j] = (*Arr)[i] ;
			j++;
		}
	}
	(*Arr)[j] = '\0';

	//Quita <-> y ->
	for(i=0, j=0; (*Arr)[i] !='\0'; i++, j++){
		if((*Arr)[i]  == '<' && (*Arr)[i+1] == '-' && (*Arr)[i+2] == '>'){
			(*Arr)[j] = '=';
			i+=2;
		}
		else if ((*Arr)[i]  == '-' && (*Arr)[i+1] == '>'){
			(*Arr)[j] = '>';
			i+=1;
		}
		else
			(*Arr)[j] = (*Arr)[i] ;
	}
	(*Arr)[j] = '\0';
}

bool validChars(char arr[]){
	int i=0, An;//categorizará los caracteres

	while(arr[i] != '\0'){

		if(arr[i] >= 'a' && arr[i] <= 'z')
			An = 0;
		else if (arr[i] == '(' || arr[i] == ')')
			An = 1;
		else if (arr[i] == '¬' || arr[i] == '|' || arr[i] == '&')
			An = 2;
		else if(arr[i] == '=' || arr[i] == '>')
			An = 3;
		else
			An = 4;

		switch(An){//logra recorrer  el arreglo sin necesidad de un for
		case 0:
			i++;
			break;
		case 1:
			i++;
			break;
		case 2:
			i++;
			break;
		case 3:
			i++;
			break;
		case 4:
			printf("Introduzca una cadena válida :,v\n");
			return false;
		}
	}
	return true;
}

void PUSH(Stack  s, char f){
	TreeNode new = node_create(f);
	stack_push(s, new);
}

int kind(TreeNode d){
	if(node_value(d) >= 'a' && node_value(d)  <= 'z')
		return Atomic;
	else if (node_value(d) == '(')
		return Aperture;
	else if (node_value(d) == ')')
		return Closure;
	else if (node_value(d) == '¬' )
		return Unary;
	else if(node_value(d) == '=' || node_value(d) == '>' || node_value(d) == '|' || node_value(d)  == '&')
		return Binary;
	return -1;
}


bool POP(Stack A, Stack B, Set Tree){
	TreeNode d, t, t2; //Temporal para almacenar el nodo que hace pop

	if(stack_size(A) == 1){

		if(stack_top(A) == NULL)
			return false;

		if(kind(stack_top(A)) == Atomic){
			t = set_add(Tree, stack_pop(A), NULL, NULL);
			set_root(Tree, t);
			return true;
		}
		else if(nodeIsComplete(stack_top(A))){
			set_root(Tree, stack_pop(A));
			return true;
		}
		return false;
	}

	do{
		if(stack_isEmpty(A) && stack_size(B) > 1)
			return false;

		if(stack_isEmpty(A) && stack_size(B) == 1){
			d = stack_pop(B);
			if(kind(d) == Atomic || nodeIsComplete(d)){
				set_root(Tree, d);
				return true;
			}
			else
				return false;
		}

		d = stack_pop(A);

		if(kind(d) == Atomic || kind(d) == Closure || nodeIsComplete(d)){
			stack_push(B, d);
		}
		else if(kind(d) == Unary){

			if(stack_top(B) == NULL)
				return false;

			if(kind(stack_top(B)) == Atomic || nodeIsComplete(stack_top(B))){
				t = set_add(Tree, d, stack_pop(B), NULL);
				stack_push(B, t);
			}
			else
				return false;
		}
		else if(kind(d) == Binary){

			t2 = stack_pop(A);

			if(stack_top(A) == NULL)
				return false;

			if(kind(t2) == Atomic && kind(stack_top(A)) == Unary){
				t = set_add(Tree, stack_pop(A), t2, NULL);
				stack_push(A, t);
				t2 = stack_pop(A);
			}

			if(stack_top(B) == NULL)
				return false;

			if(kind(t2) == Atomic && kind(stack_top(B)) == Atomic)
				t = set_add(Tree, d, t2, stack_pop(B));
			else if(nodeIsComplete(t2) && nodeIsComplete(stack_top(B)))
				t = set_add(Tree, d, t2, stack_pop(B));
			else if(kind(t2) == Atomic && nodeIsComplete(stack_top(B)))
				t = set_add(Tree, d, t2, stack_pop(B));
			else if(kind(stack_top(B)) == Atomic && nodeIsComplete(t2))
				t = set_add(Tree, d, t2, stack_pop(B));
			else
				return false;

			stack_push(B, t);
		}
		else if(kind(d) == Aperture){
			t = stack_pop(B);
			if(!stack_isEmpty(B)){

				if(stack_top(B) == NULL)
					return false;

				if(kind(stack_top(B)) == Closure)
					stack_pop(B);//Cierre
				else
					return false;
			}
			else
				return false;
			stack_push(A, t);
		}
	}while(!stack_isEmpty(B));

	return true;
}

void printChar(char t) {//por cambio de type a char
	//char * pC = (char *) t;
	if(t == '=')
		printf("<->");
	else if (t == '>')
		printf("->");
	else
		printf("%c", t);
}
