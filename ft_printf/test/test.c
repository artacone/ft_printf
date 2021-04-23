#include "../includes/ft_printf.h"

int	main()
{
	char	str[] = "Hello, world!";
	int		n = -4221;

	ft_printf("%s\n", str);
	ft_printf("%d\n", n);
	ft_printf("The message is: %s\nThe number is: %d\n", str, n);
	return (0);
}