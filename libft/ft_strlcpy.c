
/*
	ft_strlcpy() takes the full size of the destination buffer and
	guarantee NUL-termination if there is room.  Note that room for the NUL 
	should be included in dstsize.

	ft_strlcpy() copies up to dstsize - 1 characters from the string src to dst,
	NUL-terminating the result if dstsize is not 0.
*/

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	src_len;

	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	count = 0;
	while (src[count] != 0 && count < (dstsize - 1))
	{
		dst[count] = src[count];
		count ++;
	}
	dst[count] = '\0';
	return (src_len);
}
