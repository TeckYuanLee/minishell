/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_white.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 01:34:55 by telee             #+#    #+#             */
/*   Updated: 2022/08/17 01:34:55 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	inset(const char *set, int c)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static const char	*get_begin(char const *s, char const *set)
{
	while (*s)
	{
		if (inset(set, *s))
			s++;
		else
			break ;
	}
	return (s);
}

static int	get_endlen(char const *s, char *set, const size_t len)
{
	int		i;
	size_t	index;

	i = 0;
	index = len;
	while (index != 0)
	{
		if (inset(set, s[index - 1]))
		{
			index--;
			i++;
		}
		else
			break ;
	}
	free(set);
	return (i);
}

char	*ft_strtrim_white(char const *s)
{
	size_t		len;
	char		*str;
	char		*set;

	if (!s)
		return (NULL);
	set = ft_strdup("\t\n\v\f\r ");
	if (!set)
		return (NULL);
	s = get_begin(s, set);
	if (!*s)
	{
		free (set);
		return (ft_strdup(""));
	}
	len = ft_strlen(s);
	len -= get_endlen(s, set, len);
	str = malloc(len + 1);
	if (str)
	{
		ft_memcpy(str, s, len);
		str[len] = '\0';
		return (str);
	}
	return (NULL);
}
