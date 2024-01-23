#include <unistd.h>
#include <stdarg.h>

void	put_str(char *s, int *length)
{
		int i = 0;

		while (s[i])
				*length += write(1, &s[i++], 1);
}

void	put_nbr1(long long num, char *base, int base_num, int *length)
{
		if (num >= base_num)
				put_nbr1(num / base_num, base, base_num, length);
		*length += write(1, &base[num % base_num], 1);
}

void	put_nbr(long long num, char *base, int base_num, int *length)
{
		if (num < 0)
		{
				num *= -1;
				*length += write(1, "-", 1);
		}
		put_nbr1(num, base, base_num, length);
}

int	ft_printf(char *format, ... )
{
		va_list ap;
		int length;

		va_start(ap, format);
		length = 0;
		while (*format)
		{
				if (*format == '%' && (*(format + 1) == 's' || *(format + 1) == 'd' || *(format + 1) == 'x'))
				{
						format++;
						if (*format == 's')
								put_str(va_arg(ap, char *), &length);
						if (*format == 'd')
								put_nbr(va_arg(ap, int), "0123456789", 10, &length);
						if (*format == 'x')
								put_nbr(va_arg(ap, unsigned int), "0123456789abcdef", 16, &length);
				}
				else
						length += write(1, format, 1);
				format++;
		}
		va_end(ap);
		return (length);
}

/*#include <stdio.h>
int main()
{
		int a = 0;
		int b = 0;

		a = ft_printf("%s = %d\n%s = %x\n\n", "decimal", -2147483647, "hexadecimal", -2147483647);
		b = printf("%s = %d\n%s = %x\n\n", "decimal", -2147483647, "hexadecimal", -2147483647);

		printf("my return value = %d\nog return value = %d\n", a, b);
}*/
