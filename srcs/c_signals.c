#include "minishell.h"

//  exit signal /////
int	ft_exit_sig(t_env *envi)
{
	tcsetattr(2, TCSANOW, &envi->termios_p);
	rl_replace_line("exit", 0);
	rl_on_new_line();
	rl_redisplay();
	write(1, "\n", 1);
	ft_free_split(&envi->var);
	free_envp(envi->ms_envp);
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
	sig_slash.sa_handler = SIG_IGN;
	sig_c.sa_handler = SIG_DFL;
	sigaction(SIGQUIT, &sig_slash, NULL);
	sigaction(SIGINT, &sig_c, NULL);
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
