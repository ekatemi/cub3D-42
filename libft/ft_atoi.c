/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emikhayl <emikhayl@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 16:58:28 by emikhayl          #+#    #+#             */
/*   Updated: 2023/09/26 23:20:52 by emikhayl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>


static int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r' || c == ' ');
}
//special atoi
int	ft_atoi(const char *nptr)
{
	int	res;

	res = 0;
	
	while (*nptr && ft_isspace(*nptr))
		nptr++;

	while (*nptr)
	{
		if (*nptr < '0' || *nptr > '9')
		{
			printf("Error: Only integers and no spaces\n");
			return (-1);
		}
			
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	if (res < 0 || res > 255)
	{
		printf("Error: Range should be [0,255]\n");
		return (-1);
	}
		
	return (res);
}

// int	ft_atoi(const char *nptr)
// {
// 	int	sign;
// 	int	res;

// 	sign = 1;
// 	res = 0;
// 	while (*nptr && ft_isspace(*nptr))
// 		nptr++;
// 	if (*nptr == '+' || *nptr == '-')
// 	{
// 		if (*nptr == '-')
// 			sign = -1;
// 		nptr++;
// 	}
// 	while (*nptr >= '0' && *nptr <= '9')
// 	{
// 		res = res * 10 + (*nptr - '0');
// 		nptr++;
// 	}
// 	res = res * sign;
// 	return (res);
// }

// int main(void)
// {
// 	printf("Original atoi %d\n", ft_atoi("255 "));
// 	printf("My atoi %d\n", ft_atoi("   -ass2"));
// 	printf("My atoi %d\n", ft_atoi("    2s"));
// 	return 0;
// }
