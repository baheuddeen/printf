#include "main.h"

/**
 * _get_size - get size.
 * @format: strin to be printed.
 * @index: current index.
 * Return: size.
 */
int _get_size(const char *format, int *index)
{
	int curr_i = *index + 1;
	int size = 0;

	if (format[curr_i] == 'l')
		size = SIZE_L;
	else if (format[curr_i] == 'h')
		size = SIZE_S;

	if (size == 0)
		*index = curr_i - 1;
	else
		*index = curr_i;

	return (size);
}
