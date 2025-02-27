#include <stdio.h>
#include <string.h>
#include <math.h>

int d, base;
char e[100], d1[100], d2[100], add[100];
char alp[] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};

void fromdecimal(int d, int base) {

	int f, c;

	f = d;

	while(f >= 1) {
		f /= base;
		c++;
	}

	e[c] = '\0';

	while(d >= 1) {
		
	 c--;
		
	if(d % base > 9)	e[c] = alp[(d % base) - 10];

	else	e[c] = (d % base) + '0'; 
			
	d /= base;

	}	

	printf("%s", e);

}

void todecimal(char d1[], int base) {

	d = 0;

	for(int i = 0; i < strlen(d1); i++) {
		if(d1[strlen(d1) - i - 1] >= 'A' && d1[strlen(d1) - i] <= 'Z') {
			if((d1[strlen(d1) - i - 1] - 55) > base) {
				printf("Not the correct base. ");
				return;
			}
		
			d += (d1[strlen(d1) - i - 1] - 55) * pow(base, i);	
			
		} 

		else {
			if((d1[strlen(d1) - i - 1] - '0') > base) {
				printf("Not the correct base. ");
				return;					
			}

				d += (d1[strlen(d1) - i - 1] - '0') * pow(base, i);
		}
	}

	if(d > 0)	printf("%d", d);

}

void otheraddition(int base, char d1[], char d2[]) {

	int c;

	base += '0';

	int r = 0;

	if(strlen(d1) > strlen(d2)) {
		c = strlen(d1) - strlen(d2);

		memmove(d2 + c, d2, strlen(d1));

		for(int i = 0; i < c; i++) d2[i] = '0';

	}

	else {
		c = strlen(d2) - strlen(d1);

		memmove(d1 + c, d1, strlen(d2));

		for(int i = 0; i < c; i++) d1[i] = '0';
	}

	for(int i = strlen(d1); i >= 0; i--) {
		e[i] = (d1[i] + d2[i]) - '0' + r;

		r = 0;

		if(e[i] >= base) {
			r = 1;

			e[i] = e[i] - base + '0';

		}
	}

	if(r == 1) {
		memmove(e + 1, e, strlen(e) + 1);
		e[0] = '1';

		e[strlen(d1) + 1] = '\0';
	}

	else	e[strlen(d1)] = '\0';

}

void othersubtraction(int base, char d1[], char d2[]) {

    base += '0';

    int r = 0, c;

    if(strlen(d1) > strlen(d2)) {
        c = strlen(d1) - strlen(d2);

        memmove(d2 + c, d2, strlen(d1));

        for(int i = 0; i < c; i++)	d2[i] = '0';
    }

    else {
        c = strlen(d2) - strlen(d1);

        memmove(d1 + c, d1, strlen(d2));

        for(int i = 0; i < c; i++)	d1[i] = '0';
    }

    for(int i = 0; i < strlen(d1); i++) {;
        if(d1[i] > d2[i]) {
            c = 0;
            break;
        }
        if(d2[i] > d1[i]) {
            c = 1;
            break;
        }
    }

    if(c == 0) {
        for(int i = strlen(d1) - 1; i >= 0; i--) {
        
            d2[i] += r;

            r = 0;

            if(d1[i] >= d2[i])	e[i] = d1[i] - d2[i] + '0';

            else if(d1[i] < d2[i]) {
                e[i] = d1[i] + base - d2[i];
                r = 1;
            }
        }
    }

    else {
        for(int i = strlen(d1) - 1; i >= 0; i--) {
        
            d1[i] += r;

            r = 0;

            if(d2[i] >= d1[i])	e[i] = d2[i] - d1[i] + '0';

            else if(d2[i] < d1[i]) {
                e[i] = d2[i] + base - d1[i];
                r = 1;
            }
        }
    }

    if(c == 1) {
        memmove(e + 1, e, strlen(e) + 1);

        e[0] = '-';
    }

    printf("%s", e);
}

void othermultiplication(int base, char d1[], char d2[]) {

	int r, mul, f = 0, p = 0, strle;

	e[0] = '0';

	for(int i = strlen(d1) - 1; i >= 0; i--) {
		
		int c = strlen(d2) - 1;

		r = 0;

		for(int j = strlen(d2) - 1; j >= 0; j--) {

			mul = (d1[i] - '0') * (d2[j] - '0') + r;
			
			if(mul >= base) add[c] = mul - ((mul / base) * base) + '0';
			else add[c] = mul + '0';

			c--;

			if(mul >= base) {
				r = mul / base;
				f = 1;
			}

			else if(mul < base && f == 1) {
				f = 0;
				r = 0;
			}

			if(j == 0 && r > 0) {
				memmove(add + 1, add, strlen(add) + 1);

				add[0] = r + '0';
			}
		}

		p++;

		strle = strlen(add);

		for(int j = 0; j < p; j++) if(j != 0) add[strle + j - 1] = '0';

		otheraddition(base, add, e);

		memset(add, '\0', sizeof(add));

	}

}

int main() {

	int choice, r = 0, a;

	printf("Choices:\n1- Convert from decimal.\n2- Convert to decimal.\n3- Other base addition.\n4- Other base subtraction. \n5- Other base multiplication.\n");
	scanf("%d", &choice);

	printf("Enter the base: ");
	scanf("%d", &base);

	if(base > 36 || base < 2) {
		printf("Base can't be bigger than 36 or smaller than 2. \n");
		return 0;
	}

	switch(choice) {
		 
		case 1:
			printf("Enter the number: ");
			scanf("%d", &d);

			fromdecimal(d, base);
			break;

		case 2:

			printf("Enter the number: ");
			scanf("%s", &d1);

			todecimal(d1, base);
			break;
	
		case 3:

			printf("Enter the two numbers: ");
			scanf("%s %s", d1, d2);
		
			otheraddition(base, d1, d2);
			printf("%s\n", e);
			break;

		case 4:

			printf("Enter the two numbers: ");
			scanf("%s %s", d1, d2);

			othersubtraction(base, d1, d2);
			break;

		case 5:
			printf("Enter the numbers: ");
			scanf("%s %s", d1, d2);

			othermultiplication(base, d1, d2);
			printf("%s\n", e);
			break;

		default:
		
			printf("Not a choice. \n");
			break;

		}

	return 0;
}