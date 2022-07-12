/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decToHexa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 08:26:30 by telee             #+#    #+#             */
/*   Updated: 2022/05/28 08:29:40 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dectohexa(size_t n)
{
	char		hexadecinum[40];
	static char	str[40];
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
			hexadecinum[i++] = temp + 87;
		n /= 16;
	}
	j = i - 1;
	i = 0;
	ft_bzero(str, 40);
	while (j >= 0)
		str[i++] = hexadecinum[j--];
	return (str);
}
