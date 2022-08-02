/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:24:55 by telee             #+#    #+#             */
/*   Updated: 2022/08/01 14:58:31 by telee            ###   ########.fr       */
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

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

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

typedef enum s_node_t
{
	PIPE,
	NO_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	HERE_DOC,
	CMD
}		t_node_t;

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

typedef struct s_tree
{
	int				id;
	t_node_t		type;
	char			**data;
	struct s_tree	*left_node;
	struct s_tree	*right_node;
	struct s_tree	*up_node;
}		t_tree;

typedef struct s_node
{
	t_node_t		type;
	char			**arg;
}		t_node;

typedef struct s_token
{
	int				id;
	t_token_t		type;
	t_bool			is_parsed;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_input
{
	t_token	*lexer;
	t_tree	*tree;
}		t_input;

typedef struct s_exec
{
	int	fd_in[2];
	int	fd_out[2];
	int	index;
	int	builtin_check;
}	t_exec;

typedef struct s_item
{
	char	*key;
	char	*value;
}		t_item;

typedef struct s_env
{
	t_item			*ms_envp;
	char			**var;
	struct termios	termios_p;
	int				exitcode;
	t_exec			*exec;
	t_tree			**loc_tree_ptr;
}		t_env;

typedef struct s_pwdstr
{
	char	*pwd;
	char	*oldpwd;
}			t_pwdstr;

//	loop_do.c
int	do_loop(t_input *curr_input, t_env *envi);
void	init_signals(void);
void	init_here_doc_signals(void);
void	new_prompt(int sig);
void	clean_lexer(t_token **list);
void	clean_tree(t_tree **head_tree);
// static void	clean_leaves(t_tree *root_tree);
void	ignore_signals(void);
void	ft_start_tree(t_env *envi, t_tree **tree);
t_exec	*ft_init_exec(void);
void	free_envi_parent(t_env *envi);

//	init.c
// t_err	ms_init(char **envp, t_env *envi);
t_err	init_var(char **envp, t_env *envi);
t_err	ms_envp_to_var(t_item *ms_envp, char ***var);
t_err	set_shlvl(t_env *envi);
// void	save_term_settings(struct termios *termios_p);
void	ft_free_split(char ***split);

//	loop_get_input.c
t_err	get_input(t_env *envi, char **input_ptr);
t_err	process_input(char *line, t_input *input, t_env *info);
void	set_term_settings(void);
// void	restore_term_settings(struct termios *termios_p);
int	ft_exit_sig(t_env *envi);
void	free_envp(t_item *ms_envp);

//	init_envp.c
t_err	copy_to_ms_envp(char *str, t_item *custom_envp);
t_bool	key_exists(char *key, t_item *ms_envp);
t_err	combine_key_value(t_item *ms_envp, char **var);
t_err	get_env_value(t_item *envp, char *key, char **value_ptr);
t_err	update_value(char *key, char *value, t_item *envp);
t_err	add_to_ms_envp(char *key, char *value, t_item **head);

//	l_lexer.c
t_err	lexer(char *line, t_input *input);
t_err	syntax_err_lexer(char token);
t_err	tokenize(char *input, int *i, t_token **list);

//	l_dollars.c
t_token	*create_token(t_token_t type, char *data);
t_err	add_new_token(t_token	**head, t_token_t type, char *data);
t_err	add_dollar_sign(t_token	**list);

//	l_quotes.c
char	*save_word(const char *input);
t_err	d_quote_dollars(const char *dquote, int *j, t_token **list);
t_err	put_d_quote_token(const char *dquote, t_token **list, int j);
t_err	expand_d_quote(const char *dquote, t_token **list);
t_err	save_quote(const char *line, char **quote, char *input);

//	l_tokens.c
t_err	lnr_angles(char *input, int *i, t_token **list);
t_err	pipes(char *input, int *i, t_token **list);
t_err	dollars(char *input, int *i, t_token **list);
t_err	quotes(char *input, int *i, t_token **list);
t_err	words(char *input, int *i, t_token **list);
t_err	spaces(char *input, int *i, t_token **list);

//	l_tokens_utils.c
t_err	exitcode_token(const char *dquote, int *j, t_token **list);
void	add_to_tokenlist(t_token **head, t_token *new);
t_bool	allowed_char(int c, char *not_allowed);
t_err	get_env_key(const char *str, char **return_key);

//	e_expander.c
t_err	expander(t_input *input, t_env *info);
t_err	rm_double_tokens(t_token **list, t_token_t type);
t_err	quotes_to_words(t_token **list);
t_err	expand_dollars(t_token **list, t_env *info);
t_err	word_join(t_token **list);
t_err	rm_token_type(t_token **list, t_token_t type);

//	e_do_stuff.c
void	insert_token_after(t_token *list, t_token *new);
void	replace_head_token(t_token **head, t_token *new);
void	replace_token(t_token *list, t_token *new);
t_err	do_headstuff(t_token **head, char *key, char *value, char *data);
t_err	do_normalstuff(t_token *list, char *key, char *value, char *data);
t_token	*create_tailpart(char *key, char *data);
void	create_full_string(char **str, char *data, int len);

//	e_modify_token.c
void	cut_head_token(t_token **head);
void	cut_token(t_token *list);
t_err	join_token(t_token *list, t_token_t resulting_type);
t_err	join_head_token(t_token **list, t_token_t resulting_type);
t_err	prep_expand_d(t_token **head, t_env *info, char *key);
t_err	expand_d(t_token **head, t_env *info, char *key, char *data);

//	e_modify_utils.c
t_err	expand_d_tailbit(t_token **head, char *key, char *data);
t_err	insert_tokens(t_token **head, char *key, char *value, char *data);
t_err	insert_full_string(t_token **head, char *key, char *data);
void	del_token(t_token *list);
void	ft_free_str(char **str);

//	p_parser.c
t_err	parser(t_input *input);
t_err	pipe_syntax_pass(t_token *list);
t_err	redir_syntax_pass(t_token *list);
t_err	root_pass(t_token *list, t_tree **root);
t_err	redir_pass(t_token *list, t_tree **root);
t_err	cmd_pass(t_token *list, t_tree **root);
t_token	*next_branch(t_token *list);

//	p_parser_utils.c
char	*get_token_str(t_token_t type);
t_err	syntax_err(t_token_t type);
t_err	add_tree_node(t_node_t type, t_tree **tree, char **data);
char	**make_split(t_token *list, int word_amount);
char	**create_cmd_split(t_token *list, int word_count);

//	p_nodes.c
t_err	add_root_node(t_node_t type, t_tree **head_tree);
t_err	add_leaf_node(t_node_t type, char **data, t_tree *parent);
t_tree	*create_tree_node(t_node_t type, char **data);
t_tree	*last_root_node(t_tree *tree);
t_tree	*next_root_node(t_tree *tree);
void	ft_free_partial_split(char ***split, int failed_i);

//	t_check_builtin.c
int	ft_check_builtin(t_tree *tree, t_env *envi);
int	ft_builtin_echo(t_env *envi, t_tree *tree);
int	ft_pwd_builtin(t_env *envi);
void	ft_check_export(t_tree *tree, t_env *envi);
int	ft_check_builtin_end(t_tree *tree, t_env *envi, int i);
int	ft_check_builtin_add(t_tree *tree, t_env *envi, int i);

//	t_check_builtin_utils.c
int	ft_handle_echo(t_tree *tree, int i, int check, int err);
int	ft_print_echo(t_tree *tree, int i, int err);
int	ft_check_n(char *str);
char	*ft_get_pwd(char **envp);
char	*ft_get_pwd_env(char *temp);
int	ms_env(char **argv, t_env *envi);
int	env_error_msg( t_env *envi);
char	*get_path_env(char *temp);

//	t_cd.c
int	ms_perror(char *perror_str, char *string, char *string2, int rv);
t_err	update_pwd_oldpwd(char *path, t_env *envi);
int	add_string2(char *perror_str, char *string2, int rv);
t_err	only_update_oldpwd(t_env *envi, char *curr_pwd);
char	*parse_path(char *path, char *old_pwd);
t_err	update_both_pwds(t_env *envi, char *curr_pwd, char *new_pwd);

//	t_dir.c
char	**ft_edit_paths(char **paths, char **arg, int i);
char	*ft_search_bins(char **exec_paths);
int	ft_check_access(char *path, char **envp, char **arg, t_env *envi);
int	ft_exec_cmd(char *path, char **envp, char **arg, t_env *envi);
void	*ft_free_paths(char **first, char **second, char *third);
void	ft_cmd_exit(char **arg, t_env *envi, char **paths);
int	ft_parse_dir_loop(char *str);
void	ft_dir_exit(char **arg, t_env *envi, char **paths);
int	ft_is_dir(char **envp, char **arg, t_env *envi, char **paths);

//	t_export.c
t_err	single_export(t_item *ms_envp);
t_err	export_get_env_key(const char *str, char **return_key);
int	is_export_key(char *key);
int	export_error_msg(char *str);
t_err	parse_and_add_to_envp(char *str, t_item **ms_envp, char *key);
char	*point_to_value(char *str);
t_err	get_plusis_value(char *value, char *key, t_item *ms_envp, \
		char **joined);
t_err	add_value_to_envp(t_item **ms_envp, char *key, char *value);

//	t_export_utils.c
int	get_ms_envp_len(t_item *ms_envp);
int	not_ready(int *arr, int arr_len);
t_err	print_smallest_and_mark_arr(t_item *ms_envp, int *arr, int arr_len);
char	*first_available(t_item *ms_envp, int *arr, int arr_len);
int	is_smallest_key(char *key, t_item *ms_envp, int *arr);
void	print_key(char *key, t_item *ms_envp);
void	mark_array(char *key, t_item *ms_envp, int *arr);

//	t_unset.c
int	is_unset_key(char *key);
int	unset_error_msg(char *str);
t_err	rm_from_envp(char *key, t_item **envp);
void	copy_or_rm(t_item **envp, char *key, t_item **new_envp);
void	remove_dir(char parse_path[512]);
int	add_path_chunk(char parse_path[512], char *path);
t_pwdstr	init_strings(void);

//	t_exit.c
void	ft_exit_free(t_tree *tree, t_exec *exec, t_env *envi);
void	ft_exit_multi_arg(t_tree *tree, t_env *envi, int i, t_exec *exec);
int	ft_check_minus_plus(char *str);
int	ft_check_isalpha(char *str);
void	ft_exit_numeric(t_tree *tree, t_env *envi, t_exec *exec);

//	t_exit_one_arg.c
void	ft_exit_one_arg(t_tree *tree, t_env *envi, int i, t_exec *exec);
int	ft_check_isdigit(char *str);
void	ft_exit_one_range(t_tree *tree, t_env *envi, t_exec *exec);
int	ft_isplus(char *str);
long long	ft_atoi_exit(const char *str);
void	ft_exit_one_arg_plus(t_tree *tree, t_env *envi, t_exec *exec);
// static int	ft_skip(const char *str, int i);

//	t_handle_tree.c
int	ft_handle_tree(t_env *envi, t_tree *tree, t_exec *exec);
int	ft_nopipe_start(t_env *envi, t_tree *tree, t_exec *exec);
int	ft_wait_on_children(t_exec *exec, t_env *envi);
int	ft_handle_loop(t_env *envi, t_exec *exec, t_tree *tree);
int	ft_handle_loop_two(t_env *envi, t_exec *exec, t_tree *tree);
int	ft_copy_fd(t_exec *exec);
int	ft_close_fd(int fd[2]);
t_tree	*get_next_node(t_tree *tree);
void	ft_close_all(t_exec *exec);
void	ft_handle_heredoc(t_exec *exec, t_env *envi);

//	t_pipe_start.c
int	ft_pipe_start(t_env *envi, t_tree *tree, t_exec *exec);
void	ft_helper_pipe_start(t_tree *tree, t_env *envi, t_exec *exec);
int	ft_pipe_start_util(t_tree *tree, pid_t pid);
int	ft_check_builtin_child(t_tree *tree, t_env *envi, t_exec *exec);
int	ft_pipe_inbetween(t_env *envi, t_tree *tree, t_exec *exec);
void	ft_helper_pipe_inbetween(t_tree *tree, t_env *envi, t_exec *exec);

//	t_helper_nopipe_start.c
void	ft_helper_nopipe_start(t_tree *tree, t_env *envi);
int	ft_get_paths(t_env *envi, char **arg);
char	*find_path_env(char **envp, t_env *envi);
int	ft_acces_and_exec(t_env *envi, char **arg, char **paths);
int	ft_parse_dir(char **envp, char **arg, t_env *envi, char **paths);

//	t_nopipe_end.c
int	ft_nopipe_end(t_tree *tree, t_env *envi, t_exec *exec);
int	prev_heredoc_exists(t_tree *tree);
void	ft_nopipe_child(t_tree *tree, t_env *envi, t_exec *exec);
int	ft_nopipe_end_util(t_tree *tree, pid_t pid, int status);
void	ft_helper_nopipe_end(t_tree *tree, t_env *envi, t_exec *exec);

//	t_nonwriteable.c
void	process_signal(int sig, int *exitcode, int fd[2]);
void	restore_signals(void);
int	ft_check_nonwriteable(t_tree *tree, t_env *envi, t_exec *exec);
int	ft_start_builtin(t_tree *tree, t_env *envi, t_exec *exec);
int	ms_export(char **argv, t_env *envi);
t_err	ms_cd(char **argv, t_env *envi);
int	ms_unset(char **argv, t_env *envi);
int	ft_exit(t_tree *tree, t_env *envi, t_exec *exec);

//	t_redirs_loop.c
int	ft_error_exec(int code, int *fd, t_env *envi);
int	ft_redir_error(t_tree *tree, int fd, t_env *envi);
int	ft_redir_in_error(t_tree *tree, t_env *envi);
void	free_envi(t_env *envi);
int	ft_redirs_loop(t_tree *tree, t_exec *exec, t_env *envi);
int	ft_redirs_loop_two(t_tree *tree, t_exec *exec, t_env *envi);
int	make_here_doc(char *delimiter);


#endif