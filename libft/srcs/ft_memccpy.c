/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 18:56:16 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:27:19 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			a;

	a = 0;
	d = dest;
	s = (unsigned char *)src;
	while (*s && a < n)
	{
		d[a] = s[a];
		if (s[a] == (unsigned char)c)
			return (&d[a + 1]);
		a++;
	}
	return (NULL);
}
