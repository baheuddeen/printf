#include "main.h"

/**
 * _get_width - get width.
 *
 * @format: Formatted string in which to print the arguments.
 * @index: index.
 * @args: args.
 *
 * Return: width.
 */
int _get_width(const char *format, int *index, va_list args)
{
	int curr_i;
	int width = 0;

	for (curr_i = *index + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(args, int);
			break;
		}
		else
			break;
	}
	*index = curr_i - 1;
	return (width);
}
