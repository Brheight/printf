#include <stdarg.h>
#include <unistd.h>
#include "main.h"

/**
 * _printf - Produces output according to a format.
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
            else if (*format == 'd' || *format == 'i')
            {
                int num = va_arg(args, int);
                print_number(num);
                count += num_digits(num);
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

    return count;
}

/**
 * print_number - Prints an integer.
 * @num: The integer to print.
 */
void print_number(int num)
{
    if (num < 0)
    {
        write(1, "-", 1);
        num = -num;
    }

    if (num / 10 != 0)
        print_number(num / 10);

    char digit = '0' + (num % 10);
    write(1, &digit, 1);
}

/**
 * num_digits - Calculates the number of digits in an integer.
 * @num: The integer.
 *
 * Return: The number of digits.
 */
int num_digits(int num)
{
    int count = 0;
    if (num == 0)
        return 1;

    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}
