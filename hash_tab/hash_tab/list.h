typedef struct List{
	char *key;
	Pointer data;

	struct List *next;
} List;

Pointer search_data_by_key(List *list, char *key);

int data_has(List *list, char *key);

void delete_list(List *list, Destructor destr);

List* delete_item(List *list, char *key, Destructor destr);

List* add_item(List *list, char *key, Pointer data, Destructor destr);

void list_traverse(List *list, void(*f)(char *key, Pointer data));

List* push_b(List *buf, List *source);

List* pop_b(List *source);

List* peek_b(List *source);