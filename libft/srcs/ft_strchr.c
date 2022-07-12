/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:03:51 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 17:12:25 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				a;
	unsigned char	*str;

	a = 0;
	str = (unsigned char *)s;
	while (str[a])
	{
		if (str[a] == (unsigned char)c)
			return ((char *)&str[a]);
		a++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&str[a]);
	return (0);
}
