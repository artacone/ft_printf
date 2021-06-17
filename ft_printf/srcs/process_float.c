#include "../includes/ft_printf.h"

int	process_float(va_list *ap, t_specifier *specifier)
{
	return (ft_ftoa(specifier, va_arg(*ap, double)));
}
