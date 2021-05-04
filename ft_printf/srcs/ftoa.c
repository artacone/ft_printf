#include "../includes/ft_printf.h"

static const double	g_pow10[16] = {1,
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
								   1000000000000000};

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

static size_t	ftoa_handle_special(t_specifier *specifier, double value)
{
	if (value != value)
		return (print_buf_rev(specifier, "nan", 3U));
	if (value < -DBL_MAX)
		return (print_buf_rev(specifier, "fni-", 4U));
	if (value > DBL_MAX)
	{
		if (specifier->flags & FLAGS_PLUS)
			return (print_buf_rev(specifier, "fni+", 4U));
		else
			return (print_buf_rev(specifier, "fni", 3U));
	}
	return (0U);
}

static void	ftoa_handle_preparation(t_specifier *specifier, double *value,
									   char *buf, size_t *buf_index)
{
	union {
		uint64_t	U;
		double		F;
	}	u_conv;
	u_conv.F = *value;
	if (u_conv.U & (1ULL << 63U))
	{
		specifier->flags |= FLAGS_NEGATIVE;
		*value = 0 - *value;
	}
	if (!(specifier->flags & FLAGS_PRECISION))
		specifier->precision = DEFAULT_PRECISION;
	while ((*buf_index < FTOA_BUFFER_SIZE) && (specifier->precision > 15U))
	{
		buf[(*buf_index)++] = '0';
		specifier->precision--;
	}
}

static void	ftoa_process(t_specifier *specifier, double value, char *buf,
							size_t *buf_index)
{
	double	diff;
	int		whole = (int)value;
	double	tmp = (value - whole) * g_pow10[specifier->precision];
	unsigned long frac = (unsigned long)tmp;
	diff = tmp - frac;

	if (diff > 0.5)
	{
		frac++;
		if (frac >= g_pow10[specifier->precision])
		{
			frac = 0;
			whole++;
		}
	}
	else if (diff < 0.5)
		;
	else if ((frac == 0U) || (frac & 1U))
		frac++;
	if (specifier->precision == 0U)
	{
		diff = value - (double)whole;
		if (!((diff < 0.5) || (diff > 0.5)) && (whole & 1))
			whole++;
	}
	else
	{
		unsigned int count = specifier->precision;
		while (*buf_index < FTOA_BUFFER_SIZE)
		{
			count--;
			buf[(*buf_index)++] = (char)(48U + (frac % 10U));
			if (!(frac /= 10U))
				break ;
		}
		while ((*buf_index < FTOA_BUFFER_SIZE) && (count-- > 0U))
			buf[(*buf_index)++] = '0';
		if (*buf_index < FTOA_BUFFER_SIZE)
			buf[(*buf_index)++] = '.';
	}
	while ((*buf_index) < FTOA_BUFFER_SIZE)
	{
		buf[(*buf_index)++] = (char)(48 + (whole % 10));
		if (!(whole /= 10))
			break ;
	}
}

size_t	ft_ftoa(t_specifier *specifier, double value)
{
	char	buf[FTOA_BUFFER_SIZE];
	size_t	buf_index;

	buf_index = ftoa_handle_special(specifier, value);
	if (buf_index)
		return (buf_index);
	ftoa_handle_preparation(specifier, &value, buf, &buf_index);
	ftoa_process(specifier, value, buf, &buf_index);
	return (ftoa_format(specifier, buf, buf_index));
}

