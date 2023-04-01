#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#define IGNORE(x) (void)(x)
#define BUFFER_SIZE 1024

#define FLAG_FOR_PLUS 2
#define FLAG_FOR_MINUS 1
#define FLAG_FOR_HASH 8
#define FLAG_FOR_SPACE 16
#define FLAG_FOR_ZERO 4

#define SIZE_L 2
#define SIZE_S 1

/**
 * struct format - structure for operation
 * @format: The format.
 * @fn: function.
 */
struct format
{
	char format;
	int (*fn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct format format_type - Structure operation
 *
 * @format: The format.
 * @fm_t: The function associated.
 */
typedef struct format format_type;

int _printf(const char *, ...);
int _print_char(va_list, char[],
				int, int, int, int);
int _print_string(va_list, char[],
				  int, int, int, int);
int _handle_print(const char *, int *, va_list, char[], int, int, int, int);

int _print_int(va_list, char[],
			   int, int, int, int);
int _print_hexadecimal(va_list, char[],
					  int, int, int, int);
int _print_binary(va_list, char[],
				  int, int, int, int);
int _print_unsigned(va_list, char[],
					int, int, int, int);
int _print_octal(va_list, char[],
				int, int, int, int);

int _print_hexa_upper(va_list, char[],
					 int, int, int, int);

int print_hexa(va_list, char[],
			   char[], int, char, int, int, int);

int _print_percent(va_list, char[],
				   int, int, int, int);

int _print_non_printable(va_list, char[],
						int, int, int, int);

int _print_pointer(va_list, char[],
				  int, int, int, int);

int _get_width(const char *, int *i, va_list);

int _get_flags(const char *, int *i);
int _get_precision(const char *, int *i, va_list);
int _get_size(const char *, int *i);

int _print_rot13string(va_list, char[],
					  int, int, int, int);

int _handle_write_char(char c, char[],
					   int, int, int, int);
int write_number(int is_positive, int ind, char[],
				 int, int, int, int);
int write_num(int ind, char bff[], int, int, int,
			  int length, char padd, char extra_c);

int _print_reverse(va_list, char[],
				  int, int, int, int);

int write_pointer(char[], int ind, int length,
				  int, int, char padd, char extra_c, int padd_start);

int write_unsgnd(int is_negative, int ind,
				 char[],
				 int, int, int, int);

int _is_printable(char);
int append_hexa_code(char, char[], int);
int is_digit(char);

long int convert_size_number(long int num, int);
long int convert_size_unsgnd(unsigned long int num, int);

#endif /* MAIN_H */
