/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 09:25:01 by telee             #+#    #+#             */
/*   Updated: 2022/07/25 10:28:04 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_header(void)
{
	printf(BHRED SPC"═════════════════════════════════════"BHWHT"\n");
	printf(BHRED SPC"  ▆▆▆     ▆▆▆    ▆▆▆   ▆▆   ▆   ▆▆▆"BHWHT"\n");
	printf(BHRED SPC"  ▆  ▆   ▆  ▆     ▆    ▆ ▆  ▆    ▆ "BHWHT"\n");
	printf(BHRED SPC"  ▆   ▆ ▆   ▆     ▆    ▆  ▆ ▆    ▆ "BHWHT"\n");
	printf(BHRED SPC"  ▆    ▆    ▆    ▆▆▆   ▆   ▆▆   ▆▆▆"BHWHT"\n");
	printf(BHRED SPC"════════  ██  █  █  ███  █   █ ═════"BHWHT"\n");
	printf(BHRED SPC"         █    █  █  █    █   █      "BHWHT"\n");
	printf(BHRED SPC"          ▆   ████  ██   █   █      "BHWHT"\n");
	printf(BHRED SPC"           █  █  █  █    █   █      "BHWHT"\n");
	printf(BHRED SPC"         ██   █  █  ███  ███ ███    "BHWHT"\n");
	printf(BHCYN SPC"                      telee & ssoon "BHWHT"\n");
	printf(BHCYN SPC"                      ━━━━━━━━━━━━━ "BHWHT"\n");
}

void	set_term_settings(struct termios *termios_p)
{
	ft_bzero(termios_p, sizeof(struct termios));
	tcgetattr(STDIN_FILENO, termios_p);
	termios_p->c_lflag &= (~ECHOCTL | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, termios_p);
}

void	process_signal(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ignore_signals(void)
{
	struct sigaction	sig;
	struct sigaction	slash;

	bzero(&sig, sizeof(struct sigaction));
	bzero(&slash, sizeof(struct sigaction));
	sig.sa_handler = &process_signal;
	slash.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &slash, NULL);
}

void	start_minishell(char **envp)
{
	char			*line;
	struct termios	saved;
	struct termios	termios_p;
	t_envi			envi;
	t_curr_input	curr_input;

	(void)envp;
	while (1)
	{
		ignore_signals();
		tcgetattr(STDIN_FILENO, &saved);
		set_term_settings(&termios_p);
		line = readline("wtf$ ");
		lexer(line, &curr_input, &envi);
		expander(line, &curr_input, &envi);
		tcsetattr(STDIN_FILENO, TCSANOW, &saved);
		add_history(line);
		if (!strcmp(line, "exit"))
			exit(0);
		printf("%s$\n", line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	if (argc != 1)
	{
		printf("Invalid command\n");
		return (1);
	}
	print_header();
	start_minishell(envp);
}
