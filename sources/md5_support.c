/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_support.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csinglet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 16:40:07 by csinglet          #+#    #+#             */
/*   Updated: 2019/07/09 16:40:08 by csinglet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static void			t_md5_init(t_md5 *md5_variables)
{
	ft_bzero(md5_variables, sizeof(t_md5));
	md5_variables->a0 = A0_BASE;
	md5_variables->b0 = B0_BASE;
	md5_variables->c0 = C0_BASE;
	md5_variables->d0 = D0_BASE;
}

static void			apply_md5_padding(uint8_t *block, uint64_t content_len,
					uint64_t message_len, t_md5 *vars)
{
	ft_bzero(block + content_len, 64 - content_len);
	block[content_len] = 0x80;
	if (content_len == 56)
	{
		md5(vars, block);
		ft_bzero(block, 64);
	}
	((uint64_t *)block)[7] = message_len;
	md5(vars, block);
}

static void			md5_string(uint8_t *content, t_md5 *vars)
{
	uint8_t			block[64];
	uint64_t		content_len;
	uint64_t		message_len;

	content_len = ft_strlen((char *)content);
	message_len = content_len * 8;
	while (content_len >= 64)
	{
		ft_memcpy(block, content, (64 < content_len) ? 64 : content_len);
		md5(vars, block);
		content += (64 < content_len) ? 64 : content_len;
		content_len -= 64;
	}
	ft_memcpy(block, content, (64 < content_len) ? 64 : content_len);
	apply_md5_padding(block, content_len, message_len, vars);
}

static int			md5_file(const char *file_name, t_md5 *vars, unsigned flags)
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
		md5(vars, block);
	}
	(fd == 0 && (flags & FLAG_P)) ? write(1, block, content_len) : 0;
	message_len += content_len * 8;
	apply_md5_padding(block, content_len, message_len, vars);
	close(fd);
	return (0);
}

void				md5_dispatch(int ac, char **av, unsigned flags,
					t_token *tokens)
{
	t_md5			md5_variables;

	t_md5_init(&md5_variables);
	if (!isatty(0) && (tokens == NULL || flags & FLAG_P))
	{
		md5_file("stdin", &md5_variables, flags);
		print_md5_result(&md5_variables, "", flags | PIPE_INPUT);
		flags &= ~FLAG_P;
	}
	while (tokens != NULL)
	{
		t_md5_init(&md5_variables);
		if (flags & FLAG_S)
		{
			md5_string((uint8_t *)tokens->content, &md5_variables);
			print_md5_result(&md5_variables, tokens->content, flags);
			flags &= ~FLAG_S;
		}
		else if (md5_file(tokens->content, &md5_variables, flags) == 0)
			print_md5_result(&md5_variables, tokens->content, flags);
		tokens = tokens->next;
	}
}
