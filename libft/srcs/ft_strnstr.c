/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 19:28:07 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:32:22 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	a;
	size_t	b;

	a = 0;
	if (needle[a] == '\0' || haystack == needle)
		return ((char *)haystack);
	while (haystack[a] && a < len)
	{
		b = 0;
		while (haystack[a + b] == needle[b] && a + b < len)
		{
			if (needle[b + 1] == '\0')
				return ((char *)haystack + a);
			b++;
		}
		a++;
	}
	return (0);
}
