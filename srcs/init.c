#include "minishell.h"

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	if (!*split)
		return ;
	while ((*split)[i])
	{
		free((*split)[i]);
		(*split)[i] = NULL;
		i++;
	}
	free(*split);
	*split = NULL;
}

//  save current term settings
void	save_term_settings(struct termios *termios_p)
{
	tcgetattr(2, termios_p);
}

//  
t_err	set_shlvl(t_env *envi)
{
	int		lvl;
	char	*key;
	char	*value;

	if (get_env_value(envi->ms_envp, "SHLVL", &value) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (!value)
		lvl = 0;
	else
		lvl = ft_atoi(value);
	lvl++;
	if (lvl > 1)
		free(value);
	value = ft_itoa(lvl);
	if (!value)
		return (MALLOC_FAIL);
	if (key_exists("SHLVL", envi->ms_envp))
		return (replace_value("SHLVL", value, envi->ms_envp));
	key = ft_strdup("SHLVL");
	if (!key)
		return (MALLOC_FAIL);
	return (add_to_ms_envp(key, value, &envi->ms_envp));
}

//  combine key values from envp with variables
t_err	ms_envp_to_var(t_item *ms_envp, char ***var)
{
	int	i;
	int	j;

	if (!ms_envp)
		return (printf(BHRED "[ms_envp_to_var] ms_envp = NULL\n" BHWHT));
	i = 0;
	while (ms_envp[i].key)
		i++;
	if (*var)
		ft_free_split(var);
	*var = ft_calloc(i + 1, sizeof(char *));
	if (!*var)
		return (MALLOC_FAIL);
	j = 0;
	while (j < i)
	{
		if (combine_key_value(&ms_envp[j], &(*var)[j]) == MALLOC_FAIL)
		{
			ft_free_partial_split(var, j);
			return (MALLOC_FAIL);
		}
		j++;
	}
	return (NO_ERROR);
}

//  initialize variables in envi
t_err	init_var(char **envp, t_env *envi)
{
	int	i;

	i = 0;
	ft_bzero(envi, sizeof(t_env));
	while (envp[i])
		i++;
	envi->ms_envp = ft_calloc(i + 2, sizeof(t_item));
	if (!envi->ms_envp)
		return (MALLOC_FAIL);
	i = 0;
	while (envp[i])
	{
		copy_to_ms_envp(envp[i], &envi->ms_envp[i]);
		i++;
	}
	if (!key_exists("OLDPWD", envi->ms_envp))
		return (add_empty_oldpwd(&envi->ms_envp[i]));
	return (NO_ERROR);
}

//  initialize minishell
t_err	ms_init(char **envp, t_env *envi)
{
	if (init_var(envp, envi) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (ms_envp_to_var(envi->ms_envp, &envi->var) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	if (set_shlvl(envi) == MALLOC_FAIL)
		return (MALLOC_FAIL);
	save_term_settings(&envi->termios_p);
	return (NO_ERROR);
}
