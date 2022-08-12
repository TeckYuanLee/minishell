#include "minishell.h"

//	look for pwd from list of envp
char	*ft_get_pwd(char **envp)
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
int	ft_pwd_builtin(t_env *ms_env)
{
	char	*pwd;

	pwd = ft_get_pwd(ms_env->envp);
	if (!pwd)
		ft_error_exec(5, 0, ms_env);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free (pwd);
	ms_env->exitcode = 0;
	return (1);
}
