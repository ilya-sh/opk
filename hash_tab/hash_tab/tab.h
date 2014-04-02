typedef void* Pointer;
typedef unsigned(*HashFunction)(char *key);
typedef void(*Destructor)(Pointer);

#define DEFAULT_VALUE NULL

#include <stddef.h>
#include "list.h"


typedef unsigned HashTag;

typedef struct HashTable {
	unsigned size;
	List **table;
	HashFunction hashfunc;
	Destructor dtor;
} HashTable;

/* ���������������� �������.
*
* size - ������ �������� �������;
* hf   - ���-�������;
* dtor - ����������. ���� ������� ����� ������������ data ��������� ���������
*        (ht_destroy, ht_delete, � ����� ��� ���������� ��������� � ht_set).
*
* ���� hf=0, ������� ����������� ������� (��������).
* ���� dtor=0, ���������� ����������� (�� ����� ����������).
*/
HashTable *ht_init(unsigned size, HashFunction hf, Destructor dtor);

/* ���������� ������� */
void ht_destroy(HashTable *ht);

/* �������� � ������� ������������ key -> data. ���� key ��� �����������,
* �����. ���� data ����� ������� (dtor) � ������������ */
void ht_set(HashTable *ht, char *key, Pointer data);

/* �������� �������� �� �����. ���� ����� ��� � �������, ������� 0. */
Pointer ht_get(HashTable *ht, char *key);

/* �������� ������������� ����� key � �������. 1 - ����, 0 - ���. */
int ht_has(HashTable *ht, char *key);

/* ������� ������� � ������ key �� ������� (���� �� ����) */
void ht_delete(HashTable *ht, char *key);

/* ����� ������� � ���������� ���� ���������. ������� f ����� ������� ���
* ���� ��� (key, data) �� ������� */
void ht_traverse(HashTable *ht, void(*f)(char *key, Pointer data));

/* �������� ������ �������� �������.
*
* ��������� ��������: �������� ����� ������ table � ��������� � ���� ���
* ������������ ��������� List �� ������ table, ����� ������ ���������� �
* �������� �����.
*
* ��� �����������, ��� ��������� ����� ������� � ������ � ��� �����������
* �������.
*/
void ht_resize(HashTable *ht, unsigned new_size);

/*���-������� ���������*/
unsigned jenkins_hash(char *key);

unsigned uns_str_len(char *key);

void test();

void print_keys_data(char *key, Pointer data);