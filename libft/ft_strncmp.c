
/*
	The ft_strncmp() function lexicographically compare the
	null-terminated strings s1 and s2.

	The strncmp() function compares not more than n characters.

	The strcmp() and strncmp() functions return an integer greater than,
	equal to, or less than 0, according as the string s1 is greater than,
	equal to, or less than the string s2.
*/

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] != '\0' && i < n && s1[i] == s2[i])
		i ++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
