/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:28:22 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:28:22 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	look for pwd from list of envp
char	*pwd_get(char **envp)
{
	int		i;
	int		len;
	char	*temp;
	char	*cwd;

	i = -1;
	while (envp[++i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PWD", 3))
		{
			len = ft_strlen(envp[i]);
			temp = (char *)malloc(sizeof(char) * (len + 1));
			if (!temp)
				return (NULL);
			temp = ft_memcpy(temp, envp[i], ft_strlen(envp[i]));
			temp[len] = '\0';
			cwd = ft_strtrim(temp, "PWD=");
			free (temp);
			return (cwd);
		}
	}
	return (NULL);
}

//	execute pwd command
int	builtin_pwd(t_env *ms_env)
{
	char	*pwd;

	pwd = pwd_get(ms_env->envp);
	if (!pwd)
		exec_error(5, 0, ms_env);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free (pwd);
	ms_env->exitcode = 0;
	return (1);
}
