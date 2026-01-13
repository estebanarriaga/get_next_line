

//	Using malloc() joins the string 's1' and 's2'

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*newstr;
	size_t	size_s1;
	size_t	size_s2;

	if (!s1 || !s2)
		return (0);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	newstr = (char *)malloc(size_s1 + size_s2 + 1);
	if (!newstr)
		return (0);
	ft_memcpy((char *)newstr, s1, size_s1 + 1);
	ft_strlcat(newstr, s2, size_s1 + size_s2 + 1);
	return (newstr);
}
