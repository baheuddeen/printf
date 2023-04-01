#include "main.h"

/**
 * append_hexa_code - Append ascci in hexadecimal code to buffer
 * @buffer : Array of chars.
 * @i: Index at which to start appending.
 * @ascii_code: ASSCI CODE.
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int i)
{
	char maping[] = "0123456789ABCDEF";

	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[i++] = '\\';
	buffer[i++] = 'x';

	buffer[i++] = maping[ascii_code / 16];
	buffer[i] = maping[ascii_code % 16];

	return (3);
}

/**
 * _is_printable - Evaluates if a char is printable
 * @c: Char to be evaluated.
 *
 * Return: success (1) otherwise 0
 */
int _is_printable(char c)
{
	if (c >= 32 && c < 127)
		return (1);

	return (0);
}

/**
 * is_digit - is it digit?
 *
 * @c: Char to be evaluated
 *
 * Return: 1 if c is a digit, 0 otherwise
 */
int is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_unsgnd - convert
 *
 * @number: Number
 * @size: size.
 *
 * Return: Casted value of number
 */
long int convert_size_unsgnd(unsigned long int number, int size)
{
	if (size == SIZE_L)
		return (number);

	else if (size == SIZE_S)
		return ((unsigned short)number);
	return ((unsigned int)number);
}

/**
 * convert_size_number - Casts a number to the specified size
 * @number: Number to be casted.
 * @size: Number indicating the type to be casted.
 *
 * Return: Casted value of number
 */
long int convert_size_number(long int number, int size)
{
	if (size == SIZE_L)
		return (number);
	else if (size == SIZE_S)
		return ((short)number);

	return ((int)number);
}
