#include "minishell.h"

//	if key is different, copy, else remove key
void	copy_or_rm(t_item **envp, char *key, t_item **new_envp)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while ((*envp)[++i].key)
	{
		if (ft_strncmp((*envp)[i].key, key, ft_strlen(key) + 1))
		{
			(*new_envp)[j].key = (*envp)[i].key;
			(*new_envp)[j].value = (*envp)[i].value;
			j++;
		}
		else
		{
			free((*envp)[i].key);
			free((*envp)[i].value);
		}
	}
}

//	copy or remove key from env
t_err	rm_from_envp(char *key, t_item **envp)
{
	t_item	*new_envp;
	int			i;

	i = 0;
	while ((*envp)[i].key)
		i++;
	new_envp = ft_calloc(i + 1, sizeof(t_item));
	if (!new_envp)
		return (MALLOC_FAIL);
	copy_or_rm(envp, key, &new_envp);
	free(*envp);
	*envp = new_envp;
	return (NO_ERROR);
}

//	check for unset key
int	is_unset_key(char *key)
{
	size_t	i;

	i = 0;
	if (!key)
		return (0);
	if (ft_isdigit(key[0]) || key[0] == '-')
		return (0);
	while (key[i] && allowed_char(key[i], "/\\;.+=-{}*#@!^~"))
		i++;
	if (ft_strlen(key) == i)
		return (1);
	return (0);
}

//	handle unset command
int	ms_unset(char **argv, t_env *ms_env)
{
	int	i;
	int	exitcode;

	if (!argv)
		return (printf(BHRED "[ms_unset] NULL-pointing argv..\n" BHWHT));
	if (!argv[1])
		return (0);
	exitcode = 0;
	i = 1;
	while (argv[i])
	{
		if (!ft_strncmp(argv[i], "PWD", 4))
			return (0);
		else if (!is_unset_key(argv[i]))
			exitcode = unset_error_msg(argv[i]);
		else
			rm_from_envp(argv[i], &ms_env->item);
		i++;
	}
	if (ms_env_to_envp(ms_env->item, &ms_env->envp) == MALLOC_FAIL)
		return (-1);
	return (exitcode);
}
