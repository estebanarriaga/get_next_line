
/*
	The ft_memset() function writes len bytes of value c (converted to an
	unsigned char) to the string b. This function copies the value of c
	(converted to an unsigned char) into each of the first size bytes of
	the object beginning at block. It returns the value of block. 
*/

#include "libft.h"

void	*ft_memset(void	*b, int c, size_t len)
{
	unsigned char	*uc;
	size_t			i;

	uc = (unsigned char *) b;
	i = 0;
	while (i < len)
	{
		uc[i] = (unsigned char) c;
		i ++;
	}
	return (b);
}
