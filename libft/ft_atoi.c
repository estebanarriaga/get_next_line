
/*
	The atoi() function converts the initial portion
	of the string pointed to by str 
	to int representation.
*/

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	num;

	sign = 1;
	num = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str ++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = (-1);
		str ++;
	}
	if (*str < '0' || *str > '9')
		return (0);
	while (*str >= '0' && *str <= '9')
	{
		num = num * 10 + (*str - '0');
		str ++;
	}
	return (num * sign);
}
