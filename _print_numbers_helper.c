#include "main.h"

/**
 * _print_unsigned - Print unsigned number
 * @args: arguments
 * @buffer: Buffer array to handle print
 * @flags:  formated flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of printed chars.
 */
int _print_unsigned(va_list args, char buffer[],
					int flags, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);

	number = convert_size_unsgnd(number, size);
	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 10) + '0';
		number /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * _print_octal - Prints an unsigned number in octal notation
 * @args: args.
 * @buffer: Buffer.
 * @flags:  flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of printed chars.
 */
int _print_octal(va_list args, char buffer[],
				 int flags, int width, int precision, int size)
{

	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int init_num = number;

	IGNORE(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = (number % 8) + '0';
		number /= 8;
	}

	if (flags & FLAG_FOR_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**
 * _print_hexadecimal - print in hexadecimal.
 * @args: args.
 * @buffer: Buffer.
 * @flags:  flags
 * @width: width
 * @precision: Precision
 * @size: Size
 * Return: Number of printed chars.
 */
int _print_hexadecimal(va_list args, char buffer[],
					   int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789abcdef", buffer,
					   flags, 'x', width, precision, size));
}

/**
 * _print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @args: args.
 * @precision: Precision
 * @size: Size
 * @buffer: Buffer.
 * @flags:  flags
 * @width: width
 * Return: Number of printed chars.
 */
int _print_hexa_upper(va_list args, char buffer[],
					  int flags, int width, int precision, int size)
{
	return (print_hexa(args, "0123456789ABCDEF", buffer,
					   flags, 'X', width, precision, size));
}

/************** PRINT HEXX number IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @args: Lista of arguments
 * @mapper: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list args, char mapper[], char buffer[],
			   int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFFER_SIZE - 2;
	unsigned long int number = va_arg(args, unsigned long int);
	unsigned long int init_num = number;

	IGNORE(width);

	number = convert_size_unsgnd(number, size);

	if (number == 0)
		buffer[i--] = '0';

	buffer[BUFFER_SIZE - 1] = '\0';

	while (number > 0)
	{
		buffer[i--] = mapper[number % 16];
		number /= 16;
	}

	if (flags & FLAG_FOR_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}
	i++;
	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
