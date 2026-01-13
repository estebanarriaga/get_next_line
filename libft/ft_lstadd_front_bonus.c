
/*
	The function ft_lstadd_font() add the node 'new' at the
	beginning  of the list 'lst'
*/

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		new -> next = *lst;
		*lst = new;
	}
}
