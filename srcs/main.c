/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:01 by telee             #+#    #+#             */
/*   Updated: 2022/08/11 16:15:59 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_header(void)
// {
// 	printf(BHRED SPC"═════════════════════════════════════"BHWHT"\n");
// 	printf(BHRED SPC"  ▆▆▆     ▆▆▆    ▆▆▆   ▆▆   ▆   ▆▆▆"BHWHT"\n");
// 	printf(BHRED SPC"  ▆  ▆   ▆  ▆     ▆    ▆ ▆  ▆    ▆ "BHWHT"\n");
// 	printf(BHRED SPC"  ▆   ▆ ▆   ▆     ▆    ▆  ▆ ▆    ▆ "BHWHT"\n");
// 	printf(BHRED SPC"  ▆    ▆    ▆    ▆▆▆   ▆   ▆▆   ▆▆▆"BHWHT"\n");
// 	printf(BHRED SPC"════════  ██  █  █  ███  █   █ ═════"BHWHT"\n");
// 	printf(BHRED SPC"         █    █  █  █    █   █      "BHWHT"\n");
// 	printf(BHRED SPC"          ▆   ████  ██   █   █      "BHWHT"\n");
// 	printf(BHRED SPC"           █  █  █  █    █   █      "BHWHT"\n");
// 	printf(BHRED SPC"         ██   █  █  ███  ███ ███    "BHWHT"\n");
// 	printf(BHCYN SPC"                      telee & ssoon "BHWHT"\n");
// 	printf(BHCYN SPC"                      ━━━━━━━━━━━━━ "BHWHT"\n");
// }

// void	set_term_settings(struct termios *termios_p)
// {
// 	ft_bzero(termios_p, sizeof(struct termios));
// 	tcgetattr(STDIN_FILENO, termios_p);
// 	termios_p->c_lflag &= (~ECHOCTL | ISIG);
// 	tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p);
// }

// void	process_signal(int signo)
// {
// 	(void)signo;
// 	write(1, "\n", 1);
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	ignore_signals(void)
// {
// 	struct sigaction	sig;
// 	struct sigaction	slash;

// 	bzero(&sig, sizeof(struct sigaction));
// 	bzero(&slash, sizeof(struct sigaction));
// 	sig.sa_handler = &process_signal;
// 	slash.sa_handler = SIG_IGN;
// 	sigaction(SIGINT, &sig, NULL);
// 	sigaction(SIGQUIT, &slash, NULL);
// }

// void	start_minishell(char **envp)
// {
// 	char			*line;
// 	struct termios	saved;
// 	struct termios	termios_p;
// 	t_env			envi;
// 	t_input	curr_input;

// 	(void)envp;
// 	while (1)
// 	{
// 		ignore_signals();
// 		tcgetattr(STDIN_FILENO, &saved);
// 		set_term_settings(&termios_p);
// 		line = readline("wtf$ ");
// 		lexer(line, &curr_input, &envi);
// 		expander(line, &curr_input, &envi);
// 		tcsetattr(STDIN_FILENO, TCSANOW, &saved);
// 		add_history(line);
// 		if (!strcmp(line, "exit"))
// 			exit(0);
// 		printf("%s$\n", line);
// 	}
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argv;
// 	if (argc != 1)
// 	{
// 		printf("Invalid command\n");
// 		return (1);
// 	}
// 	print_header();
// 	start_minishell(envp);
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	ms_env;
	t_input	input;

	(void)argc;
	(void)argv;
	rl_outstream = stderr;
	// if (ms_init(envp, &ms_env) == MALLOC_FAIL)
	// 	return (MALLOC_FAIL);
	if (init_ms_env(envp, &ms_env) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_envp_to_var((&ms_env)->ms_envp, (&(&ms_env)->envp)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (update_shlvl(&ms_env) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	tcgetattr(2, (&(&ms_env)->termios_p));
	ft_bzero(&input, sizeof(t_input));
	return (do_loop(&input, &ms_env));
}
