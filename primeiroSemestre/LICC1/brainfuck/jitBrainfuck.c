#include <stdio.h>
int main() {
	char mem[30000];
	int i = 0;
	for (int j = 0; j < 30000; j++) {
		mem[j] = 0;
	}

	while(mem[i]) {
		mem[i]++;
		putchar(mem[i]);
		putchar(mem[i]);
		putchar(mem[i]);
		putchar(mem[i]);
		i++;
		i++;
		i--;
		i++;
		i--;
		i++;
		i--;
		i++;
		i--;
		i++;
		i--;
		i++;
		i--;
		i++;
		}
		
	printf("\n");
	for (int j = 0; j < 30000; j++) {
		if (mem[j] != 0) {
			printf("%d", mem[j]);
		}
	}
	printf("\n");
	return 0;
}