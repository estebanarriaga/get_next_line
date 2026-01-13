
/*
	The ft_memmove() function copies len bytes from string src to string dst.
	The two strings may overlap; the copy is always done in a non-destructive
	manner.

	In this version of the function, it checks whether the source pointer
	is greater than or equal to the destination pointer and if so,
	it copies the data in reverse order, from the last byte to the first byte,
	ensuring that the data is copied correctly even if the source and
	destination memory areas overlap.

	This function return dst
*/

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned const char	*csrc;
	unsigned char		*cdst;

	if (!dst && !src)
		return (0);
	cdst = (unsigned char *) dst;
	csrc = (unsigned const char *) src;
	if (src < dst && src + len > dst)
		while (len--)
			cdst[len] = csrc[len];
	else
		while (len --)
			*cdst++ = *csrc++;
	return (dst);
}
