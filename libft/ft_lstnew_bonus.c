
/*
	The function ft_lstnew() creates a new node using malloc().
	The variable 'content' is initialiced with the content of
	the parameter 'content', the variable 'next' with NULL.
*/

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = (t_list *)malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	node -> content = (void *)content;
	node -> next = NULL;
	return (node);
}
