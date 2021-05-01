#include "../includes/ft_printf.h"

static void	process_number(va_list *ap, t_specifier *specifier, int *length)
{
	char	type;

	type = specifier->type;
	if (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X')
		*length += process_integer(ap, specifier);
	else if (type == 'f' || type == 'e' || type == 'g')
		*length += process_float(ap, specifier);
}

static void	process_char(va_list *ap, t_specifier *specifier, int *length)
{
	unsigned int	l;
	char			c;

	l = 1U;
	c = (char)va_arg(*ap, int);
	if (!(specifier->flags & FLAGS_LEFT))
	{
		while (l++ < specifier->width)
			*length += write(1, " ", 1);
	}
	*length += write(1, &c, 1);
	if (specifier->flags & FLAGS_LEFT)
	{
		while (l++ < specifier->width)
			*length += write(1, " ", 1);
	}
}

static void	process_pointer(va_list *ap, t_specifier *specifier, int *length)
{
	unsigned long long	ptr;

	specifier->flags |= FLAGS_HASH | FLAGS_LONG_LONG;
	ptr = (unsigned long long)va_arg(*ap, void *);
	*length += (ft_ntoa(specifier, ptr, 16U));
}

static void	process_percent(t_specifier *specifier, int *length)
{
	unsigned int	l;

	l = 1U;
	if (!(specifier->flags & FLAGS_LEFT))
	{
		if (specifier->flags & FLAGS_ZEROPAD)
		{
			while (l++ < specifier->width)
				*length += write(1, "0", 1);
		}
		while (l++ < specifier->width)
			*length += write(1, " ", 1);
	}
	*length += write(1, "%", 1);
	if (specifier->flags & FLAGS_LEFT)
	{
		while (l++ < specifier->width)
			*length += write(1, " ", 1);
	}
}

void	process_format_specifier(va_list *ap,
							  t_specifier *specifier, int *length)
{
	char	type;
	int		*n;

	type = specifier->type;
	if (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X'
		|| type == 'f' || type == 'g' || type == 'e')
		process_number(ap, specifier, length);
	else if (type == 'c')
		process_char(ap, specifier, length);
	else if (type == 's')
		process_string(ap, specifier, length);
	else if (type == 'p')
		process_pointer(ap, specifier, length);
	else if (type == '%')
		process_percent(specifier, length);
	else if (type == 'n')
	{
		n = va_arg(*ap, int *);
		*n = *length;
	}
	else
		*length += write(1, &type, 1);
}
