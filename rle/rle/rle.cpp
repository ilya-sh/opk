#include "rle.h"
#include <stdlib.h>

void check_file(FILE* input, FILE* output)
{
	int i, flag = 0;
	char byte, prev_byte, temp;
	int count[256];
	for (i = 0; i < 256; i++)
		count[i] = 0;
	fread(&prev_byte, 1, 1, input);
	byte = prev_byte;
	temp = 0;
	do
	{
		if (prev_byte == byte)
		{
			temp++;
			if (temp > count[byte])
				count[byte] = temp;
			if (count[byte] > 3)
				flag = 1;
			prev_byte = byte;
		}
		else
		{
			temp = 1;
			prev_byte = byte;
		}
	} while (fread(&byte, 1, 1, input) == 1);
	if (!flag)
	{
		fseek(input, 0, SEEK_SET);
		while (fread(&byte, 1, 1, input))
			fwrite(&byte, 1, 1, output);
		return;
	}
	fseek(input, 0, SEEK_SET);
	comp(input, output);
}

void comp(FILE* input, FILE* output)
{
	int i, k;
	char prefix, byte, prev_byte;
	int min = INT_MAX;
	int count[256];
	for (i = 0; i < 256; i++)
		count[i] = 0;
	while (fread(&byte, 1, 1, input))
	{
		count[byte]++;
	}

	for (i = 0; i < 256; i++)
	{
		if (count[i] < min)
		{
			prefix = i;
			min = count[i];
		}
	}
	
	fwrite(&prefix, 1, 1, output);
	fseek(input, 0, SEEK_SET);

	fread(&prev_byte, 1, 1, input);
	byte = prev_byte;
	k = 0;
	do
	{
		if ((prev_byte == byte) && (k < 255))
		{
			k++;
		}
		else if ((k == 1) && (prev_byte != prefix))
		{
			fwrite(&prev_byte, 1, 1, output);
			prev_byte = byte;
		}
		else
		{
			fwrite(&prefix, 1, 1, output);
			fwrite((void*)&k, 1, 1, output);
			fwrite(&prev_byte, 1, 1, output);
			k = 1;
			prev_byte = byte;
		}
	} while (fread(&byte, 1, 1, input) == 1);
	if (prev_byte == prefix)
	{
		fwrite(&prefix, 1, 1, output);
		fwrite(&k, 1, 1, output);
		fwrite(&prev_byte, 1, 1, output);
	}
	else if (k == 1)
	{
		fwrite(&prev_byte, 1, 1, output);
	}
	else
	{
		fwrite(&prefix, 1, 1, output);
		fwrite(&k, 1, 1, output);
		fwrite(&prev_byte, 1, 1, output);
	}
	
}

void decomp(FILE* input, FILE* output)
{
	char prefix, byte, count, i;
	fread(&prefix, 1, 1, input);
	while (fread(&byte, 1, 1, input))
	{
		if (byte == prefix)
		{
			fread(&count, 1, 1, input);
			fread(&byte, 1, 1, input);
			for (i = 0; i < count; i++)
			{
				fwrite(&byte, 1, 1, output);
			}
		}
		else
			fwrite(&byte, 1, 1, output);
	}
	
}