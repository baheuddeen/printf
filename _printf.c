#include "main.h"

void _print_buffer(char buffer[], int *buffer_index);


/**
 * _print_buffer - Print the buffer.
 * @buffer: Array of chars
 * @buffer_index: Index.
 */
void _print_buffer(char buffer[], int *buffer_index)
{
	if (*buffer_index > 0)
		write(1, &buffer[0], *buffer_index);
	*buffer_index = 0;
}

/**
 * _printf - Printf function
 * @format:format.
 * Return: chars_prt chars.
 */
int _printf(const char *format, ...)
{
	int index, chars_prt = 0, prt_chars = 0;
	int precision, flags, width, size, buffer_index = 0;
	va_list args;
	char buffer[BUFFER_SIZE];

	if (format == NULL)
		return (-1);

	va_start(args, format);
	for (index = 0; format && format[index] != '\0'; index++)
	{
		if (format[index] != '%')
		{
			buffer[buffer_index++] = format[index];
			if (buffer_index == BUFFER_SIZE)
				_print_buffer(buffer, &buffer_index);
			prt_chars++;
		}
		else
		{
			_print_buffer(buffer, &buffer_index);
			flags = _get_flags(format, &index);
			width = _get_width(format, &index, args);
			precision = _get_precision(format, &index, args);
			size = _get_size(format, &index);
			++index;
			chars_prt = _handle_print(format, &index, args, buffer,
									  flags, width, precision, size);
			if (chars_prt == -1)
				return (-1);
			prt_chars += chars_prt;
		}
	}

	_print_buffer(buffer, &buffer_index);

	va_end(args);

	return (prt_chars);
}
