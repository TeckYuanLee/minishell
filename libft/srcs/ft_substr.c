/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 17:47:21 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:33:14 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	a;

	a = 0;
	if (!s)
		return (NULL);
	sub = malloc(sizeof(char) * len + 1);
	if (!sub)
		return (NULL);
	while (a < len && start < ft_strlen(s))
	{
		sub[a] = s[start + a];
		a++;
	}
	sub[a] = '\0';
	return (sub);
}
