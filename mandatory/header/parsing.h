/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyjeon <jihyjeon@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 18:42:21 by jihyjeon          #+#    #+#             */
/*   Updated: 2024/10/03 19:52:48 by jihyjeon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

//process_line (parse main)
int				parse_main(char *line, t_line *input);
int				check_quote(char *line);
int				tokenize(char *line, t_token **tokens, t_line *input);
t_process		*lexer(t_token *tokens, t_line *input);
int				add_token(t_token **token, char *s, t_tokentype type, int flag);
//tokenize
t_state			handle_general(t_token **t, char **b, char **p, int *s);
t_state			handle_quote(t_state state, char c, char **buf, t_line *line);
char			*append_char(char *buf, char c);
char			*get_redirect(char **ptr);
char			*reset_buf(int *sq_flag);
//lexer
char			*key_to_value(char *word, t_line *input);
char			*insert_value(char *origin, char *val, int name_size);
//parser
t_process		*parse_pipe(t_token **ptr);
char			**parse_command(t_token **ptr, t_redirection **redirect);
void			append_redir(t_redirection **head, t_token **ptr, int type);
char			**append_simple_cmd(char **cmd, t_token **ptr);
//node (util)
t_token			*create_token_node(t_tokentype type, int sq_flag);
t_process		*create_process_node(void);
t_redirection	*create_redir_node(int redir_type);
t_env			*create_env_node(char *key, char *value);
int				which_redir(char *word);
//env
t_env			*make_env(char **envp);
char			**make_envp(t_env *env);
int				insert_env(t_line *line, char *key, char *value);
void			init_env(t_line *line, char **envp);
int				change_env_value(t_line *line, char *key, char *new_value);
t_env			*get_key_value(char **envp);

//main (temp)
#endif