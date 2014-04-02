#include "stdafx.h"
#include "my_bsearch.h"
#include <assert.h>

void test()
{
	int int_a[10] = { -256, -128, -64, -32, -16, -16, 
	-8, -4, -2, 0};
	float float_a[11] = { -256, -128, -64, -32, -16, -16,
	-8, -4, -2, 0, 42};
	int int_key = -16;
	assert(my_bsearch(&int_key, int_a, 10, sizeof(int), int_compfun));
	float float_key = 42;
	assert(my_bsearch(&float_key, float_a, 11, sizeof(float), float_compfun));
	float_key = 1024;
	assert(!my_bsearch(&float_key, float_a, 11, sizeof(float), float_compfun));
	assert(!my_bsearch(&float_key, float_a, 0, sizeof(float), float_compfun));

}