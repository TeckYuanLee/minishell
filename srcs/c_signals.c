#include "minishell.h"

//	restore sigint and sigquit to default
void	restore_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = SIG_DFL;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
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

//  ctrl-D /////
int	ft_exit_sig(t_env *envi)
{
	tcsetattr(2, TCSANOW, &envi->termios_p);
	rl_replace_line("exit", 0);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
	ft_free_split(&envi->envp);
	free_envp(envi->item);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	exit(0);
}

//  ignore signals /////
void	ignore_signals(void)
{
	struct sigaction	sig;

	ft_bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

//  print newline /////
void	new_prompt(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

//	initialize heredoc signals /////
void	init_here_doc_signals(void)
{
	struct sigaction	sig_slash;
	struct sigaction	sig_c;

	ft_bzero(&sig_slash, sizeof(struct sigaction));
	ft_bzero(&sig_c, sizeof(struct sigaction));
	sig_c.sa_handler = SIG_DFL;
	sig_slash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig_c, NULL);
	sigaction(SIGQUIT, &sig_slash, NULL);
}

//  initialize signals /////
void	init_signals(void)
{
	struct sigaction	sig_c;
	struct sigaction	sig_q;

	ft_bzero(&sig_c, sizeof(struct sigaction));
	ft_bzero(&sig_q, sizeof(struct sigaction));
	sig_c.sa_handler = new_prompt;
	sig_q.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig_c, NULL);
	sigaction(SIGQUIT, &sig_q, NULL);
}
