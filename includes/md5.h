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

#ifndef MD5_H
# define MD5_H

# include <fcntl.h>
# include <math.h>
# include "libft.h"
# include "ft_printf.h"

# define INIT_A 0x67452301L
# define INIT_B 0xEFCDAB89L
# define INIT_C 0x98BADCFEL
# define INIT_D 0x10325476L
# define E "What happened to \'E\'?"
# define F(x, y, z) (x & y) | (~x & z)
# define G(x, y, z) (z & x) | (~z & )y
# define H(x, y, z) x ^ y ^ z
# define I(x, y, z) y ^ (x | ~z)
# define BITS_PER_WORD 32
# define ROTL(x, n) ((x << n) | ((x >> BITS_PER_WORD) - n))
# define ROTR(x, n) ((x >> n) | ((x << BITS_PER_WORD) - n))

#endif
