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
//special atoi no negativa and range (Check later)
int	ft_atoi(const char *nptr)
{
	int	res = 0;

	// Skip leading spaces
	while (*nptr && ft_isspace(*nptr))
		nptr++;
	// Immediately return error if '-' is found
	if (*nptr == '-')
	{
		printf("Error: Negative numbers are not allowed\n");
		return (-1);
	}
	// Handle optional '+', but do nothing
	if (*nptr == '+')
		nptr++;
	// If first character is not a digit, return error
	if (*nptr < '0' || *nptr > '9')
	{
		printf("Error: Invalid input\n");
		return (-1);
	}
	// Convert number
	while (*nptr >= '0' && *nptr <= '9')
	{
		res = res * 10 + (*nptr - '0');
		nptr++;
	}
	// If extra invalid characters appear at the end, return error
	if (*nptr != '\0' && !ft_isspace(*nptr))
	{
		printf("Error: Invalid trailing characters\n");
		return (-1);
	}
	if (res > 255)
	{
		printf("Error: Number out of range (0-255)\n");
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
// 	printf("My atoi %d\n", ft_atoi("  0 "));
// 	printf("My atoi %d\n", ft_atoi("   -ass2 "));
// 	printf("My atoi %d\n", ft_atoi("    2s "));
// 	return 0;
// }
