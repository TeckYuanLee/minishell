/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_signals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 14:42:16 by telee             #+#    #+#             */
/*   Updated: 2022/08/12 16:26:03 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//  change termios settings
void	set_term_settings(void)
{
	struct termios	termios_p;

	ft_bzero(&termios_p, sizeof(struct termios));
	tcgetattr(2, &termios_p);
	termios_p.c_lflag &= (~ECHOCTL | ISIG);
	tcsetattr(2, TCSANOW, &termios_p);
}

//	process sigint and sigquit
void	process_signal(int sig, int *exitcode, int fd[2])
{
	if (sig == SIGINT)
	{
		if (fd)
			ft_close_fd(fd);
		*exitcode = 130;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else if (sig == SIGQUIT)
	{
		if (fd)
			ft_close_fd(fd);
		*exitcode = 131;
		ft_putstr_fd("Quit: 3\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

//  ctrl-D
int	ft_exit_sig(t_env *ms_env)
{
	tcsetattr(2, TCSANOW, &ms_env->termios_p);
	rl_replace_line("exit", 0);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
	ft_free_split(&ms_env->envp);
	free_ms_env(ms_env->item);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(0);
}

//  print newline
void	new_readline(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

/*
1. restore signals
2. init signals
3. heredoc signals
4. ignore signals
*/
void	ms_signals(char *str)
{
	struct sigaction	sig_c;
	struct sigaction	sig_q;

	if (!ft_strncmp(str, "restore", 8))
	{
		ft_bzero(&sig_c, sizeof(struct sigaction));
		sig_c.sa_handler = SIG_DFL;
		sigaction(SIGINT, &sig_c, NULL);
		sigaction(SIGQUIT, &sig_c, NULL);
	}
	else
	{
		ft_bzero(&sig_c, sizeof(struct sigaction));
		ft_bzero(&sig_q, sizeof(struct sigaction));
		if (!ft_strncmp(str, "init", 5))
			sig_c.sa_handler = new_readline;
		else if (!ft_strncmp(str, "heredoc", 8))
			sig_c.sa_handler = SIG_DFL;
		else if (!ft_strncmp(str, "ignore", 7))
			sig_c.sa_handler = SIG_IGN;
		sig_q.sa_handler = SIG_IGN;
		sigaction(SIGINT, &sig_c, NULL);
		sigaction(SIGQUIT, &sig_q, NULL);
	}
}
