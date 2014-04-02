#include "tab.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

Pointer search_data_by_key(List *list, char *key)
{
	if (!list)
		return DEFAULT_VALUE;
	List *temp = list;
	while (temp)
	{
		if (strcmp(key, temp->key))
		{
			temp = temp->next;
		}
		else
		{
			return temp->data;
		}
	}
	return DEFAULT_VALUE;
}

int data_has(List *list, char *key)
{
	if (!list)
		return 0;
	List *temp = list;
	while (temp) 
	{
		if (strcmp(key, temp->key))
		{
			temp = temp->next;
		}
		else
		{
			return 1;
		}
	}
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
		//free(list->data);
		list->data = NULL;
		free(list->key);
		free(list);
		list = temp;

	} while(list);
}

List* delete_item(List *list, char *key, Destructor destr)
{
	if (!list)
		return NULL;
	if (!strcmp(key, list->key))
	{
		List *temp = list->next;
		free(list->key);
		if (destr)
			destr(list->data);
		list->data = NULL;
		free(list);
		return temp;
	}
	List *temp_prev = list;
	List *temp_next = temp_prev->next;
	while (temp_next)
	{
		if (!strcmp(temp_next->key, key))
			break;
		temp_prev = temp_next;
		temp_next = temp_next->next;
	}
	if (temp_next)
	{
		free(temp_next->key);
		if (destr)
		{
			destr(temp_next->data);
		}
		//free(temp_next->data);
		temp_next->data = NULL;
		List *temp2 = temp_prev->next;
		temp_prev->next = temp_next->next;
		free(temp2);
	}
	return list;
}

List* add_item(List *list, char *key, Pointer data, Destructor destr)
{
	if (!list)
	{
		list = (List*)malloc(sizeof(List));
		list->key = (char*)malloc(strlen(key) + 1);
		list->key = strcpy(list->key, key);
		list->data = data;
		list->next = NULL;
		return list;
	}
	List *beg = list;
	List *prev = NULL;
	while (list)
	{
		if (!strcmp(list->key, key))
		{
			if (destr)
				destr(list->data);
			list->data = data;
			return beg;
		}
		prev = list;
		list = list->next;
	}
	list = (List*)malloc(sizeof(List));
	list->key = (char*)malloc(strlen(key) + 1);
	list->key = strcpy(list->key, key);
	list->data = data;
	list->next = NULL;
	prev->next = list;
	return beg;
}

void list_traverse(List *list, void(*f)(char *key, Pointer data))
{
	while (list)
	{
		f(list->key, list->data);
		list = list->next;
	}
}

List* push_b(List *buf, List *source)
{	
	if (!buf)
	{
		return source;
	}
	List *beg = buf;
	while (buf->next)
	{
		buf = buf->next;
	}
	buf->next = source;
	return beg;
}

List* pop_b(List *source)
{
	List* prev = NULL;
	while (source->next)
	{
		prev = source;
		source = source->next;
	} 
	prev->next = NULL;
	return source;
}

List* peek_b(List *source)
{
	while (source->next)
	{
		source = source->next;
	}
	return source;
}

void print_keys_data(char *key, Pointer data)
{
<<<<<<< HEAD
	printf("%s\t%d\n", key, data);
}
=======
	printf("%s\t%s\n", key, data);
}
>>>>>>> b6ad44bc57d752dff31f8d8e17637fee2b355e05
