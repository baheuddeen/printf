#include "main.h"

/**
 * _get_precision - get precision.
 *
 * @format: Formatted string.
 * @index: index.
 *
 * @args: arguments.
 * Return: Precision
 */
int _get_precision(const char *format, int *index, va_list args)
{
	int current_i = *index + 1;
	int precision = -1;

	if (format[current_i] != '.')
		return (precision);

	precision = 0;

	for (current_i += 1; format[current_i] != '\0'; current_i++)
	{
		if (is_digit(format[current_i]))
		{
			precision *= 10;
			precision += format[current_i] - '0';
		}
		else if (format[current_i] == '*')
		{
			current_i++;
			precision = va_arg(args, int);
			break;
		}
		else
			break;
	}
	*index = current_i - 1;

	return (precision);
}
