#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Produces output according to a specified format.
 * @format: Format string.
 *
 * Return: Number of characters printed (excluding null byte).
 */

int _printf(const char *format, ...)
{
	va_list args;
	int count = 0;

	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == 'c')
			{
				char c = (char)va_arg(args, int);

				write(1, &c, 1);
				count++;
			}
			else if (*format == 's')
			{
				char *str = va_arg(args, char *);

				while (*str)
				{
					write(1, str, 1);
					str++;
					count++;
				}
			}
			else if (*format == '%')
			{
				write(1, "%", 1);
				count++;
			}
			else
			{
				write(1, "%", 1);
				write(1, format, 1);
				count += 2;
			}
		}
		else
		{
			write(1, format, 1);
			count++;
		}
		format++;
	}
	va_end(args);
	return (count);
}
