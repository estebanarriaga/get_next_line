
/*
	The function ft_lstdelone() takes the node 'lst' and liberates
	the memory of its content using the del() function, aside from
	liberating the memory of the content
*/

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst)
	{
		del(lst -> content);
		free(lst);
	}
}
