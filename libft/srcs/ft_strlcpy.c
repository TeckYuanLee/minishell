/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 20:01:56 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:31:20 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	if (!src && !dest)
		return (0);
	while (src[a])
		a++;
	if (size > 0)
	{
		b = 0;
		while (src[b] && b < size - 1)
		{
			dest[b] = src[b];
			b++;
		}
		dest[b] = '\0';
	}
	return (a);
}
