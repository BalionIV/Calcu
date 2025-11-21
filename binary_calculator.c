#include <stdio.h>
#include <string.h>
#include <math.h>

void from_decimal(int n, int base) {
	int f = n, cpt = 0;
	char converted[256];

	while(f >= 1) {
		f /= base;
		cpt++;
	}

	converted[cpt] = '\0';

	while(n >= 1) {
		cpt--;

		if(base < 10) converted[cpt] = (n % base) + '0';
		else {
			if((n % base) > 10) converted[cpt] = (n % base) - 10 + 'A';
			else converted[cpt] = (n % base) + '0';
		}

		n /= base;
	}

	printf("Number converted to base %d: %s\n", base, converted);
}

int main() {

	int number, base, option;

	do {
		printf("Choices:\n1- Convert from decimal.\n2- Exit.\n");
		scanf("%d", &option);		

		switch(option) {
		case 1:
			do {
				printf("Enter base (2 to 16) to convert to: ");
				scanf("%d", &base);
			} while(base < 2 || base > 16 || base == 10);

			printf("Enter number to convert to base %d: ", base);
			scanf("%d", &number);

			from_decimal(number, base);
			break;

		case 2:
			break;

		
		default:
			printf("Please choose only from the options below: \n");
			printf("Choices:\n1- Convert from decimal.\n2- Exit.\n");
			scanf("%d", &option);
			break;

		}
	} while(option != 2);

	

	return 0;
}