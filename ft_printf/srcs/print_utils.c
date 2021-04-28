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

//size_t	ft_ntoa_long_long(va_list *ap, long long value, unsigned int base, t_specifier *specifier)
//{
//	char	buf[NTOA_BUFFER_SIZE];
//	size_t	len = 0U;
//	char 	digit;
//
//	if (!value)
//	{
//		specifier->flags &= ~FLAGS_HASH;
//	}
//	if (!(specifier->flags & FLAGS_PRECISION) || value)
//	{
//		while (value && (len < NTOA_BUFFER_SIZE))
//		{
//			digit = (char)(value % base);
//			buf[len++] = digit < 10 ? '0' + digit : (flags & FLAGS_UPPERCASE ? 'A' : 'a') + digit - 10; // Change for string base
//			value /= base;
//		}
//	}
//	return (ntoa_format());
//}
