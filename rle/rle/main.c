#include "rle.h"


int main(int argc, char *argv[])
{
	if (argc != 4)
	{
		printf("Type: rle c/d infile outfile\n");
		return 0;
	}
	char check;
	FILE *input = fopen(argv[2]/*"D:\\in.txt"*/, "rb");
	if (!input)
		return 0;
	if (fread(&check, 1, 1, input) == 1)
	{
		fseek(input, 0, SEEK_SET);
	}
	else
	{
		return 0;
	}
	FILE *output = fopen(argv[3]/*"D:\\out.dat"*/, "wb");
	if (!output)
		return 0;
	/*check_file(input, output);
	fclose(input);
	fclose(output);
	input = fopen("D:\\out.dat", "rb");
	output = fopen("D:\\out1.dat", "wb");
	decomp(input, output);*/
	switch (*argv[1])
	{
	case 'c':
		check_file(input, output);
		break;
	case 'd':
		decomp(input, output);
		break;
	default:
		printf("enter c(compression) or d(decompression)\n");
		break;
	}
	fclose(input);
	fclose(output);
	return 0;
}
