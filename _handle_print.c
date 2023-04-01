#include "main.h"
/**
 * _handle_print - Prints an arg.
 * @format: string o be printed.
 * @args: args of arguments to be printed.
 * @index: index .
 * @buffer: Buffer.
 * @flags: flags
 * @width: width.
 * @precision: Precision
 * @size: Size
 * Return: Success (1) otherwise (2);
 */
int _handle_print(const char *format, int *index, va_list args, char buffer[],
				  int flags, int width, int precision, int size)
{
	int i, unknow_len = 0, printed_chars = -1;
	format_type fmt_types[] = {
		{'i', _print_int}, {'d', _print_int}, {'b', _print_binary},
		{'c', _print_char}, {'s', _print_string}, {'%', _print_percent},
		{'X', _print_hexa_upper}, {'p', _print_pointer}, {'S', _print_non_printable},
		{'u', _print_unsigned},
		{'o', _print_octal},
		{'x', _print_hexadecimal},
		{'r', _print_reverse},
		{'R', _print_rot13string},
		{'\0', NULL}};
	for (i = 0; fmt_types[i].format != '\0'; i++)
		if (format[*index] == fmt_types[i].format)
			return (fmt_types[i].fn(args, buffer, flags, width, precision, size));

	if (fmt_types[i].format == '\0')
	{
		if (format[*index] == '\0')
			return (-1);
		unknow_len += write(1, "%%", 1);
		if (format[*index - 1] == ' ')
			unknow_len += write(1, " ", 1);
		else if (width)
		{
			--(*index);
			while (format[*index] != ' ' && format[*index] != '%')
				--(*index);
			if (format[*index] == ' ')
				--(*index);
			return (1);
		}
		unknow_len += write(1, &format[*index], 1);
		return (unknow_len);
	}
	return (printed_chars);
}
