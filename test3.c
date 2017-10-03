#include "../includes/malloc.h"
#include <string.h>

#define M (1024 * 1024)

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr1;
	char *addr3;
	char *addr2;

	addr1 = (char*)malloc(16);
	addr2 = (char*)malloc(100000006);
	strcpy(addr1, "Bonjours\n");
	print(addr1);
	addr3 = (char*)realloc(addr1, 128);
	addr3[127] = 42;
	print(addr3);
	print("\\\\\\\\\\\\\\\\\\\\\\\\\\\\\n");
	dump(1);
	return (0);
}
