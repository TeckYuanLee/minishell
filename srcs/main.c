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

void	ignore_signals(void)
{
	struct sigaction	sig;

	bzero(&sig, sizeof(struct sigaction));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	start_minishell(char **envp)
{
	char	*line;
	
	(void)envp;
	while (1)
	{
		ignore_signals();
		line = readline("wtf$ ");
		if (!strcmp(line, "exit"))
			exit(0);
		printf("%s\n", line);
	}
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	start_minishell(envp);
	print_header();
}