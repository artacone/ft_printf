#include "../includes/ft_printf.h"

static const double	g_pow10[17] = {1,
								   10,
								   100,
								   1000,
								   10000,
								   100000,
								   1000000,
								   10000000,
								   100000000,
								   1000000000,
								   10000000000,
								   100000000000,
								   1000000000000,
								   10000000000000,
								   100000000000000,
								   1000000000000000,
								   10000000000000000};

static size_t	ftoa_setup(t_specifier *specifier, t_double *value, char *buf,
						 size_t *buf_index)
{
	*buf_index = 0U;
	if (value->u_double.f != value->u_double.f)
		return (*buf_index = print_buf_rev(specifier, "nan", 3U));
	if (value->u_double.f < -DBL_MAX)
		return (*buf_index = print_buf_rev(specifier, "fni-", 4U));
	if (value->u_double.f > DBL_MAX)
	{
		if (specifier->flags & FLAGS_PLUS)
			return (*buf_index = print_buf_rev(specifier, "fni+", 4U));
		else
			return (*buf_index = print_buf_rev(specifier, "fni", 3U));
	}
	if (value->u_double.u & (1UL << 63U))
	{
		specifier->flags |= FLAGS_NEGATIVE;
		value->u_double.f = 0 - value->u_double.f;
	}
	if (!(specifier->flags & FLAGS_PRECISION))
		specifier->precision = DEFAULT_PRECISION;
	while ((*buf_index < FTOA_BUFFER_SIZE) && (specifier->precision > 16U))
	{
		buf[(*buf_index)++] = '0';
		specifier->precision--;
	}
	return (0U);
}

static void	round(t_specifier *specifier, t_double *value)
{
	double	tmp;
	double	diff;

	tmp = (value->u_double.f - value->integer) * g_pow10[specifier->precision];
	value->fractional = (unsigned long)tmp;
	diff = tmp - value->fractional;
	if (diff > 0.5)
	{
		value->fractional++;
		if (value->fractional >= g_pow10[specifier->precision])
		{
			value->fractional = 0;
			value->integer++;
		}
	}
	else if (diff == 0.5)
		value->fractional++;
	if (specifier->precision == 0U)
	{
		diff = value->u_double.f - (double)value->integer;
		if ((diff == 0.5) && (value->integer & 1))
			value->integer++;
	}
}

static void	ftoa_process(t_specifier *specifier, t_double value, char *buf,
							size_t *buf_index)
{
	unsigned int	count;

	if (specifier->precision > 0)
	{
		count = specifier->precision;
		while (*buf_index < FTOA_BUFFER_SIZE)
		{
			count--;
			buf[(*buf_index)++] = (char)(48U + (value.fractional % 10U));
			value.fractional /= 10U;
			if (!value.fractional)
				break ;
		}
		while ((*buf_index < FTOA_BUFFER_SIZE) && (count-- > 0U))
			buf[(*buf_index)++] = '0';
		if (*buf_index < FTOA_BUFFER_SIZE)
			buf[(*buf_index)++] = '.';
	}
	while ((*buf_index) < FTOA_BUFFER_SIZE)
	{
		buf[(*buf_index)++] = (char)(48 + (value.integer % 10));
		value.integer /= 10;
		if (!value.integer)
			break ;
	}
}

static size_t	ftoa_format(t_specifier *specifier, char *buf, size_t buf_index)
{
	if (!(specifier->flags & FLAGS_LEFT) && (specifier->flags & FLAGS_ZEROPAD))
	{
		if (specifier->width && ((specifier->flags & FLAGS_NEGATIVE)
				|| (specifier->flags & (FLAGS_PLUS | FLAGS_SPACE))))
			specifier->width--;
		while ((buf_index < specifier->width) && (buf_index < FTOA_BUFFER_SIZE))
			buf[buf_index++] = '0';
	}
	if (buf_index < FTOA_BUFFER_SIZE)
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

size_t	ft_ftoa(t_specifier *specifier, double value)
{
	char		buf[FTOA_BUFFER_SIZE];
	size_t		buf_index;
	t_double	_value;

	_value.u_double.f = value;
	if (ftoa_setup(specifier, &_value, buf, &buf_index))
		return (buf_index);
	_value.integer = (unsigned long)(_value.u_double.f);
	round(specifier, &_value);
	if ((specifier->precision == 0U)
		&& (specifier->flags & FLAGS_HASH) && (buf_index < FTOA_BUFFER_SIZE))
		buf[buf_index++] = '.';
	ftoa_process(specifier, _value, buf, &buf_index);
	return (ftoa_format(specifier, buf, buf_index));
}
