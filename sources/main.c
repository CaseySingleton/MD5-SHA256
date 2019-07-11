/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:24:00 by csinglet          #+#    #+#             */
/*   Updated: 2019/06/06 16:24:01 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			choose_algorithm(int ac, char **av, unsigned flags,
					t_token *tokens)
{
	if (ac > 2 || !isatty(0))
	{
		if (ft_strcmp(av[1], "md5") == 0)
			md5_dispatch(ac, av, flags, tokens);
		else if (ft_strcmp(av[1], "sha256") == 0)
			sha256_dispatch(ac, av, flags, tokens);
	}
}

int					main(int argc, char *argv[])
{
	t_token			*tokens;
	unsigned		flags;

	if ((flags = set_flags(argc, argv)) == -1)
		return (0);
	tokens = get_tokens(argc, argv);
	if (argc >= 2 || !isatty(0))
	{
		if (!ft_strcmp(argv[1], "md5") || !ft_strcmp(argv[1], "sha256"))
			choose_algorithm(argc, argv, flags, tokens);
		else
			ft_printf("ft_ssl: \'%s\' is an invalid command\n", argv[1]);
	}
	else
		ft_printf("usage: ft_ssl [name] [flags] [-s string] [files...]\n");
	return (0);
}
