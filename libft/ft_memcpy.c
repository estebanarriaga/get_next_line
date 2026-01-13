
/*
	The ft_memcpy() function copies n bytes from memory area src to memory area
	dst. If dst and src overlap, behavior is undefined.  Applications in
	which dst and src might overlap should use ft_memmove() instead.
*/

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	unsigned char	*cdst;
	unsigned char	*csrc;
	size_t			i;

	if (!dst && !src)
		return (0);
	cdst = (unsigned char *) dst;
	csrc = (unsigned char *) src;
	i = 0;
	while (i < len)
	{
		cdst[i] = csrc[i];
		i ++;
	}
	return (dst);
}
