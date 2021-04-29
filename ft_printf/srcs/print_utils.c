#include "../includes/ft_printf.h"

// Put it in libft
size_t	ft_strnlen(const char *s, size_t maxlen)
{
	const char	*str;

	str = s;
	while (*str && maxlen--)
	{
		str++;
	}
	return (str - s);
}
// Took it from libft
int	ft_isdigit(int c)
{
	return ('0' <= c && c <= '9');
}

unsigned int ft_printf_atoi(const char **str)
{
	unsigned int	i;

	i = 0U;
	while (ft_isdigit(**str))
	{
		i = i * 10U + (unsigned int)(*((*str)++) - '0');
	}
	return (i);
}

//return (print_buf_rev(specifier, buf, len));
static size_t	print_buf_rev(t_specifier *specifier, char *buf, size_t len)
{
	size_t	length;
	size_t	i;

	length = 0;
	if (!(specifier->flags & FLAGS_LEFT) && !(specifier->flags & FLAGS_ZEROPAD))
	{
		i = len;
		while (i++ < specifier->width)
		{
			length += write(1, " ", 1);
		}
	}
	while (len)
	{
		length += write(1, &buf[--len], 1);
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

static size_t	ft_ntoa_format(t_specifier *specifier, char *buf, size_t len,
						 int is_negative, unsigned int base)
{
	if (!(specifier->flags & FLAGS_LEFT))
	{
		if (specifier->width && (specifier->flags & FLAGS_ZEROPAD)
			&& (is_negative || (specifier->flags & (FLAGS_PLUS | FLAGS_SPACE))))
			specifier->width--;
		while ((len < specifier->precision) && (len < NTOA_BUFFER_SIZE))
			buf[len++] = '0';
		while ((specifier->flags & FLAGS_ZEROPAD) && (len < specifier->width)
			   && (len < NTOA_BUFFER_SIZE))
			buf[len++] = '0';
	}
	if (specifier->flags & FLAGS_HASH)
	{
		if (!(specifier->flags & FLAGS_PRECISION)
			&& len && ((len == specifier->precision) || len == specifier->width))
		{
			len--;
			if (len && (base == 16U))
				len--;
		}
		if ((base == 16U) && !(specifier->flags & FLAGS_UPPERCASE)
			&& (len < NTOA_BUFFER_SIZE))
			buf[len++] = 'x';
		else if ((base == 16U) && (specifier->flags & FLAGS_UPPERCASE)
				 && (len < NTOA_BUFFER_SIZE))
			buf[len++] = 'X';
		if (len < NTOA_BUFFER_SIZE)
			buf[len++] = '0';
	}
	if (len < NTOA_BUFFER_SIZE)
	{
		if (is_negative)
			buf[len++] = '-';
		else if (specifier->flags & FLAGS_PLUS)
			buf[len++] = '+';
		else if (specifier->flags & FLAGS_SPACE)
			buf[len++] = ' ';
	}
	return (print_buf_rev(specifier, buf, len));
}

//length = ft_ntoa_long_long(specifier, value, is_negative, base);
size_t	ft_ntoa_long_long(t_specifier *specifier, unsigned long long value,
					  int is_negative, unsigned int base)
{
	char	buf[NTOA_BUFFER_SIZE];
	size_t	len = 0U;
	char 	digit;

	if (!value)
	{
		specifier->flags &= ~FLAGS_HASH;
	}
	if (!(specifier->flags & FLAGS_PRECISION) || value)
	{
		do
		{
			digit = (char)(value % base);
			buf[len++] = digit < 10 ? '0' + digit : (specifier->flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10; // Change for string base
			value /= base;
		} while (value && (len < NTOA_BUFFER_SIZE));
	}
	return (ft_ntoa_format(specifier, buf, len, is_negative, base));
}