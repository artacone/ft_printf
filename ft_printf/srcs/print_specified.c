#include "../includes/ft_printf.h"

int	print_number(va_list *ap, t_specifier *specifier)
{
	unsigned int	base;
	if (specifier->type == 'x' || specifier->type == 'X')
	{
		base = 16U;
	}
//	else if (specifier->type == 'o')
	else
	{
		base = 10U;
		specifier->flags &= ~FLAGS_HASH;
	}
	if (specifier->type == 'X')
	{
		specifier->flags |= FLAGS_UPPERCASE;
	}
	if ((specifier->type != 'i') && (specifier->type != 'd'))
	{
		specifier->flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
	}
	if (specifier->flags & FLAGS_PRECISION)
	{
		specifier->flags &= ~FLAGS_ZEROPAD;
	}
	// Conversion to ll hh here
	const int value = va_arg(*ap, int);
	int length = ntoa(); // FIXME
	return (length);
}

int	print_char(va_list *ap, t_specifier *specifier)
{
	unsigned int	l;
	int 			length;
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

int	print_string(va_list *ap, t_specifier *specifier)
{
	unsigned int	l;
	int				length;
	const char		*str;


	l = strnlen(str, specifier->precision ? specifier->precision : (size_t)(-1)); //FIXME
	length = 0;
	str = va_arg(*ap, char*);
	if (specifier->flags & FLAGS_PRECISION)
	{
		l = (l < specifier->precision ? l : specifier->precision);
	}
	if (!(specifier->flags & FLAGS_LEFT))
	{
		while (l++ < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	while ((*str != '\0') && ((!specifier->flags & FLAGS_PRECISION) || specifier->precision--))
	{
		length += write(1, str++, 1); // TODO Change for ft_putstr
	}
	if (specifier->flags & FLAGS_LEFT)
	{
		while (l++ < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	return (length);
}

int	print_ptr(va_list *ap, t_specifier *specifier)
{
	int 			length;
	void			*ptr;

	ptr = (void *)va_arg(*ap, void*);
	write(1, "kek", 3); // FIXME
	return (length);
}

int	print_specified(va_list *ap, t_specifier *specifier)
{
	int		length;
	char	type;

	length = 0;
	type = specifier->type;
	// TODO floats
	if (type == 'd' || type == 'i' || type == 'u' || type == 'x' || type == 'X')
		length += print_number(ap, specifier);
	else if (type == 'c')
		length += print_char(ap, specifier);
	else if (type == 's')
		length += print_string(ap, specifier);
	else if (type == 'p')
		length += print_ptr(ap, specifier);
	else if (type == '%')
		length += write(1, "%", 1);
	else
		length += write(1, &type,1);
	return (length);
}
