/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 18:18:06 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 17:15:11 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	a;
	size_t	b;

	if (!s1 || !s2 || !(s1 && s2))
		return (0);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	new = malloc(sizeof(char) * (a + b + 1));
	if (!new)
		return (NULL);
	a = 0;
	b = 0;
	while (s1[a])
	{
		new[a] = s1[a];
		a++;
	}
	while (s2[b])
	{
		new[a + b] = s2[b];
		b++;
	}
	new[a + b] = '\0';
	return (new);
}
