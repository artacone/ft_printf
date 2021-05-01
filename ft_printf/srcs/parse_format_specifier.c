#include "../includes/ft_printf.h"

static void	parse_flags(const char **format, t_specifier *specifier)
{
	specifier->flags = 0U;
	while (**format)
	{
		if (**format == '0')
			specifier->flags |= FLAGS_ZEROPAD;
		else if (**format == '-')
		{
			specifier->flags &= ~FLAGS_ZEROPAD;
			specifier->flags |= FLAGS_LEFT;
		}
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

static void	parse_width(const char **format,
					va_list *ap, t_specifier *specifier)
{
	int	width;

	specifier->width = 0U;
	if (ft_isdigit(**format))
	{
		specifier->width = ft_printf_atoi(format);
	}
	else if (**format == '*')
	{
		width = va_arg(*ap, int);
		if (width < 0)
		{
			specifier->flags |= FLAGS_LEFT;
			specifier->flags &= ~FLAGS_ZEROPAD;
			specifier->width = (unsigned int)(-width);
		}
		else
		{
			specifier->width = (unsigned int)width;
		}
		(*format)++;
	}
}

static void	parse_precision(const char **format,
					va_list *ap, t_specifier *specifier)
{
	int	precision;

	specifier->precision = 0U;
	if (**format == '.')
	{
		specifier->flags |= FLAGS_PRECISION;
		(*format)++;
		if (ft_isdigit(**format))
		{
			specifier->precision = ft_printf_atoi(format);
		}
		else if (**format == '*')
		{
			precision = (int)va_arg(*ap, int);
			if (precision >= 0)
				specifier->precision = (unsigned int)precision;
			else
				specifier->flags &= ~FLAGS_PRECISION;
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

// Format specifier %[flags][width][.precision][length]type
void	parse_format_specifier(const char **format,
							va_list *ap, t_specifier *specifier)
{
	parse_flags(format, specifier);
	parse_width(format, ap, specifier);
	parse_precision(format, ap, specifier);
	parse_length(format, specifier);
	specifier->type = **format;
	if (**format != '\0')
		(*format)++;
}
