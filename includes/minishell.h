/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:24:55 by telee             #+#    #+#             */
/*   Updated: 2022/08/18 01:35:14 by telee            ###   ########.fr       */
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
int		do_loop(t_input *curr_input, t_env *ms_env);
t_err	get_input(t_env *ms_env, char **input_ptr);
t_err	process_input(char *line, t_input *input, t_env *info);
t_err	lexer(char *line, t_input *input);
void	ft_start_tree(t_env *ms_env, t_tree **tree);

//	input_signals.c - OK
void	ms_signals(char *str);
void	new_readline(int sig);
int		ft_exit_sig(t_env *ms_env);
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

//	input_expander.c - OK
t_err	expander(t_input *input, t_env *info);
t_err	quotes_to_words(t_token **list);
t_err	expand_dollars(t_token **list, t_env *info);
t_err	word_join(t_token **list);

//	input_cleaner.c - OK
void	clean_tree(t_tree **head_tree);
void	clean_lexer(t_token **list);
void	free_envi(t_env *ms_env, int exitcode);
void	free_ms_env(t_item *item);
void	ft_free_split(char ***split);

//	input_error.c - OK
t_err	syntax_err(t_token_t type);
t_err	syntax_err_lexer(char token);

//	tokens_create_token.c - OK
t_token	*create_token(t_token_t type, char *data);
t_err	add_new_token(t_token	**head, t_token_t type, char *data);
void	add_to_tokenlist(t_token **head, t_token *new);
t_err	insert_tokens(t_token **head, char *key, char *value, char *data);

//	tokens_modify_token.c - OK
void	remove_token(t_token *head);
t_err	join_head_token(t_token **list, t_token_t resulting_type);
t_err	join_token(t_token *list, t_token_t resulting_type);
t_err	insert_full_string(t_token **head, char *key, char *data);

//	tokens_modify_tokens_utils.c - OK
t_err	sub_head_token(t_token **head, char *key, char *value, char *data);
t_err	sub_token(t_token *list, char *key, char *value, char *data);
t_token	*create_tailpart(char *key, char *data);
t_err	exitcode_token(const char *dquote, int *j, t_token **list);

//	tokens_rm_token.c - OK
void	del_token(t_token *list);
t_err	rm_double_tokens(t_token **list, t_token_t type);
t_err	rm_token_type(t_token **list, t_token_t type);
void	replace_token(t_token *list, t_token *new);

//	tokens_dollars.c - OK
t_err	dollars(char *input, int *i, t_token **list);
t_err	add_dollar_sign(t_token	**list);
t_err	prep_expand_d(t_token **head, t_env *info, char *key);
t_err	expand_d(t_token **head, t_env *info, char *key, char *data);
t_err	expand_d_tailbit(t_token **head, char *key, char *data);

//	tokens_quotes.c - OK
t_err	quotes(char *input, int *i, t_token **list);
t_err	save_quote(const char *line, char **quote, char *input);
t_err	d_quote_dollars(const char *dquote, int *j, t_token **list);
t_err	expand_d_quote(const char *dquote, t_token **list);

//	tree_nodes.c - OK
t_tree	*create_tree_node(t_node type, char **data);
t_err	add_root_node(t_node type, t_tree **head_tree);
t_err	add_leaf_node(t_node type, char **data, t_tree *parent);
t_token	*next_branch(t_token *list);
t_tree	*get_next_node(t_tree *tree);

//	tree_handle_tree.c - OK
int		ft_handle_tree(t_env *ms_env, t_tree *tree, t_exec *exec);
int		ft_wait_on_children(t_exec *exec, t_env *ms_env);
int		ft_close_fd(int fd[2]);
void	ft_close_all(t_exec *exec);

//	tree_pipe.c - OK
int		ft_pipe_start(t_env *ms_env, t_tree *tree, t_exec *exec);
void	ft_helper_pipe_start(t_tree *tree, t_env *ms_env, t_exec *exec);
int		ft_pipe_inbetween(t_env *ms_env, t_tree *tree, t_exec *exec);
void	ft_helper_pipe_inbetween(t_tree *tree, t_env *ms_env, t_exec *exec);

//	tree_nopipe.c - OK
int		ft_nopipe_start(t_env *ms_env, t_tree *tree, t_exec *exec);
int		ft_check_nonwriteable(t_tree *tree, t_env *ms_env, t_exec *exec);
int		ft_nopipe_end(t_tree *tree, t_env *ms_env, t_exec *exec);
void	ft_nopipe_child(t_tree *tree, t_env *ms_env, t_exec *exec);
int		ft_nopipe_end_util(t_tree *tree, pid_t pid, int status);

//	tree_loop.c - OK
int		ft_handle_loop(t_env *ms_env, t_exec *exec, t_tree *tree);
int		ft_handle_loop_two(t_env *ms_env, t_exec *exec, t_tree *tree);
int		ft_redirs_loop(t_tree *tree, t_exec *exec, t_env *ms_env);
int		ft_redirs_loop_two(t_tree *tree, t_exec *exec, t_env *ms_env);

//	tree_heredoc.c - OK
void	ft_handle_heredoc(t_exec *exec, t_env *ms_env);
int		make_heredoc(char *delim);
int		prev_heredoc_exists(t_tree *tree);

//	tree_error.c - OK
int		ft_error_exec(int code, int *fd, t_env *ms_env);
int		ft_redir_error(t_tree *tree, int fd, t_env *ms_env);
int		export_error_msg(char *str);
int		unset_error_msg(char *str);

//	tree_exit.c - OK
void	ft_exit_multi_arg(t_tree *tree, t_env *ms_env, int i);
void	ft_exit_numeric(t_tree *tree, t_env *ms_env, char c);
void	ft_exit_one_arg(t_tree *tree, t_env *ms_env, int i);
void	ft_exit_one_range(t_tree *tree, t_env *ms_env);
int		ft_exit(t_tree *tree, t_env *ms_env);

//	tree_utils.c - OK
int		ft_check_minus_plus(char *str);
int		ft_check_isalpha(char *str);
int		ft_check_isdigit(char *str);
size_t	ft_atoi_exit(const char *str);

//	builtin_echo.c - OK
int		ft_builtin_echo(t_env *ms_env, t_tree *tree);
int		ft_handle_echo(t_tree *tree, int i, int check, int err);
int		ft_print_echo(t_tree *tree, int i, int err);

//	builtin_pwd.c - OK
int		ft_pwd_builtin(t_env *ms_env);
char	*ft_get_pwd(char **envp);

//	builtin_cd.c - OK
t_err	ms_cd(char **argv, t_env *ms_env);
t_err	update_pwd_oldpwd(char *path, t_env *ms_env);
t_err	only_update_oldpwd(t_env *ms_env, char *curr_pwd);
char	*parse_path(char *path, char *old_pwd);
int		add_path_chunk(char parse_path[512], char *path);

//	builtin_cd_utils.c - OK
int		ms_perror(char *perror_str, char *string, char *string2, int rv);
int		add_str(char *perror_str, char *string2, int rv);
void	remove_dir(char parse_path[512]);

//	builtin_paths.c - OK
int		ft_get_paths(t_env *ms_env, char **arg);
char	*find_path_env(char **envp, t_env *ms_env);
int		ft_acces_and_exec(t_env *ms_env, char **arg, char **paths);
int		ft_parse_dir(char **envp, char **arg, t_env *ms_env, char **paths);
char	**ft_edit_paths(char **paths, char **arg, int i);

//	builtin_paths_utils.c - OK
char	*ft_search_bins(char **exec_paths);
int		ft_check_access(char *path, char **envp, char **arg, t_env *ms_env);
void	*ft_free_paths(char **first, char **second, char *third);
void	ft_cmd_exit(char **arg, t_env *ms_env, char **paths);
int		ft_parse_dir_loop(char *str);

//	builtin_paths_utils_a.c - OK
void	ft_dir_exit(char **arg, t_env *ms_env, char **paths);
int		ft_is_dir(char **envp, char **arg, t_env *ms_env, char **paths);

//	builtin_export.c - OK
int		ms_export(char **argv, t_env *ms_env);
t_err	ready_export(t_item *item);
t_err	dup_env_key(const char *str, char **return_key);
int		export_key(char *key);
t_err	extract_to_ms_env(char *str, t_item **item, char *key);

//	builtin_export_utils.c - OK
t_err	join_values(char *value, char *key, t_item *item, char **joined);
t_err	add_to_ms_env(t_item **item, char *key, char *value);
int		not_ready(int *arr, int arr_len);
t_err	print_smallest_and_mark_arr(t_item *item, int *arr, int arr_len);
char	*first_available(t_item *item, int *arr, int arr_len);

//	builtin_export_utils_a.c - OK
int		is_smallest_key(char *key, t_item *item, int *arr);
void	print_key(char *key, t_item *item);
void	mark_array(char *key, t_item *item, int *arr);
int		get_ms_envp_len(t_item *item);

//	builtin_unset.c - OK
int		ms_unset(char **argv, t_env *ms_env);
int		unset_key(char *key);
t_err	rm_ms_env(char *key, t_item **envp);
void	copy_or_rm(t_item **envp, char *key, t_item **new_envp);

//	builtin.c - OK
int		ft_start_builtin(t_tree *tree, t_env *ms_env, t_exec *exec);
int		ft_check_builtin(t_tree *tree, t_env *ms_env);
int		ft_check_builtin_add(t_tree *tree, t_env *ms_env, int i);
int		print_ms_env(char **argv, t_env *ms_env);
int		ft_check_builtin_child(t_tree *tree, t_env *ms_env);

#endif