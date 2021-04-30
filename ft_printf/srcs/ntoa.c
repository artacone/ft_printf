#include "../includes/ft_printf.h"


static void	ntoa_format_handle_hash(t_specifier *specifier, char *buf,
								   size_t *buf_index, unsigned int base)
{
	if (specifier->flags & FLAGS_HASH)
	{
		if (!(specifier->flags & FLAGS_PRECISION)
			&& *buf_index && ((*buf_index == specifier->precision)
				|| *buf_index == specifier->width))
		{
			(*buf_index)--;
			if (*buf_index && (base == 16U))
				(*buf_index)--;
		}
		if ((base == 16U) && !(specifier->flags & FLAGS_UPPERCASE)
			&& (*buf_index < NTOA_BUFFER_SIZE))
			buf[(*buf_index)++] = 'x';
		else if ((base == 16U) && (specifier->flags & FLAGS_UPPERCASE)
			&& (*buf_index < NTOA_BUFFER_SIZE))
			buf[(*buf_index)++] = 'X';
		if (*buf_index < NTOA_BUFFER_SIZE)
			buf[(*buf_index)++] = '0';
	}
}

static size_t	ntoa_format(t_specifier *specifier, char *buf, size_t buf_index,
						 unsigned int base)
{
	if (!(specifier->flags & FLAGS_LEFT))
	{
		if (specifier->width && (specifier->flags & FLAGS_ZEROPAD)
			&& ((specifier->flags & FLAGS_NEGATIVE)
				|| (specifier->flags & (FLAGS_PLUS | FLAGS_SPACE))))
			specifier->width--;
		while ((buf_index < specifier->precision)
			&& (buf_index < NTOA_BUFFER_SIZE))
			buf[buf_index++] = '0';
		while ((specifier->flags & FLAGS_ZEROPAD)
			&& (buf_index < specifier->width)
			   && (buf_index < NTOA_BUFFER_SIZE))
			buf[buf_index++] = '0';
	}
	ntoa_format_handle_hash(specifier, buf, &buf_index, base);
	if (buf_index < NTOA_BUFFER_SIZE)
	{
		if (specifier->flags & FLAGS_NEGATIVE)
			buf[buf_index++] = '-';
		else if (specifier->flags & FLAGS_PLUS)
			buf[buf_index++] = '+';
		else if (specifier->flags & FLAGS_SPACE)
			buf[buf_index++] = ' ';
	}
	return (print_buf_rev(specifier, buf, buf_index));
}

size_t	ft_ntoa(t_specifier *specifier, unsigned long long value,
					  unsigned int base)
{
	char	buf[NTOA_BUFFER_SIZE];
	size_t	buf_index;
	char	*digits;
	int		uppercase;

	buf_index = 0U;
	uppercase = 0;
	digits = "0123456789abcdef0123456789ABCDEF";
	if (!value)
		specifier->flags &= ~FLAGS_HASH;
	if (!(specifier->flags & FLAGS_PRECISION) || value)
	{
		if (specifier->flags & FLAGS_UPPERCASE)
			uppercase = 16;
		buf[buf_index++] = digits[(char)(value % base) + uppercase];
		value /= base;
		while (value && (buf_index < NTOA_BUFFER_SIZE))
		{
			buf[buf_index++] = digits[(char)(value % base) + uppercase];
			value /= base;
		}
	}
	return (ntoa_format(specifier, buf, buf_index, base));
}
