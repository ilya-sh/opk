typedef struct List{
	char *key;
	Pointer data;

	struct List *next;
} List;

Pointer search_data_by_key(List *list, char *key);

int data_has(List *list, char *key);

void delete_list(List *list, Destructor destr);

void delete_item(List *list, char *key, Destructor destr);

void add_item(List *list, char *key, Pointer data, Destructor destr);