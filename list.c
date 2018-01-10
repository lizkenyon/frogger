///////////////////////////////////////
//list.c
//Comp 3430
//A2
//Elizabeth Kenyon
// doubly linked list to hold logs
///////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "log.h"

/////////////////////////////////////////////

static Node *head = NULL;
//static Node *currNode = NULL;
int count = 0;

//////////////////////////////////////////////

void insert(Log *log){
	count++;
	if(log != NULL){
 
		Node *newNode = (Node *)malloc(sizeof(Node));
		if(newNode != NULL){

			newNode->log = log;
			if(head != NULL){
				newNode->next = head;
				head->prev = newNode;
				newNode->prev = NULL;
				head = newNode;
			}
			else{
				head = newNode;
				newNode->next = NULL;
				newNode->prev = NULL;
			}
		}

	}
}

void deleteNode(Node *node){
	if(node != NULL && node->next !=NULL && node->prev != NULL){
		node->prev->next = node->next;
		node->next->prev = node->prev;
		free(node->log);
		free(node);
	}
	else if(node != NULL && node->next != NULL){
		head = node->next;
		free(node->log);
		free(node);
	}
	else if(node != NULL && node->prev!= NULL){
		node->prev->next = NULL;
		free(node->log);
		free(node);
	}
	else if(node != NULL){
		head = NULL;
		free(node->log);
		free(node);
	}
}

Node *getHead(){
	return head;
}









