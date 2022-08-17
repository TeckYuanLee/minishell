/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:26:22 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:26:22 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_dir(char parse_path[512])
{
	int	i;

	i = 0;
	while (i < 255 && parse_path[i])
		i++;
	while (parse_path[i] != '/')
		parse_path[i--] = '\0';
	parse_path[i] = '\0';
}

//	join two strings together
int	add_str(char *perror_str, char *string2, int rv)
{
	char	*temp;
	char	*temp2;

	temp = ft_strjoin(perror_str, ": ");
	free (perror_str);
	if (!temp)
		return (-1);
	temp2 = ft_strjoin(temp, string2);
	free(temp);
	if (!temp2)
		return (-1);
	perror(temp2);
	free(temp2);
	return (rv);
}

//	execute perror
int	ms_perror(char *perror_str, char *string, char *string2, int rv)
{
	char	*temp;
	char	*temp2;

	if (perror_str)
	{
		if (string)
		{
			temp = ft_strjoin(perror_str, ": ");
			if (!temp)
				return (-1);
			temp2 = ft_strjoin(temp, string);
			free(temp);
			if (!temp2)
				return (-1);
			if (string2)
				return (add_str(temp2, string2, rv));
			perror(temp2);
			free(temp2);
		}
		else
			perror(perror_str);
	}
	return (rv);
}
