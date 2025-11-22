#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

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
			if((n % base) >= 10) converted[cpt] = (n % base) - 10 + 'A';
			else converted[cpt] = (n % base) + '0';
		}

		n /= base;
	}

	printf("Number converted to base %d: %s\n", base, converted);
}

void to_decimal(char *sn, int base) {

	int n = 0, c = strlen(sn) - 1;

	for(int i = 0; i < strlen(sn); i++) {
		if(((sn[i] >= 'A') &&  (sn[i] - 'A' + 10 >= base)) || ((sn[i] <= '9') && (sn[i] - '0' >= base))) {
			printf("Base incorrect.\n");
			return;
		}

		if(sn[i] >= 'A') n += (sn[i] - 'A' + 10) * pow(base, c);
		else n += (sn[i] - '0') * pow(base, c);
	}

	printf("Number in decimal: %d\n", n);
}

int main() {

	int number, base, option;
	char snumber[256];

	do {
		printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal. \n3- Exit.\n");
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
			do {
				printf("Enter base (2 to 16) to convert from: ");
				scanf("%d", &base);	
			}	while(base < 2 || base > 16 || base == 10);

			printf("Enter number to convert from base %d: ", base);
			scanf("%s", snumber);

			to_decimal(snumber, base);
			break;

		case 3:
			break;

		
		default:
			printf("Please choose only from the options below: \n");
			printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal.\n3- Exit.\n");
			scanf("%d", &option);
			break;

		}
	} while(option != 3);

	return 0;
}