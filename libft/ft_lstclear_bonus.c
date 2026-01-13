
/*
	The function ft_lstclear() eliminates the given node 'lst' and 
	all its consecutives using the function 'del' on  each pointer
*/

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*clear;

	if (lst)
	{
		while (*lst)
		{
			clear = (*lst)-> next;
			ft_lstdelone(*lst, del);
			*lst = clear;
		}
		(*lst) = NULL;
	}
}
