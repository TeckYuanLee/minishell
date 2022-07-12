/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 13:26:28 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 17:13:04 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				a;
	unsigned char	*str;

	a = 0;
	str = (unsigned char *)s;
	while (str[a])
		a++;
	if ((char)c == '\0')
		return ((char *)str + a);
	while (--a >= 0)
	{
		if (s[a] == (char)c)
			return ((char *)str + a);
	}
	return (0);
}
