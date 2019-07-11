/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 19:08:54 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/08 19:08:54 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

const int		g_sha256_k[] = {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
	0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
	0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
	0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
	0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
	0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static void		init_working_variables(t_sha256 *vars)
{
	vars->a = vars->h0;
	vars->b = vars->h1;
	vars->c = vars->h2;
	vars->d = vars->h3;
	vars->e = vars->h4;
	vars->f = vars->h5;
	vars->g = vars->h6;
	vars->h = vars->h7;
}

static void		adjust_base_variables(t_sha256 *vars)
{
	vars->h0 += vars->a;
	vars->h1 += vars->b;
	vars->h2 += vars->c;
	vars->h3 += vars->d;
	vars->h4 += vars->e;
	vars->h5 += vars->f;
	vars->h6 += vars->g;
	vars->h7 += vars->h;
}

static void		sha256_setup(t_sha256 *vars, uint8_t *block)
{
	unsigned	i;

	ft_bzero(vars->uint32_buff, sizeof(uint32_t) * 64);
	i = -1;
	while (++i < 16)
		vars->uint32_buff[i] = reverse_bytes(((uint32_t *)block)[i]);
	i = 15;
	while (++i < 64)
	{
		vars->s0 = (ROTR(vars->uint32_buff[i - 15], 7) ^\
		(ROTR(vars->uint32_buff[i - 15], 18) ^\
		(vars->uint32_buff[i - 15] >> 3)));
		vars->s1 = (ROTR(vars->uint32_buff[i - 2], 17) ^\
		(ROTR(vars->uint32_buff[i - 2], 19) ^\
		(vars->uint32_buff[i - 2] >> 10)));
		vars->uint32_buff[i] = vars->uint32_buff[i - 16] +\
		vars->s0 + vars->uint32_buff[i - 7] + vars->s1;
	}
}

static void		sha256_hash(t_sha256 *vars, unsigned i)
{
	vars->s1 = (ROTR(vars->e, 6) ^ (ROTR(vars->e, 11)) ^ (ROTR(vars->e, 25)));
	vars->ch = (vars->e & vars->f) ^ ((~vars->e) & vars->g);
	vars->temp1 = vars->h + vars->s1 + vars->ch + g_sha256_k[i] +\
	vars->uint32_buff[i];
	vars->s0 = (ROTR(vars->a, 2) ^ ROTR(vars->a, 13) ^ ROTR(vars->a, 22));
	vars->maj = (vars->a & vars->b) ^ (vars->a & vars->c) ^ (vars->b & vars->c);
	vars->temp2 = vars->s0 + vars->maj;
	vars->h = vars->g;
	vars->g = vars->f;
	vars->f = vars->e;
	vars->e = vars->d + vars->temp1;
	vars->d = vars->c;
	vars->c = vars->b;
	vars->b = vars->a;
	vars->a = vars->temp1 + vars->temp2;
}

void			sha256(t_sha256 *vars, uint8_t *block)
{
	unsigned	i;

	sha256_setup(vars, block);
	init_working_variables(vars);
	i = -1;
	while (++i < MAXIMUM_ROUNDS)
	{
		sha256_hash(vars, i);
	}
	adjust_base_variables(vars);
}
