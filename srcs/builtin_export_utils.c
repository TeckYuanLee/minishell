#include "minishell.h"

//	if keys are match, fill array
void	mark_array(char *key, t_item *ms_envp, int *arr)
{
	int	i;

	i = 0;
	while (ms_envp->key)
	{
		if (ft_strncmp(key, ms_envp->key, ft_strlen(key) + 1) == 0)
		{
			*(arr + i) = 1;
			return ;
		}
		ms_envp++;
		i++;
	}
}

//	
void	print_key(char *key, t_item *ms_envp)
{
	while (ms_envp->key)
	{
		if (ft_strncmp(key, ms_envp->key, ft_strlen(key) + 1) == 0)
		{
			if (ms_envp->value)
				printf("declare -x %s=\"%s\"\n", ms_envp->key, ms_envp->value);
			else
				printf("declare -x %s\n", ms_envp->key);
		}
		ms_envp++;
	}
}

//	check for the smallest key
int	is_smallest_key(char *key, t_item *ms_envp, int *arr)
{
	if (*(arr) == 1)
		return (0);
	if (ft_strncmp(ms_envp->key, key, ft_strlen(ms_envp->key) + 1) < 0)
		return (1);
	return (0);
}

//	look for first available key
char	*first_available(t_item *ms_envp, int *arr, int arr_len)
{
	int	i;

	i = -1;
	while (++i < arr_len)
		if (*(arr + i) == 0)
			return ((ms_envp + i)->key);
	return (0);
}

//	print first available envp and mark array
t_err	print_smallest_and_mark_arr(t_item *ms_envp, int *arr, int arr_len)
{
	int			i;
	static char	*smallest_key = NULL;
	static char	full_key[255];

	i = -1;
	ft_memchr(full_key, '~', 256);
	if (smallest_key == NULL)
		smallest_key = full_key;
	else
		smallest_key = first_available(ms_envp, arr, arr_len);
	while (++i < arr_len)
	{
		if (is_smallest_key(smallest_key, ms_envp + i, arr + i))
		{
			smallest_key = (ms_envp + i)->key;
			i = -1;
			continue ;
		}
	}
	print_key(smallest_key, ms_envp);
	mark_array(smallest_key, ms_envp, arr);
	return (NO_ERROR);
}

//	check for next position in array
int	not_ready(int *arr, int arr_len)
{
	int	i;

	i = -1;
	while (++i < arr_len)
		if (*(arr + i) == 0)
			return (1);
	return (0);
}
