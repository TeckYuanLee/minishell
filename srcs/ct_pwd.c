#include "minishell.h"

//	get pwd from env
char	*ft_get_pwd_env(char *temp)
{
	char	*cwd;

	cwd = ft_strtrim(temp, "PWD=");
	free (temp);
	if (!cwd)
		return (NULL);
	return (cwd);
}

//	look for pwd from list of envp
char	*ft_get_pwd(char **envp)
{
	int		i;
	int		len;
	char	*temp;
	char	*cwd;

	i = 0;
	while (envp[i] != NULL)
	{
		if (!ft_strncmp(envp[i], "PWD", 3))
		{
			len = ft_strlen(envp[i]);
			temp = (char *)malloc(sizeof(char) * (len + 1));
			if (!temp)
				return (NULL);
			temp = ft_memcpy(temp, envp[i], ft_strlen(envp[i]));
			temp[len] = '\0';
			cwd = ft_get_pwd_env(temp);
			if (!cwd)
				return (NULL);
			return (cwd);
		}
		i++;
	}
	return (NULL);
}

//	execute pwd command
int	ft_pwd_builtin(t_env *envi)
{
	char	*pwd;

	pwd = ft_get_pwd(envi->var);
	if (!pwd)
		ft_error_exec(5, 0, envi);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	free (pwd);
	envi->exitcode = 0;
	return (1);
}
