#include "../includes/ft_printf.h"

int	process_float(va_list *ap, t_specifier *specifier)
{
	if (specifier->type == 'f')
		return (ft_ftoa(specifier, va_arg(*ap, double)));
	if (specifier->type == 'g')
		specifier->flags |= FLAGS_ADAPT_EXP;
	return (ft_etoa(specifier, va_arg(*ap, double)));
}
