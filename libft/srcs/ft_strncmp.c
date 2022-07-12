/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 17:19:06 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:32:07 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	a;

	a = 0;
	while (s1[a] && (s1[a] == s2[a]) && a + 1 < n)
		a++;
	if (n == 0)
		return (0);
	else
		return ((unsigned char)(s1[a]) - (unsigned char)(s2[a]));
}
