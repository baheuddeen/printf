#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * _print_pointer - Prints pointer.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * Return: Number of chars printed.
 */
int _print_pointer(va_list args, char buffer[],
				   int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int index = BUFFER_SIZE - 2, length = 2, padd_start = 1;
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(args, void *);

	IGNORE(width);
	IGNORE(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFFER_SIZE - 1] = '\0';
	IGNORE(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[index--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & FLAG_FOR_ZERO) && !(flags & FLAG_FOR_MINUS))
		padd = '0';
	if (flags & FLAG_FOR_PLUS)
		extra_c = '+', length++;
	else if (flags & FLAG_FOR_SPACE)
		extra_c = ' ', length++;

	index++;
	return (write_pointer(buffer, index, length,
						  width, flags, padd, extra_c, padd_start));
}

/**
 * _print_non_printable - Prints non printable.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * Return: Number of chars printed
 */
int _print_non_printable(va_list args, char buffer[],
						 int flags, int width, int precision, int size)
{
	int first_counter = 0, offset = 0;
	char *string = va_arg(args, char *);

	IGNORE(flags);
	IGNORE(width);
	IGNORE(precision);
	IGNORE(size);

	if (string == NULL)
		return (write(1, "(null)", 6));

	while (string[first_counter] != '\0')
	{
		if (_is_printable(string[first_counter]))
			buffer[first_counter + offset] = string[first_counter];
		else
		{
			offset += append_hexa_code(
				string[first_counter], buffer, first_counter + offset);
		}
		first_counter++;
	}

	buffer[first_counter + offset] = '\0';

	return (write(1, buffer, first_counter + offset));
}

/**
 * _print_reverse - Prints string before reverse order.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * Return: Numbers of printed chars
 */

int _print_reverse(va_list args, char buffer[],
				   int flags, int width, int precision, int size)
{
	char *string;
	int first_counter, c = 0;

	IGNORE(buffer);
	IGNORE(flags);
	IGNORE(width);
	IGNORE(size);

	string = va_arg(args, char *);

	if (string == NULL)
	{
		IGNORE(precision);

		string = ")Null(";
	}
	for (first_counter = 0; string[first_counter]; first_counter++)
		;

	for (first_counter = first_counter - 1; first_counter >= 0; first_counter--)
	{
		char z = string[first_counter];

		write(1, &z, 1);
		c++;
	}
	return (c);
}

/**
 * _print_rot13string - Print a string before rot13.
 * @width: width.
 * @precision: Precision.
 * @size: Size.
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * Return: Numbers of printed chars
 */
int _print_rot13string(va_list args, char buffer[],
					   int flags, int width, int precision, int size)
{
	char number;
	char *string;
	unsigned int first_counter, second_counter;
	int c = 0;
	char before[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char after[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	string = va_arg(args, char *);
	IGNORE(buffer);
	IGNORE(flags);
	IGNORE(width);
	IGNORE(precision);
	IGNORE(size);

	if (string == NULL)
		string = "(AHYY)";
	for (first_counter = 0; string[first_counter]; first_counter++)
	{
		for (second_counter = 0; before[second_counter]; second_counter++)
		{
			if (before[second_counter] == string[first_counter])
			{
				number = after[second_counter];
				write(1, &number, 1);
				c++;
				break;
			}
		}
		if (!before[second_counter])
		{
			number = string[first_counter];
			write(1, &number, 1);
			c++;
		}
	}
	return (c);
}
