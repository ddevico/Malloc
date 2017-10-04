#include "../includes/malloc.h"
#include <string.h>
#include <stdio.h>

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr2;
	char *addr3;

	addr1 = (char*)malloc(2000);
	addr2 = (char*)malloc(20);
	printf("%s\n", addr1);
	free(addr1);
	show_alloc_mem();
	free(addr1);
	free(addr2);
	show_alloc_mem();
	return (0);
}
