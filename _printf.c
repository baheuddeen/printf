/*
 * Auth: Muhammad Baheuddeen - Salma Wagdy
 */
#include "main.h"

void _print_buffer(char buffer[], int *buffer_index);

/**
 * _printf - Printf function
 * @format:format.
 * Return: Printed chars.
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buffer_index = 0;
	va_list args;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buffer_index++] = format[i];
			if (buffer_index == BUFFER_SIZE)
				_print_buffer(buffer, &buffer_index);
			printed_chars++;
		}
		else
		{
			_print_buffer(buffer, &buffer_index);
			flags = _get_flags(format, &i);
			width = _get_width(format, &i, args);
			precision = _get_precision(format, &i, args);
			size = _get_size(format, &i);
			++i;
			printed = _handle_print(format, &i, args, buffer,
				flags, width, precision, size);
			if (printed == -1)
				return (-1);
			printed_chars += printed;
		}
	}

	_print_buffer(buffer, &buffer_index);

	va_end(args);

	return (printed_chars);
}

/**
 * _print_buffer - Prints the contents of the buffer if it exist
 * @buffer: Array of chars
 * @buffer_index: Index at which to add next char, represents the length.
 */
void _print_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);

	*buffer_index = 0;
}
