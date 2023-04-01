#include "main.h"

/**
 * _handle_write_char - Prints a string
 * @width: width.
 * @precision: precision
 * @size: Size
 * @c: char types.
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags.
 * Return: Number of chars printed.
 */
int _handle_write_char(char c, char buffer[],
					   int flags, int width, int precision, int size)
{
	int first_index = 0;
	char padding = ' ';

	IGNORE(precision);
	IGNORE(size);

	if (flags & FLAG_FOR_ZERO)
		padding = '0';

	buffer[first_index++] = c;
	buffer[first_index] = '\0';

	if (width > 1)
	{
		buffer[BUFFER_SIZE - 1] = '\0';
		for (first_index = 0; first_index < width - 1; first_index++)
			buffer[BUFFER_SIZE - first_index - 2] = padding;

		if (flags & FLAG_FOR_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFFER_SIZE - first_index - 1], width - 1));
		else
			return (write(1, &buffer[BUFFER_SIZE - first_index - 1], width - 1) +
					write(1, &buffer[0], 1));
	}

	return (write(1, &buffer[0], 1));
}

/**
 * write_number - Prints a string
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: precision specifier
 * @size: Size specifier
 * @is_negative: Lista of arguments
 * @second_index: char types.
 * @buffer: Buffer array to handle print
 *
 * Return: Number of chars printed.
 */
int write_number(int is_negative, int second_index, char buffer[],
				 int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - second_index - 1;
	char padding = ' ', extra_ch = 0;

	IGNORE(size);

	if ((flags & FLAG_FOR_ZERO) && !(flags & FLAG_FOR_MINUS))
		padding = '0';
	if (is_negative)
		extra_ch = '-';
	else if (flags & FLAG_FOR_PLUS)
		extra_ch = '+';
	else if (flags & FLAG_FOR_SPACE)
		extra_ch = ' ';

	return (write_num(second_index, buffer, flags, width, precision,
					  length, padding, extra_ch));
}
/**
 * write_unsgnd - Writes an unsigned number
 * @is_negative: Number indicating if the num is negative
 * @second_index: Index at which the number starts in the buffer
 * @buffer: Array of chars
 * @flags: Flags specifiers
 * @width: Width specifier
 * @precision: Precision specifier
 * @size: Size specifier
 *
 * Return: Number of written chars.
 */
int write_unsgnd(int is_negative, int second_index,
				 char buffer[],
				 int flags, int width, int precision, int size)
{
	int length = BUFFER_SIZE - second_index - 1, first_index = 0;
	char padding = ' ';

	IGNORE(is_negative);
	IGNORE(size);

	if (precision == 0 && second_index == BUFFER_SIZE - 2 && buffer[second_index] == '0')
		return (0);

	if (precision > 0 && precision < length)
		padding = ' ';

	while (precision > length)
	{
		buffer[--second_index] = '0';
		length++;
	}

	if ((flags & FLAG_FOR_ZERO) && !(flags & FLAG_FOR_MINUS))
		padding = '0';

	if (width > length)
	{
		for (first_index = 0; first_index < width - length; first_index++)
			buffer[first_index] = padding;

		buffer[first_index] = '\0';

		if (flags & FLAG_FOR_MINUS)
		{
			return (write(1, &buffer[second_index], length) + write(1, &buffer[0], first_index));
		}
		else
		{
			return (write(1, &buffer[0], first_index) + write(1, &buffer[second_index], length));
		}
	}

	return (write(1, &buffer[second_index], length));
}

/**
 * write_num - Write a number using a bufffer
 * @second_index: Index at which the number starts on the buffer
 * @buffer: Buffer
 * @flags: Flags
 * @width: width
 * @prec: Precision specifier
 * @length: Number length
 * @padding: Pading char
 * @extra_c: Extra char
 *
 * Return: Number of printed chars.
 */
int write_num(int second_index, char buffer[],
			  int flags, int width, int prec,
			  int length, char padding, char extra_c)
{
	int first_index, padd_start = 1;

	if (prec == 0 && second_index == BUFFER_SIZE - 2 && buffer[second_index] == '0' && width == 0)
		return (0);
	if (prec == 0 && second_index == BUFFER_SIZE - 2 && buffer[second_index] == '0')
		buffer[second_index] = padding = ' ';
	if (prec > 0 && prec < length)
		padding = ' ';
	while (prec > length)
		buffer[--second_index] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (first_index = 1; first_index < width - length + 1; first_index++)
			buffer[first_index] = padding;
		buffer[first_index] = '\0';
		if (flags & FLAG_FOR_MINUS && padding == ' ')
		{
			if (extra_c)
				buffer[--second_index] = extra_c;
			return (write(1, &buffer[second_index], length) +
					write(1, &buffer[1], first_index - 1));
		}
		else if (!(flags & FLAG_FOR_MINUS) && padding == ' ')
		{
			if (extra_c)
				buffer[--second_index] = extra_c;
			return (write(1, &buffer[1], first_index - 1) +
					write(1, &buffer[second_index], length));
		}
		else if (!(flags & FLAG_FOR_MINUS) && padding == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], first_index - padd_start) +
					write(1, &buffer[second_index], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--second_index] = extra_c;
	return (write(1, &buffer[second_index], length));
}

/**
 * write_pointer - Write a memory address
 * @buffer: Arrays of chars
 * @second_index: Index at which the number starts in the buffer
 * @length: Length of number
 * @width: Wwidth specifier
 * @flags: Flags specifier
 * @padding: padding
 * @extra_c: extra char
 * @padd_start: padding start
 *
 * Return: Number of written chars.
 */
int write_pointer(char buffer[], int second_index, int length,
				  int width, int flags, char padding, char extra_c, int padd_start)
{
	int first_index;

	if (width > length)
	{
		for (first_index = 3; first_index < width - length + 3; first_index++)
			buffer[first_index] = padding;
		buffer[first_index] = '\0';
		if (flags & FLAG_FOR_MINUS && padding == ' ')
		{
			buffer[--second_index] = 'x';
			buffer[--second_index] = '0';
			if (extra_c)
				buffer[--second_index] = extra_c;
			return (write(1, &buffer[second_index], length) +
					write(1, &buffer[3], first_index - 3));
		}
		else if (!(flags & FLAG_FOR_MINUS) && padding == ' ')
		{
			buffer[--second_index] = 'x';
			buffer[--second_index] = '0';
			if (extra_c)
				buffer[--second_index] = extra_c;
			return (
				write(1, &buffer[3], first_index - 3) +
				write(1, &buffer[second_index], length));
		}
		else if (!(flags & FLAG_FOR_MINUS) && padding == '0')
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], first_index - padd_start) +
					write(1, &buffer[second_index], length - (1 - padd_start) - 2));
		}
	}
	buffer[--second_index] = 'x';
	buffer[--second_index] = '0';
	if (extra_c)
		buffer[--second_index] = extra_c;
	return (write(1,
				  &buffer[second_index],
				  BUFFER_SIZE - second_index - 1));
}
