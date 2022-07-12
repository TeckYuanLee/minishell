/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:44:18 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:28:41 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			a;
	unsigned char	*s;

	s = b;
	a = 0;
	while (a < len)
	{
		s[a] = (unsigned char)c;
		a++;
	}
	return (b);
}
