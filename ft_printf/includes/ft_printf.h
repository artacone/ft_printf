#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

# include <float.h>

# define FLAGS_ZEROPAD		1U
# define FLAGS_LEFT			2U
# define FLAGS_PLUS			4U
# define FLAGS_SPACE		8U
# define FLAGS_HASH			16U
# define FLAGS_UPPERCASE	32U
# define FLAGS_CHAR			64U
# define FLAGS_SHORT		128U
# define FLAGS_LONG			256U
# define FLAGS_LONG_LONG	512U
# define FLAGS_PRECISION	1024U
# define FLAGS_NEGATIVE		2048U
# define FLAGS_ADAPT_EXP	4096U

# define NTOA_BUFFER_SIZE	64U
# define FTOA_BUFFER_SIZE	64U

# define DEFAULT_PRECISION	6U

typedef struct s_specifier
{
	unsigned int	flags;
	unsigned int	width;
	unsigned int	precision;
	char			type;
}	t_specifier;

typedef struct s_double
{
	union
	{
		uint64_t	u;
		double		f;
	}	u_double;
	unsigned long	integer;
	unsigned long	fractional;
}	t_double;

int				ft_printf(const char *format, ...);
void			parse_format_specifier(const char **format,
					va_list *ap, t_specifier *specifier);
void			process_format_specifier(va_list *ap,
					t_specifier *specifier, int *length);

void			process_string(va_list *ap, t_specifier *specifier,
					 int *length);
int				process_integer(va_list *ap, t_specifier *specifier);
int				process_float(va_list *ap, t_specifier *specifier);

size_t			ft_ntoa(t_specifier *specifier, unsigned long long value,
					 	unsigned int base);
size_t			ft_ftoa(t_specifier *specifier, double value);
size_t			ft_etoa(t_specifier *specifier, double value);

size_t			print_buf_rev(t_specifier *specifier, char *buf,
					   size_t buf_index);

int				ft_isdigit(int c);
unsigned int	ft_printf_atoi(const char **str);

#endif
