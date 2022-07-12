/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 18:07:05 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 17:12:13 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			a;
	unsigned char	*d;
	unsigned char	*s;

	if (!dest && !src)
		return (0);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	a = 0;
	while (a < n)
	{
		d[a] = s[a];
		a++;
	}
	return (dest);
}
