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

int	parse_format(const char *format)
{
	unsigned int	flags, width, precision, n, ret = 0;

	while (*format)
	{
		// format specifier?  %[flags][width][.precision][length]type
		if (*format != '%')
		{
			// no
			// FIXME putchar(*format)
			format++;
			continue;
		}
		else
		{
			// yes
			format++;
		}
		flags = 0U;
		do
		{
			switch (*format)
			{
				case '0': flags |= FLAGS_ZEROPAD; format++; n = 1U; break;
				case '-': flags |= FLAGS_LEFT; format++; n = 1U; break;
				case '+': flags |= FLAGS_PLUS; format++; n = 1U; break;
				case ' ': flags |= FLAGS_SPACE; format++; n = 1U; break;
				case '#': flags |= FLAGS_HASH; format++; n = 1U; break;
				default: n = 0U; break;
			}
		} while (n);
		/*
		 * WIDTH
		*/
		width = 0U;
		if (ft_isdigit(*format))
		{
			width = ft_atoi(&format); // FIXME Shift pointer!
		}
		else if (*format == '*')
		{
			const int	w = va_arg(ap, int);
			if (w < 0)
			{
				flags |= FLAGS_LEFT; // See man printf for negative width
				width = (unsigned int)-w;
			}
			else
			{
				width = (unsigned int)w;
			}
			format++;
		}
		/*
		 * PRECISION
		*/
		precision = 0U;
		if (*format = '.')
		{
			flags |= FLAGS_PRECISION;
			format++;
			if (ft_isdigit(*format))
			{
				precision = ft_atoi(&format); //FIXME Shift pointer
			}
			else if (*format == '*')
			{
				const int prec = (int) va_arg(ap, int);
				precision = prec > 0 ? (unsigned int)prec : 0U;
				format++;
			}
		}
		/*
		 * LENGTH
		 */
		switch (*format)
		{
			case 'l':
				flags |= FLAGS_LONG;
				format++;
				if (*format == 'l')
				{
					flags |= FLAGS_LONG_LONG;
					format++;
				}
				break;
			case 'h' :
				flags |= FLAGS_SHORT;
				format++;
				if (*format == 'h')
				{
					flags |= FLAGS_CHAR;
					format++;
				}
				break;
			default :
				break;
		}

		/*
		 * SPECIFIER
		 */
		switch (*format)
		{
			case 'd' :
			case 'i' :
			case 'u' :
			case 'x' :
			case 'X' :
			//case 'o' :
			{
				unsigned int base;
				if (*format == 'x' || *format == 'X')
				{
					base = 16U;
				}
				else
				{
					base = 10U;
					flags &= ~FLAGS_HASH; // No hash for decimals
				}
				if (*format == 'X')
				{
					flags |= FLAGS_UPPERCASE;
				}
				if ((*format != i) && (*format != 'd'))
				{
					flags &= ~(FLAGS_PLUS | FLAGS_SPACE);
				}
				if (flags & FLAGS_PRECISION)
				{
					flags &= ~FLAGS_ZEROPAD;
				}
				// FIXME conversion to type
				// ft_itoa()
				format++;
				break;
			}
			// TODO cases for floats here
			case 'c' :
			{
				unsigned int l = 1U;

				if (!(flags & FLAGS_LEFT))
				{
					while (l++ < width)
					{
						//ft_putchar(' ');
					}
				}
				//ft_putchar(va_arg(va, int)
				if (flags & FLAGS_LEFT)
				{
					while (l++ < width)
					{
						// ft_putchar(' ')
					}
				}
				format++;
				break;
			}
			case 's' :
			{
				const char *p = va_arg(ap, char*);
				// TODO work with strings
				format++;
				break;
			}
			case 'p' :
			{
				width = sizeof(void *) * 2U;
				flags |= FLAGS_ZEROPAD | FLAGS_UPPERCASE;
				// TODO work with pointers
				format++;
				break;
			}
			case '%' :
			{
				// ft_putchar('%');
				format++;
				break;
			}
			default :
				// ft_putchar(*format);
				format++;
				break;
		}
	}
	return (ret);
}