/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:30:33 by telee             #+#    #+#             */
/*   Updated: 2022/08/19 12:55:50 by telee            ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_env	ms_env;
	t_input	input;

	(void)argc;
	(void)argv;
	// print_header();
	// rl_outstream = stderr;
	if (init_ms_env(envp, &ms_env) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_env_to_envp((&ms_env)->item, (&(&ms_env)->envp)) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	tcgetattr(2, (&(&ms_env)->termios_p));
	ft_bzero(&input, sizeof(t_input));
	return (ms_loop(&input, &ms_env));
}
