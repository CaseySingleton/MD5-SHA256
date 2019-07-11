/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 17:47:09 by csinglet          #+#    #+#             */
/*   Updated: 2019/02/05 17:47:10 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

t_token				*new_token(char *content, int type)
{
	t_token			*token;

	if (!(token = (t_token *)malloc(sizeof(t_token))))
		return (NULL);
	token->content = content;
	token->type = type;
	token->next = NULL;
	return (token);
}

void				free_token(t_token *token)
{
	if (token != NULL)
	{
		if (token->content != NULL)
		{
			free(token->content);
			token->content = NULL;
		}
		free(token);
		token = NULL;
	}
}

void				free_token_list(t_token *token_list)
{
	t_token			*next;

	if (token_list != NULL)
	{
		while (token_list != NULL)
		{
			next = token_list->next;
			free_token(token_list);
			token_list = next;
		}
	}
}

t_token				*get_tokens(int ac, char **av)
{
	t_token			*token_list;
	t_token			*cur;
	unsigned		i;

	token_list = NULL;
	i = 2;
	while (i < ac && av[i][0] == '-')
		i++;
	while (i < ac)
	{
		if (token_list == NULL)
		{
			token_list = new_token(av[i], 0);
			cur = token_list;
		}
		else
			cur->next = new_token(av[i], 0);
		if (cur->next != NULL)
			cur = cur->next;
		i++;
	}
	return (token_list);
}
