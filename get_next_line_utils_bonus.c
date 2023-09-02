/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earriaga <earriaga@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 11:54:13 by earriaga          #+#    #+#             */
/*   Updated: 2023/08/02 14:34:45 by earriaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlen(const char *str)
{
	size_t	x;

	x = 0;
	while (str[x] != '\0')
		x++;
	return (x);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	if (c == '\0')
		return (1);
	while (s[i] != '\0')
		if (s[i++] == (char) c)
			return (1);
	return (0);
}

char	*ft_strjoin(char *first_str, char *second_str)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!first_str)
	{
		first_str = (char *)malloc(1);
		first_str[0] = '\0';
	}
	if (!first_str || !second_str)
		return (NULL);
	str = (char *)malloc(((ft_strlen(first_str) + ft_strlen(second_str)) + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = 0;
	while (first_str[++i])
		str[i] = first_str[i];
	while (second_str[j])
		str[i++] = second_str[j++];
	str[i] = '\0';
	free(first_str);
	return (str);
}
