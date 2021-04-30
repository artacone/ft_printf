#include "../includes/ft_printf.h"

static int	print_number(va_list *ap, t_specifier *specifier)
{
	int		length;
	char	type;

	type = specifier->type;
	if (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X')
		length = process_integer(ap, specifier);
	else if (type == 'f' || type == 'e' || type == 'g')
		length = process_float(ap, specifier);
	return (length);
}

static int	print_char(va_list *ap, t_specifier *specifier)
{
	unsigned int	l;
	int				length;
	char			c;

	l = 1U;
	length = 0;
	c = (char)va_arg(*ap, int);
	if (!(specifier->flags & FLAGS_LEFT))
	{
		while (l++ < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	length += write(1, &c, 1);
	if (specifier->flags & FLAGS_LEFT)
	{
		while (l++ < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	return (length);
}

static int	print_string(va_list *ap, t_specifier *specifier)
{
	unsigned int	l;
	int				length;
	const char		*str;

	str = va_arg(*ap, char *);
	if (specifier->precision)
		l = ft_strnlen(str, specifier->precision);
	else
		l = ft_strlen(str);
	length = 0;
	if ((specifier->flags & FLAGS_PRECISION) && (l > specifier->precision))
		l = specifier->precision;
	if (!(specifier->flags & FLAGS_LEFT))
		while (l++ < specifier->width)
			length += write(1, " ", 1);
	while ((*str != '\0') && (!(specifier->flags & FLAGS_PRECISION)
			|| specifier->precision--))
		length += write(1, str++, 1);
	if (specifier->flags & FLAGS_LEFT)
	{
		while (l++ < specifier->width)
			length += write(1, " ", 1);
	}
	return (length);
}

static int	print_ptr(va_list *ap, t_specifier *specifier)
{
	unsigned long long	ptr;

	specifier->width = sizeof(void *) * 2U;
	specifier->flags |= FLAGS_ZEROPAD | FLAGS_UPPERCASE;
	ptr = (unsigned long long)va_arg(*ap, void *);
	return (ft_ntoa(specifier, ptr, 16U));
}

void	print_specified(va_list *ap, t_specifier *specifier, int *length)
{
	char	type;
	int 	*n;

	type = specifier->type;
	if (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X'
		|| type == 'f' || type == 'g' || type == 'e')
		*length += print_number(ap, specifier);
	else if (type == 'c')
		*length += print_char(ap, specifier);
	else if (type == 's')
		*length += print_string(ap, specifier);
	else if (type == 'p')
		*length += print_ptr(ap, specifier);
	else if (type == '%')
		*length += write(1, "%", 1);
	else if (type == 'n')
	{
		n = va_arg(*ap, int *);
		*n = *length;
	}
	else
		*length += write(1, &type, 1);
}
