#include "tab.h"
#include <string.h>
#include <stdlib.h>

Pointer search_data_by_key(List *list, char *key)
{
	if (!list)
		return 0;
	List *temp = list;
	do {
		if (strcmp(key, temp->key))
		{
			temp = temp->next;
		}
		else
		{
			return temp->data;
		}
	} while (temp->next);
	return NULL;
}

int data_has(List *list, char *key)
{
	if (!list)
		return 0;
	List *temp = list;
	do {
		if (strcmp(key, temp->key))
		{
			temp = temp->next;
		}
		else
		{
			return 1;
		}
	} while (temp->next);
	return 0;
}

void delete_list(List *list, Destructor destr)
{
	if (!list)
		return;
	List *temp;
	do 
	{
		temp = list->next;
		if (destr)
		{
			destr(list->data);
		}
		free(list->data);
		free(list->key);
		free(list);
		list = temp;

	} while(list);
}

void delete_item(List *list, char *key, Destructor destr)
{
	if (!list)
		return;
}