/*
 * impStack.c
 *
 *  Created on: 4 may. 2017
 *      Author: Chavez
 */
#include <stdlib.h>
#include <stdio.h>
#include "theStackSet.h"

struct treenode{
	TreeNode left, right;
	char data;
	bool isComplete;
};

struct node{
	Node prior;
	TreeNode data;
};

struct stack{
	Node top;
	unsigned int size;
};


struct set{
	TreeNode root;
	unsigned int size;
	PrintFunc printFunc;
};

Stack stack_create(){
	Stack s = calloc(1,sizeof(struct stack));
	return s;
}

int   stack_size(Stack s){
	return s->size;
}

bool  stack_isEmpty(Stack s){
	return s->size == 0;
}

TreeNode stack_top(Stack s){
	if(s->top == NULL)
		return NULL;

	return s->top->data;
}

void stack_push(Stack s, TreeNode d){
	Node new = calloc(1,sizeof(struct node));
	new->data= d;

	if(s->size==0)
		s->top=new;
	else{
		new->prior = s->top;
		s->top = new;
	}
	s->size++;
}

TreeNode  stack_pop(Stack s){
	Node temp;
	TreeNode d;
	if(s->size==0)
		return NULL;

	else{
		temp = s->top;
		d = s->top->data;
		s->top = s->top->prior;
		free(temp);
		s->size--;
		return d;
	}
}

void  stack_destroy(Stack s){
	Node current = s->top;
	Node prior;

	while(current!=NULL){
		prior = current->prior;
		free(current);
		current = prior;
	}
	free(s);
}

Set set_create(PrintFunc pf){
	Set s = calloc(1,sizeof(struct set));
	s->printFunc = pf;
	return s;
}

int set_size(Set s){
	return s->size;
}

TreeNode set_add(Set s, TreeNode parent, TreeNode leftChild, TreeNode rightChild){
	parent->left = leftChild;
	parent->right = rightChild;
	parent->isComplete = true;
	s->size++;
	return parent;
}

void print(TreeNode tn, PrintFunc pf){
	if(tn != NULL){
		print(tn->left, pf);
		print(tn->right, pf);
		pf(tn->data);
	}
}

void set_print(Set s){
	print(s->root, s->printFunc);
	printf("\n");
}

void destroy(TreeNode tn){
	if(tn != NULL){
		destroy(tn->left);
		destroy(tn->right);
		free(tn);
	}
}

void set_destroy(Set s){
	destroy(s->root);
	free(s);
}

TreeNode node_create(char f){
	TreeNode new = calloc(1, sizeof(struct treenode));
	new->data = f;
	return new;
}

char node_value(TreeNode v){
	return v->data;
}

bool nodeIsComplete(TreeNode v){
	return v->isComplete;
}

void set_root(Set s, TreeNode t){
	s->root = t;
}



