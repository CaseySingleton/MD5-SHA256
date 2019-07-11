/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 20:38:08 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/09 20:38:09 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

unsigned			reverse_bytes(unsigned n)
{
	return ((n << 24) | ((n << 8) & 0x00ff0000) |\
		((n >> 8) & 0x0000ff00) | (n >> 24));
}

static unsigned		get_shift(char *str, char c)
{
	unsigned		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return ((1 << i));
		i++;
	}
	return (-1);
}

static void			print_error(char c)
{
	ft_printf("Illegal option -- %c\n", c);
	ft_printf("usage: ft_ssl [name] [flags] [-s string] [files...]\n");
}

unsigned			set_flags(int ac, char **av)
{
	unsigned		flags;
	unsigned		i;
	unsigned		j;

	flags = 0;
	i = 1;
	while (++i < ac && av[i][0] == '-')
	{
		j = 0;
		while (av[i][++j] != '\0')
		{
			flags |= get_shift("pqrs", av[i][j]);
			if (get_shift("pqrs", av[i][j]) == -1)
			{
				print_error(av[i][j]);
				return (-1);
			}
		}
	}
	if (flags & FLAG_S && i == ac)
	{
		ft_printf("md5: option requires an argument -- s\n");
		return (-1);
	}
	return (flags);
}
