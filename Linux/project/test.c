#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>

int test(void) {
	fprintf(stderr, "error: xxx.\n");
	char dest[1024];
	int a = 10;
	double b = 0.2;
	char *str = "hello!";

	sprintf(dest, "a = %d, b = %.2f, str = %s", a, b, str);
	puts(dest);

	FILE *fp = fopen("1.txt", "w");
	if (fp == NULL) {
		fprintf(stderr, "failed to open file.\n");
		exit(-1);
	}
	fprintf(fp, "str = %s, a = %d, b = %.2f", str, a, b);
	fclose(fp);

	FILE *fp2 = fopen("1.txt", "r");
	if (fp2 == NULL) {
		fprintf(stderr, "failed to open file.\n");
		exit(-1);
	}
	int var1;
	double var2;
	char var3[1024];
	fscanf(fp2, "str = %[^,], a = %d, b = %lf", var3, &var1, &var2);

	// ¸ñÊ½µÄ¶Á×Ö·û´®dest
	int num1;
	double num2;
	char str2[1024];
	sscanf(dest, "a = %d, b = %lf, str = %s", &num1, &num2, str2);

	return 0;
}