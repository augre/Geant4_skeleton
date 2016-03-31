#ifndef D_LinkedList_H
#define D_LinkedList_H

/**********************************************************
 *
 * LinkedList is responsible for ...
 *
 **********************************************************/

#include<stdlib.h>

typedef struct ListElmnt_ {
	void *data;
	struct ListElmnt_ *next;
} ListElmnt;

typedef struct List_ {
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	ListElmnt *head;
	ListElmnt *tail;
} List;

void LinkedList_Create(List *list, void (*destroy)(void * data));
void LinkedList_Destroy(List *list);
int LinkedList_InsertNext(List *list, ListElmnt *element, const void *data);
int LinkedList_RemoveNext(List *list, ListElmnt *element, void **data);
#define list_size(list) ((list)->size)

#define list_head(list) ((list)->head)

#define list_tail(list) ((list)->tail)

#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)

#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)

#define list_data(element) ((element)->data)

#define list_next(element) ((element)->next)

#endif  /* D_FakeLinkedList_H */
