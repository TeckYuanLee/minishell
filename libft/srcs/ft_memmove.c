/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 13:02:50 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:28:26 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				a;

	if (!dest && !src)
		return (0);
	d = dest;
	s = src;
	a = 0;
	if (s < d)
	{
		a += n;
		while (--a < n)
			d[a] = s[a];
	}
	else
	{
		while (a < n)
		{
			d[a] = s[a];
			a++;
		}
	}
	return (dest);
}
