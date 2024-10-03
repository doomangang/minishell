/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:11:41 by yuyu              #+#    #+#             */
/*   Updated: 2024/10/03 20:51:39 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_line	*line;
	char	*str;

	// 초기 parse
	// $?를 env에 추가...
	line = (t_line *)ft_calloc(sizeof(t_line), 1);
	// if (!line)
	// 	common_error("malloc", NULL, NULL, 1);
	init_env(line, envp);
	line->argc = argc;
	line->argv = argv;
	// std_fd_dup(line); // 기존 표준 입출력 복사.
	while (1)
	{
		str = readline("minishell$ ");
		add_history(str);
		parse_main(str, line);
		//  printf("%s\n", str);
		//  t_env *e_ptr = line->env;
		//  while (e_ptr)
		//  {
		//  	printf("%s=%s\n", e_ptr->key, e_ptr->value);
		//  	e_ptr = e_ptr->env_next;
		//  }
		t_process	*p = line->proc;
		char **cmd;
		t_redirection *r_ptr;
		while (p){
			cmd = p->cmd;
			// printf("user input : %s\n", str);
			while (*cmd)
			{
				printf("%s", *cmd);
				printf(" ");
				cmd++;
			}
			printf("redir\n");
			r_ptr = p->redirect_node;
			while (r_ptr)
			{
				if (r_ptr->type == REDIR_INPUT)
					printf("< %s ", r_ptr->file_name);
				if (r_ptr->type == REDIR_DELIMIT)
					printf("<< %s ", r_ptr->here_doc_eof);
				if (r_ptr->type == REDIR_OUTPUT)
					printf("> %s ", r_ptr->file_name);
				if (r_ptr->type == REDIR_APPEND)
					printf(">> %s ", r_ptr->file_name);
				r_ptr = r_ptr->redirect_next;
			}
			if (p->process_next)
				printf("| ");
			p = p->process_next;
		}
		printf("\n");
		free(str);
		line->proc = 0;
	}
	// rl_clear_history();
	exit(errno);
}


void	common_error(char *cmd, char *file_name, char *custom_msg, int error_code)
{
	const char	*error_msg = strerror(errno);

	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
	}
	if (file_name)
	{
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd(": ", 2);
	}
	if (custom_msg)
		ft_putendl_fd(custom_msg, 2);
	else
		ft_putendl_fd(error_msg, 2);
	if (error_code)
		exit(error_code);
	exit(errno);
}
