#include "../includes/ft_printf.h"

static void	process_int_base(t_specifier *specifier, unsigned int *base)
{
	if (specifier->type == 'x' || specifier->type == 'X')
		*base = 16U;
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
											  t_specifier *specifier,
											  int *is_negative)
{
	unsigned long long	uvalue;
	long long	value;

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
		*is_negative = 1;
		uvalue = 0 - value;
	}
	else
		uvalue = value;
	return (uvalue);
}

static unsigned long long	process_conv_unsigned(va_list *ap,
												t_specifier *specifier)
{
	unsigned long long	uvalue;

	if (specifier->flags & FLAGS_LONG_LONG)
		uvalue = va_arg(*ap, unsigned long long);
	else if (specifier->flags & FLAGS_LONG)
		uvalue = va_arg(*ap, unsigned long);
	else if (specifier->flags & FLAGS_CHAR)
		uvalue = (unsigned char)va_arg(*ap, unsigned int);
	else if (specifier->flags & FLAGS_SHORT)
		uvalue = (unsigned short int)va_arg(*ap, unsigned int);
	else
		uvalue = va_arg(*ap, unsigned int);
	return (uvalue);
}

int	process_int(va_list  *ap, t_specifier *specifier)
{
	unsigned long long	value;
	int 				is_negative;
	int					length;
	unsigned int		base;

	is_negative = 0;
	process_int_base(specifier, &base);
	if ((specifier->type == 'i') || (specifier->type == 'd'))
		value = process_conv_signed(ap, specifier, &is_negative);
	else
		value = process_conv_unsigned(ap, specifier);
	length = ft_ntoa_long_long(specifier, value, is_negative, base);
	return (length);
}