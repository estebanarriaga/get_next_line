
/*
	Returns a sub-string from the string 's' that has been
	cut from the 'start' until 'len' of 's'.
*/

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substring;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (0);
	ft_strlcpy(substring, s + start, len + 1);
	return (substring);
}
