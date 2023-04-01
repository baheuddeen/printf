#include "main.h"

/**
 * _get_flags - get flags.
 *
 * @format_string: string to print the result.
 * @i: int.
 *
 * Return: Flags:
 */
int _get_flags(const char *format_string, int *i)
{
	int first_counter, current_i;
	int flags = 0;
	const char flags_char[] = {'-', '+', '0', '#', ' ', '\0'};
	const int flags_arr[] = {
		FLAG_FOR_MINUS,
		FLAG_FOR_PLUS,
		FLAG_FOR_ZERO,
		FLAG_FOR_HASH,
		FLAG_FOR_SPACE,
		0};

	for (current_i = *i + 1; format_string[current_i] != '\0'; current_i++)
	{
		for (first_counter = 0; flags_char[first_counter] != '\0'; first_counter++)
			if (format_string[current_i] == flags_char[first_counter])
			{
				flags |= flags_arr[first_counter];
				break;
			}

		if (flags_char[first_counter] == 0)
			break;
	}
	*i = current_i - 1;

	return (flags);
}
