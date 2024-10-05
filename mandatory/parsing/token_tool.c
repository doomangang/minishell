/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 11:07:37 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/05 05:16:21 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*append_char(char *buf, char c)
{
	char	*new;
	int		size;

	size = ft_strlen(buf);
	new = (char *)ft_calloc(sizeof(char), size + 2);
	if (!new)
		common_error("malloc", 0, 0, 0);
	ft_memcpy(new, buf, size);
	new[size] = c;
	new[size + 1] = 0;
	free(buf);
	return (new);
}

char	*get_redirect(char **ptr)
{
	char	*redirect;

	redirect = 0;
	if (**ptr == '>')
	{
		if (*(*ptr + 1) == '>')
			redirect = ft_strdup(">>");
		else
			redirect = ft_strdup(">");
	}
	else if (**ptr == '<')
	{
		if (*(*ptr + 1) == '<')
			redirect = ft_strdup("<<");
		else
			redirect = ft_strdup("<");
	}
	if (!redirect)
		common_error("malloc", 0, 0, 0);
	if (ft_strlen(redirect) > 1)
		(*ptr)++;
	return (redirect);
}

char	*get_pipe(void)
{
	char	*pipe;

	pipe = ft_strdup("|");
	if (!pipe)
		common_error("malloc", 0, 0, 0);
	return (pipe);
}

char	*reset_buf(void)
{
	char	*new_buf;

	new_buf = ft_strdup("");
	if (!new_buf)
		common_error("malloc", 0, 0, 0);
	return (new_buf);
}

void	consume_token(t_token **ptr)
{
	if (!ptr || !*ptr)
		return ;
	*ptr = (*ptr)->next;
}

