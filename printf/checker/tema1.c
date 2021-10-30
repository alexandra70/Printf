#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORD 50

static int write_stdout(const char *token, int length)
{
	int rc;
	int bytes_written = 0;

	do {
		rc = write(1, token + bytes_written, length - bytes_written);
		if (rc < 0)
			return rc;

		bytes_written += rc;
	} while (bytes_written < length);

	return bytes_written;
}

//fct ce inverseaza un string
void reverse_string(char duplic[WORD], int len) {
	int i = len;
	for(int j = 0 ; j < i/2; j ++) {
		char exch = duplic[j];
		//printf("(%c - j, %c - i)", duplic[j], duplic[i - j - 1]); 
		duplic[j] = duplic[i - j - 1];
		duplic[i - j - 1] = exch;
	}
	return;
}

void nr_to_string(int nr, int* len, int base, char duplic[WORD]) {
	
	int cifra;
	int i = 0;

	memset(duplic, 0, WORD);
	unsigned int number = (unsigned int)nr;

	while (1)
	{
		if(number == 0) {
			break;
		}
		cifra = number % base;
		
		if (cifra <= 9) {
			duplic[i] = cifra + '0';
		} else {
			duplic[i] = 'a' + (cifra - 10);
		}
		number = number/base;
		i++;
	}

	*len = i;
	duplic[i] = '\0';

	reverse_string(duplic, i);

	return;
}

void d_to_string(int nr, int* len, int base, char duplic[WORD]) {
	
	int cifra;
	int i = 0;
	unsigned int number = (unsigned int)nr;

	memset(duplic, 0, WORD);

	if(nr < 0) {
		number = 0 - number;
	}

	while (1)
	{
		if(number == 0) {
			break;
		}
		cifra = number % base;
		number = number/base;
	
		if (cifra <= 9) {
			duplic[i] = cifra + '0';
		} else {
			//deci incept de la a plus cat e cifra - 10
			duplic[i] = 'a' + (cifra - 10);
		}
			i++;
	}

	*len = i; //retin lungimea
	duplic[i] = '\0';

	reverse_string(duplic, i);
	return;
}

int iocla_printf(const char *format, ...)
{
	/* TODO */
	va_list args;
	char help_str[WORD];
	char cs[1]; //string in care retin cate un element;
	int arg;
	int len;
	int rval = 0;
	
	va_start(args, format);

	for(int j = 0; j < strlen(format); j++) {

		if(format[j] == '\t') {
			cs[0] = '\t';
			rval += write_stdout(cs, 1);
			continue;
		}

		if(format[j] == '\n') {
			cs[0] = '\n';
			rval += write_stdout(cs, 1);
			continue;
		}

		if(format[j] == '%') {
			j++; // trebuie sa sar la urmatorul sa vad EXACT ce trebuie sa citesc
		
			if(format[j] == '%') { //print just %
				cs[0] = format[j];
				rval += write_stdout(cs, 1);
				continue;
			}

			if(format[j] == 'd') {
				//citesc un int, trebuie sa consum ce e in functia aia;
				arg = va_arg(args, int);
				//pastrez semnul si il criu la standard output
				if(arg < 0) {
					cs[0] = '-';
					rval += write_stdout(cs, 1);
				}
				d_to_string(arg, &len, 10, help_str);
				rval += write_stdout(help_str, len);
				continue;
			}
			if(format[j] == 's') {
				char* s;
				s = (char*)(va_arg(args, char*));
				rval += write_stdout(s, strlen(s));
				continue;
			}
			if(format[j] == 'c') {
				char helper_aux = va_arg(args, int);
				cs[0] = helper_aux;
				rval += write_stdout(cs, 1);
				continue;
			}
			if(format[j] == 'x') {
				arg = va_arg(args, int);
				nr_to_string(arg, &len, 16, help_str);
				rval += write_stdout(help_str, len);
				continue;
			}
			if(format[j] == 'u') {
				arg = va_arg(args, int);
				nr_to_string(arg, &len, 10, help_str);
				rval += write_stdout(help_str, len);
				continue;
			}
		
		}
		else {
			//se afieaza fiecare char din format-string, efectiv se afiseaza la standard output
			cs[0] = format[j];
			rval += write_stdout(cs, 1);
		}
	}

	return rval;
}
