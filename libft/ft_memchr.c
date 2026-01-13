
/*
	The ft_memchr() function locates the first occurrence of c (converted to an
	unsigned char) in string s.

	The ft_memchr() function returns a pointer to the byte located, or NULL if
	no such byte exists within n bytes.
*/

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char		uc;
	const unsigned char	*cs;
	size_t				i;

	uc = (unsigned char) c;
	cs = (const unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (cs[i] == uc)
			return ((void *) &cs[i]);
		i ++;
	}
	return (0);
}
