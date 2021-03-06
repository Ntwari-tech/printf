#include <unistd.h>
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
/**
 * _printf - produces output according to the format
 *@format: accepts all types of specifiers that are created
 *Return: length of the output
 *
 */

int printChar(va_list args);
int printString(va_list args);
int printPercentage(va_list args);
int printInteger(va_list args);

int _printf(const char *format, ...)
{
	unsigned int i;
	int ans = 0;
	va_list args; 
	pt types[] ={ 
		{"c", printChar},
		{"s", printString},
		{"%", printPercentage},
		{"d", printInteger},
		{"i", printInteger},
		{NULL, NULL}
	};
	int notfound = 1;
	if (format == NULL || (*format == '%' && *(format + 1) == '\0'))
		return (-1);
	va_start(args, format);
	while (format != NULL && *format != '\0')
	{
		if (*format == '%')
		{
			format++;
		for (i = 0; types[i].form != NULL; i++)
		{
		if (*format == *(types[i].form))
		{
			ans += types[i].f(args);
			format++;
			notfound = 0;
			break;
		}
		}
		
		if (notfound)
			ans += write(1, format++, 1);
		}
	
	else
	{
		ans += write(1, format++, 1);
	}
}
va_end(args);
return(ans);
}

/**
 * printChar - Print a character
 * @args: Argument passed
 * Return: length of data
 */
int printChar(va_list args)
{
	char c = va_arg(args, int);
	return (write(1, &c, 1));
}
/**
 * printString - Print a string
 * @args: Argument passed
 * Return: length of data;
 */

int printString(va_list args)
{
	char *str = va_arg(args, char *);
	int size;
	
	if (str == NULL)
		str = "(null)";
	size = _strlen(str);
	return (write(1, str, size));
}
/**
 * printPercentage - Prints a percent
 * @args: Argument passed
 * Return: length of data
 */

int printPercentage(va_list args)
{
	char p = '%';
	(void) args;
	return (write(1, &p, 1));
}
/**
 * printInteger - Prints an interger
 * @args: Argument passed
 * Return: length of data
 */
int printInteger(va_list args)
{
	char buff[33];
	char *str;
	int num = va_arg(args, int);
	int size;	
	str = itoa(num, buff, 10);
	size = _strlen(str);
	return (write(1, str, size));
}
/**
 * _strlen - Count the number of chars in a string
 * @s: String given
 * Return: Length of string
 */
int _strlen(const char *s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;

	return (i);
}
