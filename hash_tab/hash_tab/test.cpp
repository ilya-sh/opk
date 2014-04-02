#include "tab.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

unsigned uns_str_len(char *key)
{
	return (unsigned)strlen(key);
}


void test()
{
	HashTable *ht;

	ht = ht_init(5, uns_str_len, 0);

	ht_set(ht, "name1", (Pointer)"17657868789890890");
	ht_set(ht, "name2", (Pointer)"2");
	ht_set(ht, "name3", (Pointer)"3");
	ht_set(ht, "_name4", (Pointer)"4");
	ht_set(ht, "_name5", (Pointer)"5");

	ht_traverse(ht, print_keys_data);

	assert(ht_has(ht, "name2"));

	ht_delete(ht, "name3");

	assert(!ht_has(ht, "name3"));

	ht_set(ht, "name2", (Pointer)"2.0");

	assert(!strcmp((char*)ht_get(ht, "name2"), "2.0"));

	ht_delete(ht, "name1");
	ht_delete(ht, "name2");
	ht_delete(ht, "_name4");
	ht_delete(ht, "_name5");
	ht_delete(ht, "Noname");

	assert(!ht_has(ht, "name1"));
	assert(!ht_has(ht, "name2"));
	assert(!ht_has(ht, "_name4"));
	assert(!ht_has(ht, "_name5"));
 
	ht_resize(ht, 2);

	assert(!ht_has(ht, "name1"));
	assert(!ht_has(ht, "name2"));
	assert(!ht_has(ht, "_name4"));
	assert(!ht_has(ht, "_name5"));

	ht_destroy(ht);
}
