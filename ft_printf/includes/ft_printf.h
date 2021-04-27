#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# define FLAGS_ZEROPAD   (1U <<  0U)
# define FLAGS_LEFT      (1U <<  1U)
# define FLAGS_PLUS      (1U <<  2U)
# define FLAGS_SPACE     (1U <<  3U)
# define FLAGS_HASH      (1U <<  4U)
# define FLAGS_UPPERCASE (1U <<  5U)
# define FLAGS_CHAR      (1U <<  6U)
# define FLAGS_SHORT     (1U <<  7U)
# define FLAGS_LONG      (1U <<  8U)
# define FLAGS_LONG_LONG (1U <<  9U)
# define FLAGS_PRECISION (1U << 10U)
# define FLAGS_ADAPT_EXP (1U << 11U)

typedef struct s_specifier
{
	unsigned int 	flags;
	unsigned int	width;
	unsigned int	precision;
	char 			type;
}	t_specifier;

int		ft_printf(const char *format, ...);
char	*parse_format_specifier(const char **format, va_list *ap, t_specifier *specifier);
int		print_specified(va_list *ap, t_specifier *specifier);

#endif
