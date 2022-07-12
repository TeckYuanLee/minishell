/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: telee <telee@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 09:37:31 by telee             #+#    #+#             */
/*   Updated: 2021/05/18 08:25:35 by telee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	no_of_digits(int n)
{
	long	a;
	long	b;

	b = n;
	a = 0;
	if (b < 0)
	{
		b *= -1;
		a++;
	}
	while (b >= 10)
	{
		b /= 10;
		a++;
	}
	a++;
	return (a);
}

char	*ft_itoa(int n)
{
	char	*ascii;
	int		a;
	long	b;

	a = no_of_digits(n);
	ascii = malloc(sizeof(char) * (a + 1));
	if (!ascii)
		return (NULL);
	b = n;
	if (b < 0)
	{
		n = -1;
		b *= -1;
	}
	ascii[a] = '\0';
	while (--a >= 0)
	{
		ascii[a] = b % 10 + 48;
		b /= 10;
	}
	if (n == -1)
		ascii[0] = '-';
	return (ascii);
}
