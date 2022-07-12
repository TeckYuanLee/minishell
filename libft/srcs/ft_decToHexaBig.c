/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decToHexaBig.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:28:44 by telee             #+#    #+#             */
/*   Updated: 2022/05/28 08:29:27 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dectohexabig(size_t n)
{
	char		hexadecinum[40];
	static char	s[40];
	int			i;
	int			j;
	int			temp;

	i = 0;
	if (n == 0)
		return ("0");
	while (n != 0)
	{
		temp = 0;
		temp = n % 16;
		if (temp < 10)
			hexadecinum[i++] = temp + 48;
		else
			hexadecinum[i++] = temp + 55;
		n /= 16;
	}
	j = i - 1;
	i = 0;
	ft_bzero(s, 40);
	while (j >= 0)
		s[i++] = hexadecinum[j--];
	return (s);
}
