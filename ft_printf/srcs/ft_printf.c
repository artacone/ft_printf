#include "../includes/ft_printf.h"

// format specifier %[flags][width][.precision][length]type
static int	ft_printf_internal(const char *format, va_list *ap)
{
	int			length;
	t_specifier	specifier;

	length = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			parse_format_specifier(&format, ap, &specifier);
			length += print_specified(ap, &specifier);
		}
		else
		{
			length += write(1, format++, 1); // Change for ft_putchar()???; write protection???
		}
	}
	return (length);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap; // Argument pointer
	int		length;

	va_start(ap, format); // Point ap to the first unnamed argument
	length = ft_printf_internal(format, &ap);
	va_end(ap);
	return (length);
}