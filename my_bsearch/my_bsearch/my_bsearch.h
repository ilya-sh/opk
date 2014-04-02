void *my_bsearch(const void *key, const void *base,
	size_t nmemb, size_t size,
	int(*compar)(const void *, const void *));

void test();

int int_compfun(const void *,const void*);

int float_compfun(const void *, const void*);