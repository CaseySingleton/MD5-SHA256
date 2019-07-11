/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:58:10 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/09 16:58:11 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void			print_md5_result(t_md5 *vars, char *name, int flags)
{
	if (!(flags & (FLAG_Q | FLAG_R | PIPE_INPUT)))
	{
		if (flags & FLAG_S)
			ft_printf("MD5 (\"%s\") = ", name);
		else
			ft_printf("MD5 (%s) = ", name);
	}
	vars->a0 = reverse_bytes(vars->a0);
	vars->b0 = reverse_bytes(vars->b0);
	vars->c0 = reverse_bytes(vars->c0);
	vars->d0 = reverse_bytes(vars->d0);
	ft_printf("%.8x%.8x%.8x%.8x", vars->a0, vars->b0, vars->c0, vars->d0);
	if (!(flags & (FLAG_Q | PIPE_INPUT)) && (flags & FLAG_R))
	{
		if (flags & FLAG_S)
			ft_printf(" \"%s\"", name);
		else
			ft_printf(" %s", name);
	}
	ft_printf("\n");
}

void			print_sha256_result(t_sha256 *vars, char *name, int flags)
{
	if (!(flags & (FLAG_Q | FLAG_R | PIPE_INPUT)))
	{
		if (flags & FLAG_S)
			ft_printf("SHA256 (\"%s\") = ", name);
		else
			ft_printf("SHA256 (%s) = ", name);
	}
	ft_printf("%.8x%.8x%.8x%.8x", vars->h0, vars->h1, vars->h2, vars->h3);
	ft_printf("%.8x%.8x%.8x%.8x", vars->h4, vars->h5, vars->h6, vars->h7);
	if (!(flags & (FLAG_Q | PIPE_INPUT)) && (flags & FLAG_R))
	{
		if (flags & FLAG_S)
			ft_printf(" \"%s\"", name);
		else
			ft_printf(" %s", name);
	}
	ft_printf("\n");
}
