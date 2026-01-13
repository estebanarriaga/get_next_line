
/*
	The bzero() function writes n zeroed bytes to the string s.
	If n is zero, bzero() does nothing.
*/

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*cs;

	cs = (char *) s;
	i = 0;
	while (i < n)
	{
		cs[i] = 0;
		i ++;
	}
}
