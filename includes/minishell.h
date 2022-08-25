/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:24:55 by telee             #+#    #+#             */
/*   Updated: 2022/08/25 21:49:13 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../libft/includes/libft.h"

# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define SPC   "                                "
# define PROMPT	"minisiao$ "

# define DOUBLE_PIPE 2

typedef enum e_err
{
	NO_ERROR,
	MALLOC_FAIL,
	INPUT_ERR,
	KEY_ERR,
	NO_VALUE,
	NO_KEY,
	SYNTAX_ERR,
	EMPTY,
	DEFAULT_ERR
}		t_err;

typedef enum s_node
{
	PIPE,
	NO_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	HERE_DOC,
	CMD
}		t_node;

typedef enum s_token_t
{
	TOK_WORD,
	TOK_PIPE,
	TOK_QUOTE,
	TOK_DQUOTE,
	TOK_DOLLAR,
	TOK_REDIR_IN,
	TOK_REDIR_OUT,
	TOK_APPEND,
	TOK_HERE_DOC,
	TOK_SPACE,
	TOK_NO_TOKENS,
	TOK_ERROR
}		t_token_t;

typedef struct s_token
{
	int				id;
	t_token_t		type;
	char			*data;
	int				parsed;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_tree
{
	int				id;
	t_node			type;
	char			**data;
	struct s_tree	*next_root;
	struct s_tree	*leaf;
	struct s_tree	*prev;
}		t_tree;

typedef struct s_input
{
	t_token	*lexer;
	t_tree	*tree;
}		t_input;

typedef struct s_item
{
	char	*key;
	char	*value;
}		t_item;

typedef struct s_exec
{
	int	fd_in[2];
	int	fd_out[2];
	int	index;
	int	builtin_check;
}	t_exec;

typedef struct s_env
{
	t_item			*item;
	char			**envp;
	struct termios	termios_p;
	int				exitcode;
	t_tree			**tree_addr;
	t_exec			*exec;
}		t_env;

//	input_init.c - OK
t_err	init_ms_env(char **envp, t_env *ms_env);
t_err	ms_env_to_envp(t_item *item, char ***env_var);
t_err	key_and_value(t_item *item, char **var);
t_err	update_shlvl(t_env *ms_env);
t_err	envp_to_ms_env(char *str, t_item *custom_envp);

//	input_ms_env.c - OK
t_err	get_env_key(const char *str, char **return_key);
t_err	get_env_value(t_item *item, char *key, char **value_ptr);
t_err	update_ms_env(char *key, char *value, t_item **head);
t_err	update_value(char *key, char *value, t_item *envp);
int		ms_env_key(char *key, t_item *item);

//	input_loop_do.c - OK
int		run_ms(t_input *curr_input, t_env *ms_env);
t_err	get_input(t_env *ms_env, char **input_ptr);
t_err	process_input(char *line, t_input *input, t_env *ms_env);
t_err	lexer(char *line, t_input *input);
void	start_tree(t_env *ms_env, t_tree **tree);

//	input_signals.c - OK
void	ms_signals(char *str);
void	new_readline(int sig);
int		exit_signal(t_env *ms_env);
void	process_signal(int sig, int *exitcode, int fd[2]);
void	set_term_settings(void);

//	input_tokenize.c - OK
t_err	tokenize(char *input, int *i, t_token **list);
t_err	redir_input(char *input, int *i, t_token **list);
t_err	pipes(char *input, int *i, t_token **list);
t_err	words(char *input, int *i, t_token **list);
t_err	spaces(char *input, int *i, t_token **list);

//	input_parser.c - OK
t_err	parser(t_input *input);
t_err	pipe_syntax_pass(t_token *list);
t_err	redir_syn_root_pass(t_token *list, t_tree **root);
t_err	redir_pass(t_token *list, t_tree **root);
t_err	cmd_pass(t_token *list, t_tree **root);

//	input_utils.c - OK
char	**make_split(t_token *list, int word_amount);
char	**create_cmd_split(t_token *list, int word_count);
int		allowed_char(int c, char *not_allowed);
t_err	syntax_err(t_token_t type);
t_err	syntax_err_lexer(char token);

//	input_expander.c - OK
t_err	expander(t_input *input, t_env *ms_env);
t_err	quotes_to_words(t_token **list);
t_err	expand_dollars_words(t_token **list, t_env *ms_env);
t_err	word_join(t_token **list);

//	input_cleaner.c - OK
void	clean_tree(t_tree **head_tree);
void	clean_lexer(t_token **list);
void	free_envi(t_env *ms_env, int exitcode);
void	free_ms_env(t_item *item);
void	free_split(char ***split);

//	tokens_create_token.c - OK
t_token	*create_token(t_token_t type, char *data);
t_err	add_new_token(t_token	**head, t_token_t type, char *data);
void	add_to_tokenlist(t_token **head, t_token *new);
t_err	insert_tokens(t_token **head, char *key, char *value, char *data);
t_err	rm_tokens(t_token *new_token, char **str);

//	tokens_modify_token.c - OK
void	remove_token_head(t_token **head);
void	remove_token(t_token *list);
t_err	join_token_head(t_token **list, t_token_t resulting_type);
t_err	join_token(t_token *list, t_token_t resulting_type);
t_err	newstr_token(t_token **head, char *key, char *data);

//	tokens_modify_tokens_utils.c - OK
t_err	sub_token_head(t_token **head, char *key, char *value, char *data);
t_err	sub_token(t_token *list, char *key, char *value, char *data);
t_token	*token_tail(char *key, char *data);
t_err	exitcode_token(const char *dquote, int *j, t_token **list);

//	tokens_rm_token.c - OK
void	del_token(t_token *list);
t_err	rm_double_tokens(t_token **list, t_token_t type);
t_err	rm_token_type(t_token **list, t_token_t type);
void	replace_token(t_token *list, t_token *new);
void	replace_token_head(t_token **head, t_token *new);

//	tokens_dollars.c - OK
t_err	dollars(char *input, int *i, t_token **list);
t_err	add_dollar_sign(t_token	**list);
t_err	expand_dollars(t_token **head, t_env *ms_env, char *key);
t_err	expand_d_utils(t_token **head, t_env *ms_env, char *key, char *data);
t_err	expand_dollars_tail(t_token **head, char *key, char *data);

//	tokens_quotes.c - OK
t_err	quotes(char *input, int *i, t_token **list);
t_err	save_quote(const char *line, char **quote, char *input);
t_err	dquote_dollars(const char *dquote, int *j, t_token **list);
t_err	expand_dquote_dollars(const char *dquote, t_token **list);

//	tree_nodes.c - OK
t_tree	*create_tree_node(t_node type, char **data);
void	add_root_node(t_node type, t_tree **head_tree);
t_err	add_leaf_node(t_node type, char **data, t_tree *parent);
t_token	*next_branch(t_token *list);
t_tree	*get_next_node(t_tree *tree);

//	tree_build_tree.c - OK
int		build_tree(t_env *ms_env, t_tree *tree, t_exec *exec);
int		wait_child(t_exec *exec, t_env *ms_env);
int		close_fd(int fd[2]);
void	close_all(t_exec *exec);

//	tree_pipe.c - OK
int		start_pipe(t_env *ms_env, t_tree *tree, t_exec *exec);
void	start_pipe_utils(t_tree *tree, t_env *ms_env, t_exec *exec);
int		mid_pipe(t_env *ms_env, t_tree *tree, t_exec *exec);
void	mid_pipe_utils(t_tree *tree, t_env *ms_env, t_exec *exec);

//	tree_nopipe.c - OK
int		start_nopipe(t_env *ms_env, t_tree *tree, t_exec *exec);
int		check_cmd_data(t_tree *tree, t_env *ms_env, t_exec *exec);
int		end_nopipe(t_tree *tree, t_env *ms_env, t_exec *exec);
void	nopipe_child(t_tree *tree, t_env *ms_env, t_exec *exec);
int		end_nopipe_utils(t_tree *tree, pid_t pid, int status);

//	tree_loop.c - OK
int		handle_end_nopipe(t_env *ms_env, t_exec *exec, t_tree *tree);
int		handle_start_pipe(t_env *ms_env, t_exec *exec, t_tree *tree);
int		handle_redir_io(t_tree *tree, t_exec *exec, t_env *ms_env);
int		handle_app_heredoc(t_tree *tree, t_exec *exec, t_env *ms_env);

//	tree_heredoc.c - OK
void	handle_heredoc(t_exec *exec, t_env *ms_env);
int		make_heredoc(char *delim);
int		prev_heredoc_exists(t_tree *tree);

//	tree_error.c - OK
int		exec_error(int code, int *fd, t_env *ms_env);
int		redir_error(t_tree *tree, int fd, t_env *ms_env);
int		export_error_msg(char *str);
int		unset_error_msg(char *str);

//	tree_exit.c - OK
void	exit_multi_arg(t_tree *tree, t_env *ms_env, int i);
void	exit_numeric(t_tree *tree, t_env *ms_env, char c);
void	exit_one_arg(t_tree *tree, t_env *ms_env, int i);
void	exit_one_range(t_tree *tree, t_env *ms_env);
int		exit_cmd(t_tree *tree, t_env *ms_env);

//	tree_utils.c - OK
int		check_signs(char *str);
int		check_isalpha(char *str);
int		check_isdigit(char *str);
size_t	atoi_exit(const char *str);

//	builtin_echo.c - OK
int		builtin_echo(t_env *ms_env, t_tree *tree);
int		handle_echo(t_tree *tree, int i, int check, int err);
int		print_echo(t_tree *tree, int i, int err);

//	builtin_pwd.c - OK
int		builtin_pwd(t_env *ms_env);
char	*pwd_get(char **envp);

//	builtin_cd.c - OK
t_err	ms_cd(char **argv, t_env *ms_env);
t_err	update_pwds(char *path, t_env *ms_env);
t_err	update_oldpwd(t_env *ms_env, char *curr_pwd);
char	*parse_path(char *path, char *old_pwd);
int		copy_paths(char parse_path[512], char *path);

//	builtin_cd_utils.c - OK
int		ms_perror(char *perror_str, char *string, char *string2, int rv);
int		add_str(char *perror_str, char *string2, int rv);
void	remove_dir(char parse_path[512]);
void	ms_cd_utils(char **str);

//	builtin_paths.c - OK
int		get_paths(t_env *ms_env, char **arg);
char	*get_path_env(char **envp, t_env *ms_env);
int		access_exec(t_env *ms_env, char **arg, char **paths);
int		parse_dir(char **envp, char **arg, t_env *ms_env, char **paths);
char	**edit_paths(char **paths, char **arg, int i);

//	builtin_paths_utils.c - OK
char	*search_bins(char **exec_paths);
int		check_access(char *path, char **envp, char **arg, t_env *ms_env);
void	*free_paths(char **first, char **second, char *third);
void	cmd_not_found(char **arg, t_env *ms_env, char **paths);
int		parse_dir_utils(char *str);

//	builtin_paths_utils_a.c - OK
void	dir_exit(char **arg, t_env *ms_env, char **paths);
int		is_dir(char **envp, char **arg, t_env *ms_env, char **paths);

//	builtin_export.c - OK
int		ms_export(char **argv, t_env *ms_env);
t_err	export_ready(t_item *item);
t_err	dup_env_key(const char *str, char **return_key);
int		export_key(char *key);
t_err	extract_to_ms_env(char *str, t_item **item, char *key);

//	builtin_export_utils.c - OK
t_err	join_values(char *value, char *key, t_item *item, char **joined);
t_err	add_to_ms_env(t_item **item, char *key, char *value);
int		export_not_ready(int *arr, int arr_len);
t_err	print_first_ms_env(t_item *item, int *arr, int arr_len);
char	*first_ms_env(t_item *item, int *arr, int arr_len);

//	builtin_export_utils_a.c - OK
int		smallest_ms_env(char *key, t_item *item, int *arr);
void	print_key(char *key, t_item *item);
void	mark_array(char *key, t_item *item, int *arr);
int		ms_env_len(t_item *item);

//	builtin_unset.c - OK
int		ms_unset(char **argv, t_env *ms_env);
int		unset_key(char *key);
t_err	rm_ms_env(char *key, t_item **envp);
void	copy_or_rm(t_item **envp, char *key, t_item **new_envp);

//	builtin.c - OK
int		start_builtin(t_tree *tree, t_env *ms_env, t_exec *exec);
int		check_builtin(t_tree *tree, t_env *ms_env);
int		check_builtin_utils(t_tree *tree, t_env *ms_env, int i);
int		print_ms_env(char **argv, t_env *ms_env);
int		check_builtin_child(t_tree *tree, t_env *ms_env);

#endif