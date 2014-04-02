// my_bsearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 11

typedef int type;

void *my_bsearch(const void *key, const void *base,
	size_t nmemb, size_t size,
	int(*compar)(const void *, const void *))
{
	if (nmemb == 0)
		return NULL;

	char *mid;
	char *first = (char*)base;
	char *last = (char*)base + (size * (nmemb - 1));

	if ((*compar)(key, first) < 0)
		return NULL;
	if ((*compar)(last, key) < 0)
		return NULL;

	while (first < last)
	{
		mid = first + ((((last - first) / 2) / size) * size);
		if ((*compar)(mid, key) < 0)
		{
			first = mid + size;
		}
		else
		{
			last = mid;
		}
	}

	if ((*compar)(last, key) == 0)
	{
		return last;
	}
	else
	{
		return NULL;
	}
}

int int_compfun(const void * a1, const void* a2)
{
	return *((int*)a1) - *((int*)a2);
}

int float_compfun(const void *a1, const void* a2)
{
	return *((float*)a1) - *((float*)a2);
}

int main(int argc, char* argv[])
{
	//srand(time(NULL));
	//type a[SIZE];
	//int i;
	//for (i = 0; i < SIZE; i++)
	//{
	//	a[i] = rand() % 100;
	//	printf("%d ", a[i]);
	//}
	//printf("\n");
	//qsort(a, SIZE, sizeof(type), compfun);
	//type k;
	//for (i = 0; i < SIZE; i++)
	//{
	//	printf("%d ", a[i]);
	//}
	//printf("\n");
	//scanf("%d", &k);
	//type* res = (type*)my_bsearch(&k, a, SIZE, sizeof(type), compfun);
	//if (res != NULL)
	//{
	//	printf("FOUND\n");
	//}
	//else
	//{
	//	printf("NOT FOUND\n");
	//}
	test();
	return 0;
}

