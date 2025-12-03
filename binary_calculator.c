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


// It checks whether the number is actually in the base given.
bool check_base(char *sn, int base) {

	for(int i = 0; i < strlen(sn); i++) {
		if(((sn[i] >= 'A') &&  (sn[i] - 'A' + 10 >= base)) || ((sn[i] <= '9') && (sn[i] - '0' >= base) && (sn[i] - '0' >= 0))) {
			printf("Base incorrect.\n");
			return 0;
		}
	}

	return 1;
}

// It asks the user for the base.
int ask_base() {
	int base;

	do {
		printf("Enter the base: ");
		scanf("%d", &base);	
	} while(base < 2 || base > 16);

	return base;
} 

// It checks the size of each number and adds 0 so they become of the same length.
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
    	dif = strlen(sn2) - strlen(sn1);
    	memmove(sn1 + dif, sn1, strlen(sn2) + 1);
    	for(int i = 0; i < dif; i++) sn1[i] = '0';
    }
	else high = strlen(sn1);

	return high;
}

// It deletes zeros from the left.
void delete_zeros(char *sn) {
	int b = 0, c, p = 0;

	for(int i = 0; i < strlen(sn); i++) 
		if(sn[i] != '0' && sn[i] != '-') {
			c = i;
			break;
		}

	if(c == 0) return;

	if(sn[0] == '-') b = 1;

	for(int i = c - 1; i >= b; i--) {
		p++;
		for(int j = c; j < strlen(sn); j++) {
			sn[j - p] = sn[j - p + 1];
		}
	}

	sn[strlen(sn) - c] = '\0';
}

// It converts from decimal to any base.
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

// It converts from any base to decimal.
void to_decimal(char *sn, int base) {
	int n = 0, c = strlen(sn) - 1;

	if(!check_base(sn, base)) return;

	for(int i = 0; i < strlen(sn); i++) {
		if(sn[i] >= 'A') n += (sn[i] - 'A' + 10) * pow(base, c);
		else n += (sn[i] - '0') * pow(base, c);
		c--;
	}

	delete_zeros(sn);
	printf("Number in decimal: %d\n", n);
}

// It compares between two numbers of any given base.
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

// It adds two numbers of any given base.
void other_addition(char *sn1, char *sn2, char *res, int base) {
    int carry = 0, size, rint;

    if(!check_base(sn1, base)) {
    	strcpy(res, "NULL\0");
    	return;
    }
    if(!check_base(sn2, base)) {
    	strcpy(res, "NULL\0");
    	return;
    }

    size = check_size(sn1, sn2);
    
    res[size] = '\0';

    for(int i = size - 1; i >= 0; i--) { 
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
        	memmove(res + 1, res, size + 1);
    		res[0] = '1';
    	}
    }
}

// It subtracts two numbers of any given base.
void other_subtraction(char *sn1, char *sn2, char *res, int base) {
	int carry = 0, size, rint, max;

    if(!check_base(sn1, base)) {
    	strcpy(res, "NULL\0");
    	return;
    }
    if(!check_base(sn2, base)) {
    	strcpy(res, "NULL\0");
    	return;
    }

    max = comparison(sn1, sn2, base);
    size = check_size(sn1, sn2);
    res[size] = '\0';

    if(max == 2) {
    	res[0] = '0';
    	res[1] = '\0';
    	return;
    }

    if(max == 1) 
    	for(int i = size - 1; i >= 0; i--) {
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
    	for(int i = size - 1; i >= 0; i--) {
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
       			memmove(res + 1, res, size + 1);
      			res[0] = '-';
      		}
     	}

    delete_zeros(res);
}

// It multiplies two numbers of any given base.
void other_multiplication(char *sn1, char *sn2, char *res, int base) {
	int carry = 0, garbage, size, f = 0, rint, digit;
	char add[256], temp[256];

	if(!check_base(sn1, base)) {
		strcpy(res, "NULL\0");
		return;
	}
	if(!check_base(sn2, base)) {
		strcpy(res, "NULL\0");
		return;
	}

    strcpy(temp, "0\0");

    size = check_size(sn1, sn2);
    garbage = check_size(temp, sn1);

    for(int i = size - 1; i >= 0; i--) {
    	for(int k = size + f - 1; k >= size - 1; k--) add[k] = '0';

    	for(int j = size - 1; j >= 0; j--) {
    		if((sn1[j] >= 'A') && (sn2[i] >= 'A')) rint = (sn1[j] - 'A' + 10) * (sn2[i] - 'A' + 10) + carry;
    		else if(sn1[j] >= 'A') rint = (sn1[j] - 'A' + 10) * (sn2[i] - '0') + carry;
    		else if(sn2[i] >= 'A') rint = (sn1[j] - '0') * (sn2[i] - 'A' + 10) + carry;
    		else rint = (sn1[j] - '0') * (sn2[i] - '0') + carry;
    		
    		digit = rint % - base;
    		if(digit >= 10) add[j] = digit - 10 + 'A';
    		else add[j] = digit + '0';

    		if(rint >= base) carry = rint / base;  
    		else carry = 0;
    	}

    	add[size + f] = '\0';
    	f++;

    	if(carry != 0) {
    		memmove(add + 1, add, size + 1);
    		if(carry >= 10) add[0] = carry - 10 + 'A';
    		else add[0] = carry + '0';
    	}
    	carry = 0;

    	other_addition(temp, add, res, base);
    	if(strcmp(res, "NULL")) return;

     	strcpy(temp, res);
    }

    delete_zeros(res);
}

int main() {
	int number, base, option;
	char snumber1[256], snumber2[256], resultat[256];

	do {
		printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal.\n3- Comparison of two numbers.\n4- Addition in any base.\n5- Subtraction in any base.\n");
		printf("6- Multiplication in any base.\n7- Exit.\n");
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
			printf("6- Multiplication in any base.\n7- Exit.\n");			
			scanf("%d", &option);
			break;

		}
	} while(option != 7);

	return 0;
}