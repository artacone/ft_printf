#include "../includes/ft_printf.h"

int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

unsigned int	ft_printf_atoi(const char **str)
{
	unsigned int	i;

	i = 0U;
	while (ft_isdigit(**str))
	{
		i = i * 10U + (unsigned int)(*((*str)++) - '0');
	}
	return (i);
}

size_t	print_buf_rev(t_specifier *specifier, char *buf, size_t buf_index)
{
	size_t	length;
	size_t	i;

	length = 0;
	if (!(specifier->flags & FLAGS_LEFT) && !(specifier->flags & FLAGS_ZEROPAD))
	{
		i = buf_index;
		while (i++ < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	while (buf_index)
	{
		length += write(1, &buf[--buf_index], 1);
	}
	if (specifier->flags & FLAGS_LEFT)
	{
		while (length < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	return (length);
}
