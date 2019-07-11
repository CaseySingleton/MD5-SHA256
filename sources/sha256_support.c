/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_support.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:40:15 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/09 16:40:16 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			t_sha256_init(t_sha256 *sha256_variables)
{
	ft_bzero(sha256_variables, sizeof(t_sha256));
	sha256_variables->h0 = H0_BASE;
	sha256_variables->h1 = H1_BASE;
	sha256_variables->h2 = H2_BASE;
	sha256_variables->h3 = H3_BASE;
	sha256_variables->h4 = H4_BASE;
	sha256_variables->h5 = H5_BASE;
	sha256_variables->h6 = H6_BASE;
	sha256_variables->h7 = H7_BASE;
}

static void			apply_sha256_padding(uint8_t *block, uint64_t content_len,
					uint64_t message_len, t_sha256 *vars)
{
	unsigned		i;

	i = -1;
	ft_bzero(block + content_len, 64 - content_len);
	block[content_len] = 0x80;
	if (content_len == 56)
	{
		sha256(vars, block);
		ft_bzero(block, 64);
	}
	while (++i < 8)
		block[56 + i] = ((uint8_t *)&message_len)[7 - i];
	sha256(vars, block);
}

static void			sha256_string(uint8_t *content, t_sha256 *vars)
{
	uint8_t			block[64];
	uint64_t		content_len;
	uint64_t		message_len;

	content_len = ft_strlen((char *)content);
	message_len = content_len * 8;
	while (content_len >= 64)
	{
		ft_memcpy(block, content, 64);
		sha256(vars, block);
		content += 64;
		content_len -= 64;
	}
	ft_memcpy(block, content, content_len);
	apply_sha256_padding(block, content_len, message_len, vars);
}

static int			sha256_file(const char *file_name, t_sha256 *vars,
					unsigned flags)
{
	int				fd;
	uint8_t			block[64];
	unsigned long	content_len;
	unsigned long	message_len;

	message_len = 0;
	if (ft_strcmp(file_name, "stdin") == 0)
		fd = 0;
	else if ((fd = open(file_name, O_RDONLY)) < 0)
		return (ft_printf("%s: No such file or directory\n", file_name));
	while ((content_len = read(fd, block, 64)) == 64)
	{
		(fd == 0 && (flags & FLAG_P)) ? write(1, block, content_len) : 0;
		message_len += content_len * 8;
		sha256(vars, block);
	}
	(fd == 0 && (flags & FLAG_P)) ? write(1, block, content_len) : 0;
	message_len += content_len * 8;
	apply_sha256_padding(block, content_len, message_len, vars);
	close(fd);
	return (0);
}

void				sha256_dispatch(int ac, char **av, unsigned flags,
					t_token *tokens)
{
	t_sha256		sha256_variables;

	t_sha256_init(&sha256_variables);
	if (!isatty(0) && (tokens == NULL || flags & FLAG_P))
	{
		sha256_file("stdin", &sha256_variables, flags);
		print_sha256_result(&sha256_variables, "", flags | PIPE_INPUT);
		flags &= ~FLAG_P;
	}
	while (tokens != NULL)
	{
		t_sha256_init(&sha256_variables);
		if (flags & FLAG_S)
		{
			sha256_string((uint8_t *)tokens->content, &sha256_variables);
			print_sha256_result(&sha256_variables, tokens->content, flags);
			flags &= ~FLAG_S;
		}
		else if (sha256_file(tokens->content, &sha256_variables, flags) == 0)
			print_sha256_result(&sha256_variables, tokens->content, flags);
		tokens = tokens->next;
	}
}
