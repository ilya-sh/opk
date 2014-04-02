#include "tab.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

HashTable *ht_init(unsigned size, HashFunction hf, Destructor dtor)
{
	HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
	if (!ht)
		return NULL;
	ht->size = size;
	if (hf == NULL)
	{
		ht->hashfunc = jenkins_hash;
	}
	else
	{
		ht->hashfunc = hf;
	}
	ht->dtor = dtor;
	ht->table = (List**)malloc(sizeof(List*) * size);
	if (ht->table == NULL)
	{
		free(ht);
		return NULL;
	}
	unsigned i;
	for (i = 0; i < size; i++)
		ht->table[i] = NULL;
	return ht;
}

Pointer ht_get(HashTable *ht, char *key)
{
	if ((!ht) || (!key))
		return NULL;
	HashTag h_tag = ht->hashfunc(key);
	Pointer res = search_data_by_key(ht->table[h_tag % ht->size], key);
	return res;
}

int ht_has(HashTable *ht, char *key)
{
	if ((!ht) || (!key))
		return 0;
	HashTag h_tag = ht->hashfunc(key);
	return (data_has(ht->table[h_tag % ht->size], key));
}

void ht_destroy(HashTable *ht)
{
	if (!ht)
		return;
	unsigned i;
	for (i = 0; i < ht->size; i++)
	{
		delete_list(ht->table[i], ht->dtor);
	}
	free(ht->table);
	free(ht);
}

void ht_delete(HashTable *ht, char *key)
{
	if ((!ht) || (!key))
		return;
	HashTag h_tag = ht->hashfunc(key);
	if (!ht->table[h_tag % ht->size])
		return;
	ht->table[h_tag % ht->size] = delete_item(ht->table[h_tag % ht->size], key, ht->dtor);
}

void ht_set(HashTable *ht, char *key, Pointer data)
{
	if ((!ht) || (!key) || (!data))
		return;
	HashTag h_tag = ht->hashfunc(key);
	ht->table[h_tag % ht->size] = add_item(ht->table[h_tag % ht->size], key, data, ht->dtor);
}

void ht_traverse(HashTable *ht, void(*f)(char *key, Pointer data))
{
	if ((!ht) || (!f))
		return;
	unsigned i;
	for (i = 0; i < ht->size; i++)
		list_traverse(ht->table[i], f);
}

void ht_resize(HashTable *ht, unsigned new_size)
{
	if ((!ht) || (!new_size))
		return;
	List** new_table = (List**)malloc(sizeof(List*)* new_size);
	if (!new_table)
	{
		return;
	}
	unsigned i;
	for (i = 0; i < new_size; i++)
		new_table[i] = NULL;
	HashTag h_tag;
	for (i = 0; i < ht->size; i++)
	{
		while (ht->table[i])
		{
			h_tag = ht->hashfunc((peek_b(ht->table[i]))->key);
			new_table[h_tag % new_size] = push_b(new_table[h_tag % new_size], pop_b(ht->table[i]));
		}
	}
	free(ht->table);
	ht->table = new_table;
	ht->size = new_size;
}

unsigned jenkins_hash(char *key)
{
	unsigned hash = 0;

	for (; *key; ++key) 
	{
		hash += *key;
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;
}
