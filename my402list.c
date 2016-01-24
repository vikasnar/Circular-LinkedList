#include <stdio.h>
#include <stdlib.h>
#include "cs402.h"
#include "my402list.h"


int My402ListInit(My402List *list){
	if(list == NULL)
		list = (My402List*)malloc(sizeof(My402List));
	list->num_members = 0;
	if(list == NULL ){//|| (list->anchor) == NULL
		fprintf(stderr,"Failed to Allocate Memory!!");
		return FALSE;
	}
	list->anchor.next = &list->anchor;
	list->anchor.prev = &list->anchor; 
	return TRUE;
}

int My402ListLength(My402List* list){
	return list->num_members;
}

int My402ListEmpty(My402List* list){
	if(list == NULL) return TRUE;
	// if(list->anchor) return TRUE;
	if(list->anchor.next != &list->anchor && list->anchor.prev != &list->anchor) return FALSE;
	return TRUE;
}

My402ListElem* My402ListFirst(My402List *list){
	if(My402ListEmpty(list)) 
		return NULL;
	else{ 
		My402ListElem *hook = &list->anchor;
		return hook->next;
	}
}

My402ListElem* My402ListLast(My402List *list){
	if(My402ListEmpty(list)) 
		return NULL;
	else{
		My402ListElem *hook = &list->anchor;
		return hook->prev;
	}
}

My402ListElem* My402ListNext(My402List *list, My402ListElem* elem){
	if(My402ListEmpty(list))
		return NULL;
	if(My402ListLast(list) == elem) return NULL;
	return elem->next;
}

My402ListElem* My402ListPrev(My402List *list, My402ListElem *elem){
	if(My402ListEmpty(list))
		return NULL;
	if(My402ListFirst(list) == elem) return NULL;
	return elem->prev;
}

My402ListElem* My402ListFind(My402List *list,void *data){
	if(My402ListEmpty(list)){
		return NULL;
	}
	else{
		My402ListElem* hook = &list->anchor;
		My402ListElem* cur = hook->next;
		while(cur != hook){
			if(cur->obj == data){
				return cur;
			}
			cur = cur->next;
		}
		return NULL;
	}
}

int My402ListAppend(My402List* list,void *data){
	My402ListElem *newNode = (My402ListElem*)malloc(sizeof(My402ListElem));
	newNode->obj = data;
	My402ListElem *hook = &list->anchor;
	if(My402ListEmpty(list)){
		hook->next = newNode;
		hook->prev = newNode;
		newNode->next = hook;
		newNode->prev = hook;
		list->num_members += 1;
		return TRUE;
	}else{
		hook->prev->next = newNode;
		newNode->prev = hook->prev;
		hook->prev = newNode;
		newNode->next = hook;
		list->num_members += 1;
		return TRUE;
	}
	return FALSE;
}

int My402ListPrepend(My402List* list,void *data){
	My402ListElem *newNode = (My402ListElem*)malloc(sizeof(My402ListElem));
	newNode->obj = data;
	My402ListElem *hook = &list->anchor;
	if(My402ListEmpty(list)){
		hook->next = newNode;
		hook->prev = newNode;
		newNode->next = hook;
		newNode->prev = hook;
		list->num_members += 1;
		return TRUE;
	}else{
		hook->next->prev = newNode;
		newNode->next = hook->next;
		newNode->prev = hook;
		hook->next = newNode;
		list->num_members += 1;
		return TRUE;
	}
	return FALSE;
}

void My402ListUnlink(My402List *list, My402ListElem *elem){
	if(elem == NULL) return;
	elem->prev->next = elem->next;
	elem->next->prev = elem->prev;
	free(elem);
	list->num_members -= 1;
}	

void My402ListUnlinkAll(My402List *list){
	My402ListElem *hook = &list->anchor;
	My402ListElem *cur = hook->next;
	while(cur != hook){
		My402ListElem *temp = cur->next;
		free(cur);
		cur = temp;
	}
	list->num_members -= 0;
	hook->next = NULL;
	hook->prev = NULL;
}

int My402ListInsertAfter(My402List *list, void *data, My402ListElem *elem){
	if(elem == NULL){
		My402ListAppend(list,data);
		return TRUE;
	}
	else{
		My402ListElem *newNode = (My402ListElem*)malloc(sizeof(My402ListElem));
		newNode->obj = data;
		elem->next->prev = newNode;
		newNode->next = elem->next;
		elem->next = newNode;
		newNode->prev = elem;
		list->num_members += 1;
		return TRUE;
	}
	return FALSE;
}

int My402ListInsertBefore(My402List *list, void *data, My402ListElem *elem){
	if(elem == NULL){
		My402ListPrepend(list,data);
		return TRUE;
	}
	else{
		My402ListElem *newNode = (My402ListElem*)malloc(sizeof(My402ListElem));
		newNode->obj = data;
		elem->prev->next = newNode;
		newNode->prev = elem->prev;
		newNode->next = elem;
		elem->prev = newNode;
		list->num_members += 1;
		return TRUE;
	}
	return FALSE;
}
