/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 22:23:17 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/01 22:23:19 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Granted the string 'content' is not NULL, then there will be at least
**	one token to return, which is the entire string 'content'
*/

char			**ft_strtok(char *content, int delim)
{
	ft_putstr("ft_strtok() is a work in progress, do not use\n");
	char		**tokens;
	int			num_tokens;
	int			i;
	int			j;

	if (content == NULL)
		return (NULL);
	num_tokens = ft_wrdcount(content, delim);
	if (!(tokens = (char **)malloc(sizeof(char *) * num_tokens + 1)))
		return (NULL);
	tokens[num_tokens] = NULL;
	tokens[0] = content;
	i = -1;
	j = 1;
	while (content[++i] != '\0')
	{
		if (content[i] == delim)
		{
			content[i] = '\0';
			tokens[j++] = content + i + 1;
		}
	}
	return (tokens);
}
