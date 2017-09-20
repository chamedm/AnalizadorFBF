/*
 * theStack.h
 *
 *  Created on: 4 may. 2017
 *      Author: Chavez ft Madriz
 */

#ifndef THESTACKSET_H_
#define THESTACKSET_H_
typedef void* Type;
typedef struct node* Node;
typedef struct stack* Stack;
typedef struct treenode* TreeNode;

typedef enum { false, true } bool;
typedef enum {Atomic, Aperture, Closure, Unary, Binary, Nodes} Types;

Stack stack_create();
int   stack_size(Stack);
bool  stack_isEmpty(Stack);
TreeNode  stack_top(Stack);
void  stack_push(Stack, TreeNode);
TreeNode  stack_pop(Stack);
void  stack_destroy(Stack);

typedef struct set* Set;
typedef void (*PrintFunc) (char); //cambio de type a char

Set set_create(PrintFunc);
int set_size(Set);
TreeNode set_add(Set, TreeNode, TreeNode, TreeNode);
void set_destroy(Set);
void set_print(Set);
TreeNode node_create(char f);
char node_value(TreeNode v);
bool nodeIsComplete(TreeNode);
void set_root(Set, TreeNode);



#endif /* THESTACKSET_H_ */
