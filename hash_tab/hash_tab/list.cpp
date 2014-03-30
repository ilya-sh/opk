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
	List *temp = list;
	List *temp_next = temp->next;
	while (temp_next)
	{
		if (!strcmp(temp_next->key, key))
			break;
		temp = temp_next;
		temp_next = temp_next->next;
	}
	if (temp_next)
	{
		free(temp_next->key);
		if (destr)
		{
			destr(temp_next->data);
		}
		free(temp_next->data);
		List *temp2 = temp->next;
		temp->next = temp_next->next;
		free(temp2);
	}
}

void add_item(List *list, char *key, Pointer data, Destructor destr)
{
	if (!list)
	{
		list = (List*)malloc(sizeof(List));
		list->key = (char*)malloc(strlen(key) + 1);
		list->key = strcpy(list->key, key);
		list->data = (Pointer)malloc();
	}
}