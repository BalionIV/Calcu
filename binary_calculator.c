#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

bool check_base(char *sn, int base) {

	for(int i = 0; i < strlen(sn); i++) {
		if(((sn[i] >= 'A') &&  (sn[i] - 'A' + 10 >= base)) || ((sn[i] <= '9') && (sn[i] - '0' >= base))) {
			printf("Base incorrect.\n");
			return 0;
		}
	}

	return 1;
}

int ask_base() {
	int base;

	do {
		printf("Enter the base: ");
		scanf("%d", &base);	
	} while(base < 2 || base > 16);

	return base;
} 

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

	if(!check_base(sn, base)) {
			return;
	}

	for(int i = 0; i < strlen(sn); i++) {
		if(sn[i] >= 'A') n += (sn[i] - 'A' + 10) * pow(base, c);
		else n += (sn[i] - '0') * pow(base, c);
	}

	printf("Number in decimal: %d\n", n);
}

void other_addition(char *sn1, char *sn2, char *res, int base) {
    int ret = 0, high, dif = strlen(sn1) - strlen(sn2), rint;

    if(!check_base(sn1, base)) return;
    if(!check_base(sn2, base)) return;

    if(strlen(sn1) > strlen(sn2)) {
    	high = strlen(sn1);
    	memmove(sn2 + dif, sn2, strlen(sn2) + 1);
    	for(int i = 0; i < dif; i++) {printf("a");sn2[i] = '0';}
    }
    else if(strlen(sn2) > strlen(sn1)) {
    	high = strlen(sn2);
    	memmove(sn1 + dif, sn1, strlen(sn2) + 1);
    	for(int i = 0; i < dif; i++) sn1[i] = '0';
    }
	else high = strlen(sn1);
    
    res[high] = '\0';

    for(int i = high - 1; i >= 0; i--) { 
        if((sn1[i] >= 'A') && (sn2[i] >= 'A')) {
            rint = sn1[i] + sn2[i] - (2 * 'A') + 20 + ret;
            ret = 0;
            if(rint >= base) {
                ret = 1;
                rint -= base;
            }
        }
        else if((sn1[i] >= 'A') || (sn2[i] >= 'A')) {
            rint = sn1[i] + sn2[i] - 'A' - '0' + 10 + ret;
            ret = 0;
            if(rint >= base) {
                ret = 1;
                rint -= base;
            }
        }
        else {
            rint = sn1[i] + sn2[i] - (2 * '0') + ret;
            ret = 0;
            if(rint >= base) {
                ret = 1;
                rint -= base;
            }
        }

        if(rint >= 10) res[i] = rint + 'A' - 10;
        else res[i] = rint + '0';

        if(i == 0 && ret == 1) {
        	memmove(res + 1, res, high + 1);
    		res[0] = '1';
    	}
    }
}

int main() {

	int number, base, option;
	char snumber1[256], snumber2[256], resultat[256];

	do {
		printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal. \n3- Addition in any base. \n4- Exit.\n");
		scanf("%d", &option);		

		switch(option) {
		case 1:
			base = ask_base();

			printf("Enter number to convert to base %d: ", base);
			scanf("%d", &number);

			from_decimal(number, base);
			break;

		case 2:
			base = ask_base();

			printf("Enter number to convert from base %d: ", base);
			scanf("%s", snumber1);

			to_decimal(snumber1, base);
			break;

		case 3:
            base = ask_base();

            printf("Enter the numbers: ");
            scanf("%s %s", snumber1, snumber2);

            other_addition(snumber1, snumber2, resultat, base);
            printf("Result: %s\n", resultat);
			break;

		case 4:
			break;
			
		default:
			printf("Please choose only from the options below: \n");
			printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal. \n3- Addition in any base. \n4- Exit.\n");
			scanf("%d", &option);
			break;

		}
	} while(option != 4);

	return 0;
}