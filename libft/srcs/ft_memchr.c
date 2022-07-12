/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/10 17:45:48 by telee             #+#    #+#             */
/*   Updated: 2021/05/21 13:45:20 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	a;

	a = 0;
	while (a < n)
	{
		if (((unsigned char *)s)[a] == (unsigned char)c)
			return ((void *)&s[a]);
		a++;
	}
	return (NULL);
}
