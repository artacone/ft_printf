#include "../includes/ft_printf.h"

int	main()
{
	char	str[] = "Hello, world!";
	int		n = -4221;
	char	c = 'A';
	int 	*ptr = &n;

// format specifier %[flags][width][.precision][length]type
	ft_printf("%d\n", n);
	ft_printf("%0#10c\n", c);
	ft_printf("%s\n", str);
	ft_printf("%p\n", ptr);
	ft_printf("%%\n");
	ft_printf("%%%%%%\nThe number is: %d\nThe char is: %c\nThe message is: %s\n", n, c, str);
	return (0);
}