#include "../includes/ft_printf.h"

static void	process_base(t_specifier *specifier, unsigned int *base)
{
	if (specifier->type == 'x' || specifier->type == 'X')
		*base = 16U;
	else if (specifier->type == 'o')
		*base = 8U;
	else if (specifier->type == 'b')
		*base = 2U;
	else
	{
		*base = 10U;
		specifier->flags &= ~FLAGS_HASH;
	}
	if (specifier->type == 'X')
		specifier->flags |= FLAGS_UPPERCASE;
	if ((specifier->type != 'i') && (specifier->type != 'd'))
		specifier->flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
	if (specifier->flags & FLAGS_PRECISION)
		specifier->flags &= ~FLAGS_ZEROPAD;
}

static unsigned long long	process_conv_signed(va_list *ap,
											  t_specifier *specifier)
{
	unsigned long long	uvalue;
	long long			value;

	if (specifier->flags & FLAGS_LONG_LONG)
		value = va_arg(*ap, long long);
	else if (specifier->flags & FLAGS_LONG)
		value = va_arg(*ap, long);
	else if (specifier->flags & FLAGS_CHAR)
		value = (char)va_arg(*ap, int);
	else if (specifier->flags & FLAGS_SHORT)
		value = (short int)va_arg(*ap, int);
	else
		value = va_arg(*ap, int);
	if (value < 0)
	{
		specifier->flags |= FLAGS_NEGATIVE;
		uvalue = 0 - value;
	}
	else
		uvalue = value;
	return (uvalue);
}

static unsigned long long	process_conv_unsigned(va_list *ap,
												t_specifier *specifier)
{
	unsigned long long	value;

	if (specifier->flags & FLAGS_LONG_LONG)
		value = va_arg(*ap, unsigned long long);
	else if (specifier->flags & FLAGS_LONG)
		value = va_arg(*ap, unsigned long);
	else if (specifier->flags & FLAGS_CHAR)
		value = (unsigned char)va_arg(*ap, unsigned int);
	else if (specifier->flags & FLAGS_SHORT)
		value = (unsigned short int)va_arg(*ap, unsigned int);
	else
		value = va_arg(*ap, unsigned int);
	return (value);
}

int	process_integer(va_list *ap, t_specifier *specifier)
{
	unsigned long long	value;
	unsigned int		base;

	process_base(specifier, &base);
	if ((specifier->type == 'i') || (specifier->type == 'd'))
		value = process_conv_signed(ap, specifier);
	else
		value = process_conv_unsigned(ap, specifier);
	return (ft_ntoa(specifier, value, base));
}
