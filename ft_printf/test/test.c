#include "../includes/ft_printf.h"
#include <stdio.h>
#include <stdlib.h>

int	main()
{
//	char	str[] = "Hello, world!";
//	int		n = -4221;
//	char	c = 'A';
//	int 	*ptr = &n;
//	int 	X = 0x1234FA;

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

//	PRINT(" --- Return : %d\n", PRINT("%-00000-----*i, %---0.*d, %0-0-0-0-0.*d, %-0-0-0-0-.*d, %-----.*d", a, i, a, i, a, i, a, i, a, i));
//	PRINT(" --- Return : %d\n", PRINT("%-00000-----*i, %---0.*d, %0-0-0-0-0.*d, %-0-0-0-0-.*d, %-----.*d", a, j, a, j, a, j, a, j, a, j));
//	PRINT(" --- Return : %d\n", PRINT("%-00000-----*i, %---0.*d, %0-0-0-0-0.*d, %-0-0-0-0-.*d, %-----.*d", a, l, a, l, a, l, a, l, a, l));

//	printf("%#");
//	printf("\n");
//	ft_printf("fprint|%#");
//	printf("\n");
//
//	printf("printf|% *.5i|\n", 4, 42);
//	ft_printf("fprint|% *.5i|\n", 4, 42);

//	printf("printf|%0-00000-----*i|\n", 12, 8);
//	ft_printf("fprint|%0-00000-----*i|\n", 12, 8);

//	printf("printf|%05i|\n", -54);
//	ft_printf("fprint|%05i|\n", -54);
//
//	printf("printf|%0*i|\n", -7, -54);
//	ft_printf("fprint|%0*i|\n", -7, -54);
//
//	printf("printf|%0*i|\n", -7, 54);
//	ft_printf("fprint|%0*i|\n", -7, 54);
//
//	printf("printf|%.*s|\n", 0, "hello");
//	ft_printf("fprint|%.*s|\n", 0, "hello");
	printf("printf|%.1f|\n", 3.85);
	ft_printf("fprint|%.1f|\n", 3.85);
	printf("printf|%.1f|\n", -3.95);
	ft_printf("fprint|%.1f|\n", -3.95);
	printf("printf|%.3f|\n", -3.9995);
	ft_printf("fprint|%.3f|\n", -3.9995);

	return (0);
}