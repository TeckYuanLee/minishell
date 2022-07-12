/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/11 16:02:27 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:30:37 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	unsigned int	slen;
	char			*ptr;
	int				a;

	slen = 0;
	while (src[slen])
		slen++;
	ptr = malloc(sizeof(*src) * (slen + 1));
	if (!ptr)
		return (NULL);
	a = 0;
	while (src[a])
	{
		ptr[a] = src[a];
		a++;
	}
	ptr[a] = '\0';
	return (ptr);
}
