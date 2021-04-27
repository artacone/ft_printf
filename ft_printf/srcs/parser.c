#include "../includes/ft_printf.h"

#define FLAGS_ZEROPAD   (1U <<  0U)
#define FLAGS_LEFT      (1U <<  1U)
#define FLAGS_PLUS      (1U <<  2U)
#define FLAGS_SPACE     (1U <<  3U)
#define FLAGS_HASH      (1U <<  4U)
#define FLAGS_UPPERCASE (1U <<  5U)
#define FLAGS_CHAR      (1U <<  6U)
#define FLAGS_SHORT     (1U <<  7U)
#define FLAGS_LONG      (1U <<  8U)
#define FLAGS_LONG_LONG (1U <<  9U)
#define FLAGS_PRECISION (1U << 10U)
#define FLAGS_ADAPT_EXP (1U << 11U)

static void	parse_flags(const char **format, t_specifier *specifier)
{
	specifier->flags = 0U;
	while (**format)
	{
		if (**format == '0')
			specifier->flags |= FLAGS_ZEROPAD;
		else if (**format == '-')
			specifier->flags |= FLAGS_LEFT;
		else if (**format == '+')
			specifier->flags |= FLAGS_PLUS;
		else if (**format == ' ')
			specifier->flags |= FLAGS_SPACE;
		else if (**format == '#')
			specifier->flags |= FLAGS_HASH;
		else
		{
			break ;
		}
		(*format)++;
	}
}

static void	parse_width(const char **format, va_list *ap, t_specifier *specifier)
{
	specifier->width = 0U;
	if (ft_isdigit(**format))
	{
		specifier->width = ft_atoi(*format); // FIXME Shift pointer
	}
	else if (**format == '*')
	{
		const int	w = va_arg(ap, int);
		if (w < 0)
		{
			specifier->flags |= FLAGS_LEFT;
			specifier->width = (unsigned int)(-w);
		}
		else
		{
			specifier->width = (unsigned int)w;
		}
		(*format)++;
	}
}

static void	*parse_precision(const char **format, va_list *ap, t_specifier *specifier)
{
	specifier->precision = 0U;
	if (**format = '.')
	{
		specifier->flags |= FLAGS_PRECISION;
		(*format)++;
		if (ft_isdigit(**format))
		{
			specifier->precision = ft_atoi(*format); // FIXME Shift pointer
		}
		else if (**format == '*')
		{
			const int	prec = (int) va_arg(ap, int);
			specifier->precision = prec > 0 ? (unsigned int)prec : 0U;
			(*format)++;
		}
	}
}

static void	parse_length(const char **format, t_specifier *specifier)
{
	if (**format == 'l')
	{
		specifier->flags |= FLAGS_LONG;
		(*format)++;
		if (**format == 'l')
		{
			specifier->flags |= FLAGS_LONG_LONG;
			(*format)++;
		}
	}
	else if (**format == 'h')
	{
		specifier->flags |= FLAGS_SHORT;
		(*format)++;
		if (**format == 'h')
		{
			specifier->flags |= FLAGS_CHAR;
			(*format)++;
		}
	}
}

// format specifier %[flags][width][.precision][length]type
void	parse_format_specifier(const char **format, va_list *ap, t_specifier *specifier)
{
	parse_flags(format, specifier);
	parse_width(format, ap, specifier);
	parse_precision(format, ap, specifier);
	parse_length(format, specifier);
	specifier->type = **format;
	(*format)++;
}