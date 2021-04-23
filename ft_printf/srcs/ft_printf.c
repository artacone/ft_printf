#include "../includes/ft_printf.h"

// format specifier?  %[flags][width][.precision][length]type

int ft_printf(const char *format, ...)
{
	va_list	ap; // Argument pointer
	char	*p, *sval;
	int		ival;
	int 	ret;

	va_start(ap, format); // Point ap to the first unnamed argument
	ret = parse_format(format, ap);
//	for (p = format; *p; p++)
//	{
//		if (*p != '%')
//		{
//			ft_putchar_fd(*p, 1);
//			continue;
//		}
//		switch (*++p)
//		{
//			case 'd':
//				ival = va_arg(ap, int);
//				ft_putnbr_fd(ival, 1);
//				break;
//			case 's':
//				sval = va_arg(ap, char *);
//				ft_putstr_fd(sval, 1);
//				break;
//			default:
//				ft_putchar_fd(*sval, 1);
//				break;
//		}
//	}
	va_end(ap);
	return (ret);
}