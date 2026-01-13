
/*
	The calloc() function contiguously allocates enough 
	space for count objects that are size bytes of
	memory each and returns a pointer to the allocated memory.
	The allocated memory is filled with bytes
	of value zero.

	If successful, calloc() function
	returns a pointer to allocated memory.  If there is an error,
	they return a NULL pointer and set errno to ENOMEM.
*/

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*ptr;

	ptr = (char *) malloc(count * size);
	if (!ptr)
		return (0);
	i = 0;
	while (i < count * size)
	{
		ptr[i] = 0;
		i ++;
	}
	return (ptr);
}
