/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:12:52 by yuyu              #+#    #+#             */
/*   Updated: 2024/09/02 19:49:29 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
// # include <unistd.h>
// # include <stddef.h>
// # include <stdlib.h>

# include <stdio.h>
// printf
# include <readline/readline.h>
// readline, rl_clear_history, rl_on_new_line, rl_replace_line, rl_redisplay, add_history
# include <fcntl.h>
// open
# include <sys/wait.h>
// wait, waitpid, wait3, wait4
# include <signal.h>
// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>
// stat, lstat, fstat
# include <dirent.h>
// opendir, readdir, closedir
# include <string.h>
// strerror
# include <sys/ioctl.h>
// ioctl
# include <termios.h>
// tcsetattr, tcgerattr
# include <term.h>
// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

// global variable
int	singal;

typedef struct s_command
{
	char	*line;
	char	**path;
	char	**command;
	char	**env;
	int		flag;
	pid_t	*pid;
	// char	**pipe;
	// char	**cc;
	// char 	**filename;
	
}	t_command;

#endif
