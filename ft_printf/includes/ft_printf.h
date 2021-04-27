#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct s_specifier
{
	unsigned int 	flags;
	unsigned int	width;
	unsigned int	precision;
	char 			type;
}	t_specifier;

int		ft_printf(const char *format, ...);
char	*parse_format_specifier(const char **format, va_list *ap, t_specifier *specifier);

#endif
