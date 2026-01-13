
/*
	The ft_memcmp() function compares byte string s1 against byte string s2.  
	Both strings are assumed to be n bytes long.

	The ft_memcmp() function returns zero if the two strings are identical,
	otherwise returns the difference between the first two differing bytes
	(treated as unsigned char values, so that '\200' is greater than '\0',
	for example).  Zero-length strings are always identical.
	This behavior is not required by C and portable code should only depend
	on the sign of the returned value.
*/

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*cs1;
	const unsigned char	*cs2;

	cs1 = (const unsigned char *) s1;
	cs2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (cs1[i] < cs2[i])
			return (cs1[i] - cs2[i]);
		else if (cs1[i] > cs2[i])
			return (cs1[i] - cs2[i]);
		i ++;
	}
	return (0);
}
