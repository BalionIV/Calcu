#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

// Je sais qu'il n'est pas nécessaire d'effectuer toutes ces opérations arithmétiques dans leur bases d'origines. 
// Je peux simplement les convertir en décimal puis faire une opération avec des entiers (int)
// Mais je préfére celle ci pour apprendre a résoudre des problémes de manière efficace.

// I know that is not necessary to do all the arithmetic operations in their original bases.
// I could simply convert them to decimal then do them normally using integers
// But I prefer using this way to learn to solve problems effictively

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

int check_size(char *sn1, char *sn2) {
	int high, dif;

	if(strlen(sn1) > strlen(sn2)) {
    	high = strlen(sn1);
    	dif = strlen(sn1) - strlen(sn2);
    	memmove(sn2 + dif, sn2, strlen(sn2) + 1);
    	for(int i = 0; i < dif; i++) sn2[i] = '0';
    }
    else if(strlen(sn2) > strlen(sn1)) {
    	high = strlen(sn2);
    	dif = strlen(sn1) - strlen(sn2);
    	memmove(sn1 + dif, sn1, strlen(sn2) + 1);
    	for(int i = 0; i < dif; i++) sn1[i] = '0';
    }
	else high = strlen(sn1);

	return high;
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

	if(!check_base(sn, base)) return;

	for(int i = 0; i < strlen(sn); i++) {
		if(sn[i] >= 'A') n += (sn[i] - 'A' + 10) * pow(base, c);
		else n += (sn[i] - '0') * pow(base, c);
		c--;
	}

	printf("Number in decimal: %d\n", n);
}

int comparison(char *sn1, char *sn2, int base) {
	if(!check_base(sn1, base)) return -1;
	if(!check_base(sn2, base)) return -1;

	if(strlen(sn1) > strlen(sn2)) return 1;	
	else if(strlen(sn2) > strlen(sn1)) return 0;
	else 
		for(int i = 0; i < strlen(sn1); i++) {
			if(sn1[i] > sn2[i]) return 1;
			else if(sn2[i] > sn1[i]) return 0;
		}

	return 2;
}

void other_addition(char *sn1, char *sn2, char *res, int base) {
    int carry = 0, high, rint;

    if(!check_base(sn1, base)) return;
    if(!check_base(sn2, base)) return;

    high = check_size(sn1, sn2);
    
    res[high] = '\0';

    for(int i = high - 1; i >= 0; i--) { 
        if((sn1[i] >= 'A') && (sn2[i] >= 'A')) {
            rint = sn1[i] + sn2[i] - 2 * 'A' + 20 + carry;
            carry = 0;
            if(rint >= base) {
                carry = 1;
                rint -= base;
            }
        }
        else if((sn1[i] >= 'A') || (sn2[i] >= 'A')) {
            rint = sn1[i] + sn2[i] - 'A' - '0' + 10 + carry;
            carry = 0;
            if(rint >= base) {
                carry = 1;
                rint -= base;
            }
        }
        else {
            rint = sn1[i] + sn2[i] - 2 * '0' + carry;
            carry = 0;
            if(rint >= base) {
                carry = 1;
                rint -= base;
            }
        }

        if(rint >= 10) res[i] = rint + 'A' - 10;
        else res[i] = rint + '0';

        if(i == 0 && carry == 1) {
        	memmove(res + 1, res, high + 1);
    		res[0] = '1';
    	}
    }
}

void other_subtraction(char *sn1, char *sn2, char *res, int base) {
	int carry = 0, high, rint, max;

    if(!check_base(sn1, base)) return;
    if(!check_base(sn2, base)) return;

    max = comparison(sn1, sn2, base);
    high = check_size(sn1, sn2);
    res[high] = '\0';

    if(max == 2) {
    	res[0] = '0';
    	res[1] = '\0';
    	return;
    }

    if(max == 1) 
    	for(int i = high - 1; i >= 0; i--) {
    		if(sn1[i] >= sn2[i] + carry) {
    			if((sn1[i] >= 'A') && (sn2[i] >= 'A')) rint = sn1[i] - (sn2[i] + carry) + 20;
    			else if((sn1[i] >= 'A') || (sn2[i] >= 'A')) rint = sn1[i] - (sn2[i] + carry) - 7;
        		else rint = sn1[i] - (sn2[i] + carry);
        		carry = 0;
        	}
       		else {
        		if((sn1[i] >= 'A') && (sn2[i] >= 'A')) rint = sn1[i] + base - (sn2[i] + carry);
        		else if((sn1[i] >= 'A') || (sn2[i] >= 'A')) rint = sn1[i] + base - (sn2[i] + carry) - 7;
        		else rint = sn1[i] + base - (sn2[i] + carry);
        		carry = 1;
        	}

 	        if(rint >= 10) res[i] = rint - 10 + 'A';
    	    else res[i] = rint + '0';
    	}
    else
    	for(int i = high - 1; i >= 0; i--) {
    		if(sn2[i] >= sn1[i] + carry) {
    			if((sn1[i] >= 'A') && (sn2[i] >= 'A')) rint = sn2[i] - (sn1[i] + carry);
    			else if((sn1[i] >= 'A') || (sn2[i] >= 'A')) rint = sn2[i] - (sn1[i] + carry) - 7;
        		else rint = sn2[i] - (sn1[i] + carry);
        		carry = 0;
        	}
       		else {
        		if((sn1[i] >= 'A') && (sn2[i] >= 'A')) rint = sn2[i] + base - (sn1[i] + carry) + 20;
        		else if((sn1[i] >= 'A') || (sn2[i] >= 'A')) rint = sn2[i] + base - (sn1[i] + carry) - 7;
        		else rint = sn2[i] + base - (sn1[i] + carry);
        		carry = 1;
        	}

 	        if(rint >= 10) res[i] = rint - 10 + 'A';
    	    else res[i] = rint + '0';
    		if(i == 0) {
       			memmove(res + 1, res, high + 1);
      			res[0] = '-';
      		}
     	}
}

void other_multiplication(char *sn1, char *sn2, char *res, int base) {
	int carry = 0, high, rint, digit, cpt;
	char add[256];

    if(!check_base(sn1, base)) return;
    if(!check_base(sn2, base)) return;	

    for(int i = strlen(sn2); i >= 0; i--) {
    	cpt = strlen(sn1) + i;
    	for(int j = strlen(sn1); j >= 0; j--) {
    		if((sn1[i] >= 'A') && (sn2[i] >= 'A')) rint = (sn1[i] - 'A' + 10) * (sn2[i] - 'A' + 10) + carry;
    		else if(sn1[i] >= 'A') rint = (sn1[i] - 'A' + 10) * (sn2[i] - '0') + carry;
    		else if(sn2[i] >= 'A') rint = (sn1[i] - '0') * (sn2[i] - 'A' + 10) + carry;
    		else rint = (sn1[i] - '0') * (sn2[i] - '0') + carry; 

    		digit = rint % base;
    		if(digit >= 10) add[cpt] = digit - 10 + 'A';
    		else add[cpt] = digit + '0';

    		if(rint >= base) carry = rint / base;  
    		else carry = 0;
    		cpt--;
    	}
    }
}

int main() {
	int number, base, option;
	char snumber1[256], snumber2[256], resultat[256];

	do {
		printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal.\n3- Comparison of two numbers.\n4- Addition in any base.\n5- Subtraction in any base.\n");
		printf("6- Multiplication in any base.\n 7- Exit.\n");
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

			printf("Enter the numbers to compare: ");
			scanf("%s %s", snumber1, snumber2);
			int max = comparison(snumber1, snumber2, base);

			if(max == 1) printf("%s is bigger than %s.\n", snumber1, snumber2);
			else if(max == 0) printf("%s is bigger %s.\n", snumber2, snumber1);
			else if(max == 2) printf("They are equal.\n");
			break;

		case 4:
            base = ask_base();

            printf("Enter the numbers: ");
            scanf("%s %s", snumber1, snumber2);

            other_addition(snumber1, snumber2, resultat, base);
            printf("Result: %s\n", resultat);
			break;

		case 5:
			base = ask_base();

			printf("Enter the numbers: ");
			scanf("%s %s", snumber1, snumber2);

			other_subtraction(snumber1, snumber2, resultat, base);
			printf("Result: %s\n", resultat);
			break;

		case 6:
			base = ask_base();

			printf("Enter the numbers: ");
			scanf("%s %s", snumber1, snumber2);

			other_multiplication(snumber1, snumber2, resultat, base);
			printf("Result: %s\n", resultat);
			break;

		case 7:
			break;
			
		default:
			printf("Please choose only from the options below: \n");
			printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal.\n3- Comparison of two numbers.\n4- Addition in any base.\n5- Subtraction in any base.\n");
			printf("6- Multiplication in any base.\n 7- Exit.\n");			
			scanf("%d", &option);
			break;

		}
	} while(option != 6);

	return 0;
}