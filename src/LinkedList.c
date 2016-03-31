#include<string.h>
#include<stdlib.h>

#include "LinkedList.h"

void LinkedList_Create(List *list, void (*destroy)(void *data))
{
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void LinkedList_Destroy(List *list)
{
	void *data;

	while (list_size(list)>0)
	{
		if(LinkedList_RemoveNext(list, NULL, (void**)&data)==0 && list->destroy !=NULL)
		{
			list->destroy(data);
		}
	}

	memset(list, 0, sizeof(List));
}


int LinkedList_InsertNext(List *list, ListElmnt *element, const void *data)
{
	ListElmnt *new_element;
	if ((new_element = (ListElmnt *)malloc(sizeof(ListElmnt))) == NULL)
		return -1;

	new_element->data = (void *) data;

	if (element == NULL){
		if(list->size == 0)
			list->tail = new_element;
		new_element->next = list->head;
		list->head = new_element;
	}
	else{
		if (element->next == NULL)
			list->tail = new_element;
		new_element->next = element->next;
		element->next = new_element;
	}

	list->size++;
	return 0; 
}

int LinkedList_RemoveNext(List *list, ListElmnt *element, void **data){
	ListElmnt *old_lement;

	if (list_size(list) == 0)
		return -1;

	if (element == NULL)
	{
		*data = list->head->data;
		old_lement = list->head;
		list->head = list->head->next;
		if(list_size(list)==1)
			list->tail = NULL;
	}
	else
	{
		if(element->next == NULL)
			return -1;

		*data = element->next->data;
		old_lement = element->next;
		element->next = element->next->next;

		if(element->next == NULL)
			list->tail = element;
	}

	free(old_lement);
	list->size--;
	return 0;
}
