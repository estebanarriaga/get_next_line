
/*
	This function copies the string s into a newly allocated string. 
	The string is allocated using malloc(); see Unconstrained Allocation.
	If malloc cannot allocate space for the new string, strdup returns 
	a null pointer. Otherwise it returns a pointer to the new string
*/

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = (char *)malloc(ft_strlen(s) + 1);
	if (!dest)
		return (0);
	i = 0;
	while (s[i])
	{
		dest[i] = (char)s[i];
		i ++;
	}
	dest[i] = 0;
	return (dest);
}
