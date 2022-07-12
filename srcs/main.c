#include "minishell.h"

// int	main(int argc, char **argv, char **envp)
// {
// 	// char	*line;

// 	// line = readline("Enter a line: ");
// 	// printf("readline: %s\n", line);
// 	// add_history(line);
// 	// // rl_clear_history();

// 	// // HIST_ENTRY **history_list(void);
// 	// HIST_ENTRY **mylist;
// 	// mylist = history_list();
// 	// printf("history_list: %s\n", mylist[0]->line);
	
// }
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

void	start_minishell(char **envp)
{
	(void)envp;
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	
	start_minishell(envp);
	print_header();
}