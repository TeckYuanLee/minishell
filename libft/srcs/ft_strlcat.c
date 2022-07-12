/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 12:02:41 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:31:06 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	a;
	size_t	b;
	size_t	len;
	char	*s;

	s = (char *)src;
	if (size > ft_strlen(dest))
		len = ft_strlen(dest) + ft_strlen(s);
	else
		len = size + ft_strlen(s);
	a = ft_strlen(dest);
	if (size > 0)
	{
		b = 0;
		while (s[b] && a < size - 1)
		{
			dest[a] = s[b];
			b++;
			a++;
		}
		dest[a] = '\0';
	}
	return (len);
}
