/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 16:22:59 by csinglet          #+#    #+#             */
/*   Updated: 2019/06/06 16:23:01 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "ft_printf.h"

/*
** initial values for md5
*/
# define A0_BASE 0x67452301
# define B0_BASE 0xefcdab89
# define C0_BASE 0x98badcfe
# define D0_BASE 0x10325476

/*
** initial values for sha256
*/
# define H0_BASE 0x6a09e667
# define H1_BASE 0xbb67ae85
# define H2_BASE 0x3c6ef372
# define H3_BASE 0xa54ff53a
# define H4_BASE 0x510e527f
# define H5_BASE 0x9b05688c
# define H6_BASE 0x1f83d9ab
# define H7_BASE 0x5be0cd19

/*
** flag bitmasks
*/
# define FLAG_P (1 << 0)
# define FLAG_Q (1 << 1)
# define FLAG_R (1 << 2)
# define FLAG_S (1 << 3)

/*
** input types
*/
# define PIPE_INPUT (1 << 4)

# define BITS_PER_WORD 32
# define MAXIMUM_ROUNDS 64
# define ROTL(x, n) ((x << n) | (x >> (32 - n)))
# define ROTR(x, n) ((x >> n) | (x << (32 - n)))

typedef struct		s_md5
{
	unsigned		flags;
	uint32_t		*uint32_buff;
	unsigned		a0;
	unsigned		b0;
	unsigned		c0;
	unsigned		d0;
	unsigned		a;
	unsigned		b;
	unsigned		c;
	unsigned		d;
	unsigned		f;
	unsigned		g;
}					t_md5;

typedef struct		s_sha256
{
	unsigned		flags;
	uint32_t		uint32_buff[64];
	unsigned		s0;
	unsigned		s1;
	unsigned		h0;
	unsigned		h1;
	unsigned		h2;
	unsigned		h3;
	unsigned		h4;
	unsigned		h5;
	unsigned		h6;
	unsigned		h7;
	unsigned		a;
	unsigned		b;
	unsigned		c;
	unsigned		d;
	unsigned		e;
	unsigned		f;
	unsigned		g;
	unsigned		h;
	unsigned		ch;
	unsigned		temp1;
	unsigned		temp2;
	unsigned		maj;
}					t_sha256;

typedef struct		s_token
{
	unsigned		type;
	char			*content;
	struct s_token	*next;
}					t_token;

/*
** main.c
*/
void				print_bits(void *bytes, int number_of_bytes);

/*
** md5.c
*/
void				md5(t_md5 *vars, uint8_t *block);

/*
** md5_support.c
*/
void				md5_dispatch(int ac, char **av, unsigned flags,
					t_token *tokens);

/*
** sha256.c
*/
void				sha256(t_sha256 *vars, uint8_t *block);

/*
** sha256_support.c
*/
void				sha256_dispatch(int ac, char **av, unsigned flags,
					t_token *tokens);

/*
** printing.c
*/
void				print_md5_result(t_md5 *vars, char *name, int flags);
void				print_sha256_result(t_sha256 *vars, char *name, int flags);

/*
** tokens.c
*/
t_token				*get_tokens(int ac, char **av);
void				free_token_list(t_token *token_list);

/*
** utils.c
*/
unsigned			reverse_bytes(unsigned n);
unsigned			set_flags(int ac, char **av);

#endif
