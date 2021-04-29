#include "libft.h"

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
