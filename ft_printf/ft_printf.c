/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 09:23:12 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/10 13:26:42 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	ft_pourcentage(char c, va_list args)
{
	if (c == 'c')
		return (pourcentage_c(args));
	else if (c == '%')
		return (pourcentage_double());
	else if (c == 'd' || c == 'i')
		return (pourcentage_int(args));
	else if (c == 's')
		return (pourcentage_s(args));
	else if (c == 'p')
		return (pourcentage_addr(args));
	else if (c == 'u')
		return (pourcentage_u(args));
	else if (c == 'x')
		return (pourcentage_x(args, 0));
	else if (c == 'X')
		return (pourcentage_x(args, 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			count;
	int			i;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			if (str[i])
				count += ft_pourcentage(str[i], args);
			else
				return (count);
		}
		else
		{
			count += write(1, &str[i], 1);
		}
		i++;
	}
	va_end(args);
	return (count);
}

// int main()
// {
// int n3 = printf("salut toi\n");
// printf("n = %d\n",n3);
// int nb = ft_printf("salut toi\n");
// ft_printf("n = %d\n",nb);
// ft_printf("Test %% et %c et %d\n",'X',42);
// char *ptr = NULL;
// ft_printf("str = %s\n", ptr);
// ft_printf("str = %s\n","test good");
// char *ptr1 = NULL;
// int n = ft_printf("str = %p\n", ptr1);
// 	ft_printf("str = %d\n", n);
// ft_printf("Unsigned : %u\n", 4294967295);
// ft_printf("Unsigned : %u\n", 42);
// ft_printf("Unsigned : %u\n", 0);
// unsigned int n1 = 10;
// unsigned int n2 = 254;
// unsigned int n3 = 48879; 
// unsigned int n4 = 4294967295;
// ft_printf("%%x = ");
// ft_printf("ft_printf: %X | %X | %X | %X\n", n1, n2, n3, n4);
// ft_printf("ft_printf: %X | %X | %X | %X\n", n1, n2, n3, n4);	
// }
// #include <stdio.h>
// #include <limits.h>
// #include "ft_printf.h"
// int main(void)
// {
//     int ret1, ret2;
//     char *str_null = NULL;
//     void *ptr_null = NULL;
//     void *ptr_valid = (void *)0xdeadbeef;
//     unsigned int uvals[] = {0, 1, UINT_MAX, 123456789};
//     int ivals[] = {INT_MIN, INT_MAX, -1, 0, 42};
//     char chars[] = {'A', 'z', '\0', '%'};
//     char *strings[] = {"Hello", "", str_null};

//     // Test simple conversions
//     for (int i = 0; i < 4; i++)
//     {
//         ret1 = printf("printf   : %c\n", chars[i]);
//         ret2 = ft_printf("ft_printf: %c\n", chars[i]);
//         if (ret1 != ret2) printf("Mismatch!\n");
//     }

//     for (int i = 0; i < 3; i++)
//     {
//         ret1 = printf("printf   : %s\n", strings[i]);
//         ret2 = ft_printf("ft_printf: %s\n", strings[i]);
//         if (ret1 != ret2) printf("Mismatch!\n");
//     }

//     for (int i = 0; i < 5; i++)
//     {
//         ret1 = printf("printf : %d %i\n", ivals[i], ivals[i]);
//         ret2 = ft_printf("ft_printf:%d %i\n", ivals[i], ivals[i]);
//         if (ret1 != ret2) printf("Mismatch!\n");
//     }

//   for (int i = 0; i < 4; i++)
//   {
//    ret1 = printf("printf   : %u %x %X\n", uvals[i], uvals[i], uvals[i]);
//    ret2 = ft_printf("ft_printf: %u %x %X\n", uvals[i], uvals[i], uvals[i]);
//    if (ret1 != ret2) printf("Mismatch!\n");
//   }
//     // Test pointeurs
//     ret1 = printf("printf   : %p %p %p\n", ptr_null, ptr_valid, str_null);
//     ret2 = ft_printf("ft_printf: %p %p %p\n", ptr_null, ptr_valid, str_null);
//     if (ret1 != ret2) printf("Mismatch!\n");

//     // Test %% et combinaisons
//     ret1 = printf("printf   : %% %% %%\n");
//     ret2 = ft_printf("ft_printf: %% %% %%\n");
//     if (ret1 != ret2) printf("Mismatch!\n");

//     // Test combiné complexe
// ret1 = printf("printf   : %c %s %d %i %u %x %X %p %%\n",
// 'Z', str_null, INT_MIN, INT_MAX, UINT_MAX, 0xdeadbeef, 0xDEADBEEF, ptr_null);
// ret2 = ft_printf("ft_printf: %c %s %d %i %u %x %X %p %%\n",
// 'Z', str_null, INT_MIN, INT_MAX, UINT_MAX, 0xdeadbeef, 0xDEADBEEF, ptr_null);
//     if (ret1 != ret2) printf("Mismatch!\n");
//     // Test chaîne longue avec % consécutifs
//     ret1 = printf("printf   : %%%%%%%% %%%% %%%% %c %s\n", 'X', "TEST");
//     ret2 = ft_printf("ft_printf: %%%%%%%% %%%% %%%% %c %s\n", 'X', "TEST");
//     if (ret1 != ret2) printf("Mismatch!\n");

//     return 0;
// }
