/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 13:11:02 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/08 13:11:03 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

/*
**	Formula: (Use the table, it is more accurate)
**	for (int i = 0; i < 64; i++)
**	{
** 		s[i] = floor(pow(2, 32) * fabs(sin(i + 1)));
**	}
*/

const int g_md5_s[] = {
	7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21
};

const int g_md5_k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391
};

static void		init_working_variables(t_md5 *vars)
{
	vars->a = vars->a0;
	vars->b = vars->b0;
	vars->c = vars->c0;
	vars->d = vars->d0;
}

static void		adjust_working_variables(t_md5 *vars, unsigned i)
{
	vars->f = vars->f + vars->a + g_md5_k[i] + vars->uint32_buff[vars->g];
	vars->a = vars->d;
	vars->d = vars->c;
	vars->c = vars->b;
	vars->b += ROTL(vars->f, g_md5_s[i]);
}

static void		adjust_base_variables(t_md5 *vars)
{
	vars->a0 += vars->a;
	vars->b0 += vars->b;
	vars->c0 += vars->c;
	vars->d0 += vars->d;
}

static void		md5_hash(t_md5 *vars, unsigned i)
{
	if (i < 16)
	{
		vars->f = (vars->b & vars->c) | ((~vars->b) & vars->d);
		vars->g = i;
	}
	else if (i < 32)
	{
		vars->f = (vars->d & vars->b) | ((~vars->d) & vars->c);
		vars->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		vars->f = vars->b ^ vars->c ^ vars->d;
		vars->g = (3 * i + 5) % 16;
	}
	else
	{
		vars->f = vars->c ^ (vars->b | (~vars->d));
		vars->g = (7 * i) % 16;
	}
}

void			md5(t_md5 *vars, uint8_t *block)
{
	unsigned	i;

	i = -1;
	vars->uint32_buff = (uint32_t *)block;
	init_working_variables(vars);
	while (++i < MAXIMUM_ROUNDS)
	{
		md5_hash(vars, i);
		adjust_working_variables(vars, i);
	}
	adjust_base_variables(vars);
}
