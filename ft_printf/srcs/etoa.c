#include "../includes/ft_printf.h"

size_t	ft_etoa(t_specifier *specifier, double value)
{
	t_double	v;

	v.u_double.f = value;
	if ((value != value) || (value > DBL_MAX) || (value < -DBL_MAX))
	{
		return (ft_ftoa(specifier, value));
	}
	if (v.u_double.u & (1UL << 63U))
	{
		specifier->flags |= FLAGS_NEGATIVE;
		value = 0 - value;
		v.u_double.f = 0 - v.u_double.f;
	}
	if (!(specifier->flags & FLAGS_PRECISION))
	{
		specifier->precision = DEFAULT_PRECISION;
	}
	int exp2 = (int)((v.u_double.u >> 52U) & 0x07FFU) - 1023; // effectively log2
	v.u_double.u = (v.u_double.u & ((1ULL << 52U) - 1U)) | (1023ULL << 52U); //drop the exponent so conv.F is now in [1,2)
	// now approximate log10 from the log2 integer part and an expansion of ln around 1.5
	int expval = (int)(0.1760912590558 + exp2 * 0.3010299956663981 + (v.u_double.f - 1.5) * 0.289529654602168);
	// now we want to compute 10^expval but we want to be sure it won't overflow
	exp2 = (int)(expval * 3.321928094887362 + 0.5);
	const double z  = expval * 2.302585092994046 - exp2 * 0.6931471805599453;
	const double z2 = z * z;
	v.u_double.u = (unsigned long)(exp2 + 1023) << 52U;
	// compute exp(z) using continued fractions, see https://en.wikipedia.org/wiki/Exponential_function#Continued_fractions_for_ex
	v.u_double.f *= 1 + 2 * z / (2 - z + (z2 / (6 + (z2 / (10 + z2 / 14)))));
	// correct for rounding errors
	if (value < v.u_double.f)
	{
		expval--;
		v.u_double.f /= 10;
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
		value /= v.u_double.f;
	}
	// output the floating part
	size_t buf_index;
	specifier->width = fwidth;
	buf_index = ft_ftoa(specifier, value);
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
		else
			specifier->flags &= ~FLAGS_NEGATIVE;
		specifier->precision = 0;
		specifier->width = minwidth - 1;
		specifier->flags |= FLAGS_ZEROPAD | FLAGS_PLUS;
		buf_index += ft_ntoa(specifier, expval, 10);
		// might need to right-pad spaces
		if (specifier->flags & FLAGS_LEFT)
		{
			while (buf_index < specifier->width)
				buf_index += write(1, " ", 1);
		}
	}
	return (buf_index);
}
