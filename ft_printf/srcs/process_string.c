#include "../includes/ft_printf.h"

static size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*str;

	str = s;
	while (*str && maxlen--)
	{
		str++;
	}
	return (str - s);
}

static size_t	ft_strlen(const char *s)
{
	const char	*str;

	str = s;
	while (*str)
	{
		str++;
	}
	return (str - s);
}

void	process_string(va_list *ap, t_specifier *specifier, int *length)
{
	unsigned int	l;
	const char		*str;

	str = va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	if (specifier->precision)
		l = ft_strnlen(str, specifier->precision);
	else
		l = ft_strlen(str);
	if ((specifier->flags & FLAGS_PRECISION) && (l > specifier->precision))
		l = specifier->precision;
	if (!(specifier->flags & FLAGS_LEFT))
		while (l++ < specifier->width)
			*length += write(1, " ", 1);
	while ((*str != '\0') && (!(specifier->flags & FLAGS_PRECISION)
			|| specifier->precision--))
		*length += write(1, str++, 1);
	if (specifier->flags & FLAGS_LEFT)
	{
		while (l++ < specifier->width)
			*length += write(1, " ", 1);
	}
}
