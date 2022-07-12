/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/12 20:10:33 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 16:15:05 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_true(char c, char const *set)
{
	int	a;

	a = 0;
	while (set[a])
	{
		if (c == set[a])
			return (1);
		a++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		start;
	int		end;
	int		size;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && is_true(s1[start], set))
		start++;
	size = ft_strlen(s1) - 1;
	end = 0;
	while (size >= 0 && is_true(s1[size], set))
	{
		size--;
		end++;
	}
	new = ft_substr(s1, start, ((unsigned int)ft_strlen(s1) - start - end));
	return (new);
}
