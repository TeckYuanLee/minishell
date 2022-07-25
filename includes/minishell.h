/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:24:55 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 10:18:06 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"

# define BHRED "\e[1;91m"
# define BHGRN "\e[1;92m"
# define BHYEL "\e[1;93m"
# define BHBLU "\e[1;94m"
# define BHMAG "\e[1;95m"
# define BHCYN "\e[1;96m"
# define BHWHT "\e[1;97m"
# define SPC   "                                "

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

typedef enum s_nodetype
{
	PIPE,
	NO_PIPE,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APP,
	HERE_DOC,
	CMD
}		t_nodetype;

typedef enum s_token_type
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
}		t_token_type;

typedef struct s_tree
{
	int				id;
	t_nodetype		type;
	char			**data;
	struct s_tree	*left_node;
	struct s_tree	*right_node;
	struct s_tree	*prev_node;
}		t_tree;

typedef struct s_node
{
	t_nodetype		type;
	char			**arg;
}		t_node;

typedef struct s_token
{
	int				id;
	t_token_type	type;
	t_bool			is_parsed;
	char			*data;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct s_curr_input
{
	t_token	*lexer;
	t_tree	*tree;
}		t_curr_input;

typedef struct s_executor
{
	int	fd_in[2];
	int	fd_out[2];
	int	index;
	int	builtin_check;
}	t_executor;

typedef struct s_ms_envp
{
	char	*key;
	char	*value;
}		t_ms_envp;

typedef struct s_envi
{
	t_ms_envp		*ms_envp;
	char			**var;
	struct termios	termios_p;
	int				exitcode;
	t_executor		*exec;
	t_tree			**loc_tree_ptr;
}		t_envi;

t_err	syntax_err_lexer(char token);
t_err	lexer(char *line, t_curr_input *input, t_envi *info);
t_err	tokenize(char *input, int *i, t_token **list);
t_err	lnr_angles(char *input, int *i, t_token **list);
t_err	pipes_dollars(char *input, int *i, t_token **list);
t_err	quotes(char *input, int *i, t_token **list);
t_err	words(char *input, int *i, t_token **list);
t_err	spaces(char *input, int *i, t_token **list);

t_token	*create_token(t_token_type type, char *data);
t_err	add_new_token(t_token **head, t_token_type type, char *data);
t_err	exitcode_token(const char *dquote, int *j, t_token **list);
t_err	add_dollar_sign(t_token **list);

char	*save_word(const char *input);
t_err	d_quote_dollars(const char *dquote, int *j, t_token **list);
t_err	put_d_quote_token(const char *dquote, t_token **list, int j);
t_err	expand_d_quote(const char *dquote, t_token **list);
t_err	save_quote(const char *line, char **quote, char *input);

void	add_to_tokenlist(t_token **head, t_token *new);
t_bool	allowed_char(int c, char *not_allowed);
t_err	get_env_key(const char *str, char **return_key);

#endif