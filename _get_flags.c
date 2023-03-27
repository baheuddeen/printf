/*
 * Auth: Muhammad Baheuddeen- Salma Wagdy
 */
#include "main.h"

/**
 * _get_flags - Calculates active flags
 * @format: Formatted string in which to print the arguments
 * @i: take a parameter.
 * Return: Flags:
 */
int _get_flags(const char *format, int *i)
{
	int j, current_i;
	int flags = 0;
	const char flags_char[] = {'-', '+', '0', '#', ' ', '\0'};
	const int flags_arr[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (current_i = *i + 1; format[current_i] != '\0'; current_i++)
	{
		for (j = 0; flags_char[j] != '\0'; j++)
			if (format[current_i] == flags_char[j])
			{
				flags |= flags_arr[j];
				break;
			}

		if (flags_char[j] == 0)
			break;
	}

	*i = current_i - 1;
	return (flags);
}
