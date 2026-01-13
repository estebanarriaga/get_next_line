
/*
	The function ft_lstsize() returns the number
	of nodes in a list
*/

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		lst_size;
	t_list	*node;

	if (!lst)
		return (0);
	lst_size = 0;
	node = lst;
	while (node -> next)
	{
		lst_size ++;
		node = node -> next;
	}
	return (lst_size + 1);
}
