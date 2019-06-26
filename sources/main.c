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

#include "md5.h"

/*
#define R0(a,b,c,d,k,s,t) { \
	a+=((k)+(t)+F((b),(c),(d))); \
	a=ROTATE(a,s); \
	a+=b; };\

#define R1(a,b,c,d,k,s,t) { \
	a += ((k) + (t) + G((b),(c),(d))); \
	a=ROTATE(a,s); \
	a+=b; };

#define R2(a,b,c,d,k,s,t) { \
	a+=((k)+(t)+H((b),(c),(d))); \
	a=ROTATE(a,s); \
	a+=b; };

#define R3(a,b,c,d,k,s,t) { \
	a+=((k)+(t)+I((b),(c),(d))); \
	a=ROTATE(a,s); \
	a+=b; };

Formula:
for i from 0 to 63
    K[i] := floor(232 × abs(sin(i + 1)))

Or the table:
K[ 0.. 3] := { 0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee }
K[ 4.. 7] := { 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 }
K[ 8..11] := { 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be }
K[12..15] := { 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 }
K[16..19] := { 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa }
K[20..23] := { 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 }
K[24..27] := { 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed }
K[28..31] := { 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a }
K[32..35] := { 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c }
K[36..39] := { 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 }
K[40..43] := { 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 }
K[44..47] := { 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 }
K[48..51] := { 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 }
K[52..55] := { 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 }
K[56..59] := { 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 }
K[60..63] := { 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 }
*/

void			read_file(char *file_name)
{
	int			fd;
	int			bytes_read;
	int			panic_bits;
	int			total_bytes_read;
	int			buff[64 * 2];
	unsigned int	k[64];
	unsigned long	a;
	unsigned long	b;
	unsigned long	c;
	unsigned long	d;
	unsigned long	aa = INIT_A;
	unsigned long	bb = INIT_B;
	unsigned long	cc = INIT_C;
	unsigned long	dd = INIT_D;

	total_bytes_read = 0;
	fd = open(file_name, O_RDONLY);
	if (fd > -1)
	{
		// ft_printf("File: \'%s\': is valid\n", file_name);
		for (int i = 0; i < 64; i++)
		{
			long j = pow(2, 32);
			k[i] = floor(j * fabs(sin(i + 1)));
			// printf("%x, ", k[i]);
		}
		while ((bytes_read = read(fd, buff, 64)) > 0)
		{
			a = aa;
			b = bb;
			c = cc;
			d = dd;
			total_bytes_read += bytes_read;
			unsigned long	f;
			int				g;
			int				s[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
			if (bytes_read < 64)
			{
				ft_printf("APPEND THAT SHIT\n");
				if (bytes_read < 56)
					ft_printf("FINAL ROUND\n");
				else
				{
					ft_printf("APPEND 1 and 0's\n");
					
				}
			}
			for (int i = 0; i < 64; i++)
			{
				if (i < 16)
				{
					f = (b & c) | (~b & d);
					g = i;
				}
				else if (i < 32)
				{
					f = (d & b) | (~d & c);
					g = (i * 5) % 16;
				}
				else if (i < 48)
				{
					f = b ^ c ^ d;
					g = (i * 3) % 16;
				}
				else
				{
					f = c ^ (b | (~d));
					g = (i * 5) % 16;
				}
				f = f + a + k[i] + buff[g];
				a = d;
				d = c;
				c = b;
				b += ((f << s[i]) | ((f >> BITS_PER_WORD) - s[i]));
			}
			aa += a;
			bb += b;
			cc += c;
			dd += d;
		}
	}
	printf("a: %x\n", (int)a);
	printf("b: %x\n", (int)b);
	printf("c: %x\n", (int)c);
	printf("d: %x\n", (int)d);
	printf("%x%x%x%x\n", (int)a, (int)b, (int)c, (int)d);
	panic_bits = (64 - total_bytes_read % 64) - 8;
	ft_printf("Total bytes read: %d\n", total_bytes_read * 8);
	ft_printf("Panic bits: %d\n", panic_bits);
	ft_printf("Grand total: %d\n", total_bytes_read * 8 + panic_bits * 8 + 64);
}

int				main(int argc, char *argv[])
{
	int			i;
	uint64_t	test;

	i = 1;
    // ft_printf("Hello, ssl md5!\n");
	while (i < argc)
	{
		ft_printf("(%s) = ", argv[i]);
		read_file(argv[i++]);
	}
    return (0);
}
