#include "../includes/ft_printf.h"

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
			process_format_specifier(ap, &specifier, &length);
		}
		else
		{
			length += write(1, format++, 1);
		}
	}
	return (length);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		length;

	va_start(ap, format);
	length = ft_printf_internal(format, &ap);
	va_end(ap);
	return (length);
}
