#include "../includes/ft_printf.h"

size_t	ft_ftoa(t_specifier *specifier, double value)
{
	char	buf[FTOA_BUFFER_SIZE];
	size_t	buf_index;
	double 	diff;

	static const double pow10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

	buf_index = 0U;
	diff = 0.0;
	// test for special values
	if (value != value)
		return (print_buf_rev(specifier, "nan", 3));
	if (value < -DBL_MAX)
		return (print_buf_rev(specifier, "fni-", 4));
	if (value > DBL_MAX)
		return (print_buf_rev(specifier, "fni+", 4)); // FiXME FLAGS_PLUS
	// test for negative
	if (value < 0)
	{
		specifier->flags |= FLAGS_NEGATIVE;
		value = 0 - value;
	}
	// set default precision if not set explicitly
	if (!(specifier->flags & FLAGS_PRECISION))
	{
		specifier->precision = DEFAULT_PRECISION;
	}
	// this prevents overflow
	while ((buf_index < FTOA_BUFFER_SIZE) && (specifier->precision > 9U)) // FIXME this prevents overflow
	{
		buf[buf_index++] = '0';
		specifier->precision--;
	}
	int		whole = (int)value;
	double	tmp = (value - whole) *pow10[specifier->precision];
	unsigned long frac = (unsigned long)tmp;
	diff = tmp - frac;

	if (diff > 0.5)
	{
		frac++;
		// handle rollover e.g. 0.99 (with precision 1) is 1.0
		if (frac >= pow10[specifier->precision])
		{
			frac = 0;
			whole++;
		}
	}
	else if (diff < 0.5) // FIXME
		;
	else if ((frac == 0U) || (frac & 1U))
	{
		// if halfway, round up if odd or if last digit is 0
		frac++;
	}

	if (specifier->precision == 0U)
	{
		diff = value - (double)whole;
		if ((!(diff < 0.5) || (diff > 0.5)) && (whole & 1))
		{
			// exactly 0.5 and odd then round up
			// 1.5 -> 2, but 2.5 -> 2
			whole++;
		}
	}
	else
	{
		unsigned int count = specifier->precision;
		// now do fractional part, as an unsigned number
		while (buf_index < FTOA_BUFFER_SIZE)
		{
			count--;
			buf[buf_index++] = (char)(48U + (frac % 10U));
			if (!(frac /= 10U))
			{
				break ;
			}
		}
		// add extra 0s
		while ((buf_index < FTOA_BUFFER_SIZE) && (count-- > 0U))
		{
			buf[buf_index++] = '0';
		}
		if (buf_index < FTOA_BUFFER_SIZE)
		{
			// add decimal
			buf[buf_index++] = '.';
		}
	}
	//do whole part, number is reversed
	while (buf_index < FTOA_BUFFER_SIZE)
	{
		buf[buf_index++] = (char)(48 + (whole % 10));
		if (!(whole /= 10))
		{
			break ;
		}
	}

	// pad leading zeros
	if (!(specifier->flags & FLAGS_LEFT) && (specifier->flags & FLAGS_ZEROPAD))
	{
		if (specifier->width && ((specifier->flags & FLAGS_NEGATIVE)
			|| (specifier->flags & (FLAGS_PLUS | FLAGS_SPACE))))
		{
			specifier->width--;
		}
		while ((buf_index < specifier->width) && (buf_index < FTOA_BUFFER_SIZE))
		{
			buf[buf_index++] = '0';
		}
	}

	if (buf_index < FTOA_BUFFER_SIZE)
	{
		if (specifier->flags & FLAGS_NEGATIVE)
		{
			buf[buf_index++] = '-';
		} else if (specifier->flags & FLAGS_PLUS)
		{
			buf[buf_index++] = '+';
		} else if (specifier->flags & FLAGS_SPACE)
		{
			buf[buf_index++] = ' ';
		}
	}
	return (print_buf_rev(specifier, buf, buf_index));
}

size_t	ft_etoa(t_specifier *specifier, double value) // FIXME
{
	// check for special values
	if ((value != value) || (value > DBL_MAX) || (value < -DBL_MAX))
	{
		return (ft_ftoa(specifier, value));
	}
	// check if negative
	if (value < 0)
	{
		specifier->flags |= FLAGS_NEGATIVE;
		value = 0 - value;
	}
	// default precision
	if (!(specifier->flags & FLAGS_PRECISION))
	{
		specifier->precision = DEFAULT_PRECISION;
	}
	// determine the decimal exponent
	// based on the algorithm by David Gay (https://www.ampl.com/netlib/fp/dtoa.c)
	union {
		uint64_t	U;
		double		F;
	}	conv;

	conv.F = value;
	int exp2 = (int)((conv.U >> 52U) & 0x07FFU) - 1023; // effectively log2
	conv.U = (conv.U & ((1ULL << 52U) - 1U)) | (1023ULL << 52U); //drop the exponent so conv.F is now in [1,2)
	// now approximate log10 from the log2 integer part and an expansion of ln around 1.5
	int expval = (int)(0.1760912590558 + exp2 * 0.3010299956663981 + (conv.F - 1.5) * 0.289529654602168);
	// now we want to compute 10^expval but we want to be sure it won't overflow
	exp2 = (int)(expval * 3.321928094887362 + 0.5);
	const double z  = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
	const double z2 = z * z;
	conv.U = (uint64_t)(exp2 + 1023) << 52U;
	// compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex
	conv.F *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
	// correct for rounding errors
	if (value < conv.F)
	{
		expval--;
		conv.F /= 10;
	}
	// the exponent format is "%+03d" and largest value is "307" so set aside 4-5 characters
	unsigned int minwidth = ((expval < 100) && (expval > -100)) ? 4U : 5U;
	// in "%g" mode, specifier->precision is the number of *significant figures* not decimals
	if (specifier->flags & FLAGS_ADAPT_EXP)
	{
		// do we want to fall-back to "%f" mode?
		if ((value >= 1e-4) && (value < 1e6))
		{
			if ((int)specifier->precision > expval)
			{
				specifier->precision = (unsigned)((int)specifier->precision - expval - 1);
			}
			else
			{
				specifier->precision = 0;
			}
			specifier->flags |= FLAGS_PRECISION;
			// no characters in exponent
			minwidth = 0U;
			expval = 0;
		}
		else
		{
			// we use one sigfig for the whole part
			if ((specifier->precision > 0) && (specifier->flags & FLAGS_PRECISION))
			{
				specifier->precision--;
			}
		}
	}
	// will everything fit?
	unsigned int fwidth = specifier->width;
	if (specifier->width > minwidth)
	{
		// we didn't fall-back to subtract the characters required for the exponent
		fwidth -= minwidth;
	}
	else
	{
		// not enough characters, so go back to default sizing
		fwidth = 0U;
	}
	if ((specifier->flags & FLAGS_LEFT) && minwidth)
	{
		// if we're padding on the right, DON't pad the floating part
		fwidth = 0U;
	}
	// rescale the float value
	if (expval)
	{
		value /= conv.F;
	}
	// output the floating part
	size_t buf_index;
	buf_index = ft_ftoa(specifier, value); // FIXME
	// output the exponent part
	if (minwidth)
	{
		// output the exponential symbol
		buf_index += write(1, "e", 1);
		if (expval < 0)
		{
			specifier->flags |= FLAGS_NEGATIVE;
			expval = 0 - expval;
		}
		specifier->precision = 0;
		specifier->width = minwidth - 1;
		specifier->flags |= FLAGS_ZEROPAD | FLAGS_PLUS;
		buf_index += ft_ntoa(specifier, (expval < 0) ? -expval : expval, 10); // FIXME flags
		// might need to right-pad spaces
		if (specifier->flags & FLAGS_LEFT)
		{
			while (buf_index < specifier->width)
				buf_index += write(1, " ", 1);
		}
	}
	return (buf_index);
}

int	process_float(va_list *ap, t_specifier *specifier)
{
	if (specifier->type == 'f')
		return (ft_ftoa(specifier, va_arg(*ap, double)));
	if (specifier->type == 'g')
		specifier->flags |= FLAGS_ADAPT_EXP;
	return (ft_etoa(specifier, va_arg(*ap, double)));
}