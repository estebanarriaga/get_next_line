
/*
	The strnstr() function locates the first occurrence of the null-terminated
	string needle in the string haystack, where not more than len characters
	are searched.  Characters that appear after a
	'\0' character are not searched.

	If needle is an empty string, haystack is returned; if needle occurs
	nowhere in haystack, NULL is returned; otherwise a pointer to the first
	character of the first occurrence of needle is returned.
*/

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	needle_len;

	needle_len = ft_strlen(needle);
	if (!needle || !*needle)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != 0 && i < len)
	{
		j = 0;
		k = i;
		while (haystack[k] == needle[j] && k < len && needle[j] != 0)
		{
			j++;
			k++;
		}
		if (j == needle_len)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
