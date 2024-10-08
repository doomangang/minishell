/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 17:04:28 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/06 16:31:50 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	process_line(char *line, t_line *input)
{
	t_token	*tokens;
	t_token	*ptr;
	int		flag;

	if (!line || !ft_strlen(line))
		return (FAIL);
	if (check_quote(line) == FAIL)
		return (syntax_error(input, 0, QUOTE_INCOMPLETE));
	tokens = 0;
	tokenize(line, &tokens, input);
	flag = SUCCESS;
	ptr = tokens;
	input->proc = parse_pipe(&tokens, &flag, input);
	free_tokens(&ptr);
	if (flag == SYNTAX_ERROR || !input->proc)
		return (FAIL);
	return (SUCCESS);
}

int	check_quote(char *line)
{
	int	quote_flag;
	int	dquote_flag;
	int	i;

	quote_flag = 0;
	dquote_flag = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'' && !dquote_flag)
			quote_flag = !quote_flag;
		else if (line[i] == '"' && !quote_flag)
			dquote_flag = !dquote_flag;
		i++;
	}
	if (quote_flag || dquote_flag)
		return (FAIL);
	return (SUCCESS);
}

void	tokenize(char *line, t_token **tokens, t_line *input)
{
	char	*curr;
	char	*buf;
	t_state	state;

	buf = reset_buf(&state);
	curr = line;
	while (*curr)
	{
		if (state == STATE_GENERAL)
		{
			if (*curr == '$')
				handle_dollar(&buf, &curr, input);
			else
				state = handle_general(tokens, &buf, &curr);
		}
		else if (state == STATE_HEREDOC)
			state = handle_redir(tokens, &curr, &buf, state);
		else
			state = handle_quote(state, &curr, &buf, input);
		curr++;
	}
	if (ft_strlen(buf) > 0)
		add_token(tokens, buf, TOKEN_STRING);
	free(buf);
}

int	syntax_error(t_line *line, t_token *error_pos, int error_code)
{
	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (error_code == QUOTE_INCOMPLETE)
		ft_putendl_fd("syntax error quote is incomplete", 2);
	else
	{
		ft_putstr_fd("syntax error near unexpected token `", 2);
		if (!error_pos)
			ft_putstr_fd("newline", 2);
		else
			ft_putstr_fd(error_pos->word, 2);
		ft_putendl_fd("'", 2);
	}
	change_exit_code(line, SYNTAX_ERROR);
	return (error_code);
}

int	empty_quote(char *str)
{
	char	quote;

	quote = *str;
	if (*(str + 1) == quote)
	{
		if (ft_isspace(*(str + 2)))
			return (SUCCESS);
		if (*(str + 2) == '|')
			return (SUCCESS);
		if (*(str + 2) == '>' || *(str + 2) == '<')
			return (SUCCESS);
		if (*(str + 2) == 0)
			return (SUCCESS);
	}
	return (FAIL);
}
