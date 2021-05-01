#include "../includes/ft_printf.h"
#include <stdio.h>

int	main()
{
//	char	str[] = "Hello, world!";
//	int		n = -4221;
//	char	c = 'A';
//	int 	*ptr = &n;
//	int 	X = 0x1234FA;

// format specifier %[flags][width][.precision][length]type
//	ft_printf("%d\n", n);
//	ft_printf("%0#10c\n", c);
//	ft_printf("%s\n", str);
//	ft_printf("%p\n", ptr);
//	ft_printf("%X\n", X);
//	ft_printf("%%\n");
//	ft_printf("%%%%%%\nThe number is: %d\nThe char is: %c\nThe message is: %s\n", n, c, str);
//	ft_printf("Floats: |%4.2f|%4.3f|%4.1f|%4.0f|%4f|\n", 3.141592, 3.141592, 3.141592, 3.141592, 3.141592);
//
//	ft_printf("Characters: %c %c \n", 'a', 65);
//	ft_printf("Decimals: %d %ld\n", 1977, 650000L);
//	ft_printf("Preceding with blanks: %10d \n", 1977);
//	ft_printf("Preceding with zeros: %010d \n", 1977);
//	ft_printf("Some different radices: %d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
//	ft_printf("floats: %4.2f %+.0e \n", 3.1416, 3.1416);
//	ft_printf("Width trick: %*d \n", 5, 10);
//	ft_printf("%s \n", "A string");

//	printf("printf|%-8.5d|\n", 34);
//	ft_printf("fprint|%-8.5d|\n", 34);
//
//	printf("printf|%8.5d|\n", 34);
//	ft_printf("fprint|%8.5d|\n", 34);

	printf("printf|%05%|\n");
	ft_printf("fprint|%05%|\n");

	printf("printf|%-05%|\n");
	ft_printf("fprint|%-05%|\n");

	printf("printf|%-5%|\n");
	ft_printf("fprint|%-5%|\n");
	return (0);
}
//when precision is on pad with leading zeros